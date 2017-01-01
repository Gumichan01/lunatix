
/*
*   Copyright © 2017 Luxon Jean-Pierre
*   https://gumichan01.github.io/
*
*   LunatiX is a free, SDL2-based library.
*   It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*   luxon.jean.pierre@gmail.com
*/

#ifndef LX_LOG_HPP_INCLUDED
#define LX_LOG_HPP_INCLUDED

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
*   | LX_LOG_APPLICATION | Info           |
*   | LX_LOG_ASSERT      | Warning        |
*   | LX_LOG_TEST        | Verbose        |
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
*   @enum LX_CATEGORY
*   @brief The log categories of the program
*
*/
enum LX_CATEGORY: int {LX_LOG_APPLICATION = 0,  /**< Application log    */
                       LX_LOG_ASSERT = 1,       /**< Assertion log      */
                       LX_LOG_ERROR = 2,        /**< Error log          */
                       LX_LOG_SYSTEM = 3,       /**< System log         */
                       LX_LOG_AUDIO = 4,        /**< Audio log          */
                       LX_LOG_VIDEO = 5,        /**< Video log          */
                       LX_LOG_RENDER = 6,       /**< Rendering log      */
                       LX_LOG_INPUT = 7,        /**< Input log          */
                       LX_LOG_TEST = 8          /**< Test log           */
                      };

/**
*   @fn bool isDebugMode()
*   Check if the program is in debug mode
*   @return TRUE if the program is in debug mode, false otherwise
*/
bool isDebugMode();
/**
*   @fn void setDebugMode(bool debug)
*   Set the debug mode
*   @param [in] debug Optionnal argument, TRUE by default when it is not used
*/
void setDebugMode(bool debug = true);

/**
*   @fn void setDefaultPriority()
*   Set the default priorities to the application
*/
void setDefaultPriority();
/**
*   @fn void setVerbosePriority(LX_CATEGORY category)
*   Set the verbose priority to a log category
*   @param [in] category
*/
void setVerbosePriority(LX_CATEGORY category);
/**
*   @fn void setDebugPriority(LX_CATEGORY category)
*   Set the debug priority to a log category
*   @param [in] category
*/
void setDebugPriority(LX_CATEGORY category);
/**
*   @fn void setInfoPriority(LX_CATEGORY category)
*   Set the info priority to a log category
*   @param [in] category
*/
void setInfoPriority(LX_CATEGORY category);
/**
*   @fn void setWarningPriority(LX_CATEGORY category)
*   Set the warning priority to a log category
*   @param [in] category
*/
void setWarningPriority(LX_CATEGORY category);

/**
*   @fn void setErrorPriority(LX_CATEGORY category)
*   Set the error priority to a log category
*   @param [in] category
*/
void setErrorPriority(LX_CATEGORY category);
/**
*   @fn void setCriticalPriority(LX_CATEGORY category)
*   Set the critical priority to a log category
*   @param [in] category
*/
void setCriticalPriority(LX_CATEGORY category);

/**
*   @fn void logVerbose(LX_CATEGORY category,std::string format,...)
*
*   Log a message with the verbose priority and a specified category
*
*   @param [in] category Category of the log
*   @param [in] format   String format
*/
void logVerbose(LX_CATEGORY category,std::string format,...);
/**
*   @fn void logDebug(LX_CATEGORY category,std::string format,...)
*
*   Log a message with the debug priority and a specified category
*
*   @param [in] category Category of the log
*   @param [in] format   String format
*/
void logDebug(LX_CATEGORY category,std::string format,...);
/**
*   @fn void logInfo(LX_CATEGORY category,std::string format,...)
*
*   Log a message with the info priority and a specified category
*
*   @param [in] category Category of the log
*   @param [in] format   String format
*/
void logInfo(LX_CATEGORY category,std::string format,...);
/**
*   @fn void logWarning(LX_CATEGORY category,std::string format,...)
*
*   Log a message with the warning priority and a specified category
*
*   @param [in] category Category of the log
*   @param [in] format   String format
*/
void logWarning(LX_CATEGORY category,std::string format,...);
/**
*   @fn void logError(LX_CATEGORY category,std::string format,...)
*
*   Log a message with the error priority and a specified category
*
*   @param [in] category Category of the log
*   @param [in] format   String format
*/
void logError(LX_CATEGORY category,std::string format,...);
/**
*   @fn void logCritical(LX_CATEGORY category,std::string format,...)
*
*   Log a message with the critical priority and a specified category
*
*   @param [in] category Category of the log
*   @param [in] format   String format
*/
void logCritical(LX_CATEGORY category,std::string format,...);

/**
*   @fn void log(std::string format,...)
*   Log a message with the info priority and the applicatiion category
*   @param [in] format String format
*/
void log(std::string format,...);

};

#endif // LX_LOG_HPP_INCLUDED
