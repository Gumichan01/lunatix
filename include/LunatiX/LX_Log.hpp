#ifndef LX_LOG_HPP_INCLUDED
#define LX_LOG_HPP_INCLUDED

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
*	@file LX_Log.cpp
*	@brief The Log file
*	@author Luxon Jean-Pierre(Gumichan01)
*
*/

namespace LX_Log
{

void setDefaultMode(bool debug = true);

void setVerbosePriority(void);
void setDebugPriority(void);
void setInfoPriority(void);
void setWarningPriority(void);
void setErrorPriority(void);
void setCriticalPriority(void);

void setDefaultPriority(void);


};

#endif // LX_LOG_HPP_INCLUDED
