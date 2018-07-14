
/*
*   Copyright © 2018 Luxon Jean-Pierre
*   https://gumichan01.github.io/
*
*   LunatiX is a free, SDL2-based library.
*   It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*   luxon.jean.pierre@gmail.com
*/

#ifndef WINDOWMANAGER_HPP_INCLUDED
#define WINDOWMANAGER_HPP_INCLUDED

/**
*   @file WindowManager.hpp
*   @brief The window manager
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*
*/

#include <cinttypes>
#include <memory>

namespace lx
{

namespace Win
{

class Window;
class WinManager_;


class WindowNotFoundException final : public std::exception
{
    std::string _string_error;

    WindowNotFoundException& operator =( const WindowNotFoundException& w ) = delete;

public:

    explicit WindowNotFoundException( const std::string& err );
    const char * what() const noexcept override;
    ~WindowNotFoundException() noexcept = default;

};

/**
*   @class WindowManager
*   @brief The windows manager
*
*   WindowManager allows the user to handle several windows
*   inside an application.
*/
class WindowManager final
{
    std::unique_ptr<WinManager_> m_wmpimpl;

    WindowManager();
    ~WindowManager();

    WindowManager( const WindowManager& )  = delete;
    WindowManager( const WindowManager&& ) = delete;
    WindowManager& operator =( const WindowManager& )   = delete;
    WindowManager&& operator =( const WindowManager&& ) = delete;

public:

    /**
    *   @fn WindowManager& WindowManager::getInstance() noexcept
    *   Return a unique instance of the window manager
    *   @return The windo manager
    */
    static WindowManager& getInstance() noexcept;
    /**
    *   @fn bool WindowManager::addWindow(Window& w) noexcept
    *
    *   Add a window in the manager
    *
    *   @param [in] w The window
    *
    *   @return true on success, false otherwise
    *
    *   @sa Window
    *   @sa removeWindow
    */
    bool addWindow( Window& w ) noexcept;
    /**
    *   @fn bool WindowManager::removeWindow(const uint32_t id) noexcept
    *
    *   Delete a window from the list acording to its ID
    *   and returns the pointer to it.
    *
    *   @param [in] id The ID of the window that must be deleted
    *
    *   @return true on success, false otherwise
    *
    *   @note This function does not destroy the window, because each instance
    *        of a window in the list can be statically or dymanically allocated
    *        So, the user is responsible of releasing the window.
    *
    *   @sa addWindow
    */
    bool removeWindow( const uint32_t id ) noexcept;
    /**
    *   @fn Window& WindowManager::getWindow(const uint32_t id) const
    *
    *   Get a window according to its ID
    *
    *   @param [in] id The id of the window
    *
    *   @return A valid pointer to a Window instance if it exists,
    *          a null pointer otherwise
    */
    Window& getWindow( const uint32_t id ) const;
    /**
    *   @fn std::size_t WindowManager::nbWindows() noexcept
    *   Count the number of windows
    *   @return The number of registered windows
    */
    std::size_t nbWindows() const noexcept;

    /**
    *   @fn void WindowManager::updateWindows() noexcept
    *   Update the windows
    */
    void updateWindows() noexcept;
    /**
    *   @fn void WindowManager::clearWindows() noexcept
    *   Clear the content of the windows
    */
    void clearWindows() noexcept;
};

/**
*   @fn WindowManager& getWindowManager() noexcept
*
*   Return the singleton, if allocated
*
*   @return The unique instance of WindowManager
*   @note This function is equivalent to WindowManager::getInstance
*/
WindowManager& getWindowManager() noexcept;

}   // Win

}   // lx

#endif // WINDOWMANAGER_HPP_INCLUDED
