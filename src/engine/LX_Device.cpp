

/*
*	Copyright (C) 2014-2015 Luxon Jean-Pierre
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
*	@brief The LX_Device implementation
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.3
*
*/

#include <cstring>
#include <iostream>
#include <sstream>

#include "LX_Device.hpp"

using namespace std;

namespace LX_Device{


    /**
    *   @fn int numberOfDevices(void)
    *
    *   Count the number of connected devices (joystick and gamepads)
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
    *   @return the name of the joystick, NULL if the pointer is not valid
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
    *   @return the name of the game controller, NULL if the pointer is not valid
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

        if(joy == NULL || info == NULL)
            return -1;

        // Get information
        info->id = SDL_JoystickInstanceID(joy);
        tmp = SDL_JoystickName(joy);

        if(tmp == NULL)
            return -1;

        strcpy(info->name,tmp);
        info->numAxis = SDL_JoystickNumAxes(joy);
        info->numBalls = SDL_JoystickNumBalls(joy);
        info->numButtons = SDL_JoystickNumButtons(joy);
        info->numHats = SDL_JoystickNumHats(joy);


        if(info->id == -1 || info->numAxis == -1
            || info->numBalls == -1 || info->numButtons == -1 || info->numHats == -1)
            return -1;

        return 0;
    }



    /**
    *   @fn int statGamepad(SDL_GameController * gp, LX_GamepadInfo *info)
    *
    *   Get the name of a game controller
    *
    *   @param gp The game controller to get information from
    *   @param info The structure to store information
    *
    *   @return 0 if the game controller is valid and the function got information
    *               -1 on failure
    *
    */
    int statGamepad(SDL_GameController * gp, LX_GamepadInfo *info)
    {
        return statGamepad(SDL_GameControllerGetJoystick(gp),info);
    }


    /**
    *   @fn const char * gamepadToString(LX_GamepadInfo *info)
    *
    *   Get the string format of the information structure
    *
    *   @param info The structure you want to get the string format from
    *
    *   @return A valid C string
    *
    *   @note This function never returns NULL
    *   @warning If info is NULL, a segmentation fault will occur
    *
    */
    const char * gamepadToString(LX_GamepadInfo *info)
    {
        ostringstream stream;

        stream << endl << " ==== Joystick Information ==== " << endl << endl
                << "Joystick ID : " << info->id << endl
                << "Joystick Name : " << info->name << endl
                << "Joystick Number of Axes : " << info->numAxis << endl
                << "Joystick Number of Balls : " << info->numBalls << endl
                << "Joystick Number of Buttons : " << info->numButtons << endl
                << "Joystick Number of Hats : " << info->numHats << endl;

        return stream.str().c_str();
    }


    /**
    *   @fn int mouseCursorDisplay(int toggle)
    *
    *   Define is the cursor will be shown or not
    *
    *   @param toggle Tha value : 1 to show it, 0 to hide, -1 to get the current state
    *
    *   @return 1 if the cursor is shown, 0 if it is hidden, a negative value on failure
    *
    */
    int mouseCursorDisplay(int toggle)
    {
        return SDL_ShowCursor(toggle);
    }


};




