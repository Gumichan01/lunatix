
/*
*    Copyright (C) 2016 Luxon Jean-Pierre
*    https://gumichan01.github.io/
*
*    LunatiX is a free, SDL2-based library.
*    It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*    Luxon Jean-Pierre (Gumichan01)
*    luxon.jean.pierre@gmail.com
*/

/**
*    @file LX_Gamepad.cpp
*    @brief The gamepad implementation
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.9
*/

#include <LunatiX/LX_Gamepad.hpp>
#include <LunatiX/LX_Haptic.hpp>
#include <LunatiX/LX_Device.hpp>
#include <LunatiX/LX_Error.hpp>
#include <LunatiX/LX_Log.hpp>

#include <SDL2/SDL_gamecontroller.h>
#include <SDL2/SDL_haptic.h>

#include <stdexcept>
#include <cstring>

#define __FILENAME__ (strrchr(__FILE__, LX_SEP) ? strrchr(__FILE__, LX_SEP) + 1 : __FILE__)

namespace LX_Device
{

#ifdef __WIN32__
const char LX_SEP = '\\';
#else
const char LX_SEP = '/';
#endif // __WIN32__

namespace
{
const char * nameOf_(SDL_Joystick * joy)
{
    return SDL_JoystickName(joy);
}


const char * nameOf_(SDL_GameController * controller)
{
    return SDL_GameControllerName(controller);
}
};


struct LX_Gamepad_
{
    SDL_GameController *_gc;
    SDL_Joystick *_joy;
    std::unique_ptr<LX_Haptic> _haptic;
    bool _closed;

private:

    bool lx_stat_(SDL_Joystick * joy, LX_GamepadInfo& info) const;
    bool gstat_(SDL_Joystick * joy, SDL_GameController * gc, LX_GamepadInfo& info) const;
    bool statGamepad_(SDL_Joystick * joy, LX_GamepadInfo& info) const;
    bool statGamepad_(SDL_GameController * gp, LX_GamepadInfo& info) const;

public:

    LX_Gamepad_(): _gc(nullptr),_joy(nullptr),_haptic(nullptr),_closed(true) {}

    bool isConnected() const
    {
        if(_gc != nullptr)
            return SDL_GameControllerGetAttached(_gc) == SDL_TRUE;
        else
            return SDL_JoystickGetAttached(_joy) == SDL_TRUE;
    }

    bool isHaptic() const
    {
        return _haptic != nullptr && _haptic->isOpened();
    }

    int32_t getID() const
    {
        if(_gc != nullptr)
            return SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(_gc));
        else
            return SDL_JoystickInstanceID(_joy);
    }

    LX_Haptic * getHaptic() const
    {
        return _haptic.get();
    }

    const char * getName() const
    {
        if(_gc != nullptr)
            return nameOf_(_gc);
        else
            return nameOf_(_joy);
    }

    bool stat(LX_GamepadInfo& info) const
    {
        bool res;

        if(_gc != nullptr)
            res = statGamepad_(_gc,info);
        else
            res = statGamepad_(_joy,info);

        if(!res)
            LX_SetError(UTF8string(std::string("LX_Gamepad::stat: ") + LX_GetError()));

        return res;
    }

    UTF8string toString() const
    {
        LX_GamepadInfo gi;

        if(stat(gi))
            return gamepadToString(gi);

        return UTF8string("Unknown gamepad");
    }

    ~LX_Gamepad_() = default;
};


// Private functions
bool LX_Gamepad_::lx_stat_(SDL_Joystick * joy, LX_GamepadInfo& info) const
{
    if(joy == nullptr)
    {
        LX_SetError("Invalid joystick\n");
        return false;
    }

    // Get information
    info.id = SDL_JoystickInstanceID(joy);
    info.uid = SDL_JoystickGetGUID(joy);
    info.is_haptic = isHaptic() ? "Yes" : "No";
    info.nb_axis = SDL_JoystickNumAxes(joy);
    info.nb_balls = SDL_JoystickNumBalls(joy);
    info.nb_buttons = SDL_JoystickNumButtons(joy);
    info.nb_hats = SDL_JoystickNumHats(joy);

    if(info.id == -1 || info.nb_axis == -1 || info.nb_balls == -1
            || info.nb_buttons == -1 || info.nb_hats == -1)
    {
        LX_SetError("Cannot get information\n");
        return false;
    }

    return true;
}


bool LX_Gamepad_::gstat_(SDL_Joystick * joy, SDL_GameController * gc,
                         LX_GamepadInfo& info) const
{
    if(joy != nullptr)
    {
        info.name = nameOf_(joy);
        return lx_stat_(joy,info);
    }
    else if(gc != nullptr)
    {
        info.name = nameOf_(gc);
        return lx_stat_(SDL_GameControllerGetJoystick(gc),info);
    }
    else
    {
        LX_Log::logCritical(LX_Log::LX_LOG_APPLICATION,
                            "%s:%d - Internal error: Invalid LX_Gamepad object",
                            __FILENAME__,__LINE__);
        throw std::runtime_error("Internal error - Bad LX_Gamepad");
    }
}


bool LX_Gamepad_::statGamepad_(SDL_Joystick * joy, LX_GamepadInfo& info) const
{
    return gstat_(joy,nullptr,info);
}


bool LX_Gamepad_::statGamepad_(SDL_GameController * gc, LX_GamepadInfo& info) const
{
    return gstat_(nullptr,gc,info);
}


LX_Gamepad::LX_Gamepad(): _gpimpl(new LX_Gamepad_()) {}


LX_Gamepad::~LX_Gamepad()
{
    _gpimpl.reset();
}


bool LX_Gamepad::open(int index)
{
    if(!_gpimpl->_closed)
    {
        std::string s = getName();

        LX_Log::logError(LX_Log::LX_LOG_SYSTEM,
                            "Gamepad opened and connected to %s", s.c_str());
        LX_SetError("Instance of gamepad already connected to another device");
        return false;
    }

    if(index < numberOfDevices() && SDL_IsGameController(index))
        _gpimpl->_gc = SDL_GameControllerOpen(index);

    if(_gpimpl->_gc == nullptr)
    {
        _gpimpl->_joy = SDL_JoystickOpen(index);
        if(SDL_JoystickIsHaptic(_gpimpl->_joy) == 1)
            _gpimpl->_haptic.reset(new LX_Haptic(_gpimpl->_joy));
    }
    else
    {
        if(SDL_JoystickIsHaptic(SDL_GameControllerGetJoystick(_gpimpl->_gc)) == 1)
            _gpimpl->_haptic.reset(new LX_Haptic(_gpimpl->_gc));
    }
    _gpimpl->_closed = false;
    return true;
}


void LX_Gamepad::close()
{
    _gpimpl->_haptic.reset();

    if(!_gpimpl->_closed)
    {
        if(_gpimpl->_gc != nullptr)
        {
            SDL_GameControllerClose(_gpimpl->_gc);
            _gpimpl->_gc = nullptr;
        }
        else if(_gpimpl->_joy != nullptr)
        {
            SDL_JoystickClose(_gpimpl->_joy);
            _gpimpl->_joy = nullptr;
        }
        _gpimpl->_closed = true;
    }
}


bool LX_Gamepad::isConnected() const
{
    return _gpimpl->isConnected();
}


bool LX_Gamepad::isHaptic() const
{
    return _gpimpl->isHaptic();
}


int32_t LX_Gamepad::getID() const
{
    return _gpimpl->getID();
}


LX_Haptic * LX_Gamepad::getHaptic() const
{
    return _gpimpl->getHaptic();
}


const char * LX_Gamepad::getName() const
{
    return _gpimpl->getName();
}


bool LX_Gamepad::stat(LX_GamepadInfo& info) const
{
    return _gpimpl->stat(info);
}


UTF8string LX_Gamepad::toString() const
{
    return _gpimpl->toString();
}

};
