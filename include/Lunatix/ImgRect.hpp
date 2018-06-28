
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

#ifndef LX_IMGRECT_H_INCLUDED
#define LX_IMGRECT_H_INCLUDED

/**
*   @file ImgRect.hpp
*   @brief The definition of LX_ImgRect
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*/

#include <Lunatix/Hitbox.hpp>

namespace LX_Physics
{
struct LX_FloatPosition;
struct LX_FloatingBox;
}

namespace lx
{

namespace Graphics
{

/**
*   @ingroup Graphics
*   @struct LX_ImgCoord
*   @brief Image coordinates
*/
struct LX_ImgCoord final
{
    int x;      /**< X position */
    int y;      /**< Y position */
};

/**
*   @fn LX_ImgCoord toPixelPosition(const lx::Physics::LX_FloatPosition& p) noexcept
*
*   @param p
*   @return The LX_ImgCoord
*/
LX_ImgCoord toPixelPosition( const lx::Physics::LX_FloatPosition& p ) noexcept;

/**
*   @ingroup Graphics
*   @struct LX_ImgRect
*   @brief The Image box
*
*   This box, defined as an Axis-Aligned Bounding Box (AABB) contains information
*   about the position and the dimension of the image to display
*/
struct LX_ImgRect final
{
    LX_ImgCoord p;  /**< Position   */
    int w, h;       /**< Dimension  */
};

/**
*   @fn LX_ImgRect toImgRect(const lx::Physics::LX_FloatingBox& b) noexcept
*
*   @param b
*   @return The LX_ImgRect
*/
LX_ImgRect toImgRect( const lx::Physics::LX_FloatingBox& b ) noexcept;

/**
*   @fn bool operator ==(const LX_ImgCoord& a, const LX_ImgCoord& b) noexcept
*
*   @param [in] a The first point
*   @param [in] b The second point
*
*   @return TRUE If these points have exactly the same coordinates,
*          FALSE otherwise
*/
bool operator ==( const LX_ImgCoord& a, const LX_ImgCoord& b ) noexcept;
/**
*   @fn bool operator !=(const LX_ImgCoord& a, const LX_ImgCoord& b) noexcept
*
*   @param [in] a The first point
*   @param [in] b The second point
*
*   @return TRUE If these points have not the same coordinates, FALSE otherwise
*/
bool operator !=( const LX_ImgCoord& a, const LX_ImgCoord& b ) noexcept;
/**
*   @fn bool operator ==(const LX_ImgRect& a, const LX_ImgRect& b) noexcept
*
*   @param [in] a The first rectangle
*   @param [in] b The second rectangle
*
*   @return TRUE If these points have exactly the same coordinates,
*          FALSE otherwise
*/
bool operator ==( const LX_ImgRect& a, const LX_ImgRect& b ) noexcept;
/**
*   @fn bool operator !=(const LX_ImgRect& a, const LX_ImgRect& b) noexcept
*
*   @param [in] a The first rectangle
*   @param [in] b The second rectangle
*
*   @return TRUE If these points have not the same coordinates, FALSE otherwise
*/
bool operator !=( const LX_ImgRect& a, const LX_ImgRect& b ) noexcept;

}   // Graphics

}   // lx

#endif  /* LX_IMGRECT_H_INCLUDED */
