

/*
*    Copyright (C) 2016 Luxon Jean-Pierre
*    gumichan01.olympe.in
*
*    The LunatiX Engine is a SDL2-based game engine.
*    It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*    Luxon Jean-Pierre (Gumichan01)
*    luxon.jean.pierre@gmail.com
*/

/**
*    @file LX_Log.cpp
*    @brief The Log file
*    @author Luxon Jean-Pierre(Gumichan01)
*
*/

#include <LunatiX/LX_Log.hpp>
#include <sstream>
#include <ctime>

#if defined(__WIN32__)
#include <Windows.h>
#elif defined(__linux__)
#include <cmath>
#else
#error "Not supported system"
#endif

namespace
{

// Debug
bool debug_mode = false;

// Get the time in millisecond
long getMillisTime()
{
    long ms;

#if defined(__WIN32__)  // Windows

    SYSTEMTIME st;
    GetSystemTime(&st);
    ms = static_cast<long>(st.wMilliseconds);

#elif defined(linux) || defined(__linux) || defined(__linux__)  // Unix/Linux

    struct timespec t;
    clock_gettime(CLOCK_REALTIME, &t);
    ms = static_cast<long>(round(t.tv_nsec / 1.0e6));

#else   // Other system
#error "Unrecognized operating system"
#endif

    return ms;
}

std::string getDate()
{
    const size_t SZ = 256;
    char datestr[SZ] = {'\0'};
    const time_t t = time(nullptr);

    if(t == -1)
    {
        // This error must not happen
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR,
                        "Internal error - Cannot get the time: %s");
        return std::string("");
    }

    const struct tm *tmp = localtime(&t);

    if(tmp == nullptr)
    {
        // This error must not happen
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR,
                        "Internal error - Cannot get the local time");
        return std::string("");
    }

    std::ostringstream ss;
    strftime(datestr,SZ,"[%Y-%m-%d %H:%M:%S.",tmp);
    ss << getMillisTime() << "] ";

    return std::string(datestr + ss.str());

}
};

namespace LX_Log
{

bool isDebugMode(void)
{
    return debug_mode;
}


void setDebugMode(bool debug)
{
    if(debug)
        SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
    else
        setDefaultPriority();

    debug_mode = debug;
}


void setDefaultPriority(void)
{
    SDL_LogResetPriorities();
}


void setVerbosePriority(LX_CATEGORY category)
{
    SDL_LogSetPriority(category,SDL_LOG_PRIORITY_VERBOSE);
}


void setDebugPriority(LX_CATEGORY category)
{
    SDL_LogSetPriority(category,SDL_LOG_PRIORITY_DEBUG);
}


void setInfoPriority(LX_CATEGORY category)
{
    SDL_LogSetPriority(category,SDL_LOG_PRIORITY_INFO);
}


void setWarningPriority(LX_CATEGORY category)
{
    SDL_LogSetPriority(category,SDL_LOG_PRIORITY_WARN);
}


void setErrorPriority(LX_CATEGORY category)
{
    SDL_LogSetPriority(category,SDL_LOG_PRIORITY_ERROR);
}


void setCriticalPriority(LX_CATEGORY category)
{
    SDL_LogSetPriority(category,SDL_LOG_PRIORITY_CRITICAL);
}


void logVerbose(LX_CATEGORY category,std::string format,...)
{
    va_list args;
    va_start(args,format);
    std::string str = getDate() + format;
    SDL_LogMessageV(category,SDL_LOG_PRIORITY_VERBOSE,str.c_str(),args);
    va_end(args);
}


void logDebug(LX_CATEGORY category,std::string format,...)
{
    va_list args;
    va_start(args,format);
    std::string str = "   " +  getDate() + format;
    SDL_LogMessageV(category,SDL_LOG_PRIORITY_DEBUG,str.c_str(),args);
    va_end(args);
}


void logInfo(LX_CATEGORY category,std::string format,...)
{
    va_list args;
    va_start(args,format);
    std::string str = "    " + getDate() + format;
    SDL_LogMessageV(category,SDL_LOG_PRIORITY_INFO,str.c_str(),args);
    va_end(args);
}


void logWarning(LX_CATEGORY category,std::string format,...)
{
    va_list args;
    va_start(args,format);
    std::string str = "    " + getDate() + format;
    SDL_LogMessageV(category,SDL_LOG_PRIORITY_WARN,str.c_str(),args);
    va_end(args);
}


void logError(LX_CATEGORY category,std::string format,...)
{
    va_list args;
    va_start(args,format);
    std::string str = "   " + getDate() + format;
    SDL_LogMessageV(category,SDL_LOG_PRIORITY_ERROR,str.c_str(),args);
    va_end(args);
}


void logCritical(LX_CATEGORY category,std::string format,...)
{
    va_list args;
    va_start(args,format);
    std::string str = getDate() + format;
    SDL_LogMessageV(category,SDL_LOG_PRIORITY_CRITICAL,str.c_str(),args);
    va_end(args);
}


void log(std::string format,...)
{
    va_list args;
    va_start(args,format);
    std::string str = "    " + getDate() + format;
    SDL_LogMessageV(LX_LOG_APPLICATION,SDL_LOG_PRIORITY_INFO,str.c_str(),args);
    va_end(args);
}

};
