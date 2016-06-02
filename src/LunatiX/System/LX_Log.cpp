

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

#include <cstdarg>
#include <LunatiX/LX_Log.hpp>

namespace LX_Log
{

//  Private field in the namespace
static bool debug_mode = false;


/**
*   @fn bool isDebugMode(void)
*
*   Check if the program is in debug mode
*
*   @return TRUE if the program is in debug mode, false otherwise
*/
bool isDebugMode(void)
{
    return debug_mode;
}

/**
*   @fn void setDebugMode(bool debug)
*
*   Set the debug mode
*
*   @param debug Optionnal argument, TRUE by default when it is not used
*/
void setDebugMode(bool debug)
{
    if(debug)
        SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
    else
        setDefaultPriority();

    debug_mode = debug;
}

/**
*   @fn void setDefaultPriority(void)
*
*   Set the default priorities to the application
*/
void setDefaultPriority(void)
{
    SDL_LogResetPriorities();
}

/**
*   @fn void setVerbosePriority(LX_CATEGORY category)
*
*   Set the verbose priority to a log category
*/
void setVerbosePriority(LX_CATEGORY category)
{
    SDL_LogSetPriority(category,SDL_LOG_PRIORITY_VERBOSE);
}

/**
*   @fn void setDebugPriority(LX_CATEGORY category)
*
*   Set the debug priority to a log category
*/
void setDebugPriority(LX_CATEGORY category)
{
    SDL_LogSetPriority(category,SDL_LOG_PRIORITY_DEBUG);
}

/**
*   @fn void setInfoPriority(LX_CATEGORY category)
*
*   Set the info priority to a log category
*/
void setInfoPriority(LX_CATEGORY category)
{
    SDL_LogSetPriority(category,SDL_LOG_PRIORITY_INFO);
}

/**
*   @fn void setWarningPriority(LX_CATEGORY category)
*
*   Set the warning priority to a log category
*/
void setWarningPriority(LX_CATEGORY category)
{
    SDL_LogSetPriority(category,SDL_LOG_PRIORITY_WARN);
}

/**
*   @fn void setErrorPriority(LX_CATEGORY category)
*
*   Set the error priority to a log category
*/
void setErrorPriority(LX_CATEGORY category)
{
    SDL_LogSetPriority(category,SDL_LOG_PRIORITY_ERROR);
}

/**
*   @fn void setCriticalPriority(LX_CATEGORY category)
*
*   Set the critical priority to a log category
*/
void setCriticalPriority(LX_CATEGORY category)
{
    SDL_LogSetPriority(category,SDL_LOG_PRIORITY_CRITICAL);
}

/**
*   Log a message with the verbose priority and a specified category
*/
void logVerbose(LX_CATEGORY category,char *format,...)
{
    va_list args;
    va_start(args,format);
    SDL_LogMessageV(category,SDL_LOG_PRIORITY_VERBOSE,format,args);
    va_end(args);
}

/**
*   Log a message with the debug priority and a specified category
*/
void logDebug(LX_CATEGORY category,char *format,...)
{
    va_list args;
    va_start(args,format);
    SDL_LogMessageV(category,SDL_LOG_PRIORITY_DEBUG,format,args);
    va_end(args);
}

/**
*   Log a message with the info priority and a specified category
*/
void logInfo(LX_CATEGORY category,char *format,...)
{
    va_list args;
    va_start(args,format);
    SDL_LogMessageV(category,SDL_LOG_PRIORITY_INFO,format,args);
    va_end(args);
}

/**
*   Log a message with the warning priority and a specified category
*/
void logWarning(LX_CATEGORY category,char *format,...)
{
    va_list args;
    va_start(args,format);
    SDL_LogMessageV(category,SDL_LOG_PRIORITY_WARN,format,args);
    va_end(args);
}

/**
*   Log a message with the error priority and a specified category
*/
void logError(LX_CATEGORY category,char *format,...)
{
    va_list args;
    va_start(args,format);
    SDL_LogMessageV(category,SDL_LOG_PRIORITY_ERROR,format,args);
    va_end(args);
}

/**
*   Log a message with the critical priority and a specified category
*/
void logCritical(LX_CATEGORY category,char *format,...)
{
    va_list args;
    va_start(args,format);
    SDL_LogMessageV(category,SDL_LOG_PRIORITY_CRITICAL,format,args);
    va_end(args);
}

/**
*   Log a message with the info priority and the applicatiion category
*/
void log(char *format,...)
{
    va_list args;
    va_start(args,format);
    SDL_LogMessageV(LX_LOG_APPLICATION,SDL_LOG_PRIORITY_INFO,format,args);
    va_end(args);
}



};

























