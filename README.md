# LunatiX Engine #

 LunatiX Engine is a SDL-based game engine. It can be used for open-source or commercial games thanks to the zlib/libpng license. 

 It contains these following libraries: 

 - LX_Graphics : a 2D library based on SDL and SDL_Image
 - LX_TrueTypeFont : a True Type Font (TTF) library based on SDL_TTF
 - LX_Mixer : a mix library using SDL_Mixer
 - LX_Physics : a physics engine
 - LX_Device : a Device information library

 The engine works on Windows and Linux system.


 
 ## Contribute ##
 
  - You may take a look on the library or get the development version on [Github](https://github.com/Gumichan01/lunatix-engine)
  - You can also find the library reference on my [website](http://gumichan01.olympe.in/reference/lunatix-engine/)
 
 
 
 ## Installation ##


 ### On Windows ###

  - You can use the makefile to generate an executable file to launch the program.
  - You can also import a new project using the XML file provided in the directory into your IDE.


 ### On Linux system ###

 Requirements :
 
  - SDL 2.0.1 at least
  - Lua 5.1
  - OpenGL 2.1 at least
  
 Warning :
 
  - It is possible you get an issue if you use a recent version of Lua. 


 You just need to execute the following command :
	$make

 So, you can launch the demo program



Warning : No static or shared libraries are provided when you generate the executable file.
However, all SDL2 and Lua files (.lib, .a, .dll for win32 version, .so for Lua) are provided.


