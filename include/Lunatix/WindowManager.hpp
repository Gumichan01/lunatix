
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

#ifndef LX_WINDOWMANAGER_HPP_INCLUDED
#define LX_WINDOWMANAGER_HPP_INCLUDED

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

class LX_Window;
class LX_WM_;


class LX_WindowNotFoundException final : public std::exception
{
    std::string _string_error;

    LX_WindowNotFoundException& operator =( const LX_WindowNotFoundException& w ) = delete;

public:

    explicit LX_WindowNotFoundException( const std::string& err );
    const char * what() const noexcept override;
    ~LX_WindowNotFoundException() noexcept = default;

};

/**
*   @class LX_WindowManager
*   @brief The windows manager
*
*   LX_WindowManager allows the user to handle several windows
*   inside an application.
*/
class LX_WindowManager final
{
    std::unique_ptr<LX_WM_> _wmpimpl;

    LX_WindowManager();
    ~LX_WindowManager();

    LX_WindowManager( const LX_WindowManager& )  = delete;
    LX_WindowManager( const LX_WindowManager&& ) = delete;
    LX_WindowManager& operator =( const LX_WindowManager& )   = delete;
    LX_WindowManager&& operator =( const LX_WindowManager&& ) = delete;

public:

    /**
    *   @fn LX_WindowManager& LX_WindowManager::getInstance() noexcept
    *   Return a unique instance of the window manager
    *   @return The windo manager
    */
    static LX_WindowManager& getInstance() noexcept;
    /**
    *   @fn bool LX_WindowManager::addWindow(LX_Window& w) noexcept
    *
    *   Add a window in the manager
    *
    *   @param [in] w The window
    *
    *   @return true on success, false otherwise
    *
    *   @sa LX_Window
    *   @sa removeWindow
    */
    bool addWindow( LX_Window& w ) noexcept;
    /**
    *   @fn bool LX_WindowManager::removeWindow(const uint32_t id) noexcept
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
    *   @fn LX_Window& LX_WindowManager::getWindow(const uint32_t id) const
    *
    *   Get a window according to its ID
    *
    *   @param [in] id The id of the window
    *
    *   @return A valid pointer to a LX_Window instance if it exists,
    *          a null pointer otherwise
    */
    LX_Window& getWindow( const uint32_t id ) const;
    /**
    *   @fn std::size_t LX_WindowManager::nbWindows() noexcept
    *   Count the number of windows
    *   @return The number of registered windows
    */
    std::size_t nbWindows() const noexcept;

    /**
    *   @fn void LX_WindowManager::updateWindows() noexcept
    *   Update the windows
    */
    void updateWindows() noexcept;
    /**
    *   @fn void LX_WindowManager::clearWindows() noexcept
    *   Clear the content of the windows
    */
    void clearWindows() noexcept;
};

/**
*   @fn LX_WindowManager& getWindowManager() noexcept
*
*   Return the singleton, if allocated
*
*   @return The unique instance of LX_WindowManager
*   @note This function is equivalent to LX_WindowManager::getInstance
*/
LX_WindowManager& getWindowManager() noexcept;

}   // Win

}   // lx

#endif // LX_WINDOWMANAGER_HPP_INCLUDED
