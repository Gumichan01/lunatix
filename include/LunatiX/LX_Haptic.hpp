#ifndef LX_HAPTIC_HPP_INCLUDED
#define LX_HAPTIC_HPP_INCLUDED


/*
*    Copyright (C) 2016 Luxon Jean-Pierre
*    gumichan01.olympe.in
*
*    LunatiX is a free, SDL2-based library.
*    It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*    Luxon Jean-Pierre (Gumichan01)
*    luxon.jean.pierre@gmail.com
*/

/**
*    @file LX_Haptic.hpp
*    @brief The library that deals force feedback
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.8
*
*/

#include <SDL2/SDL_haptic.h>
#include <SDL2/SDL_gamecontroller.h>

namespace LX_Device
{

class LX_Haptic;

/**
*   @fn int numberOfHapticDevices(void)
*
*   Get the number of haptic systems
*
*   @return The number of haptic systems
*/
int numberOfHapticDevices(void);
/**
*   @fn bool mouseIsHaptic
*
*   Check if the current mouse has haptic feedback
*
*   @return TRUE if the mouse has haptic feedback, FALSE otherwise
*/
bool mouseIsHaptic(void);
/**
*   @fn LX_Haptic * getMouseHaptic(void)
*
*   Get the haptic system of the mouse
*
*   @return The haptic system of mouse if it has haptic feedback, NULL otherwise
*/
LX_Haptic * getMouseHaptic(void);

/**
*   @class LX_Haptic
*   @brief The haptic device
*
*   This class describes the force feedback system related to a device.
*/
class LX_Haptic
{
    SDL_Haptic *_haptic;
    int _instanceID;

    LX_Haptic(LX_Haptic& h);
    LX_Haptic& operator =(LX_Haptic& h);

public :

    /// Default constructor, useful for creating a haptic device from the mouse
    LX_Haptic();

    /**
    *   @fn LX_Haptic(int index)
    *   @brief Constructor
    *
    *   Create the instance of the haptic system using the index
    *
    *   @param [in] index The index of the device to open
    *
    */
    explicit LX_Haptic(int index);
    /**
    *   @fn LX_Haptic(SDL_Joystick *joy)
    *   @brief Constructor
    *
    *   Create the instance of the haptic device using the joystick
    *
    *   @param [in] joy The joystick to open the device from
    *
    */
    explicit LX_Haptic(SDL_Joystick *joy);
    /**
    *   @fn LX_Haptic(SDL_GameController *gc)
    *   @brief Constructor
    *
    *   Create the instance of the haptic device using the game controller
    *
    *   @param [in] gc The game controller to open the device from
    *
    */
    explicit LX_Haptic(SDL_GameController *gc);

    /**
    *   @fn LX_Haptic& operator =(SDL_Haptic& haptic)
    *
    *   Set the haptic device
    *
    *   @param [in] haptic The SDL haptic device
    *   @return The current instance of LX_Haptic
    *
    */
    LX_Haptic& operator =(SDL_Haptic& haptic);

    /**
    *   @fn bool isOpened(void)
    *
    *   Check if the haptic device is opened
    *
    *   @return TRUE is the device is opened, FALSE otherwise
    *
    */
    bool isOpened(void);
    /**
    *   @fn bool rumbleEffectInit(void)
    *
    *   Initializes the haptic device for simple rumble playback
    *
    *   @return TRUE on success, FALSE otherwise
    *
    */
    bool rumbleEffectInit(void);
    /**
    *   @fn void rumbleEffectPlay(void)
    *
    *   Play the rumble effect with default values
    *
    */
    void rumbleEffectPlay(void);
    /**
    *   @fn void rumbleEffectPlay(float strength, Uint32 length)
    *
    *   Play the rumble effect
    *
    *   @param [in] strength Strength of the rumble to play as a float value
    *          (between 0.0 and 1.0)
    *   @param [in] length Length of the rumble to play in milliseconds
    *
    */
    void rumbleEffectPlay(float strength, Uint32 length);

    /**
    *   @fn bool effectSupported(SDL_HapticEffect& effect)
    *
    *   Check if an effect is supported by the current device
    *
    *   @param [in] effect Effect to check
    *
    *   @return TRUE if the effect is supported. FALSE otherwise
    *
    *   @sa newEffect
    */
    bool effectSupported(SDL_HapticEffect& effect);
    /**
    *   @fn int newEffect(SDL_HapticEffect& effect)
    *
    *   Add a new effect
    *
    *   @param [in] effect Properties of the effect to create
    *
    *   @return The id of the effect on success or -1 on error.
    *
    *   @sa runEffect
    *   @sa stopEffect
    */
    int newEffect(SDL_HapticEffect& effect);
    /**
    *   @fn void runEffect(int effect_id, Uint32 iterations)
    *
    *   Play the effect
    *
    *   @param [in] effect_id Identifier of the haptic effect to run
    *   @param [in] iterations iterations Number of iterations to run the effect.
    *           Use SDL_HAPTIC_INFINITY for infinity.
    *
    *   @sa newEffect
    *   @sa stopEffect
    */
    void runEffect(int effect_id, Uint32 iterations);
    /**
    *   @fn void stopEffect(int effect_id)
    *
    *   Stop the effect
    *
    *   @param [in] effect_id Identifier of the haptic effect to stop
    *
    *   @sa newEffect
    *   @sa runEffect
    */
    void stopEffect(int effect_id);

    /**
    *   @fn int numberOfEffects(void)
    *
    *   Get the number of playable effects
    *
    *   @return The number of loaded effects
    *
    *   @sa newEffect
    *   @sa runEffect
    *   @sa stopEffect
    */
    int numberOfEffects(void);

    /// Destructor
    ~LX_Haptic();
};

};

#endif // LX_HAPTIC_HPP_INCLUDED
