# LunatiX #

LunatiX is a free SDL2-based library. It can be used for open-source or
commercial games thanks to the zlib/libpng license.

It contains these following libraries:
- LX\_Graphics: A 2D library based on SDL_Image 2.0 (supporting JPEG, PNG,...)
- LX\_TrueTypeFont: The True Type Font (TTF) library based on SDL_TTF 2.0
- LX\_Mixer: The audio library based on SDL_Mixer 2.0 (supporting MP3, OGG, WAV, ...)
- LX\_Physics: The physics engine

LunatiX also contains these modules:
- LX\_Device: The information library about Gamepads
- LX\_FileIO: The Input/Output file library
- LX\_MSGBox: The Message box module
- LX\_ParticleEngine: A basic particle system
- LX\_Random: The Random Number Generator (RNG) library
- LX_VersionInfo: A module to get the version of the library
- LX\_SystemInfo: The System information library

The library works on Windows and Linux.

## Contribute ##

You may take a look on the library or get the development version
on [Github](https://github.com/Gumichan01/lunatix-engine) ~~You can also find
the library reference on my [website](http://gumichan01.kappatau.fr/reference/lunatix-engine/v0.8.0/).~~

## Getting started ##
### On Windows ###

~~First of all, download the stable [development and runtime libraries](https://github.com/Gumichan01/lunatix-engine/releases/tag/LX-v0.8.0) (v0.8.0)
It includes the library files and all necessary materials to develop any project.
You must include them in the root directory of the project you are working on.~~

### On a Linux system ###

You just need to download the source code of the library and build libraries.

### Build ###
#### On Linux ####

The LunatiX source code is written according to the C++11 standard, and
uses Clang to be compiled.
So you must ensure that Clang (version 3.4 at least) is installed to compile the code.
However, the source code is still compilable with g++, but you will have to
modify the Makefile to compile.

Requirements:

|   Library  | Minimal version |
|     ---    |       ---       |
|    SDL2    |      2.0.3+     |
| SDL2_image |      2.0.0+     |
|  SDL2_TTF  |      2.0.12+    |
| SDL2_Mixer |      2.0.2+     |
|   OpenGL   |       3.1+      |

If you want to generate the library libraries you just need
to execute the following command:

    $ make

These two library files are generated into the *lib/linux/* directory.

To test the library, execute the following command:

    $ make test

If you want to generate the documentation, do:

    $ make doc

To use the library into your project, copy these following directories
into your project tree:

 - *config/*
 - *include/*
 - *lib/*

It is very important to keep the library hierarchy. If you do not respect that,
the library will not work correctly.
