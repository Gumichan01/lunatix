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
*	@file LX_Log.hpp
*	@brief The Log file header
*	@author Luxon Jean-Pierre(Gumichan01)
*
*/

#include <SDL2/SDL_log.h>
#include <LunatiX/utils/utf8_string.hpp>

/**
*   @namespace LX_Log
*   @brief The log module
*/
namespace LX_Log
{

// Category of log
/**
*   @enum LX_CATEGORY
*   @brief The log categories of the program
*
*   Here are the default level priorities of each application category:
*   - LX_LOG_APPLICATION : INFO level
*   - LX_LOG_APPLICATION : WARN level
*   - LX_LOG_TEST        : VERBOSE level
*   - All other          : CRITICAL level
*/
enum LX_CATEGORY {LX_LOG_APPLICATION = SDL_LOG_CATEGORY_APPLICATION,
                  LX_LOG_ERROR = SDL_LOG_CATEGORY_ERROR,
                  LX_LOG_SYSTEM = SDL_LOG_CATEGORY_SYSTEM,
                  LX_LOG_AUDIO = SDL_LOG_CATEGORY_AUDIO,
                  LX_LOG_VIDEO = SDL_LOG_CATEGORY_VIDEO,
                  LX_LOG_RENDER = SDL_LOG_CATEGORY_RENDER,
                  LX_LOG_INPUT = SDL_LOG_CATEGORY_INPUT,
                  LX_LOG_TEST = SDL_LOG_CATEGORY_TEST
                 };

/**
*   @fn bool isDebugMode(void)
*
*   Check if the program is in debug mode
*
*   @return TRUE if the program is in debug mode, false otherwise
*/
bool isDebugMode(void);

/**
*   @fn void setDebugMode(bool debug)
*
*   Set the debug mode
*
*   @param debug Optionnal argument, TRUE by default when it is not used
*/
void setDebugMode(bool debug = true);

/**
*   @fn void setDefaultPriority(void)
*
*   Set the default priorities to the application
*/
void setDefaultPriority(void);

/**
*   @fn void setVerbosePriority(LX_CATEGORY category)
*
*   Set the verbose priority to a log category
*
*   @param category
*/
void setVerbosePriority(LX_CATEGORY category);

/**
*   @fn void setDebugPriority(LX_CATEGORY category)
*
*   Set the debug priority to a log category
*
*   @param category
*/
void setDebugPriority(LX_CATEGORY category);

/**
*   @fn void setInfoPriority(LX_CATEGORY category)
*
*   Set the info priority to a log category
*
*   @param category
*/
void setInfoPriority(LX_CATEGORY category);

/**
*   @fn void setWarningPriority(LX_CATEGORY category)
*
*   Set the warning priority to a log category
*
*   @param category
*/
void setWarningPriority(LX_CATEGORY category);

/**
*   @fn void setErrorPriority(LX_CATEGORY category)
*
*   Set the error priority to a log category
*
*   @param category
*/
void setErrorPriority(LX_CATEGORY category);

/**
*   @fn void setCriticalPriority(LX_CATEGORY category)
*
*   Set the critical priority to a log category
*
*   @param category
*/
void setCriticalPriority(LX_CATEGORY category);

/**
*   @fn void logVerbose(LX_CATEGORY category,std::string format,...)
*
*   Log a message with the verbose priority and a specified category
*
*   @param category : Category of the log
*   @param format   : String format
*/
void logVerbose(LX_CATEGORY category,std::string format,...);

/**
*   @fn void logDebug(LX_CATEGORY category,std::string format,...)
*
*   Log a message with the debug priority and a specified category
*
*   @param category : Category of the log
*   @param format   : String format
*/
void logDebug(LX_CATEGORY category,std::string format,...);

/**
*   @fn void logInfo(LX_CATEGORY category,std::string format,...)
*
*   Log a message with the info priority and a specified category
*
*   @param category : Category of the log
*   @param format   : String format
*/
void logInfo(LX_CATEGORY category,std::string format,...);

/**
*   @fn void logWarning(LX_CATEGORY category,std::string format,...)
*
*   Log a message with the warning priority and a specified category
*
*   @param category : Category of the log
*   @param format   : String format
*/
void logWarning(LX_CATEGORY category,std::string format,...);

/**
*   @fn void logError(LX_CATEGORY category,std::string format,...)
*
*   Log a message with the error priority and a specified category
*
*   @param category : Category of the log
*   @param format   : String format
*/
void logError(LX_CATEGORY category,std::string format,...);

/**
*   @fn void logCritical(LX_CATEGORY category,std::string format,...)
*
*   Log a message with the critical priority and a specified category
*
*   @param category : Category of the log
*   @param format   : String format
*/
void logCritical(LX_CATEGORY category,std::string format,...);

/**
*   @fn void log(std::string format,...)
*
*   Log a message with the info priority and the applicatiion category
*
*   @param format : String format
*/
void log(std::string format,...);

};

#endif // LX_LOG_HPP_INCLUDED
