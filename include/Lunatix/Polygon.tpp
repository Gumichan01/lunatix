
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

#include <algorithm>

namespace lx
{

namespace Physics
{

template <typename Iterator>
void LX_Polygon::addPoints(Iterator beg, Iterator last)
{
    std::for_each(beg, last,[this](const LX_FloatPosition& p)
    {
        addPoint_(p);
    });
    convexity_();
}

}   // Physics

}   // lx
