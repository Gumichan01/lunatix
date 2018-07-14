
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


template <typename T>
AbstractFile& operator <<( AbstractFile& f, const T data ) noexcept
{
    f.write( &data, sizeof( T ) );
    return f;
}

template <typename T>
AbstractFile& operator >>( AbstractFile& f, T& data ) noexcept
{
    f.read( &data, sizeof( T ) );
    return f;
}
