
/*
*	Copyright (C) 2016 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX Engine is a SDL2-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_Device.cpp
*	@brief The implementation of the device
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.8
*
*/

#include <cstring>
#include <iostream>
#include <sstream>

#include <SDL2/SDL_mouse.h>

#include <LunatiX/LX_Device.hpp>
#include <LunatiX/LX_Error.hpp>

using namespace std;

static const short GUID_SIZE = 16;          // Size of the data in SDL_JoystickGUID


namespace LX_Device
{
static int lx_stat(SDL_Joystick * joy, LX_GamepadInfo& info);
static int gstat(SDL_Joystick * joy, SDL_GameController * gc,
                 LX_GamepadInfo& info);
};


namespace LX_Device
{

static int lx_stat(SDL_Joystick * joy, LX_GamepadInfo& info)
{
    if(joy == nullptr)
        return LX_SetError("Invalid joystick\n");

    // Get information
    info.id = SDL_JoystickInstanceID(joy);
    info.uid = SDL_JoystickGetGUID(joy);
    info.nb_axis = SDL_JoystickNumAxes(joy);
    info.nb_balls = SDL_JoystickNumBalls(joy);
    info.nb_buttons = SDL_JoystickNumButtons(joy);
    info.nb_hats = SDL_JoystickNumHats(joy);

    if(info.id == -1 || info.nb_axis == -1 || info.nb_balls == -1
            || info.nb_buttons == -1 || info.nb_hats == -1)
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
*   @return The name of the joystick, a null pointer if the pointer is invalid
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
*   @return The name of the game controller, a null pointer
*           if the pointer is invalid
*
*/
const char * nameOf(SDL_GameController * controller)
{
    return SDL_GameControllerName(controller);
}



/**
*   @fn int statGamepad(SDL_Joystick * joy, LX_GamepadInfo& info)
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
int statGamepad(SDL_Joystick * joy, LX_GamepadInfo& info)
{
    return gstat(joy,nullptr,info);
}



/**
*   @fn int statGamepad(SDL_GameController * gc, LX_GamepadInfo& info)
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
int statGamepad(SDL_GameController * gc, LX_GamepadInfo& info)
{
    return gstat(nullptr,gc,info);
}


static int gstat(SDL_Joystick * joy, SDL_GameController * gc,
                 LX_GamepadInfo& info)
{
    if(joy != nullptr)
    {
        info.name = nameOf(joy);
        return lx_stat(joy,info);
    }
    else if(gc != nullptr)
    {
        info.name = nameOf(gc);
        return lx_stat(SDL_GameControllerGetJoystick(gc),info);
    }
    else
        return LX_SetError("Invalid joystick/game controller\n");
}



/**
*   @fn std::string gamepadToString(LX_GamepadInfo& info)
*
*   Get the string format of the information structure
*
*   @param info The information structure
*   @return Always returns a valid string
*
*   @note This function never returns an invalid string
*   @warning If info or str is not valid, a segmentation fault will occur
*   @warning str must be long enough to get the entire text.
*
*   @sa statGamepad
*/
std::string gamepadToString(LX_GamepadInfo& info)
{
    ostringstream stream;
    char guid[GUID_SIZE+1];

    memset(&guid,0,GUID_SIZE+1);
    SDL_JoystickGetGUIDString(info.uid,guid,GUID_SIZE);

    stream << endl << " ==== Gamepad Information ==== " << endl << endl
           << "Gamepad - ID : " << info.id << endl
           << "Gamepad - UID : " << guid << endl
           << "Gamepad - Name : " << info.name << endl
           << "Gamepad - Number of Axes : " << info.nb_axis << endl
           << "Gamepad - Number of Balls : " << info.nb_balls << endl
           << "Gamepad - Number of Buttons : " << info.nb_buttons << endl
           << "Gamepad - Number of Hats : " << info.nb_hats << endl;

    return stream.str();
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
*   @return 1 if the cursor is shown, 0 if it is hidden,
*           a negative value on failure
*
*/
int mouseCursorDisplay(int toggle)
{
    return SDL_ShowCursor(toggle);
}


};
