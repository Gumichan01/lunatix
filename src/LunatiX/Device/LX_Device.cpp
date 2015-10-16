
/*
*	Copyright (C) 2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	LunatiX Engine is a SDL-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_Device.cpp
*	@brief The implementation of the device
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.6
*
*/

#include <cstring>
#include <iostream>
#include <sstream>

#include <SDL2/SDL_mouse.h>

#include <LunatiX/LX_Device.hpp>
#include <LunatiX/LX_Error.hpp>

using namespace std;

static const short GUID_SIZE = 16;    // Size of the data in SDL_JoystickGUID


namespace LX_Device
{
int lx_stat(SDL_Joystick * joy, LX_GamepadInfo *info);
};


/**
*   @namespace LX_Device
*
*   @brief The device module
*
*/
namespace LX_Device
{

int lx_stat(SDL_Joystick * joy, LX_GamepadInfo *info)
{
    if(joy == NULL)
        return LX_SetError("Invalid joystick\n");

    if(info == NULL)
        return LX_SetError("Invalid gamepad info\n");

    // Get information
    info->id = SDL_JoystickInstanceID(joy);
    info->uid = SDL_JoystickGetGUID(joy);
    info->numAxis = SDL_JoystickNumAxes(joy);
    info->numBalls = SDL_JoystickNumBalls(joy);
    info->numButtons = SDL_JoystickNumButtons(joy);
    info->numHats = SDL_JoystickNumHats(joy);

    if(info->id == -1
            || info->numAxis == -1
            || info->numBalls == -1
            || info->numButtons == -1
            || info->numHats == -1)
    {
        return LX_SetError("Cannot get information\n");
    }

    return 0;
}


/**
*   @fn int numberOfDevices(void)
*
*   Count the number of connected devices (gamepads)
*
*   @return The number of gamepads
*
*/
int numberOfDevices(void)
{
    return SDL_NumJoysticks();
}


/**
*   @fn const char * nameOf(SDL_Joystick * joy)
*
*   Get the name of a joystick
*
*   @param joy The pointer to a joystick structure
*
*   @return The name of the joystick, NULL if the pointer is not valid
*
*/
const char * nameOf(SDL_Joystick * joy)
{
    return SDL_JoystickName(joy);
}


/**
*   @fn const char * nameOf(SDL_GameController * controller)
*
*   Get the name of a game controller
*
*   @param controller The pointer to a structure relative to the gamepad
*
*   @return The name of the game controller, NULL if the pointer is not valid
*
*/
const char * nameOf(SDL_GameController * controller)
{
    return SDL_GameControllerName(controller);
}



/**
*   @fn int statGamepad(SDL_Joystick * joy, LX_GamepadInfo *info)
*
*   Get the name of a game controller
*
*   @param joy The joystick to get information from
*   @param info The structure to store information
*
*   @return 0 if the joystick is valid and the function got information
*               -1 on failure
*
*/
int statGamepad(SDL_Joystick * joy, LX_GamepadInfo *info)
{
    const char *tmp;

    if(joy == NULL)
        return LX_SetError("Invalid joystick\n");

    if(info == NULL)
        return LX_SetError("Invalid gamepad info\n");

    tmp = nameOf(joy);

    if(tmp == NULL)
        return LX_SetError("Cannot get the name of the joystick\n");

    strcpy(info->name,tmp);

    return lx_stat(joy,info);
}



/**
*   @fn int statGamepad(SDL_GameController * gc, LX_GamepadInfo *info)
*
*   Get the name of a game controller
*
*   @param gc The game controller to get information from
*   @param info The structure to store information
*
*   @return 0 if the game controller is valid and the function got information
*               -1 on failure
*
*/
int statGamepad(SDL_GameController * gc, LX_GamepadInfo *info)
{
    const char *tmp;

    if(gc == NULL)
        return LX_SetError("Invalid game controller\n");

    if(info == NULL)
        return LX_SetError("Invalid gamepad info\n");

    tmp = nameOf(gc);

    if(tmp == NULL)
        return LX_SetError("Cannot get the name of the game controller\n");

    strcpy(info->name,tmp);

    return lx_stat(SDL_GameControllerGetJoystick(gc),info);
}


/**
*   @fn const char * gamepadToString(LX_GamepadInfo *info, char * str)
*
*   Get the string format of the information structure
*
*   @param info The structure you want to get the string format from
*   @param str The string to fiil in
*
*   @return Always returns a non-NULL C string
*
*   @note This function never returns NULL
*   @warning If info or str is NULL, a segmentation fault will occur
*   @warning str must be long enough to get the entire text.
*            ::LX_PADSTRING_SIZE is a good length
*
*   @sa statGamepad
*/
const char * gamepadToString(LX_GamepadInfo *info, char * str)
{
    ostringstream stream;
    char guid[GUID_SIZE+1];

    memset(&guid,0,GUID_SIZE+1);
    SDL_JoystickGetGUIDString(info->uid,guid,GUID_SIZE);

    stream << endl << " ==== Gamepad Information ==== " << endl << endl
    << "Gamepad - ID : " << info->id << endl
    << "Gamepad - UID : " << guid << endl
    << "Gamepad - Name : " << info->name << endl
    << "Gamepad - Number of Axes : " << info->numAxis << endl
    << "Gamepad - Number of Balls : " << info->numBalls << endl
    << "Gamepad - Number of Buttons : " << info->numButtons << endl
    << "Gamepad - Number of Hats : " << info->numHats << endl;

    strcpy(str,stream.str().c_str());
    return str;
}


/**
*   @fn int mouseCursorDisplay(int toggle)
*
*   Define is the cursor will be shown or not
*
*   @param toggle One of hese following values :
*           1 to show it
*           0 to hide
*           -1 to get the current state
*
*   @return 1 if the cursor is shown, 0 if it is hidden, a negative value on failure
*
*/
int mouseCursorDisplay(int toggle)
{
    return SDL_ShowCursor(toggle);
}


};


