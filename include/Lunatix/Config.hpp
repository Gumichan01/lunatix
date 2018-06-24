
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

#ifndef LX_CONFIG_H_INCLUDED
#define LX_CONFIG_H_INCLUDED

/**
*   @file Config.hpp
*   @brief The configuration class header
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*
*/


/**
*   @ingroup Config
*   @namespace LX_Config
*   @brief The configuration
*/
namespace LX_Config
{

/**
*   @class LX_Configuration
*   @brief The configuration loader of Lunatix
*
*   This class is responsible of loading the configuration of the library
*/
class LX_Configuration final
{
    LX_Configuration() noexcept;
    LX_Configuration( LX_Configuration& c ) = delete;
    LX_Configuration( LX_Configuration&& c ) = delete;
    LX_Configuration& operator =( LX_Configuration& c ) = delete;
    LX_Configuration&& operator =( LX_Configuration&& c ) = delete;
    ~LX_Configuration() = default;

    void loadFlags_() noexcept;

public:


    /**
    *   @fn LX_Configuration& getInstance() noexcept
    *   Get the singleton of the LX_Configuration class
    *   @return The instance of LX_Configuration
    */
    static LX_Configuration& getInstance() noexcept;

    /**
    *   @fn bool getVideoFlag() const noexcept
    *   Get the video flag
    *   @return TRUE if the flag is set, FALSE otherwise
    */
    bool getVideoFlag() const noexcept;
    /**
    *   @fn bool getVSyncFlag() const noexcept
    *   Get the Vertical Synchronization (VSync) flag
    *   @return TRUE if the flag is set, FALSE otherwise
    */
    bool getVSyncFlag() const noexcept;
    /**
    *   @fn bool getTTFFlag() const noexcept
    *   Get the True Type Font (TTF) flag
    *   @return TRUE if the flag is set, FALSE otherwise
    */
    bool getTTFFlag() const noexcept;
    /**
    *   @fn bool getAudioFlag() const noexcept
    *   Get the audio flag
    *   @return TRUE if the flag is set, FALSE otherwise
    */
    bool getAudioFlag() const noexcept;
    /**
    *   @fn bool getGamepadFlag() const noexcept
    *   Get the audio flag
    *   @return TRUE if the flag is set, FALSE otherwise
    */
    bool getGamepadFlag() const noexcept;
    /**
    *   @fn bool getOpenGLFlag() const noexcept
    *   Get the opengl flag
    *   @return TRUE if the flag is set, FALSE otherwise
    */
    bool getOpenGLFlag() const noexcept;
};

}
#endif // LX_CONFIG_H_INCLUDED