#ifndef LX_CHANNEL_HPP_INCLUDED
#define LX_CHANNEL_HPP_INCLUDED

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

/**
*    @file LX_Channel.hpp
*    @brief The channel API
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.8
*
*/

#include <LunatiX/LX_Sync.hpp>
#include <queue>
#include <vector>

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
    bool send(const T& data);
    bool recv(T& data);
    bool vsend(const std::vector<T>& vec);
    bool vrecv(std::vector<T>& vec, const unsigned long nb);
    void close();
    ~LX_Channel();
};

#include "LX_Channel.tpp"

};

#endif // LX_CHANNEL_HPP_INCLUDED
