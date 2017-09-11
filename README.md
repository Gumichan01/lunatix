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


    #include <LunatiX/LX_LunatiX.hpp>

    using namespace LX_Event;

    int main(int argc, char** argv)
    {
        LX_AABB position = {0,0,256,256};
        LX_EventHandler ev;
        bool go = true;

        if(!LX_Init())
        {
            LX_Log::log("Cannot load the library: %s",LX_GetError());
            return -1;
        }

        // Information about how to build the window
        LX_Win::LX_WindowInfo info;
        LX_Win::LX_loadWindowConfig(info);
        info.w = 256;
        info.h = 256;

        LX_Win::LX_Window w(info);
        LX_Graphics::LX_Sprite sprite("data/bullet.png",w);

        while(go)
        {
            while(ev.pollEvent())
            {
                switch(ev.getEventType())
                {
                case LX_EventType::LX_QUIT:
                    go = false;
                    break;
                default:
                    break;
                }
            }

            w.clearWindow();
            sprite.draw(&position);
            w.update();
            LX_Timer::delay(33);
        }

        LX_Quit();
        return 0;
    }


## Contribute ##

You may take a look on the library or get the development version on [Github][].
The library reference is also available [here][] (version 0.10.0).

### Prerequisites ###

You must install [git-lfs][] in your computer in order to retrieve the repository.

## Build ##

### On Windows ###

First of all, download the stable development and runtime [libraries][] (v0.11.0).
It includes the library files and all necessary materials (SDL2 libraries)
to develop any project.

The source code is compilable using [MinGW][].
It should work with Visual C++ (if you are lucky).

You can build it using the CodeBlocks project provided in the directory (*lunatix-win32.cbp*).

### On Linux ###

The Makefile uses Clang in order to compile the library.
So you must ensure that Clang (version 3.4 at least) is installed to compile the code.
If not, you can compile the source code using g++ (4.7.1+), but you will have to
modify the Makefile to do it.

In order to build the library, you need to get these following libraries
installed.

|   Library  | Minimal version |
|     ---    |       ---       |
|    SDL2    |      2.0.3+     |
| SDL2_image |      2.0.0+     |
|  SDL2_TTF  |      2.0.12+    |
| SDL2_Mixer |      2.0.2+     |
|   OpenGL   |       3.0+      |


If you want to generate the library files you just need to execute
the following command:

    $ make

These two library files are generated into the *lib/linux/* directory.

If you just want to compile and launch the example code,
execute the following command:

    $ make lunatix-demo
    $ ./lunatix-demo

To test the library, execute the following command:

    $ make test
    $ bash ./test/test.sh

## Documentation ##

The documentation of the library can be build with Doxygen,
using the **dox** configuration file.

## Games that use LunatiX ##

- [Target Xplosion][tx]: 2D scrolling shooter game
- [Br8k0ut][tx]: 8-bit platformer game

---

[LunatiX Logo]: https://raw.githubusercontent.com/Gumichan01/lunatix/master/data/lunatix-logo.png
[Github]: https://github.com/Gumichan01/lunatix
[here]: https://github.com/Gumichan01/lunatix/tree/gh-pages/reference
[git-lfs]: https://github.com/git-lfs/git-lfs/wiki/Installation
[libraries]: https://github.com/Gumichan01/lunatix-engine/releases/tag/LX-v0.11.0
[MinGW]: http://www.mingw.org/
[tx]: https://github.com/Gumichan01/target-xplosion/
