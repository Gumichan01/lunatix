# LunatiX Engine v0.7 - Release note #

## Introduction  ##

This new version of the LunatiX engine contains a lot of updates and new  
features.  
The architecture of the engine and the source code organizaton have been updated  
for a better use in a project.


## Important changes ##

 - Modern C++11 code
 - Clang support on Linux, and MinGW/g++ 4.7+ on Windows
 - Re-organization of the engine architecture
 - Re-organization of the source tree
 - Refactoring of the physics module
 - Unique function to update and clear the display of *LX\_window*

## New features ##

 - Screenshot of a window
 - Vertical synchronization (VSync) integrated as configuration option
 - Selection between hardware acceleration and software rendering


## Details ##

 - Good by C++98/C++0x! C++11 is supported by the LunatiX engine. So, the source code
was entirely changed to integrate this standard. The source code architecture was simplified
thanks to the use of the constructor delegation.

 - Now Clang is supported on Linux and is the default compiler on this platform. 
g++ can still be used on Linux. But it is necessary to use g++ 4.7 to get the C++11 support. 
Clang 3.4 is the minimum required version to get this support.

 - The architecture of the engine underwent a little modification.

Here is the schema of this architecture:

    LX_Engine  
    | LX_Graphics  
    | LX_TrueTypeFont  
    | LX_Mixer  
    | LX_Physics  
    | LX_Device  
    | LX_FileIO  
    | LX_MSGBox  
    | LX_ParticleEngine  
    | LX_Random  
    | LX_SystemInfo  
    | LX_VersionInfo  

The different modules now depend on a general module : *LX\_Engine*


 - The source tree was changed. Now the *.hpp* file are located in *include/LunatiX/*  
and the *.cpp* file are under some different directories. Each directory symbolizes  
a module of the engine. Moreover, *src/engine/* was renamed to *src/LunatiX/*.

 - The *_build/* directory was also added. It contains the different object files

Here is the new tree of the source code:  

    lunatix-engine/
    ├── _build
    │   └── LunatiX
    │       ├── Device
    │       ├── FileIO
    │       ├── Graphics
    │       ├── Library
    │       ├── Mixer
    │       ├── MSGBox
    │       ├── ParticleEngine
    │       ├── Physics
    │       ├── Random
    │       ├── System
    │       ├── TrueTypeFont
    │       └── Version
    ├── config
    ├── data
    ├── font
    ├── include
    │   ├── GL
    │   ├── Lua
    │   ├── LunatiX
    │   └── SDL2
    ├── lib
    │   ├── linux
    │   └── win32
    ├── script
    ├── src
    │   └── LunatiX
    │       ├── Device
    │       ├── FileIO
    │       ├── Graphics
    │       ├── Library
    │       ├── Mixer
    │       ├── MSGBox
    │       ├── ParticleEngine
    │       ├── Physics
    │       ├── Random
    │       ├── System
    │       ├── TrueTypeFont
    │       └── Version
    └── test


 - The physics module was completely changed. Every functions of the modules  
use references as argument instead of pointers. The polygon class underwent   
minor modifications to keep data encapsulation.

 - The *LX\_Window* has one function to update and clear its content.  
The old functions become private because the instance will select the  
function to call acording to the display method. The display method should  
be defined as what kind of data the user wants to use  
(*SDL\_Surface* or *SDL\_Texture*).  
These functions are : *LX\_Window::update()* and *LX\_Window::clear()*.

 - Now it is possible to make a screenshot of the window.

 - The configuration module can handle the VSync(Vertical synchronization)  
option to prevent tearing. The VSync option is defined in the configuration file.

 - While creating the window, it is possible to set the rendering mode.  
That is to say the software rendreing or the hardware acceleration.


## FIXES

 - Fixed an [issue] [] with SDL2. Indeed, the version of SDL2\_Image was not good.

[issue]: https://github.com/Gumichan01/lunatix-engine/commit/7d5085d30017e3bd089a78abe7cd8821ea20da5b


## Other changes

 - The documentation of the engine can be done using *$ make doxy*
 
 - The test script is called using *$ make test* instead of *./test/test.sh*
 
 - Every object files are generated into the *_build/* directory

 - It is possible to compare circles using these following operations:  
*'=='*, *'!='*, *'>'*, *'<'*, *'>='*, *'<='*.  
Please take a look on the reference for more information.

 - *LX\_Circle*, *LX\_Polygon*, *LX\_Point* and *LX\_Vector2D* are included into  
the *LX\_Physics* namespace.

 - Some operations are possible with *LX\_Point*: *'='*, *'=='*, *'!='*
Please take a look on the reference for more information.

 - Comparison and arithmetic operations on *LX\_Vector2D* objects are possible:  
*'=='*, *'!='*, *'+'*, *'-'*, *'++'*, *'--'*, *'+='*.  
Some functions on vectors are also defined and implemented.

 - The structure of *LX\_Circle* was changed, the coordinates fields was replaced  
by a *LX\_Point* field.

 - Some default contructors and copy contructors were added in *LX\_Circle*, *LX\_Point* and *LX\_Vector2D*.

 - The signature of *LX\_VersionInfo::LX\_EngineVersion* has been changed.  
The argument is a reference to the structure.

 - *LX\_WindowManager* can update the display of the windows it manages  
using *LX\_WindowManager::updateWindows()*. It can also clear their contents  
using *LX\_WindowManager::clearWindows()*.

 - Refactored the *LX_Vector2D* structure. Now its fields are declared as float  
instead of int. These following functions about *LX_Vector2D*:

   - *scalar\_product()*
   - *vector\_product()*
   - *scalar\_norm()*
   - *movePoint()*, *moveRect()*, *moveCircle()* and *movePoly()*  
from *LX\_Physics* using an *LX\_Vector2D* object as argument

use reference instead of pointers.

 - Added two constant values : *LX\_GL\_MAJOR\_VERSION*, *LX\_GL\_MINOR\_VERSION*
 - Updated the game controller database
 - The getters of *LX\_Config* that returned an integer now returns a boolean value
 - Added the default values to arguments in *loadTextureFromFile()* and  
*loadTextureFromSurface()*
 - The particle system was improved. The texture of a particle 
must be loaded from a file buffer to improve the performance of the engine.




