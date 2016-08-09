
/*
*	Copyright (C) 2016 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX Engine is a SDL2-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_Haptic.cpp
*	@brief The Haptic system implementation
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.8
*
*/

#include <LunatiX/LX_Haptic.hpp>


namespace LX_Device
{


/**
*   @fn int numberOfHapticDevices(void)
*
*   Get the number of haptic system
*
*   @return The number of haptic system
*
*/
int numberOfHapticDevices(void)
{
    return SDL_NumHaptics();
}


/**
*   @fn LX_Haptic::LX_Haptic(int index)
*
*   Create the instance of the haptic system using the index
*
*   @param index The index of the device to open
*
*/
LX_Haptic::LX_Haptic(int index)
    : _haptic(SDL_HapticOpen(index)), _instanceID(index)
{
    // Empty
}


/**
*   @fn LX_Haptic::LX_Haptic(SDL_Joystick *joy)
*
*   Create the instance of the haptic device using the joystick
*
*   @param joy The joystick to open the device from
*
*/
LX_Haptic::LX_Haptic(SDL_Joystick *joy)
    : _haptic(SDL_HapticOpenFromJoystick(joy)),
      _instanceID(SDL_JoystickInstanceID(joy))
{
    // Empty
}


/**
*   @fn LX_Haptic::LX_Haptic(SDL_GameController *gc)
*
*   Create the instance of the haptic device using the game controller
*
*   @param gc The game controller to open the device from
*
*/
LX_Haptic::LX_Haptic(SDL_GameController *gc)
    : LX_Haptic(SDL_GameControllerGetJoystick(gc))
{
    // Empty
}


LX_Haptic::~LX_Haptic()
{
    SDL_HapticClose(_haptic);
}


/**
*   @fn bool LX_Haptic::isOpened(void)
*
*   Check if the haptic device is opened
*
*   @return TRUE is the device is opened, FALSE otherwise
*
*/
bool LX_Haptic::isOpened(void)
{
    return SDL_HapticOpened(_instanceID) == 1;
}


/**
*   @fn bool LX_Haptic::rumbleEffectInit(void)
*
*   Initializes the haptic device for simple rumble playback
*
*   @return TRUE on success, FALSE otherwise
*
*/
bool LX_Haptic::rumbleEffectInit(void)
{
    if(SDL_HapticRumbleSupported(_haptic) == SDL_TRUE)
        return SDL_HapticRumbleInit(_haptic) == 0;

    return false;
}


/**
*   @fn void LX_Haptic::rumbleEffectPlay(void)
*
*   Play the rumble effect with default values
*
*/
void LX_Haptic::rumbleEffectPlay(void)
{
    rumbleEffectPlay(1,100);
}


/**
*   @fn void LX_Haptic::rumbleEffectPlay(float strength, Uint32 length)
*
*   Play the rumble effect
*
*   @param strength Strength of the rumble to play as a float value
*          (between 0.0 and 1.0)
*   @param length Length of the rumble to play in milliseconds
*
*/
void LX_Haptic::rumbleEffectPlay(float strength, Uint32 length)
{
    if(strength < 0.0f)
        strength = 0.0f;
    else if(strength > 1.0f)
        strength = 1.0f;

    SDL_HapticRumblePlay(_haptic,strength,length);
}


/**
*   @fn int LX_Haptic::newEffect(SDL_HapticEffect& effect)
*
*   Add a new effect
*
*   @param effect Properties of the effect to create
*
*   @return The id of the effect on success or -1 on error.
*
*   @sa runEffect
*   @sa stopEffect
*/
int LX_Haptic::newEffect(SDL_HapticEffect& effect)
{
    return SDL_HapticNewEffect(_haptic,&effect);
}


/**
*   @fn void LX_Haptic::runEffect(int effect_id, Uint32 iterations)
*
*   Play the effect
*
*   @param effect_id Identifier of the haptic effect to run
*   @param iterations iterations Number of iterations to run the effect. Use
*         SDL_HAPTIC_INFINITY for infinity.
*
*   @sa newEffect
*   @sa stopEffect
*/
void LX_Haptic::runEffect(int effect_id, Uint32 iterations)
{
    SDL_HapticRunEffect(_haptic,effect_id,iterations);
}


/**
*   @fn void LX_Haptic::stopEffect(int effect_id)
*
*   Stop the effect
*
*   @param effect_id Identifier of the haptic effect to stop
*
*   @sa newEffect
*   @sa runEffect
*/
void LX_Haptic::stopEffect(int effect_id)
{
    SDL_HapticStopEffect(_haptic,effect_id);
}


/**
*   @fn int LX_Haptic::numberOfEffects(void)
*
*   Get the number of playable effects
*
*   @return The number of loaded effects
*
*   @sa newEffect
*   @sa runEffect
*   @sa stopEffect
*/
int LX_Haptic::numberOfEffects(void)
{
    return SDL_HapticNumEffects(_haptic);
}

};
