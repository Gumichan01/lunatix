
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

#ifndef IMGRECT_H_INCLUDED
#define IMGRECT_H_INCLUDED

/**
*   @file ImgRect.hpp
*   @brief The definition of ImgRect
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*/

#include <Lunatix/Hitbox.hpp>

namespace Physics
{
struct FloatPosition;
struct FloatingBox;
}

namespace lx
{

namespace Graphics
{

/**
*   @ingroup Graphics
*   @struct ImgCoord
*   @brief Image coordinates
*/
struct ImgCoord final
{
    int x;      /**< X position */
    int y;      /**< Y position */
};

/**
*   @fn ImgCoord toPixelPosition(const lx::Physics::FloatPosition& p) noexcept
*
*   @param p
*   @return The ImgCoord
*/
ImgCoord toPixelPosition( const lx::Physics::FloatPosition& p ) noexcept;

/**
*   @ingroup Graphics
*   @struct ImgRect
*   @brief The Image box
*
*   This box, defined as an Axis-Aligned Bounding Box (AABB) contains information
*   about the position and the dimension of the image to display
*/
struct ImgRect final
{
    ImgCoord p;  /**< Position   */
    int w, h;       /**< Dimension  */
};

/**
*   @fn ImgRect toImgRect(const lx::Physics::FloatingBox& b) noexcept
*
*   @param b
*   @return The ImgRect
*/
ImgRect toImgRect( const lx::Physics::FloatingBox& b ) noexcept;

/**
*   @fn bool operator ==(const ImgCoord& a, const ImgCoord& b) noexcept
*
*   @param [in] a The first point
*   @param [in] b The second point
*
*   @return TRUE If these points have exactly the same coordinates,
*          FALSE otherwise
*/
bool operator ==( const ImgCoord& a, const ImgCoord& b ) noexcept;
/**
*   @fn bool operator !=(const ImgCoord& a, const ImgCoord& b) noexcept
*
*   @param [in] a The first point
*   @param [in] b The second point
*
*   @return TRUE If these points have not the same coordinates, FALSE otherwise
*/
bool operator !=( const ImgCoord& a, const ImgCoord& b ) noexcept;
/**
*   @fn bool operator ==(const ImgRect& a, const ImgRect& b) noexcept
*
*   @param [in] a The first rectangle
*   @param [in] b The second rectangle
*
*   @return TRUE If these points have exactly the same coordinates,
*          FALSE otherwise
*/
bool operator ==( const ImgRect& a, const ImgRect& b ) noexcept;
/**
*   @fn bool operator !=(const ImgRect& a, const ImgRect& b) noexcept
*
*   @param [in] a The first rectangle
*   @param [in] b The second rectangle
*
*   @return TRUE If these points have not the same coordinates, FALSE otherwise
*/
bool operator !=( const ImgRect& a, const ImgRect& b ) noexcept;

}   // Graphics

}   // lx

#endif  /* IMGRECT_H_INCLUDED */
