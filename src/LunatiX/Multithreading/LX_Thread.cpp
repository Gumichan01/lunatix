
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

//#ifdef __linux__

#include <LunatiX/LX_Thread.hpp>
#include <LunatiX/utils/tinythread/tinythread.h>
#include <LunatiX/LX_Log.hpp>

#include <SDL2/SDL_thread.h>
#include <functional>
#include <stdexcept>


namespace
{
using LX_ThreadFun_ = void(void *);
};

class LX_Thread_
{
    std::function<LX_ThreadFun_> _f;
    std::string _name;
    bool _launched;
    tthread::thread * _thread;
    LX_Multithreading::LX_Data _data;

public:

    LX_Thread_(const std::function<LX_ThreadFun_>& f, std::string name,
               LX_Multithreading::LX_Data data)
        : _f(f), _name(name), _launched(false),
          _thread(nullptr), _data(data) {}


    void start()
    {
        if(_launched)
            return;

        _thread = new tthread::thread(*_f.target<void(*)(void *)>(),_data);
        _launched = true;
    }

    void startAndDetach()
    {
        start();

        if(joinable())
        {
            _thread->detach();
        }
    }

    bool joinable()
    {
        return _thread != nullptr && _thread->joinable();
    }

    void join()
    {
        if(!_launched || _thread == nullptr || !joinable())
            throw std::invalid_argument("Not joinable thread");

        _thread->join();
        delete _thread;
        _thread = nullptr;
        _launched = false;
    }

    const std::string& getName() const
    {
        return _name;
    }

    ~LX_Thread_()
    {
        if(joinable() && _launched)
            join();
    }
};


namespace LX_Multithreading
{

unsigned long getID()
{
    return SDL_GetThreadID(nullptr);
}

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

void LX_Thread::startAndDetach()
{
    _th->startAndDetach();
}

bool LX_Thread::joinable()
{
    return _th->joinable();
}

void LX_Thread::join()
{
    _th->join();
}

const std::string& LX_Thread::getName() const
{
    return _th->getName();
}

LX_Thread::~LX_Thread()
{
    delete _th;
}

};
//#endif  // __linux__
