# LunatiX Engine #


LunatiX Engine is a SDL2-based game engine. It can be used for open-source or
commercial games thanks to the zlib/libpng license.

It contains these following libraries:
- LX\_Graphics : A 2D library based on SDL_Image 2.0 (supporting JPEG, PNG,...)
- LX\_TrueTypeFont : The True Type Font (TTF) library based on SDL_TTF 2.0
- LX\_Mixer : The audio library based on SDL_Mixer 2.0 (supporting MP3, OGG, WAV, ...)
- LX\_Physics : The physics engine

LunatiX Engine also contains these modules:
- LX\_Device : The information library about Gamepads
- LX\_FileIO : The FileIO library
- LX\_MSGBox : The Message box module
- LX\_ParticleEngine : The particle engine
- LX\_Random : The Random Number Generator (RNG) library
- LX_VersionInfo : A module to get the version of the engine
- LX\_SystemInfo : The System information library


The engine works on Windows and Linux system.


## Contribute ##

You may take a look on the library or get the development version
on [Github] (https://github.com/Gumichan01/lunatix-engine) You can also find
the library reference on my [website] (http://gumichan01.kappatau.fr/reference/lunatix-engine/v0.7.2/).


## Getting started ##

### On Windows ###

First of all, download the stable [development and runtime libraries]
(http://gumichan01.kappatau.fr/download/luna-devel-0.7.2-mingw.zip) (v0.7.2)
It includes the library files and all necessary materials to develop any project.
You must include them in the root directory of the project you are working on.



### On a Linux system ###

You just need to download the source code of the engine and build libraries.


### Build ###

#### On Linux ####

The LunatiX Engine source code is written according to the C++11 standard, and
uses Clang to be compiled.
So you must ensure that Clang (version 3.4 at least) is installed to compile the code.
However, the source code is still compilable with g++, but you will have to
modify the Makefile to compile.

No libraries are provided in this version, except for the Lua library which is
provided.
The engine uses Lua 5.1.

Requirements:
 - SDL 2.0.3+
 - Lua 5.1
 - OpenGL 3.1+

Warning/Information:
 - It is possible you get an issue if you use a recent version of Lua on Linux.
 - The program uses the compiled Lua file (.luac).
 - A shared Lua library file (.so file) on Linux is provided. It uses Lua 5.1.


If you want to generate the engine libraries you just need
to execute the following command:
 *$ make*

These two library files are generated into the *lib/linux/* directory.

To test the engine, execute the following command:
 *$ make test*


If you want to generate the documentation, do:
 *$ make doxy*


To use the engine into your project, copy these following directories
into your project tree:
 - *config/*
 - *include/*
 - *lib/*
 - *script/*

It is very important to keep the engine hierarchy. If you do not respect that,
the engine will not work correctly.
