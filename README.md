# LunatiX #

![LunatiX Logo](https://media.githubusercontent.com/media/Gumichan01/lunatix/master/data/lunatix-logo.png)

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
                switch(ev.getType())
                {
                case LX_QUIT:
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

You may take a look on the library or get the development version
on [Github](https://github.com/Gumichan01/lunatix). The library reference
is also available [online (version 0.9)](https://gumichan01.github.io/lunatix/reference/v0.9.0/).

## Build ##

### On Windows ###

First of all, download the stable [development and runtime libraries](https://github.com/Gumichan01/lunatix-engine/releases/tag/LX-v0.9.0) (v0.9.0)
It includes the library files and all necessary materials (SDL2 libraries)
to develop any project.

The source code is compilable using [MinGW](http://www.mingw.org/).
It should work with Visual C++ (if you are lucky).

You can build it using the CodeBlocks project provided in the directory (*lunatix-win32.cbp*).

### On Linux ###

The Makefile uses Clang in order to get the library being compiled.
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


If you want to generate the library libraries you just need to execute
the following command:

    $ make

These two library files are generated into the *lib/linux/* directory.

To test the library, execute the following command:

    $ make test

## Documentation ##

The documentation of the library can be build with Doxygen,
using the **dox** configuration file.
