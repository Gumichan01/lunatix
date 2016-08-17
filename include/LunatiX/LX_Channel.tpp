
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


namespace LX_Multithreading
{

/* Channel interface */

template <typename T>
LX_Channel<T>::LX_Channel() : _closed(false) {}


template <typename T>
LX_Channel<T>::~LX_Channel() {}


/* Asynchronous channel */

template <typename T>
LX_ASyncChannel<T>::LX_ASyncChannel() : _nbwaiters(0) {}


template <typename T>
bool LX_ASyncChannel<T>::send(T& data)
{
    this->_mutex.lock();

    if(this->_closed)
    {
        this->_mutex.unlock();
        return false;
    }

    _qdata.push(data);

    if(_nbwaiters > 0)
        _cond.signal();

    this->_mutex.unlock();
    return true;
}


template <typename T>
bool LX_ASyncChannel<T>::recv(T& data)
{
    this->_mutex.lock();

    // If the channel is empty but not closed → Wait for input
    while(_qdata.empty() && !this->_closed)
    {
        _nbwaiters += 1;
        _cond.wait(this->_mutex);
        _nbwaiters -= 1;
    }

    // If the channel is closed and empty → cannot read it
    if(_qdata.empty() && this->_closed)
    {
        this->_mutex.unlock();
        return false;
    }

    data = _qdata.front();
    _qdata.pop();
    this->_mutex.unlock();
    return true;
}


template <typename T>
void LX_ASyncChannel<T>::close()
{
    this->_mutex.lock();
    this->_closed = true;
    _cond.broadcast();
    this->_mutex.unlock();
}


template <typename T>
LX_ASyncChannel<T>::~LX_ASyncChannel() {}

};
