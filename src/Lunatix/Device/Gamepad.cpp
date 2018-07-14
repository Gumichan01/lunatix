
/*
*   Copyright © 2018 Luxon Jean-Pierre
*   https://gumichan01.github.io/
*
*   LunatiX is a free, SDL2-based library.
*   It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*   luxon.jean.pierre@gmail.com
*/

/**
*   @file Gamepad.cpp
*   @brief The gamepad implementation
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*/

#include <Lunatix/Gamepad.hpp>
#include <Lunatix/Haptic.hpp>
#include <Lunatix/Device.hpp>
#include <Lunatix/Error.hpp>
#include <Lunatix/Log.hpp>

#include <SDL2/SDL_gamecontroller.h>
#include <SDL2/SDL_haptic.h>

#include <stdexcept>
#include <sstream>
#include <cstring>


namespace lx
{

namespace Device
{

#ifdef __WIN32__
const char SEP = '\\';
#else
const char SEP = '/';
#endif // __WIN32__

#define __FILENAME__ \
(strrchr(__FILE__, SEP) ? strrchr(__FILE__, SEP) + 1 : __FILE__)

namespace
{

const char * nameOf_( SDL_Joystick * joy ) noexcept
{
    return SDL_JoystickName( joy );
}

const char * nameOf_( SDL_GameController * controller ) noexcept
{
    return SDL_GameControllerName( controller );
}

SDL_JoystickPowerLevel powerLevelOf_( SDL_Joystick * joy ) noexcept
{
    return SDL_JoystickCurrentPowerLevel( joy );
}

UTF8string batteryLevelToString( BatteryLevel bl )
{
    UTF8string battery_level_str;

    switch ( bl )
    {
    case BatteryLevel::UNKNOWN:
        battery_level_str = "Unknown";
        break;
    case BatteryLevel::EMPTY:
        battery_level_str = "Empty";
        break;
    case BatteryLevel::LOW:
        battery_level_str = "Low";
        break;
    case BatteryLevel::MEDIUM:
        battery_level_str = "Medium";
        break;
    case BatteryLevel::FULL:
        battery_level_str = "Full";
        break;
    case BatteryLevel::WIRED:
        battery_level_str = "Wired";
        break;
    case BatteryLevel::MAX:
        battery_level_str = "Maximum";
        break;
    }

    return battery_level_str;
}

}


UTF8string gamepadToString( GamepadInfo& info ) noexcept
{
    const int GUID_SIZE = 33;       // Size of the data in SDL_JoystickGUID
    char guid[GUID_SIZE] = {'\0'};
    SDL_JoystickGetGUIDString( info.uid, guid, GUID_SIZE );

    std::ostringstream stream;
    stream << "\n ==== Gamepad Information ==== "
           << "\nGamepad - ID: "                << info.id
           << "\nGamepad - UID: "               << guid
           << "\nGamepad - Name: "              << info.name
           << "\nGamepad - Is haptic: "         << info.is_haptic
           << "\nGamepad - Battery level: "     << batteryLevelToString( info.battery )
           << "\nGamepad - Number of Axes: "    << info.nb_axis
           << "\nGamepad - Number of Balls: "   << info.nb_balls
           << "\nGamepad - Number of Buttons: " << info.nb_buttons
           << "\nGamepad - Number of Hats: "    << info.nb_hats << "\n";

    return UTF8string( stream.str() );
}


// Private implementation
struct Gamepad_ final
{
    SDL_GameController * gc = nullptr;
    SDL_Joystick * joy = nullptr;
    std::unique_ptr<Haptic> haptic = nullptr;
    bool _closed = true;

private:

    Gamepad_( const Gamepad_& g ) = delete;
    Gamepad_& operator =( const Gamepad_& ) = delete;

    bool lx_stat_( SDL_Joystick * joystick, GamepadInfo& info ) const;
    bool gstat_( SDL_Joystick * joystick, SDL_GameController * gamepad, GamepadInfo& info ) const;
    bool statGamepad_( SDL_Joystick * joystick, GamepadInfo& info ) const;
    bool statGamepad_( SDL_GameController * gp, GamepadInfo& info ) const;

public:

    Gamepad_() = default;
    void close() noexcept;

    bool isConnected() const noexcept
    {
        if ( gc != nullptr )
            return SDL_GameControllerGetAttached( gc ) == SDL_TRUE;
        else
            return SDL_JoystickGetAttached( joy ) == SDL_TRUE;
    }

    bool isHaptic() const
    {
        return haptic != nullptr && haptic->isOpened();
    }

    int32_t getID() const
    {
        if ( gc != nullptr )
            return SDL_JoystickInstanceID( SDL_GameControllerGetJoystick( gc ) );
        else
            return SDL_JoystickInstanceID( joy );
    }

    Haptic * getHaptic() const
    {
        return haptic.get();
    }

    BatteryLevel getBatteryLevel() const noexcept
    {
        if ( gc != nullptr )
            return static_cast<BatteryLevel>( powerLevelOf_( SDL_GameControllerGetJoystick( gc ) ) );
        else
            return static_cast<BatteryLevel>( powerLevelOf_( joy ) );
    }

    const char * getName() const noexcept
    {
        if ( gc != nullptr )
            return nameOf_( gc );
        else
            return nameOf_( joy );
    }

    bool stat( GamepadInfo& info ) const
    {
        bool res;

        if ( gc != nullptr )
            res = statGamepad_( gc, info );
        else
            res = statGamepad_( joy, info );

        if ( !res )
            lx::setError( std::string( "Gamepad::stat: " ) + lx::getError() );

        return res;
    }

    UTF8string toString() const noexcept
    {
        GamepadInfo gi;

        try
        {
            if ( stat( gi ) )
                return gamepadToString( gi );
        }
        catch ( ... ) {}

        return UTF8string( "Unknown gamepad" );
    }

    ~Gamepad_()
    {
        haptic.reset();
    }
};


// Private functions

void Gamepad_::close() noexcept
{
    haptic.reset();

    if ( !_closed )
    {
        if ( gc != nullptr )
        {
            SDL_GameControllerClose( gc );
            gc = nullptr;
        }
        else if ( joy != nullptr )
        {
            SDL_JoystickClose( joy );
            joy = nullptr;
        }
        _closed = true;
    }
}

bool Gamepad_::lx_stat_( SDL_Joystick * joystick, GamepadInfo& info ) const
{
    if ( joystick == nullptr )
    {
        lx::setError( "Invalid joystick\n" );
        return false;
    }

    // Get information
    info.id = SDL_JoystickInstanceID( joystick );
    info.uid = SDL_JoystickGetGUID( joystick );
    info.is_haptic = isHaptic() ? "Yes" : "No";
    info.battery = getBatteryLevel();
    info.nb_axis = SDL_JoystickNumAxes( joystick );
    info.nb_balls = SDL_JoystickNumBalls( joystick );
    info.nb_buttons = SDL_JoystickNumButtons( joystick );
    info.nb_hats = SDL_JoystickNumHats( joystick );

    if ( info.id == -1 || info.nb_axis == -1 || info.nb_balls == -1
            || info.nb_buttons == -1 || info.nb_hats == -1 )
    {
        lx::setError( "Cannot get information\n" );
        return false;
    }

    return true;
}


bool Gamepad_::gstat_( SDL_Joystick * joystick, SDL_GameController * gamepad,
                       GamepadInfo& info ) const
{
    if ( joystick != nullptr )
    {
        info.name = nameOf_( joystick );
        return lx_stat_( joystick, info );
    }
    else if ( gamepad != nullptr )
    {
        info.name = nameOf_( gamepad );
        return lx_stat_( SDL_GameControllerGetJoystick( gamepad ), info );
    }
    else
    {
        lx::Log::logCritical( lx::Log::APPLICATION,
                              "%s:%d - Internal error: Invalid Gamepad object",
                              __FILENAME__, __LINE__ );
        throw std::runtime_error( "Internal error - Bad Gamepad" );
    }
}


bool Gamepad_::statGamepad_( SDL_Joystick * joystick, GamepadInfo& info ) const
{
    return gstat_( joystick, nullptr, info );
}


bool Gamepad_::statGamepad_( SDL_GameController * gamepad, GamepadInfo& info ) const
{
    return gstat_( nullptr, gamepad, info );
}


/* Gamepad - public class */

Gamepad::Gamepad() noexcept: m_gpimpl( new Gamepad_() ) {}


bool Gamepad::open( int index ) noexcept
{
    if ( !m_gpimpl->_closed )
    {
        std::string s = getName();

        lx::Log::logError( lx::Log::SYSTEM,
                           "Gamepad opened and connected to %s", s.c_str() );
        lx::setError( "Instance of gamepad already connected to another device" );
        return false;
    }

    if ( index < numberOfDevices() && SDL_IsGameController( index ) )
        m_gpimpl->gc = SDL_GameControllerOpen( index );

    if ( m_gpimpl->gc == nullptr )
    {
        m_gpimpl->joy = SDL_JoystickOpen( index );

        if ( SDL_JoystickIsHaptic( m_gpimpl->joy ) == 1 )
            m_gpimpl->haptic.reset( new Haptic( m_gpimpl->joy ) );
    }
    else
    {
        if ( SDL_JoystickIsHaptic( SDL_GameControllerGetJoystick( m_gpimpl->gc ) ) == 1 )
            m_gpimpl->haptic.reset( new Haptic( m_gpimpl->gc ) );
    }

    m_gpimpl->_closed = false;
    return true;
}


void Gamepad::close() noexcept
{
    m_gpimpl->close();
}


bool Gamepad::isConnected() const noexcept
{
    return m_gpimpl->isConnected();
}


bool Gamepad::isHaptic() const noexcept
{
    return m_gpimpl->isHaptic();
}


int32_t Gamepad::getID() const noexcept
{
    return m_gpimpl->getID();
}


Haptic * Gamepad::getHaptic() const noexcept
{
    return m_gpimpl->getHaptic();
}


BatteryLevel Gamepad::getBatteryLevel() noexcept
{
    return m_gpimpl->getBatteryLevel();
}


const char * Gamepad::getName() const noexcept
{
    return m_gpimpl->getName();
}


bool Gamepad::stat( GamepadInfo& info ) const noexcept
{
    return m_gpimpl->stat( info );
}


UTF8string Gamepad::toString() const noexcept
{
    return m_gpimpl->toString();
}

Gamepad::~Gamepad()
{
    m_gpimpl.reset();
}

}   // Device

}   // lx
