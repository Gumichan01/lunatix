#ifndef LX_HAPTIC_HPP_INCLUDED
#define LX_HAPTIC_HPP_INCLUDED


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
*	@file LX_Haptic.hpp
*	@brief The library that deals force feedback
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.8
*
*/

#include <SDL2/SDL_haptic.h>
#include <SDL2/SDL_gamecontroller.h>

namespace LX_Device
{

class LX_Haptic;

int numberOfHapticDevices(void);
bool mouseIsHaptic();
LX_Haptic * getMouseHaptic();

/**
*   @class LX_Haptic
*   @brief The haptic device
*
*   This class describes the force feedback device.
*/
class LX_Haptic
{
    SDL_Haptic *_haptic;
    int _instanceID;

    LX_Haptic(LX_Haptic& h);
    LX_Haptic& operator =(LX_Haptic& h);

public :

    LX_Haptic();
    LX_Haptic(int index);
    LX_Haptic(SDL_Joystick *joy);
    LX_Haptic(SDL_GameController *gc);
    LX_Haptic& operator =(SDL_Haptic& haptic);

    bool isOpened(void);
    bool rumbleEffectInit(void);
    void rumbleEffectPlay(void);
    void rumbleEffectPlay(float strength, Uint32 length);

    bool effectSupported(SDL_HapticEffect& effect);
    int newEffect(SDL_HapticEffect& effect);
    void runEffect(int effect_id, Uint32 iterations);
    void stopEffect(int effect_id);

    int numberOfEffects(void);

    ~LX_Haptic();
};

};

#endif // LX_HAPTIC_HPP_INCLUDED
