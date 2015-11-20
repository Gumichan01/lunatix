#ifndef LX_WINDOWMANAGER_HPP_INCLUDED
#define LX_WINDOWMANAGER_HPP_INCLUDED


/*
*	Copyright (C) 2015 Luxon Jean-Pierre
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
*	@version 0.6
*
*/


#define LX_NBMAX_WINDOWS 64    /**< The maximum number of windows to display */


namespace LX_Graphics
{

class LX_Window;

/**
*   @class LX_WindowManager
*   @brief The windows manager
*
*/
class LX_WindowManager
{
    unsigned int size;
    unsigned int nbWin;
    LX_Window *windows[LX_NBMAX_WINDOWS];

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

