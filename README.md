# LunatiX #

![LunatiX Logo][]

LunatiX is a free SDL2-based library. It can be used for open-source or
commercial games thanks to the zlib/libpng license.

It contains these following modules:
- Graphics: 2D module for rendering (sprite, text, ...) and window management
- Audio: Audio module for mixing (music, channels, effect, ...)
- Physics: Physics Module (collision detection, movement, ...)
- And some others ...

The library works on Windows and Linux (maybe on Mac OS X).

## Features ##

- 2D hardware acceleration
- 2D basic animation
- Support for OpenGL 3.0+
- Support for multiple windows
- Basic particle system
- Multithreading
- Text input
- Gamepad support
- many other things...

## Examples ##

```cpp
#include <Lunatix/Lunatix.hpp>

using namespace LX_Event;

int main( int argc, char** argv )
{
	if ( !lx::init() )
	{
		lx::Log::log( "Cannot load the library: %s", LX_getError() );
		return -1;
	}

    // Information about how to build the window
    LX_Win::LX_WindowInfo info;
    LX_Win::LX_loadWindowConfig( info );
    info.w = 256;
    info.h = 256;

    LX_Win::LX_Window w( info );
    const std::string s = "data/bullet.png";
    LX_Graphics::LX_Sprite sprite( s, w );
    const LX_Graphics::LX_ImgRect position = { { 0, 0 }, 256, 256 };
    LX_EventHandler ev;
    bool go = true;

    while ( go )
    {
        while ( ev.pollEvent() )
        {
            switch ( ev.getEventType() )
            {
            case LX_EventType::QUIT:
                go = false;
                break;
            default:
                break;
            }
        }

        w.clearWindow();
        sprite.draw( position );
        w.update();
        lx::time::delay( 33 );
    }

    lx::quit();
    return 0;
}
```

## Contribute ##

You may take a look on the library or get the development version on [Github][].
The library reference is also available [here][].

### Prerequisites ###

You must install [git-lfs][] in your computer in order to retrieve the repository.

## Build ##

### On Windows ###

First of all, download the stable development and runtime [libraries][].
It includes the library files and all necessary materials (SDL2 libraries)
to develop any project.

You also need to clone the project and execute `git-lfs pull`.

The source code is compilable using [MinGW][].
It should work with Visual C++ (if you are lucky).

You can build it using the CodeBlocks project provided in the directory (*lunatix-win32.cbp*).

### On Linux ###

You must have at least GNU GCC 4.8.1 or Clang 3.4 to compile the code.

In order to build the library, you need to get these following libraries
installed.

|   Library  | Minimal version |
|     ---    |       ---       |
|    SDL2    |      2.0.3+     |
| SDL2_image |      2.0.0+     |
|  SDL2_TTF  |      2.0.12+    |
| SDL2_Mixer |      2.0.0+     |
|   OpenGL   |       3.0+      |

[How to build LunatiX properly][howto]

## Documentation ##

The documentation of the library can be built with Doxygen,
using the **dox** configuration file.

## Games that use LunatiX ##

- [Target Xplosion][tx]: 2D scrolling shooter game
- [Br8k0ut][br]: 8-bit platformer game

---

[LunatiX Logo]: https://raw.githubusercontent.com/Gumichan01/lunatix/master/data/lunatix-logo.png
[Github]: https://github.com/Gumichan01/lunatix
[here]: https://github.com/Gumichan01/lunatix/tree/gh-pages/reference
[git-lfs]: https://github.com/git-lfs/git-lfs/wiki/Installation
[libraries]: https://github.com/Gumichan01/lunatix-engine/releases/tag/LX-v0.13.0
[MinGW]: http://www.mingw.org/
[howto]: https://gist.github.com/Gumichan01/0731cb32832df3ff293b90601b34e0dc
[tx]: https://github.com/Gumichan01/target-xplosion/
[br]: https://github.com/Gumichan01/br8k0ut/
