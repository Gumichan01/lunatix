#ifndef LX_TEXT_HPP_INCLUDED
#define LX_TEXT_HPP_INCLUDED

/*
*    Copyright (C) 2016 Luxon Jean-Pierre
*    gumichan01.olympe.in
*
*    LunatiX is a free, SDL2-based library.
*    It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*    Luxon Jean-Pierre (Gumichan01)
*    luxon.jean.pierre@gmail.com
*/

/**
*    @file LX_Text.hpp
*    @brief The interface of LX_TextInput
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.8
*
*/

#include <LunatiX/utils/utf8_string.hpp>

union SDL_Event;

/**
*   @namespace LX_Text
*   @brief The Text input module
*/
namespace LX_Text
{

/**
*   @class LX_RedrawCallback
*   @brief Function object
*
*   This class defines a callback function as a function object
*
*/
class LX_RedrawCallback
{
public:
    LX_RedrawCallback();

    /**
    *   @fn virtual void operator ()(UTF8string& u8str, size_t cursor = 0) = 0;
    *
    *   Virtual function that must be implemented in a subclass
    *   @param [in] u8str The utf-8 encoded string that will be displayed
    *   @param [in] cursor The position of the cursor on the string
    */
    virtual void operator ()(UTF8string& u8str, size_t cursor = 0) = 0;
    /// Destructor
    virtual ~LX_RedrawCallback();
};

/**
*   @class LX_TextInput
*   @brief Text input class
*
*   LX_TextInput is a class that handles text input. The text input is activated
*   at class intantiation and unactivated at class destruction.
*   This class can handle Unicode string in UTF-8 thanks to
*   [UTF8string](https://github.com/Gumichan01/utf8_string).
*
*   The API provides a callback (*LX_RedrawCallback*) function defined as a function object.
*   This callback was designed to redraw the current window that displays
*   the user-typed text at each user input.
*   It is not necessary to handle text input events, because *LX_TextInput* does that properly.
*
*   So, in order to use LX_TextInput, you need to:
*   - Define a class as a subclass of the pure virtuel class *LX_RedrawCallback*.
*   - Define the operator () provided by *LX_RedrawCallback*.
*   - Declare an object of type *LX_TextInput*.
*   - Call the function **LX_TextInput::eventLoop** of this object giving the callback function in argument.
*
*   Example of code :
*
*       // Define and implement a subclass of LX_RedrawCallback
*       class FuncDraw : public LX_RedrawCallback
*       {
*           LX_Win::LX_Window& _w;
*           LX_TrueTypeFont::LX_Font _font;
*
*       public:
*
*           ...
*
*           void operator ()(UTF8String& u8str)
*           {
*               LX_Graphics::LX_BlendedTextImage img(_font,_w);
*
*               _w.clearWindow();
*
*               if(!u8str.utf8_empty())
*               {
*                   img.setText(u8str,24);
*                   img.setPosition(100,100);
*                   img.draw();
*               }
*                   _w.update();
*           }
*
*           ...
*
*       }
*
*       ...
*
*       // In a function that uses the callback
*
*       ...
*
*       void textInput()
*       {
*           FuncDraw callbck;
*           LX_TextInput input;
*           input.eventLoop(callbck);
*       }
*
*   LX_TextInput also support clipboard handling.
*/

class LX_TextInput
{
    UTF8string _u8text;
    size_t _cursor;
    bool _done;
    bool _draw;

    LX_TextInput(LX_TextInput& t);
    LX_TextInput(LX_TextInput&& t);
    LX_TextInput& operator =(LX_TextInput t);

    // Save a text in the clipboard get it from it
    void save_();
    void paste_();

    // Input
    void keyboardInput_(SDL_Event& ev);
    void textInput_(SDL_Event& ev);
    void textEdit_(SDL_Event& ev);

    // Operation on the string
    void u8stringInput_(UTF8string& ntext);
    void utf8Pop_();
    void backslashKey_();
    void deleteKey_();

public:

    /// Constructor
    LX_TextInput();
    /**
    *   @fn void eventLoop(LX_RedrawCallback& redraw)
    *   Launch the event loop
    *   @param [in] redraw Callback function to call
    */
    void eventLoop(LX_RedrawCallback& redraw);
    /// Destructor
    ~LX_TextInput();
};

};

#endif // LX_TEXT_HPP_INCLUDED
