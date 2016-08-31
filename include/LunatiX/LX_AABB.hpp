#ifndef LX_AABB_H_INCLUDED
#define LX_AABB_H_INCLUDED

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
*
*    @file LX_AABB.hpp
*    @brief The definition of LX_AABB
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.8
*
*/

struct SDL_Rect;

/**
*   @struct LX_AABB
*   @brief The Axis-Aligned Bounding Box (AABB)
*/
struct LX_AABB
{
    int x, y;
    int w, h;
};

inline const SDL_Rect * toRect(const LX_AABB *box)
{
    return reinterpret_cast<const SDL_Rect *>(box);
}

inline SDL_Rect * toRect(LX_AABB *box)
{
    return reinterpret_cast<SDL_Rect *>(box);
}

#endif  /* LX_AABB_H_INCLUDED */
