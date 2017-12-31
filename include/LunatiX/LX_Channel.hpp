
/*
*   Copyright © 2018 Luxon Jean-Pierre
*   https://gumichan01.github.io/
*
*   LunatiX is a free, SDL2-based library.
*   It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*   luxon.jean.pierre@gmail.com
*/

#ifndef LX_CHANNEL_HPP_INCLUDED
#define LX_CHANNEL_HPP_INCLUDED

/**
*   @file LX_Channel.hpp
*   @brief The channel API
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.12
*/

#include <LunatiX/LX_Sync.hpp>
#include <queue>
#include <vector>

namespace LX_Multithreading
{

/**
*   @brief Multithread synchronization primitive
*
*   @arg T Generic type that implements '=' (and a copy constructor for classes)
*
*   This is a C++ implementation of the channel
*   introduced by the Go language.
*
*   See this link:
*   - https://en.wikipedia.org/wiki/Go_(programming_language)#Concurrency:_goroutines_and_channels
*/
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

    /// Constructor
    LX_Channel();
    /**
    *   @fn bool send(const T& data)
    *
    *   Send data into the channel
    *
    *   @param [in] data Data to send
    *
    *   @return TRUE on success, FALSE if the channel is closed
    */
    bool send(const T& data);
    /**
    *   @fn bool recv(T& data)
    *
    *   Receive data from the channel
    *
    *   @param [out] data Data to fill in
    *
    *   @return TRUE on success, FALSE if the channel is closed and empty
    *   @note If no data is available yet, the calls blocks until
    *        until thre is something to retrieve
    */
    bool recv(T& data);

    /**
    *   @fn template <typename Iterator> bool vsend(Iterator begin, Iterator end)
    *
    *   Send multiple data into the channel
    *
    *   @param [in] begin iterator to the first element
    *   @param [in] end iterator to the last element
    *
    *   @return TRUE on success, FALSE if the channel is closed
    */
    template <typename Iterator>
    bool vsend(Iterator begin, Iterator end);

    /**
    *   @fn bool vrecv(std::vector<T>& vec, const unsigned long nb)
    *
    *   Receive multiple data from the channel
    *
    *   @param [out] vec list of data to send
    *   @param [in] nb Number of data values
    *
    *   @return TRUE on success, FALSE if the channel is closed and empty
    *
    *   @note This functions can retrieve less data than expected
    */
    bool vrecv(std::vector<T>& vec, const unsigned long nb);
    /**
    *   @fn void close()
    *   Close the channel
    */
    void close();
    /// Destructor
    ~LX_Channel();
};

#include "LX_Channel.tpp"

}

#endif // LX_CHANNEL_HPP_INCLUDED
