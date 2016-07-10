#ifndef LX_WINDOWMANAGER_HPP_INCLUDED
#define LX_WINDOWMANAGER_HPP_INCLUDED


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
*	@file LX_WindowManager.hpp
*	@brief The window manager
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.8
*
*/

#include <array>

//#define LX_NBMAX_WINDOWS 8    /**< The maximum number of windows to display */


namespace LX_Win
{

class LX_Window;

/**
*   @class LX_WindowManager
*   @brief The windows manager
*
*/
class LX_WindowManager
{
    static const int LX_NBMAX_WINDOWS = 8;
    unsigned int size;
    unsigned int nbWin;                                 /* Number of existing windows */
    std::array<LX_Win::LX_Window*, LX_NBMAX_WINDOWS> windows;

    LX_WindowManager();
    ~LX_WindowManager();

    LX_WindowManager(LX_WindowManager& wm);
    LX_WindowManager& operator =(LX_WindowManager& wm);

public:

    static void init(void);
    static LX_WindowManager * getInstance();
    static void destroy(void);

    int addWindow(LX_Window *w);
    LX_Window * removeWindow(unsigned int id);
    unsigned int nbWindows(void);

    void updateWindows();
    void clearWindows();

    LX_Window * getWindow(unsigned int id);
};

LX_WindowManager * getWindowManager();

};

#endif // LX_WINDOWMANAGER_HPP_INCLUDED

