
/*
*   Copyright © 2018 Luxon Jean-Pierre
*   https://gumichan01.github.io/
*
*   LunatiX is a free, SDL2-based library.
*   It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*   luxon.jean.pierre@gmail.com
*/

#ifndef LX_TEXT_HPP_INCLUDED
#define LX_TEXT_HPP_INCLUDED

/**
*   @file Text.hpp
*   @brief The interface of LX_TextInput
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*/

#include <LunatiX/utils/utf8_string.hpp>
#include <memory>


namespace LX_Event
{
class LX_EventHandler;
}


/**
*   @ingroup Event
*   @namespace LX_Text
*   @brief The Text input namespace
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

    LX_RedrawCallback( LX_RedrawCallback& ) = delete;
    LX_RedrawCallback& operator =( LX_RedrawCallback& ) = delete;

public:

    LX_RedrawCallback() noexcept = default;
    /**
    *   @fn virtual void operator ()(UTF8string& u8str, UTF8string& u8comp,
    *                               const bool update, size_t cursor,
    *                               size_t prev_cur) = 0;
    *
    *   Virtual function that update the display of a string
    *   @param [in] u8str The utf-8 encoded string written by the user
    *   @param [in] u8comp The utf-8 encoded string that has been composed
    *   @param [in] update A constant value that specify if the display
    *          of the string has to be updated
    *   @param [in] cursor The current position of the cursor on the string
    *   @param [in] prev_cur The previous position of the cursor on the string
    *
    *   @note 1 — This function must be implemented in a subclass
    *   @note 2 — u8str is the string written by the user
    *   @note 3 — u8comp is the string that is currently composed but
    *          not yet validated by the user (often used for non-latin words)
    */
    virtual void operator ()( UTF8string& u8str, UTF8string& u8comp, const bool update,
                              size_t cursor, size_t prev_cur ) noexcept = 0;

    virtual ~LX_RedrawCallback() = default;
};

class LX_TextInput_;

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
*   - Define a class as a subclass of the pure virtual class *LX_RedrawCallback*.
*   - Define the operator () provided by *LX_RedrawCallback*.
*   - Declare an object of type *LX_TextInput*.
*   - Call the function **LX_TextInput::eventLoop** of this object by giving
*     the callback function in argument.
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
*               LX_Graphics::LX_BlendedTextTexture img(_font, _w);
*
*               _w.clearWindow();
*
*               if(!u8str.utf8_empty())
*               {
*                   img.setText(u8str, 24);
*                   img.setPosition(100, 100);
*                   img.draw();
*               }
*               _w.update();
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
class LX_TextInput final
{
    std::unique_ptr<LX_TextInput_> _timpl;

    LX_TextInput( LX_TextInput& t ) = delete;
    LX_TextInput( LX_TextInput&& t ) = delete;
    LX_TextInput& operator =( LX_TextInput t ) = delete;

public:

    LX_TextInput() noexcept;
    /**
    *   @fn void eventLoop(LX_RedrawCallback& redraw) noexcept
    *   Launch the event loop
    *   @param [in] redraw Callback function to call
    */
    void eventLoop( LX_RedrawCallback& redraw ) noexcept;
    ~LX_TextInput() noexcept;
};

}

#endif // LX_TEXT_HPP_INCLUDED
