 # LunatiX Engine #

 LunatiX Engine is a SDL-based game engine. It can be used for open-source or commercial games thanks to the zlib/libpng license. 

 It contains these following libraries: 

 - LX_Graphics : a 2D library based on SDL and SDL_Image
 - LX_TrueTypeFont : a True Type Font (TTF) library based on SDL_TTF
 - LX_Mixer : a mix library using SDL_Mixer
 - LX_Physics : a physics engine 

 At the moment, the engine only works on windows. The Linux support will be done soon.

 
 You can find the library reference [here](http://gumichan01.olympe.in/reference/lunatix-engine/)


 
 ## Installation ##


 ### On Windows ###

 - You can use the makefile to generate an executable file to launch the program.
 - Otherwise you can import a new project using the XML file provided in the directory into your IDE.


 ### On Linux system ###

 Requirements :
 
  - SDL 2.0.1 at least must be installed on your system.
  - Lua 5.1 must be installed on you computer.
  
 Warning :
 
  - It is possible you get an issue if you use a recent version of Lua. 


 You just need to execute the following command :
	$make

 So, you can launch the demo program



Warning : No static or shared library are provided when you generate the executable file.
However, all SDL2 and Lua files (.lib, .a, .dll for win32 version, .so for Lua) are provided.


