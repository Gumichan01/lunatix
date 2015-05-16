# LunatiX Engine #

 LunatiX Engine is a SDL-based game engine. It can be used for open-source or commercial games thanks to the zlib/libpng license. 

 It contains these following libraries: 

 - LX\_Graphics : a 2D library based SDL_Image (supporting JPEG, PNG, GIF, ...)
 - LX\_TrueTypeFont : The True Type Font (TTF) library based on SDL_TTF
 - LX\_Mixer : The mix library based on SDL_Mixer (supporting MP3, OGG Vorbis, WMA, WAV, ...)
 - LX\_Physics : The physics engine
 
 LunatiX Engine also contains these modules
 
 - LX\_Device : The information library about Gamepad
 - LX\_SystemInfo : The System information library

 The engine works on Windows and Linux system.


 
 ## Contribute ##
 
  - You may take a look on the library or get the development version on [Github](https://github.com/Gumichan01/lunatix-engine)
  - You can also find the library reference on my [website](http://gumichan01.olympe.in/reference/lunatix-engine/)
 
 
 
 ## Installation ##


 ### On Windows ###

  - You can use the makefile to generate an executable file to launch the program.
  - You can also import a new project using the XML file provided in the directory into your IDE (CodeBlocks).
  - You do not need to install something, SDL2 and Lua files (.lib, .a, .dll for win32 version) are provided

  
 ### On Linux system ###

 Requirements :
 
  - SDL 2.0.1 at least
  - Lua 5.1
  - OpenGL 2.1 at least
  
 Warning/Information :
 
  - It is possible you get an issue if you use a recent version of Lua. So be sure you have the same version as requested.
  - The program uses the compiled Lua file, (the luac file created while the program builing), not the script.
  - A shared Lua libray file (.so file) is provided. It uses Lua 5.1


 You just need to execute the following command : 
	$make

 So, you can launch the demo program.

 To test the engine, execute the following command : 
 	$./test/test.sh

 You need to be on the root directory to launch the script.
 Otherwise, th script will not work.

Warning : No static or shared libraries are created when you generate the executable file.



