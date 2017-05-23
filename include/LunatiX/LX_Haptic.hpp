
/*
*   Copyright © 2017 Luxon Jean-Pierre
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
*   @version 0.10
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
*   @fn int numberOfHapticDevices()
*   Get the number of haptic systems
*   @return The number of haptic systems
*/
int numberOfHapticDevices();
/**
*   @fn bool mouseIsHaptic
*   Check if the current mouse has haptic feedback
*   @return TRUE if the mouse has haptic feedback, FALSE otherwise
*/
bool mouseIsHaptic();


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

    LX_Haptic(LX_Haptic& h);
    LX_Haptic& operator =(LX_Haptic& h);

    // Used by LX_Gamepad
    explicit LX_Haptic(LX_Joystick *joy);
    explicit LX_Haptic(LX_GameController *gc);

protected:

    std::unique_ptr<LX_Haptic_common> _hcimpl;

    LX_Haptic();

public:

    /**
    *   @fn LX_Haptic(int index)
    *   @brief Constructor
    *
    *   Create the instance of the haptic system using the index
    *   @param [in] index The index of the device to open
    */
    explicit LX_Haptic(int index);

    /**
    *   @fn virtual bool isOpened() const
    *   Check if the haptic device is opened
    *   @return TRUE is the device is opened, FALSE otherwis
    */
    virtual bool isOpened() const;
    /**
    *   @fn virtual bool rumbleEffectInit()
    *   Initializes the haptic device for simple rumble playback
    *   @return TRUE on success, FALSE otherwise
    */
    virtual bool rumbleEffectInit();
    /**
    *   @fn virtual void rumbleEffectPlay()
    *   Play the rumble effect with default values
    */
    virtual void rumbleEffectPlay();
    /**
    *   @fn virtual void rumbleEffectPlay(float strength, uint32_t length)
    *
    *   Play the rumble effect
    *
    *   @param [in] strength Strength of the rumble to play as a float value
    *         (between 0.0 and 1.0)
    *   @param [in] length Length of the rumble to play in milliseconds
    */
    virtual void rumbleEffectPlay(float strength, uint32_t length);

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
    virtual bool effectSupported(LX_HapticEffect& effect) const;
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
    virtual int newEffect(LX_HapticEffect& effect);
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
    virtual void runEffect(int effect_id, uint32_t iterations);
    /**
    *   @fn virtual void stopEffect(int effect_id)
    *   Stop the effect
    *   @param [in] effect_id Identifier of the haptic effect to stop
    *
    *   @sa newEffect
    *   @sa runEffect
    */
    virtual void stopEffect(int effect_id);

    /**
    *   @fn virtual int numberOfEffects() const
    *   Get the number of playable effects
    *   @return The number of loaded effects
    *
    *   @sa newEffect
    *   @sa runEffect
    *   @sa stopEffect
    */
    virtual int numberOfEffects() const;

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
    LX_MouseHaptic(LX_Haptic& h);
    LX_MouseHaptic& operator =(LX_MouseHaptic& h);

public:

    /// Constructor
    LX_MouseHaptic();
    virtual bool isOpened() const;
    /// Desstructor
    ~LX_MouseHaptic();
};


}

#endif // LX_HAPTIC_HPP_INCLUDED
