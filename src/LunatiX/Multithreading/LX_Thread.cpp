
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

#include <LunatiX/LX_Thread.hpp>
#include <LunatiX/LX_Error.hpp>
#include <LunatiX/LX_Log.hpp>
#include <SDL2/SDL_thread.h>

#include <functional>
#include <stdexcept>


namespace
{
using LX_ThreadFun_ = int(void *);

const std::string JOIN_MSG("This thread is detached, has already been joined, or has not been launched");
const std::string DETACH_MSG("This thread is already detached, has been joined, or has not been launched");

const char * nameOfThread(SDL_Thread * th)
{
    return th == nullptr ? "unknown thread": SDL_GetThreadName(th);
}

};
class LX_Thread_
{
    std::function<LX_ThreadFun_> _f;
    std::string _name;
    bool _joinable;
    bool _launched;
    SDL_Thread * _thread;
    LX_Multithreading::LX_Data _data;

public:

    LX_Thread_(const std::function<LX_ThreadFun_>& f, std::string name,
               LX_Multithreading::LX_Data data)
        : _f(f), _name(name), _joinable(true), _launched(false),
          _thread(nullptr), _data(data) {}


    void start()
    {
        if(_launched)
            return;

        _thread = SDL_CreateThread(*_f.target<int(*)(void *)>(),
                                   _name.c_str(),_data);

        if(_thread == nullptr)
        {
            LX_Log::logCritical(LX_Log::LX_LOG_APPLICATION,
                                "Couldn't launch the thread: %d",LX_GetError());
            throw std::runtime_error("An error occurred while starting the thread");
        }

        _launched = true;
    }

    bool joinable()
    {
        return _joinable;
    }

    void join(int *ret)
    {
        if(!_joinable || !_launched)
        {
            LX_Log::logCritical(LX_Log::LX_LOG_APPLICATION,
                                "<%s> #%ld: not joinable",
                                nameOfThread(_thread),getID());
            throw std::invalid_argument(JOIN_MSG);
        }

        SDL_WaitThread(_thread,ret);
        _thread = nullptr;
        _joinable = false;
        _launched = false;
    }

    void detach()
    {
        if(!_joinable || !_launched)
        {
            LX_Log::logCritical(LX_Log::LX_LOG_APPLICATION,
                                "<%s> #%ld: cannot be detached",
                                nameOfThread(_thread),getID());
            throw std::invalid_argument(DETACH_MSG);
        }

        SDL_DetachThread(_thread);
        _joinable = false;
    }

    unsigned long getID() const
    {
        return SDL_GetThreadID(_thread);
    }

    std::string getName() const
    {
        return SDL_GetThreadName(_thread);
    }

    ~LX_Thread_()
    {
        if(_joinable && _launched)
            join(nullptr);
    }
};


namespace LX_Multithreading
{

LX_Thread::LX_Thread(LX_ThreadFun fun, std::string name, LX_Multithreading::LX_Data data)
    : _th(nullptr)
{
    if(fun == nullptr)
    {
        LX_Log::logCritical(LX_Log::LX_LOG_APPLICATION,"NULL pointer of function");
        throw std::invalid_argument("The function must be defined");
    }

    _th = new LX_Thread_(std::function<LX_ThreadFun_>(fun),name,data);
}

void LX_Thread::start()
{
    _th->start();
}

bool LX_Thread::joinable()
{
    return _th->joinable();
}

void LX_Thread::join(int *ret)
{
    _th->join(ret);
}

void LX_Thread::detach()
{
    _th->detach();
}

unsigned long LX_Thread::getID() const
{
    _th->getID();
}

std::string LX_Thread::getName() const
{
    return _th->getName();
}

LX_Thread::~LX_Thread()
{
    delete _th;
}

};
