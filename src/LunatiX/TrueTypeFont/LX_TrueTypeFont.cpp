
/*
*	Copyright (C) 2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX Engine is a SDL-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_TrueTypeFont.cpp
*	@brief The LunatiX Engine True type Font (TTF) implementation.
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.6
*
*/

#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_render.h>

#include <LunatiX/LX_Config.hpp>
#include <LunatiX/LX_Graphics.hpp>
#include <LunatiX/LX_TrueTypeFont.hpp>
#include <LunatiX/LX_Window.hpp>
#include <LunatiX/LX_WindowManager.hpp>
#include <LunatiX/LX_Error.hpp>
#include <LunatiX/LX_FileBuffer.hpp>
#include <LunatiX/LX_FileIO.hpp>


using namespace LX_Graphics;
using namespace LX_FileIO;


namespace LX_TrueTypeFont
{


/**
*
*   @fn LX_Font::LX_Font(SDL_Color& color, unsigned int size)
*
*   Construct the font with color and the size of the text
*
*   @param color The default color font
*   @param size the size of the text
*
*   @note   If size is 0, then the default value define in the configuratnion
*           file is used.
*
*   @warning    You must initialize the SDL_TTF library
*               setting the TTF flag to 1 in lxsdl.cfg.
*
*   @exception LX_FileIO::IOException if the file cannot be loaded
*
*/
LX_Font::LX_Font(SDL_Color& color, unsigned int size)
    : font_str(""), font_size(size),
    font_color(color), font_buffer(NULL)
{
    // Load the configuration
    LX_Configuration *ttf_config = LX_Configuration::getInstance();

    if(ttf_config != NULL)
    {
        font_str = ttf_config->getFontFile();

        if(font_size == 0)
            font_size = ttf_config->getFontSize();
    }

    createbuffer();
}



/**
*
*   @fn LX_Font::LX_Font(string font_file, SDL_Color& color)
*
*   Construct the font with font file and color
*
*   @param font_file The font file you want to use
*   @param color The default color font
*
*   @warning    You must initialize the SDL_TTF library
*               setting the TTF flag to 1 in lxsdl.cfg
*
*   @exception LX_FileIO::IOException if the file cannot be loaded
*
*/
LX_Font::LX_Font(string font_file, SDL_Color& color)
    : font_str(font_file), font_size(LX_TTF_DEFAULT_FONT_SIZE),
    font_color(color), font_buffer(NULL)
{
    createbuffer();
}


/**
*
*   @fn LX_Font::LX_Font(string font_file, SDL_Color& color, unsigned int size)
*
*  Construct the font with a font file, a color and a size.
*
*   @param font_file The font file you want to load
*   @param color The color font needed
*   @param size The size of the text to display
*
*   @warning    You must initialize the SDL_TTF library setting
*               the ttf flag to 1 in lxsdl.cfg.
*
*   @exception LX_FileIO::IOException if the file cannot be loaded
*
*/
LX_Font::LX_Font(string font_file, SDL_Color& color, unsigned int size)
    : font_str(font_file), font_size(LX_TTF_DEFAULT_FONT_SIZE),
    font_color(color), font_buffer(NULL)
{
    createbuffer();
}


/*
*
*   This private function creates a file buffer from font_str.
*   This function can throw an IException instance if the buffer cannot
*   be loaded.
*
*/
void LX_Font::createbuffer()
{
    font_buffer = new LX_FileBuffer(font_str.c_str());
}


/**
*   @fn LX_Font::~LX_Font()
*
*   Destroy the instance
*
*/
LX_Font::~LX_Font()
{
    delete font_buffer;
}


/**
*   @fn int LX_Font::sizeOfText(string text, int& w, int& h)
*
*   Calculate the resulting surface size of the text rendererd using the default font
*
*   @param text The string to size up
*   @param w The reference of an integral to fill in the text width
*   @param h The reference of an integral to fill in the text height
*
*   @return A control value, 0 on success, -1 on failure
*
*/
int LX_Font::sizeOfText(string text, int& w, int& h)
{
    return sizeOfText(text.c_str(),font_size,w,h);
}


/**
*   @fn int LX_Font::sizeOfText(string text, int size, int& w, int& h)
*
*   Calculate the resulting surface size of the text rendererd using the default font
*
*   @param text The string to size up
*   @param size The size of the text to be used when you load the texture
*   @param w The reference of an integral to fill in the text width
*   @param h The reference of an integral to fill in the text height
*
*   @return A control value, 0 on success, -1 on failure
*
*/
int LX_Font::sizeOfText(string text, int size, int& w, int& h)
{
    TTF_Font *ttf = NULL;
    int sz;

    ttf = createInternalFont(size);

    if(ttf == NULL)
        return -1;

    sz = sizeOfText(ttf,text.c_str(),w,h);

    TTF_CloseFont(ttf);
    ttf = NULL;
    return sz;
}



/*
*
*   Calculate the resulting surface size of the text to display
*   using the font given in parameter
*
*/
int LX_Font::sizeOfText(TTF_Font *ttf, string text, int& w, int& h)
{
    return TTF_SizeUTF8(ttf,text.c_str(),&w,&h);
}


/**
*   @fn SDL_Surface * LX_Font::drawSolidText(string text)
*
*   Create an UTF-8 encoded text in solid mode
*
*   @param text The string to display
*
*   @return An instance of SDL_Surface on success, a null pointer otherwise
*
*/
SDL_Surface * LX_Font::drawSolidText(string text)
{
    if(font_size == 0)
    {
        LX_SetError("LX_Font::drawBlendetText: cannot fraw a text with a null size");
        return NULL;
    }

    return drawSolidText(text.c_str(),font_size);
}


/**
*   @fn SDL_Surface * LX_Font::drawSolidText(string text, unsigned int size)
*
*   Render the UTF-8 encoded text in solid mode. The size has to be specified
*
*   @param text The string to display
*   @param size The size defined by the user
*
*   @return An instance of SDL_Surface on success, a null pointer otherwise
*
*   @note   The size does not change anything when the text is displayed using
*           the display method with a renderer and texutres.
*
*/
SDL_Surface * LX_Font::drawSolidText(string text, unsigned int size)
{
    return drawText(LX_TTF_SOLID,text.c_str(),size);
}


/**
*   @fn SDL_Surface * LX_Font::drawShadedText(string text, SDL_Color bg)
*
*   Create an UTF-8 encoded text in shaded mode
*
*   @param text The string to display
*   @param bg The background color
*
*   @return An instance of SDL_Surface on success, a null pointer otherwise
*
*/
SDL_Surface * LX_Font::drawShadedText(string text, SDL_Color bg)
{
    if(font_size == 0)
    {
        LX_SetError("LX_Font::drawBlendetText: cannot fraw a text with a null size");
        return NULL;
    }

    return drawShadedText(text.c_str(), bg.r, bg.g, bg.b);
}


/**
*   @fn SDL_Surface * LX_Font::drawShadedText(string text, Uint8 r, Uint8 g, Uint8 b)
*
*   Create an UTF-8 encoded text in shaded mode
*
*   @param text The text you want to display
*   @param r The red channel
*   @param g The green channel
*   @param b The blue channel
*
*   @return An instance of SDL_Surface on success, a null pointer otherwise
*
*/
SDL_Surface * LX_Font::drawShadedText(string text, Uint8 r, Uint8 g, Uint8 b)
{
    if(font_size == 0)
    {
        LX_SetError("LX_Font::drawBlendetText: cannot fraw a text with a null size");
        return NULL;
    }

    return drawText(LX_TTF_SHADED,text.c_str(),font_size,r,g,b);
}


/**
*   @fn SDL_Surface * LX_Font::drawShadedText(string text, Uint8 r, Uint8 g,
                                              Uint8 b, unsigned int size)
*
*   Render the UTF-8 encoded text in shaded mode. The size has to be specified.
*
*   @param text The text you want to display
*   @param r The red color of the background
*   @param g The green color of the background
*   @param b The blue color of the background
*   @param size The size defined by the user
*
*   @return An instance of SDL_Surface on success, a null pointer otherwise
*
*   @note   The size does not change anything when the text is displayed using
*           the display method with a renderer and texutres.
*
*/
SDL_Surface * LX_Font::drawShadedText(string text, Uint8 r, Uint8 g, Uint8 b,
                                      unsigned int size)
{
    return drawText(LX_TTF_SHADED,text.c_str(),size,r,g,b);
}


/**
*   @fn SDL_Surface * LX_Font::drawBlendedText(string text)
*
*   Create an UTF-8 encoded text surface in blended mode
*
*   @param text The text you want to display
*
*   @return An instance of SDL_Surface on success, a null pointer otherwise
*
*/
SDL_Surface * LX_Font::drawBlendedText(string text)
{
    if(font_size == 0)
    {
        LX_SetError("LX_Font::drawBlendetText: cannot fraw a text with a null size");
        return NULL;
    }

    return drawBlendedText(text.c_str(),font_size);
}


/**
*
*   @fn SDL_Surface * LX_Font::drawBlendedText(string text, unsigned int size)
*
*   Render the UTF-8 encoded text in blended mode. The size has to be specified.
*
*   @param text The text you want to display
*   @param size The size defined by the user
*
*   @return An instance of SDL_Surface on success, a null pointer otherwise
*
*   @note   The size does not change anything when the text is displayed using
*           the display method with a renderer and texutres.
*
*/
SDL_Surface * LX_Font::drawBlendedText(string text, unsigned int size)
{
    return drawText(LX_TTF_BLENDED,text.c_str(),size);
}


/*
*   Create a text surface according to the type,
*   the color bakground, if necessary, and its size
*
*   If size is 0, then the font size set by the user is used
*   r, g, b and size are optionnal in this private function.
*
*
*/
SDL_Surface * LX_Font::drawText(LX_TTF_TypeText type, string text,
                                unsigned int size,Uint8 r, Uint8 g, Uint8 b)
{
    TTF_Font *ttf = NULL;
    SDL_Surface *loaded = NULL;

    if(size == 0)
    {
        LX_SetError("drawText: Invalid size, must be a positive value");
        return NULL;
    }
    else
        ttf = createInternalFont(size);

    if(ttf == NULL)
        return loaded;

    // Select the text to draw
    switch(type)
    {
        case LX_TTF_SOLID :
            loaded = TTF_RenderUTF8_Solid(ttf,text.c_str(),font_color);
            break;

        case LX_TTF_SHADED :
            loaded = TTF_RenderUTF8_Shaded(ttf,text.c_str(),font_color,{r,g,b});
            break;

        case LX_TTF_BLENDED :
            loaded = TTF_RenderUTF8_Blended(ttf,text.c_str(),font_color);
            break;

        default :
            break;
    }

    TTF_CloseFont(ttf);
    return loaded;
}

/*
*   Create an internal and temporal font
*   according to the font file in the class
*   or the file buffer if it exists
*/
TTF_Font * LX_Font::createInternalFont(unsigned int size)
{
    if(font_buffer == NULL)
        return NULL;        // This code will normally never be executed

    // The font buffer exists
    return font_buffer->getFontFromBuffer(size);
}


/**
*   @fn SDL_Texture * LX_Font::drawTextToTexture(LX_TTF_TypeText type,
                                                 string text, unsigned int size,
                                                 int idWindow)
*
*   Create a Texture from a text according to the type and the size
*
*   @param type The type of the text(Solid, Shaded, or Blended)
*   @param text The string you want to draw
*   @param size The size of the text on the window
*   @param idWindow The ID of the window to get the renderer from.
*                   It is necessary to load the texture
*
*   @return An instance of SDL_Texture on success, a null pointer
*           if the window is not valid or if something wrong happened
*
*/
SDL_Texture * LX_Font::drawTextToTexture(LX_TTF_TypeText type,string text, unsigned int size, int idWindow)
{
    LX_Window * target_window = NULL;

    if(idWindow < 0)
    {
        LX_SetError("LX_Font::drawTextToTexture(): invalid id");
        return NULL;
    }

    // Get the window to use the renderer
    target_window = LX_WindowManager::getInstance()->getWindow(idWindow);

    return drawTextToTexture(type,text.c_str(),size,target_window);
}


/**
*   @fn SDL_Texture * LX_Font::drawTextToTexture(LX_TTF_TypeText type,string text,
                                                 unsigned int size, LX_Window *win)
*
*   Create a Texture from a text according to the type and the size
*
*   @param type The type of the text(Solid, Shaded, or Blended)
*   @param text The string you want to draw
*   @param size The size of the text on the window
*   @param win The window to get the renderer from.
*                   It is necessary to load the texture
*
*   @return An instance of SDL_Texture on success,
*           a null pointer if the window is not valid
*           or if something wrong happened
*
*/
SDL_Texture * LX_Font::drawTextToTexture(LX_TTF_TypeText type,string text,
                                         unsigned int size, LX_Window *win)
{
    SDL_Surface *surface = NULL;
    SDL_Texture *texture = NULL;

    int black = 0;

    if(win == NULL)
    {
        LX_SetError("LX_Font::drawTextToTexture(): invalid window");
        return NULL;
    }

    surface = drawText(type,text.c_str(),size,black,black,black);

    if(surface == NULL)
        return texture;

    // Get the texture
    texture = SDL_CreateTextureFromSurface(win->getRenderer(),surface);
    SDL_FreeSurface(surface);

    return texture;
}

/**
*   @fn void LX_Font::setColor(SDL_Color *color)
*
*   This function sets the new color of texts.
*
*   @param color The new color
*
*/
void LX_Font::setColor(SDL_Color *color)
{
    if(color != NULL)
    {
        font_color.r = color->r;
        font_color.g = color->g;
        font_color.b = color->b;
    }
}


};
