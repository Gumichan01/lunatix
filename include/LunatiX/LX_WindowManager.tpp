

/*
*   Copyright © 2017 Luxon Jean-Pierre
*   https://gumichan01.github.io/
*
*   LunatiX is a free, SDL2-based library.
*   It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*   luxon.jean.pierre@gmail.com
*/

#include <algorithm>

namespace LX_Win
{

template<class Fun>
void LX_WindowManager::map(Fun f)
{
    std::for_each(_windows.begin(), _windows.end(),f);
}

}
