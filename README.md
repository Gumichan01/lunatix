# LunatiX Engine #

LunatiX Engine is an SDL2-based game engine. It can be used for open-source or commercial games thanks to the zlib/libpng license.

It contains these following libraries:
- LX\_Graphics : A 2D library based on SDL_Image 2.0 (supporting JPEG, PNG, GIF, ...)
- LX\_TrueTypeFont : The True Type Font (TTF) library based on SDL_TTF 2.0
- LX\_Mixer : The audio library based on SDL_Mixer 2.0(supporting MP3, OGG Vorbis, WMA, WAV, ...)
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
 
You may take a look on the library or get the development version on [Github](https://github.com/Gumichan01/lunatix-engine).  
You can also find the library reference on my [website](http://gumichan01.olympe.in/reference/lunatix-engine/).

## Installation ##
### On Windows ###

 Supported compiler:
 - MinGW/g++ 4.7.1+

Import a new project using the XML file provided in the directory into your IDE (Well, it works on CodeBlocks).  
You need to install Lua 5.1 to compile the Lua script.  
The static and shared files (.lib, .a, .dll for win32 version) required to compile with SDL2 and Lua are provided.

Warning:  
It is possible the engine cannot be compiled with Visual C++.

### On Linux system ###

 Supported compilers:
 - Clang 3.4+
 - g++ 4.7+

The source code is stil compilable with g++ 4.6 but its support is deprecated.


 Requirements:
 - Clang 3.4 at least (it is used in the makefile)
 - SDL 2.0.3 at least
 - Lua 5.1
 - OpenGL 3.1 at least


### Warning/Information ###

 - It is possible you get an issue if you use a recent version of Lua on Linux.
 - The program uses the compiled Lua file, (the .luac file created during the program building), not the script.
 - A shared Lua library file (.so file) on Linux is provided. It uses Lua 5.1

### Build the program ###

#### On Linux ####

If you want to generate the libraries you just need  
to execute the following command:  
 *$make*

These two libraries can be used in any program

To test the engine, execute the following command:  
 *$./test/test.sh*

You need to be in the root directory of the source code to launch the script.  
Otherwise, the script will not work.

To use the engine into your project, you need to copy these following directories  
into your project tree :
 - *config/*
 - *include/*
 - *lib/*
 - *script/*

It is very important to keep the engine hierarchy. If you do not respect that,  
the engine will not work correctly.

Finally, copy the shared libraries in *lib/linux*.


#### On Windows ####

This current version is unstable, so no development library is provided yet.
However, it is possible to get the last stable version of the engine donwload this 
[development library (v0.6.1)] (http://gumichan01.olympe.in/download/dev-luna-win32.zip)  
It includes the library files and all necessary materials to develop any project.  

Warning : The static or shared libraries are not completely installed on the system.
 So you need to do that manually.



