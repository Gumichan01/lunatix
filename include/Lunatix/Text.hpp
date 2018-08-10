
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

#ifndef TEXT_HPP_INCLUDED
#define TEXT_HPP_INCLUDED

/**
*   @file Text.hpp
*   @brief The interface of TextInput
*   @author Luxon Jean-Pierre(Gumichan01)
*
*/

#include <Lunatix/utils/utf8_string.hpp>
#include <memory>


namespace Event
{
class EventHandler;
}

namespace lx
{

/**
*   @ingroup Event
*   @namespace lx::Text
*   @brief The Text input namespace
*/
namespace Text
{

/**
*   @class RedrawCallback
*   @brief Function object
*
*   This class defines a callback function as a function object
*
*/
class RedrawCallback
{

    RedrawCallback( RedrawCallback& ) = delete;
    RedrawCallback& operator =( RedrawCallback& ) = delete;

public:

    RedrawCallback() noexcept = default;
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

    virtual ~RedrawCallback() = default;
};

class TextInput_;

/**
*   @class TextInput
*   @brief Text input class
*
*   TextInput is a class that handles text input. The text input is activated
*   at class intantiation and unactivated at class destruction.
*   This class can handle Unicode string in UTF-8 thanks to
*   [UTF8string](https://github.com/Gumichan01/utf8_string).
*
*   The API provides a callback (*RedrawCallback*) function defined as a function object.
*   This callback was designed to redraw the current window that displays
*   the user-typed text at each user input.
*   It is not necessary to handle text input events, because *TextInput* does that properly.
*
*   So, in order to use TextInput, you need to:
*   - Define a class as a subclass of the pure virtual class *RedrawCallback*.
*   - Define the operator () provided by *RedrawCallback*.
*   - Declare an object of type *TextInput*.
*   - Call the function **TextInput::eventLoop** of this object by giving
*     the callback function in argument.
*
*   Example of code :
*
*       // Define and implement a subclass of RedrawCallback
*       class FuncDraw : public RedrawCallback
*       {
*           lx::Win::Window& _w;
*           lx::TrueTypeFont::Font _font;
*
*       public:
*
*           ...
*
*           void operator ()(UTF8String& u8str)
*           {
*               lx::Graphics::BlendedTextTexture img(_font, _w);
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
*           TextInput input;
*           input.eventLoop(callbck);
*       }
*
*   TextInput also support clipboard handling.
*/
class TextInput final
{
    std::unique_ptr<TextInput_> m_timpl;

    TextInput( TextInput& t ) = delete;
    TextInput( TextInput&& t ) = delete;
    TextInput& operator =( TextInput t ) = delete;

public:

    TextInput() noexcept;
    /**
    *   @fn void eventLoop(RedrawCallback& redraw) noexcept
    *   Launch the event loop
    *   @param [in] redraw Callback function to call
    */
    void eventLoop( RedrawCallback& redraw ) noexcept;
    ~TextInput() noexcept;
};

}   // Text

}   // lx

#endif // TEXT_HPP_INCLUDED
