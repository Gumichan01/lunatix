
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

#ifndef HPP_INCLUDED
#define HPP_INCLUDED

/**
*   @file LX_Log.hpp
*   @brief The Log file header
*   @author Luxon Jean-Pierre(Gumichan01)
*/

#include <SDL2/SDL_log.h>
#include <LunatiX/utils/utf8_string.hpp>

/**
*   @ingroup System
*   @namespace LX_Log
*   @brief The log namespace
*
*   It handles log messages with categories and priorities
*
*   For each category, a priority level is associated with it.
*   These are the level priorities:
*   - Verbose
*   - Debug
*   - Info
*   - Warning
*   - Error
*   - Critical
*
*
*   The default level priorities are defined as follows:
*
*   |      Category      |      Level     |
*   |--------------------|----------------|
*   | APPLICATION | Info           |
*   | ASSERT      | Warning        |
*   | TEST        | Verbose        |
*   | Everything else    | Critical       |
*
*
*   @note If you're debugging your program you might want to call:
*
*      setDebugMode(true);
*
*/
namespace LX_Log
{

// Category of log
/**
*   @enum LX_LogType
*   @brief The log types of the program
*
*/
enum LX_LogType: int {APPLICATION = 0,  /**< Application log    */
                      ASSERT = 1,       /**< Assertion log      */
                      ERROR = 2,        /**< Error log          */
                      SYSTEM = 3,       /**< System log         */
                      AUDIO = 4,        /**< Audio log          */
                      VIDEO = 5,        /**< Video log          */
                      RENDER = 6,       /**< Rendering log      */
                      INPUT = 7,        /**< Input log          */
                      TEST = 8          /**< Test log           */
                     };

/**
*   @fn bool isDebugMode() noexcept
*   Check if the program is in debug mode
*   @return TRUE if the program is in debug mode, false otherwise
*/
bool isDebugMode() noexcept;
/**
*   @fn void setDebugMode(bool debug) noexcept
*   Set the debug mode
*   @param [in] debug Optionnal argument, TRUE by default when it is not used
*/
void setDebugMode(bool debug = true) noexcept;

/**
*   @fn void setDefaultPriority() noexcept
*   Set the default priorities to the application
*/
void setDefaultPriority() noexcept;
/**
*   @fn void setVerbosePriority(LX_LogType category) noexcept
*   Set the verbose priority to a log category
*   @param [in] category
*/
void setVerbosePriority(LX_LogType category) noexcept;
/**
*   @fn void setDebugPriority(LX_LogType category) noexcept
*   Set the debug priority to a log category
*   @param [in] category
*/
void setDebugPriority(LX_LogType category) noexcept;
/**
*   @fn void setInfoPriority(LX_LogType category) noexcept
*   Set the info priority to a log category
*   @param [in] category
*/
void setInfoPriority(LX_LogType category) noexcept;
/**
*   @fn void setWarningPriority(LX_LogType category) noexcept
*   Set the warning priority to a log category
*   @param [in] category
*/
void setWarningPriority(LX_LogType category) noexcept;

/**
*   @fn void setErrorPriority(LX_LogType category) noexcept
*   Set the error priority to a log category
*   @param [in] category
*/
void setErrorPriority(LX_LogType category) noexcept;
/**
*   @fn void setCriticalPriority(LX_LogType category) noexcept
*   Set the critical priority to a log category
*   @param [in] category
*/
void setCriticalPriority(LX_LogType category) noexcept;

/**
*   @fn void logVerbose(LX_LogType category, std::string format, ...) noexcept
*
*   Log a message with the verbose priority and a specified category
*
*   @param [in] category Category of the log
*   @param [in] format   String format
*/
void logVerbose(LX_LogType category, std::string format, ...) noexcept;
/**
*   @fn void logDebug(LX_LogType category,std::string format,...) noexcept
*
*   Log a message with the debug priority and a specified category
*
*   @param [in] category Category of the log
*   @param [in] format   String format
*/
void logDebug(LX_LogType category, std::string format, ...) noexcept;
/**
*   @fn void logInfo(LX_LogType category, std::string format,...) noexcept
*
*   Log a message with the info priority and a specified category
*
*   @param [in] category Category of the log
*   @param [in] format   String format
*/
void logInfo(LX_LogType category, std::string format, ...) noexcept;
/**
*   @fn void logWarning(LX_LogType category, std::string format,...) noexcept
*
*   Log a message with the warning priority and a specified category
*
*   @param [in] category Category of the log
*   @param [in] format   String format
*/
void logWarning(LX_LogType category, std::string format, ...) noexcept;
/**
*   @fn void logError(LX_LogType category, std::string format,...) noexcept
*
*   Log a message with the error priority and a specified category
*
*   @param [in] category Category of the log
*   @param [in] format   String format
*/
void logError(LX_LogType category, std::string format, ...) noexcept;
/**
*   @fn void logCritical(LX_LogType category, std::string format,...) noexcept
*
*   Log a message with the critical priority and a specified category
*
*   @param [in] category Category of the log
*   @param [in] format   String format
*/
void logCritical(LX_LogType category, std::string format, ...) noexcept;

/**
*   @fn void log(std::string format, ...) noexcept
*   Log a message with the info priority and the applicatiion category
*   @param [in] format String format
*/
void log(std::string format, ...) noexcept;

}

#endif // HPP_INCLUDED
