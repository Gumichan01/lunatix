#ifndef LX_SOUND_H_INCLUDED
#define LX_SOUND_H_INCLUDED



/*
*	Copyright (C) 2014-2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX-engine is a SDL-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_Sound.h
*	@brief The abstract sound class
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.2
*	@date February 20th, 2015
*
*
*/

#include <iostream>

class LX_Sound{


    public:

    virtual bool load(std::string filename) = 0;
    virtual void play() = 0;
    virtual int volume(int newVolume) = 0;

    ~LX_Sound(){};
};




#endif // LX_SOUND_H_INCLUDED
