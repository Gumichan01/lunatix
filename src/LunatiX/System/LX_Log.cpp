

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

#include <ctime>
#include <cstdarg>
#include <cerrno>
#include <cstring>
#include <string>
#include <sstream>
#include <LunatiX/LX_Log.hpp>

#if defined(WIN32) || defined(_WIN32) || defined(__CYGWIN__) || defined(__MINGW32__)
#undef __WIN32__
#define __WIN32__
#include <Windows.h>
#else
#include <cmath>
#endif

namespace LX_Log
{

//  Private field in the namespace
static bool debug_mode = false;
long getMillisTime();
std::string getDate();

// Get the time in millisecond
long getMillisTime()
{
    long ms = 0L;

#if defined(__WIN32__)

    SYSTEMTIME st;
    GetSystemTime(&st);
    ms = static_cast<long>(st.wMilliseconds);

#elif defined(linux) || defined(__linux) || defined(__linux__)

    struct timespec t;
    clock_gettime(CLOCK_REALTIME, &t);
    ms = static_cast<long>(round(t.tv_nsec / 1.0e6));

#endif

    return ms;
}

std::string getDate()
{
    const size_t sz = 256;
    char datestr[sz] = {'\0'};
    const time_t t = time(nullptr);

    if(t == -1)
    {
        // This error must not happen
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR,
                        "Internal error - Cannot get the time: %s",
                        strerror(errno));
        return std::string("");
    }

    const struct tm *tmp = localtime(&t);

    if(tmp == nullptr)
    {
        // This error must not happen
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR,
                        "Internal error - Cannot get the local time: %s",
                        strerror(errno));
        return std::string("");
    }

    std::ostringstream ss;
    strftime(datestr,sz,"[%Y-%m-%d %H:%M:%S.",tmp);
    ss << getMillisTime() << "] ";

    return std::string(datestr + ss.str());

}

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
*
*   @param category
*/
void setVerbosePriority(LX_CATEGORY category)
{
    SDL_LogSetPriority(category,SDL_LOG_PRIORITY_VERBOSE);
}

/**
*   @fn void setDebugPriority(LX_CATEGORY category)
*
*   Set the debug priority to a log category
*
*   @param category
*/
void setDebugPriority(LX_CATEGORY category)
{
    SDL_LogSetPriority(category,SDL_LOG_PRIORITY_DEBUG);
}

/**
*   @fn void setInfoPriority(LX_CATEGORY category)
*
*   Set the info priority to a log category
*
*   @param category
*/
void setInfoPriority(LX_CATEGORY category)
{
    SDL_LogSetPriority(category,SDL_LOG_PRIORITY_INFO);
}

/**
*   @fn void setWarningPriority(LX_CATEGORY category)
*
*   Set the warning priority to a log category
*
*   @param category
*/
void setWarningPriority(LX_CATEGORY category)
{
    SDL_LogSetPriority(category,SDL_LOG_PRIORITY_WARN);
}

/**
*   @fn void setErrorPriority(LX_CATEGORY category)
*
*   Set the error priority to a log category
*
*   @param category
*/
void setErrorPriority(LX_CATEGORY category)
{
    SDL_LogSetPriority(category,SDL_LOG_PRIORITY_ERROR);
}

/**
*   @fn void setCriticalPriority(LX_CATEGORY category)
*
*   Set the critical priority to a log category
*
*   @param category
*/
void setCriticalPriority(LX_CATEGORY category)
{
    SDL_LogSetPriority(category,SDL_LOG_PRIORITY_CRITICAL);
}

/**
*   @fn void logVerbose(LX_CATEGORY category,std::string format,...)
*
*   Log a message with the verbose priority and a specified category
*
*   @param category : Category of the log
*   @param format   : String format
*/
void logVerbose(LX_CATEGORY category,std::string format,...)
{
    va_list args;
    va_start(args,format);
    std::string str = getDate() + format;
    SDL_LogMessageV(category,SDL_LOG_PRIORITY_VERBOSE,str.c_str(),args);
    va_end(args);
}

/**
*   @fn void logDebug(LX_CATEGORY category,std::string format,...)
*
*   Log a message with the debug priority and a specified category
*
*   @param category : Category of the log
*   @param format   : String format
*/
void logDebug(LX_CATEGORY category,std::string format,...)
{
    va_list args;
    va_start(args,format);
    std::string str = "   " +  getDate() + format;
    SDL_LogMessageV(category,SDL_LOG_PRIORITY_DEBUG,str.c_str(),args);
    va_end(args);
}

/**
*   @fn void logInfo(LX_CATEGORY category,std::string format,...)
*
*   Log a message with the info priority and a specified category
*
*   @param category : Category of the log
*   @param format   : String format
*/
void logInfo(LX_CATEGORY category,std::string format,...)
{
    va_list args;
    va_start(args,format);
    std::string str = "    " + getDate() + format;
    SDL_LogMessageV(category,SDL_LOG_PRIORITY_INFO,str.c_str(),args);
    va_end(args);
}

/**
*   @fn void logWarning(LX_CATEGORY category,std::string format,...)
*
*   Log a message with the warning priority and a specified category
*
*   @param category : Category of the log
*   @param format   : String format
*/
void logWarning(LX_CATEGORY category,std::string format,...)
{
    va_list args;
    va_start(args,format);
    std::string str = "    " + getDate() + format;
    SDL_LogMessageV(category,SDL_LOG_PRIORITY_WARN,str.c_str(),args);
    va_end(args);
}

/**
*   @fn void logError(LX_CATEGORY category,std::string format,...)
*
*   Log a message with the error priority and a specified category
*
*   @param category : Category of the log
*   @param format   : String format
*/
void logError(LX_CATEGORY category,std::string format,...)
{
    va_list args;
    va_start(args,format);
    std::string str = "   " + getDate() + format;
    SDL_LogMessageV(category,SDL_LOG_PRIORITY_ERROR,str.c_str(),args);
    va_end(args);
}

/**
*   @fn void logCritical(LX_CATEGORY category,std::string format,...)
*
*   Log a message with the critical priority and a specified category
*
*   @param category : Category of the log
*   @param format   : String format
*/
void logCritical(LX_CATEGORY category,std::string format,...)
{
    va_list args;
    va_start(args,format);
    std::string str = getDate() + format;
    SDL_LogMessageV(category,SDL_LOG_PRIORITY_CRITICAL,str.c_str(),args);
    va_end(args);
}

/**
*   @fn void log(std::string format,...)
*
*   Log a message with the info priority and the applicatiion category
*
*   @param format : String format
*/
void log(std::string format,...)
{
    va_list args;
    va_start(args,format);
    std::string str = "    " + getDate() + format;
    SDL_LogMessageV(LX_LOG_APPLICATION,SDL_LOG_PRIORITY_INFO,str.c_str(),args);
    va_end(args);
}

};
