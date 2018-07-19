
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

#ifndef HAPTIC_HPP_INCLUDED
#define HAPTIC_HPP_INCLUDED

/**
*   @file Haptic.hpp
*   @brief The force feedback (Haptic) interface
*   @author Luxon Jean-Pierre(Gumichan01)
*
*/

#include <memory>
#include <cstdint>

struct _SDL_Joystick;
struct _SDL_GameController;
union SDL_HapticEffect;

namespace lx
{

namespace Device
{

struct Haptic_;
struct Haptic_common;
class Gamepad;

using Joystick = _SDL_Joystick;
using GameController = _SDL_GameController;
using HapticEffect = SDL_HapticEffect;


/**
*   @fn int numberOfHapticDevices() noexcept
*   Get the number of haptic systems
*   @return The number of haptic systems
*/
int numberOfHapticDevices() noexcept;
/**
*   @fn bool mouseIsHaptic() noexcept
*   Check if the current mouse has haptic feedback
*   @return TRUE if the mouse has haptic feedback, FALSE otherwise
*/
bool mouseIsHaptic() noexcept;


/**
*   @class Haptic
*   @brief The haptic device
*
*   This class describes the force feedback system related to a device.
*/
class Haptic
{
    friend class lx::Device::Gamepad;
    std::unique_ptr<Haptic_> m_himpl;

    Haptic( Haptic& h ) = delete;
    Haptic& operator =( Haptic& h ) = delete;

    // Used by Gamepad
    explicit Haptic( Joystick * joy ) noexcept;
    explicit Haptic( GameController * gc ) noexcept;

protected:

    std::unique_ptr<Haptic_common> _hcimpl;
    Haptic() noexcept;

public:

    /**
    *   @fn Haptic(int index) noexcept
    *   @param [in] index The index of the device to open
    */
    explicit Haptic( int index ) noexcept;

    /**
    *   @fn virtual bool isOpened() const noexcept
    *   Check if the haptic device is opened
    *   @return TRUE is the device is opened, FALSE otherwis
    */
    virtual bool isOpened() const noexcept;
    /**
    *   @fn virtual bool rumbleEffectInit() noexcept
    *   Initializes the haptic device for simple rumble playback
    *   @return TRUE on success, FALSE otherwise
    */
    virtual bool rumbleEffectInit() noexcept;
    /**
    *   @fn virtual void rumbleEffectPlay() noexcept
    *   Play the rumble effect with default values
    */
    virtual void rumbleEffectPlay() noexcept;
    /**
    *   @fn virtual void rumbleEffectPlay(float strength, uint32_t length)
    *
    *   Play the rumble effect
    *
    *   @param [in] strength Strength of the rumble to play as a float value
    *         (between 0.0 and 1.0)
    *   @param [in] length Length of the rumble to play in milliseconds
    */
    virtual void rumbleEffectPlay( float strength, uint32_t length ) noexcept;

    /**
    *   @fn virtual bool effectSupported(HapticEffect& effect) const
    *
    *   Check if an effect is supported by the current device
    *
    *   @param [in] effect Effect to check
    *   @return TRUE if the effect is supported. FALSE otherwise
    *
    *   @sa newEffect
    */
    virtual bool effectSupported( HapticEffect& effect ) const noexcept;
    /**
    *   @fn virtual int newEffect(HapticEffect& effect)
    *
    *   Add a new effect
    *
    *   @param [in] effect Properties of the effect to create
    *   @return The id of the effect on success or -1 on error.
    *
    *   @sa runEffect
    *   @sa stopEffect
    */
    virtual int newEffect( HapticEffect& effect ) noexcept;
    /**
    *   @fn virtual void runEffect(int effect_id, uint32_t iterations)
    *
    *   Play the effect
    *
    *   @param [in] effect_id Identifier of the haptic effect to run
    *   @param [in] iterations iterations Number of iterations to run the effect.
    *          Use SDL_HAPTIC_INFINITY for infinity.
    *
    *   @sa newEffect
    *   @sa stopEffect
    */
    virtual void runEffect( int effect_id, uint32_t iterations ) noexcept;
    /**
    *   @fn virtual void stopEffect(int effect_id)
    *   Stop the effect
    *   @param [in] effect_id Identifier of the haptic effect to stop
    *
    *   @sa newEffect
    *   @sa runEffect
    */
    virtual void stopEffect( int effect_id ) noexcept;

    /**
    *   @fn virtual int numberOfEffects() const
    *   Get the number of playable effects
    *   @return The number of loaded effects
    *
    *   @sa newEffect
    *   @sa runEffect
    *   @sa stopEffect
    */
    virtual int numberOfEffects() const noexcept;

    virtual ~Haptic();
};

/**
*   @class MouseHaptic
*   @brief The mouse haptic device
*   This class describes the force feedback system related to the mouse.
*/
class MouseHaptic final : public Haptic
{
    MouseHaptic( Haptic& h ) = delete;
    MouseHaptic& operator =( MouseHaptic& h ) = delete;

public:

    MouseHaptic() noexcept;
    virtual bool isOpened() const noexcept override;
    ~MouseHaptic() = default;
};

}   // Device

}   // lx

#endif // HAPTIC_HPP_INCLUDED
