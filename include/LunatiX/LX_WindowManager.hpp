#ifndef LX_WINDOWMANAGER_HPP_INCLUDED
#define LX_WINDOWMANAGER_HPP_INCLUDED


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
*    @file LX_WindowManager.hpp
*    @brief The window manager
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.8
*
*/

#include <array>


namespace LX_Win
{

class LX_Window;

/// @todo (#1#) LX_WindowManager - private implementation
/// @todo (#2#) LX_Window - Refactor the window research and deletion

/**
*   @class LX_WindowManager
*   @brief The windows manager
*
*/
class LX_WindowManager
{
    static const int _LX_NBMAX_WINDOWS = 8;
    unsigned int _size;
    unsigned int _nbwin;                        /* Number of created windows */
    std::array<LX_Win::LX_Window*, _LX_NBMAX_WINDOWS> _windows;

    LX_WindowManager();
    ~LX_WindowManager();

    LX_WindowManager(LX_WindowManager& wm);
    LX_WindowManager& operator =(LX_WindowManager& wm);

public:

    /**
    *   @fn void LX_WindowManager::init()
    *   Initialize the window manager
    */
    static void init();

    /**
    *   @fn LX_WindowManager * LX_WindowManager::getInstance()
    *
    *   Return an instance of the singleton LX_WindowManager
    *
    *   @return The singleton
    */
    static LX_WindowManager * getInstance();

    /**
    *   @fn void LX_WindowManager::destroy()
    *
    *   Destroy the instance of the singleton
    *
    *   @warning    The windows contained in the window manager
    *               are not destroyed. So it is necessary to keep an external
    *               pointer to the windows added in the manager.
    */
    static void destroy();

    /**
    *   @fn int LX_WindowManager::addWindow(LX_Window *w)
    *
    *   Add a window to the list
    *
    *   @param [in] w The window
    *
    *   @return The ID of the window that was added if the instance is valid
    *           -1 otherwise
    *
    *   @sa LX_Window
    *   @sa removeWindow
    */
    int addWindow(LX_Window *w);

    /**
    *   @fn LX_Window * LX_WindowManager::removeWindow(unsigned int id)
    *
    *   Delete a window from the list acording to its ID
    *   and returns the pointer to it.
    *
    *   @param [in] id The ID of the window that must be deleted
    *
    *   @return A valid pointer to a window if the ID refers to a valid window,
    *           a null pointer otherwise
    *
    *   @sa addWindow
    */
    LX_Window * removeWindow(unsigned int id);

    /**
    *   @fn unsigned int LX_WindowManager::nbWindows()
    *
    *   Count the number of opened windows
    *
    *   @return The number of opened windows
    */
    unsigned int nbWindows();

    /**
    *   @fn void LX_WindowManager::updateWindows()
    *   Update the windows
    */
    void updateWindows();

    /**
    *   @fn void LX_WindowManager::clearWindows()
    *   Clear the content of the windows
    */
    void clearWindows();

    /**
    *   @fn LX_Window * LX_WindowManager::getWindow(unsigned int id)
    *
    *   Get a window according to its ID
    *
    *   @param [in] id The id of the window
    *
    *   @return A reference to a LX_Window instance if it exists,
    *           a null pointer otherwise
    */
    LX_Window * getWindow(unsigned int id);
};

/**
*   @fn LX_WindowManager * getWindowManager()
*
*   Return an instance of the singleton LX_WindowManager
*
*   @return The unique instance of LX_WindowManager
*   @note This function is equivalent to LX_WindowManager::getInstance
*/
LX_WindowManager * getWindowManager();

};

#endif // LX_WINDOWMANAGER_HPP_INCLUDED
