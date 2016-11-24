
/*
*    Copyright (C) 2016 Luxon Jean-Pierre
*    https://gumichan01.github.io/
*
*    LunatiX is a free, SDL2-based library.
*    It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*    Luxon Jean-Pierre (Gumichan01)
*    luxon.jean.pierre@gmail.com
*/


template <typename T>
LX_Channel<T>::LX_Channel() : _closed(false), _nbwaiters(0) {}

template <typename T>
LX_Channel<T>::~LX_Channel() {}


template <typename T>
bool LX_Channel<T>::send(const T& data)
{
    _mutex.lock();

    if(_closed)
    {
        _mutex.unlock();
        return false;
    }

    _qdata.push(data);

    if(_nbwaiters > 0)
        _cond.signal();

    _mutex.unlock();
    return true;
}


template <typename T>
bool LX_Channel<T>::recv(T& data)
{
    _mutex.lock();

    // If the channel is empty but not closed → Wait for input
    while(_qdata.empty() && !_closed)
    {
        _nbwaiters += 1;
        _cond.wait(_mutex);
        _nbwaiters -= 1;
    }

    // If the channel is closed and empty → cannot read it
    if(_qdata.empty() && _closed)
    {
        _mutex.unlock();
        return false;
    }

    data = _qdata.front();
    _qdata.pop();
    _mutex.unlock();
    return true;
}

template <typename T>
bool LX_Channel<T>::vsend(const std::vector<T>& vec)
{
    _mutex.lock();

    if(_closed)
    {
        _mutex.unlock();
        return false;
    }

    for(T datum: vec)
    {
        _qdata.push(datum);
    }

    if(_nbwaiters > 0)
        _cond.signal();

    _mutex.unlock();
    return true;
}

template <typename T>
bool LX_Channel<T>::vrecv(std::vector<T>& vec, const unsigned long nb)
{
    _mutex.lock();

    while(_qdata.empty() && !_closed)
    {
        _nbwaiters += 1;
        _cond.wait(_mutex);
        _nbwaiters -= 1;
    }

    if(_qdata.empty() && _closed)
    {
        _mutex.unlock();
        return false;
    }

    const unsigned long QSIZE = _qdata.size();
    const unsigned long N = (nb < QSIZE) ? nb : QSIZE;

    for(unsigned long i = 0; i < N; i++)
    {
        vec.push_back(_qdata.front());
        _qdata.pop();
    }

    _mutex.unlock();
    return true;
}


template <typename T>
void LX_Channel<T>::close()
{
    _mutex.lock();
    _closed = true;
    _cond.broadcast();
    _mutex.unlock();
}
