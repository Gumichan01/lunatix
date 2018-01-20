
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

#ifndef LX_HAPTIC_HPP_INCLUDED
#define LX_HAPTIC_HPP_INCLUDED

/**
*   @file LX_Haptic.hpp
*   @brief The force feedback (Haptic) interface
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.12
*/

#include <memory>
#include <cstdint>

struct _SDL_Joystick;
struct _SDL_GameController;
union SDL_HapticEffect;

namespace LX_Device
{

struct LX_Haptic_;
struct LX_Haptic_common;
class LX_Gamepad;

using LX_Joystick = _SDL_Joystick;
using LX_GameController = _SDL_GameController;
using LX_HapticEffect = SDL_HapticEffect;


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
*   @class LX_Haptic
*   @brief The haptic device
*
*   This class describes the force feedback system related to a device.
*/
class LX_Haptic
{
    friend class LX_Device::LX_Gamepad;
    std::unique_ptr<LX_Haptic_> _himpl;

    LX_Haptic(LX_Haptic& h) = delete;
    LX_Haptic& operator =(LX_Haptic& h) = delete;

    // Used by LX_Gamepad
    explicit LX_Haptic(LX_Joystick *joy) noexcept;
    explicit LX_Haptic(LX_GameController *gc) noexcept;

protected:

    std::unique_ptr<LX_Haptic_common> _hcimpl;
    LX_Haptic() noexcept;

public:

    /**
    *   @fn LX_Haptic(int index) noexcept
    *   @param [in] index The index of the device to open
    */
    explicit LX_Haptic(int index) noexcept;

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
    virtual void rumbleEffectPlay(float strength, uint32_t length) noexcept;

    /**
    *   @fn virtual bool effectSupported(LX_HapticEffect& effect) const
    *
    *   Check if an effect is supported by the current device
    *
    *   @param [in] effect Effect to check
    *   @return TRUE if the effect is supported. FALSE otherwise
    *
    *   @sa newEffect
    */
    virtual bool effectSupported(LX_HapticEffect& effect) const noexcept;
    /**
    *   @fn virtual int newEffect(LX_HapticEffect& effect)
    *
    *   Add a new effect
    *
    *   @param [in] effect Properties of the effect to create
    *   @return The id of the effect on success or -1 on error.
    *
    *   @sa runEffect
    *   @sa stopEffect
    */
    virtual int newEffect(LX_HapticEffect& effect) noexcept;
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
    virtual void runEffect(int effect_id, uint32_t iterations) noexcept;
    /**
    *   @fn virtual void stopEffect(int effect_id)
    *   Stop the effect
    *   @param [in] effect_id Identifier of the haptic effect to stop
    *
    *   @sa newEffect
    *   @sa runEffect
    */
    virtual void stopEffect(int effect_id) noexcept;

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

    /// Destructor
    virtual ~LX_Haptic();
};

/**
*   @class LX_MouseHaptic
*   @brief The mouse haptic device
*   This class describes the force feedback system related to the mouse.
*/
class LX_MouseHaptic: public LX_Haptic
{
    LX_MouseHaptic(LX_Haptic& h) = delete;
    LX_MouseHaptic& operator =(LX_MouseHaptic& h) = delete;

public:

    /// Constructor
    LX_MouseHaptic() noexcept;
    virtual bool isOpened() const noexcept;
    /// Desstructor
    ~LX_MouseHaptic();
};

}

#endif // LX_HAPTIC_HPP_INCLUDED
