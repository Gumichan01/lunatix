#ifndef LX_CHANNEL_HPP_INCLUDED
#define LX_CHANNEL_HPP_INCLUDED

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
*    @file LX_Channel.hpp
*    @brief The channel API
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.8
*
*/

#include <LunatiX/LX_Sync.hpp>
#include <queue>

namespace LX_Multithreading
{

template <typename T>
class LX_Channel
{
protected:

    bool _closed;
    unsigned int _nbwaiters;
    std::queue<T> _qdata;
    LX_Mutex _mutex;
    LX_Cond _cond;

public:

    LX_Channel();
    bool send(T& data);
    bool recv(T& data);
    void close();
    ~LX_Channel();
};

#include "LX_Channel.tpp"

};

#endif // LX_CHANNEL_HPP_INCLUDED
