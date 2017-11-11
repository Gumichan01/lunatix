
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

#include <LunatiX/LX_Sync.hpp>
#include <LunatiX/utils/tinythread/tinythread.h>


namespace LX_Multithreading
{

/* Mutex */

class LX_Mutex_
{
    friend class LX_Cond_;
    std::unique_ptr<tthread::mutex> _mutex;

public:

    LX_Mutex_() noexcept: _mutex(new tthread::mutex()) {}

    void lock() noexcept
    {
        _mutex->lock();
    }

    void unlock() noexcept
    {
        _mutex->unlock();
    }

    ~LX_Mutex_()
    {
        _mutex.reset();
    }
};


LX_Mutex::LX_Mutex() noexcept: _mu(new LX_Mutex_) {}


void LX_Mutex::lock() noexcept
{
    _mu->lock();
}


void LX_Mutex::unlock() noexcept
{
    _mu->unlock();
}


LX_Mutex::~LX_Mutex()
{
    _mu.reset();
}


/* Condition variable */

class LX_Cond_
{
    std::unique_ptr<tthread::condition_variable> _condition;

public:

    LX_Cond_() noexcept: _condition(new tthread::condition_variable()) {}

    void wait(LX_Mutex_ *mutex) noexcept
    {
        _condition->wait(*(mutex->_mutex.get()));
    }

    void signal() noexcept
    {
        _condition->notify_one();
    }

    void broadcast() noexcept
    {
        _condition->notify_all();
    }

    ~LX_Cond_()
    {
        _condition.reset();
    }
};


LX_Cond::LX_Cond() noexcept: _cond(new LX_Cond_()) {}


void LX_Cond::wait(LX_Mutex& mutex) noexcept
{
    _cond->wait(mutex._mu.get());
}


void LX_Cond::signal() noexcept
{
    _cond->signal();
}


void LX_Cond::broadcast() noexcept
{
    _cond->broadcast();
}


LX_Cond::~LX_Cond()
{
    _cond.reset();
}

}
