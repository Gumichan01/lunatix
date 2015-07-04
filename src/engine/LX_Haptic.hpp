#ifndef LX_HAPTIC_HPP_INCLUDED
#define LX_HAPTIC_HPP_INCLUDED



/*
*	Copyright (C) 2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	LunatiX Engine is a SDL-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_Haptic.hpp
*	@brief The library that deals force feedbaxck
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.5
*
*/

#include <SDL2/SDL_haptic.h>

#include "LX_Device.hpp"


namespace LX_Device
{

int numberOfHapticDevices(void);
bool isHaptic(SDL_Joystick *joy);



class LX_Haptic
{
    SDL_Haptic *haptic;

public :

    LX_Haptic(int index=0);
    LX_Haptic(SDL_Joystick *joy);

    bool isOpened(void);

    bool RumbleEffectInit(void);
    void RumbleEffectPlay(void);
    void RumbleEffectPlay(float strengh, Uint32 length);

    bool newEffect(SDL_HapticEffect * effect);
    void destroyEffect(SDL_HapticEffect * effect);
    bool runEffect(int effectID, Uint32 iterations);
    void stopEffect(int effectID);

    int numberOfEffects(void);

    ~LX_Haptic();
};


};




#endif // LX_HAPTIC_HPP_INCLUDED














