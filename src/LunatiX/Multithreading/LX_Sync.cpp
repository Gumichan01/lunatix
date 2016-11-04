
/*
*    Copyright (C) 2016 Luxon Jean-Pierre
*    gumichan01.olympe.in
*
*    LunatiX is a free, SDL2-based library.
*    It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*    Luxon Jean-Pierre (Gumichan01)
*    luxon.jean.pierre@gmail.com
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

    LX_Mutex_(): _mutex(new tthread::mutex()) {}

    void lock()
    {
        _mutex->lock();
    }

    void unlock()
    {
        _mutex->unlock();
    }

    ~LX_Mutex_()
    {
        _mutex.reset();
    }
};


LX_Mutex::LX_Mutex(): _mu(new LX_Mutex_) {}


void LX_Mutex::lock()
{
    _mu->lock();
}


void LX_Mutex::unlock()
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

    LX_Cond_(): _condition(new tthread::condition_variable()) {}

    void wait(LX_Mutex_ *mutex)
    {
        _condition->wait(*(mutex->_mutex.get()));
    }

    void signal()
    {
        _condition->notify_one();
    }

    void broadcast()
    {
        _condition->notify_all();
    }

    ~LX_Cond_()
    {
        _condition.reset();
    }
};


LX_Cond::LX_Cond(): _cond(new LX_Cond_()) {}


void LX_Cond::wait(LX_Mutex& mutex)
{
    _cond->wait(mutex._mu.get());
}


void LX_Cond::signal()
{
    _cond->signal();
}


void LX_Cond::broadcast()
{
    _cond->broadcast();
}


LX_Cond::~LX_Cond()
{
    _cond.reset();
}

};
