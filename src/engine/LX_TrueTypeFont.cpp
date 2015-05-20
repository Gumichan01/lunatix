

/*
*	Copyright (C) 2014-2015 Luxon Jean-Pierre
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
*	@version 0.4
*
*/

#include <SDL2/SDL.h>

#include "LX_Config.hpp"
#include "LX_Graphics.hpp"
#include "LX_TrueTypeFont.hpp"
#include "LX_WindowManager.hpp"
#include "LX_Error.hpp"


using namespace LX_Graphics;


namespace LX_TrueTypeFont{


    /**
    *
    *   @fn LX_Font::LX_Font(SDL_Color *color)
    *
    *   Construct the font with color
    *
    *   @param color The default color font
    *
    *   @note If you do not need to specify the font color, you may put NULL instead of this color
    *   @warning You must initialize the SDL_TTF library setting the TTF flag to 1 in lxsdl.cfg.
    *
    */
    LX_Font::LX_Font(SDL_Color *color)
    {
        // load the configuration
        LX_Configuration *ttf_config = LX_Configuration::getInstance();

        if( ttf_config == NULL)
        {
            font_str = "";
            font_size = LX_TTF_DEFAULT_FONT_SIZE;
        }
        else
        {
            font_str = ttf_config->getFontFile();
            font_size = ttf_config->getFontSize();
        }

        init(font_str,color,font_size);
    }



    /**
    *
    *   @fn LX_Font::LX_Font(std::string font_file, SDL_Color *color)
    *
    *   Construct the font with font file and color
    *
    *   @param font_file The font file you want to use
    *   @param color The default color font
    *
    *   @note If you do not need to specify the font color, you may put NULL
    *   @warning You must initialize the SDL_TTF library setting the TTF flag to 1 in lxsdl.cfg
    *
    */
    LX_Font::LX_Font(std::string font_file, SDL_Color *color)
    {
        init(font_file.c_str(),color,0);
    }


    /**
    *
    *   @fn LX_Font::LX_Font(std::string font_file, SDL_Color *color, int size)
    *
    *  Construct the font with a font file, a color and a size.
    *
    *   @param font_file The font file you want to load
    *   @param color The color font needed
    *   @param size The size of the text you will display
    *
    *   @note If you do not need to specify the font color, you may put NULL instead of this color
    *   @note If you do not need to specify the size, put 0
    *   @warning You must initialize the SDL_TTF library setting the ttf flag to 1 in lxsdl.cfg.
    *
    */
    LX_Font::LX_Font(std::string font_file, SDL_Color *color, int size)
    {
        init(font_file.c_str(),color,size);
    }



    /**
    *
    *   @fn void LX_Font::init(std::string font_file, SDL_Color *color, int size)
    *
    *   This function initializes The LX_TTF instance with a font file, a color and the size.
    *
    *   @param font_file The font file you want to load
    *   @param color The color font needed
    *   @param size The size of the text you will display
    *
    */
    void LX_Font::init(std::string font_file, SDL_Color *color, int size)
    {

        if(size <= 0)
        {
             size = LX_TTF_DEFAULT_FONT_SIZE;
        }

        // Put color if it is not null
        if( color != NULL )
        {
            font_color.r = color->r;
            font_color.g = color->g;
            font_color.b = color->b;
        }
        else
        {
            font_color.r = LX_WHITE_COLOR;
            font_color.g = LX_WHITE_COLOR;
            font_color.b = LX_WHITE_COLOR;
        }
    }


    /**
    *   @fn LX_Font::~LX_Font()
    *
    *   Destroy the instance
    *
    */
    LX_Font::~LX_Font(){}


    /**
    *   @fn int LX_Font::sizeOfText(std::string text, int *w, int *h)
    *
    *   Calculate the resulting surface size of the text rendererd using the default font
    *
    *   @param text The string to size up
    *   @param w The pointer of int to fill in the text width
    *   @param h The pointer of int to fill in the text height
    *
    *   @return A control value, 0 on success, -1 on failure
    *
    */
    int LX_Font::sizeOfText(std::string text, int *w, int *h)
    {
        TTF_Font *ttf = NULL;
        int sz;

        ttf = TTF_OpenFont(font_str.c_str(),font_size);

        if(ttf == NULL)
            return -1;

        sz = sizeOfText(ttf,text.c_str(),w,h);

        TTF_CloseFont(ttf);
        return sz;
    }


    /**
    *   @fn int LX_Font::sizeOfText(TTF_Font *ttf, std::string text, int *w, int *h)
    *
    *   Calculate the resulting surface size of the text rendererd using the font
    *   given in parameter
    *
    *   @param ttf The font you use for the text
    *   @param text The texte string to size up
    *   @param w The pointer to int in which to fille the text width
    *   @param h The pointer to int in which to fille the text height
    *
    *   @return A control value, 0 on success, -1 on failure
    *
    *   @warning If the font is NULL, then you have an undefined behavior
    *
    */
    int LX_Font::sizeOfText(TTF_Font *ttf, std::string text, int *w, int *h)
    {
        return TTF_SizeUTF8(ttf,text.c_str(),w,h);
    }


    /**
    *   @fn SDL_Surface * LX_Font::draw_SolidText(std::string text)
    *
    *   Create an UTF-8 encoded text in solid mode
    *
    *   @param text The string to display
    *
    *   @return An instance of SDL_Surface on success, NULL otherwise
    *
    */
    SDL_Surface * LX_Font::draw_SolidText(std::string text)
    {
        return draw_SolidText(text.c_str(),font_size);
    }


    /**
    *   @fn SDL_Surface * LX_Font::draw_SolidText(std::string text, unsigned int size)
    *
    *   Render the UTF-8 encoded text in solid mode. The size has to be specified
    *
    *   @param text The string to display
    *   @param size The size defined by the user
    *
    *   @return An instance of SDL_Surface on success, NULL otherwise
    *
    */
    SDL_Surface * LX_Font::draw_SolidText(std::string text, unsigned int size)
    {
        return drawText(LX_TTF_SOLID,text.c_str(),0,0,0,size);
    }



    /**
    *   @fn SDL_Surface * LX_Font::draw_ShadedText(std::string text, SDL_Color bg)
    *
    *   Create an UTF-8 encoded text in shaded mode
    *
    *   @param text The string to display
    *   @param bg The background color
    *
    *   @return An instance of SDL_Surface on success, NULL otherwise
    *
    */
    SDL_Surface * LX_Font::draw_ShadedText(std::string text, SDL_Color bg)
    {
        return draw_ShadedText(text.c_str(), bg.r, bg.g, bg.b);
    }


    /**
    *   @fn SDL_Surface * LX_Font::draw_ShadedText(std::string text, Uint8 r, Uint8 g, Uint8 b)
    *
    *   Create an UTF-8 encoded text in shaded mode
    *
    *   @param text The text you want to display
    *   @param r The red channel
    *   @param g The green channel
    *   @param b The blue channel
    *
    *   @return An instance of SDL_Surface on success, NULL otherwise
    *
    */
    SDL_Surface * LX_Font::draw_ShadedText(std::string text, Uint8 r, Uint8 g, Uint8 b)
    {
        return draw_ShadedText(text.c_str(),{r,g,b});
    }


    /**
    *   @fn SDL_Surface * LX_Font::draw_ShadedText(std::string text, Uint8 r, Uint8 g, Uint8 b, unsigned int size)
    *
    *   Render the UTF-8 encoded text in shaded mode. The size has to be specified.
    *
    *   @param text The text you want to display
    *   @param r The red color of the background
    *   @param g The green color of the background
    *   @param b The blue color of the background
    *   @param size The size defined by the user
    *
    *   @return An instance of SDL_Surface on success, NULL otherwise
    *
    */
    SDL_Surface * LX_Font::draw_ShadedText(std::string text, Uint8 r, Uint8 g, Uint8 b, unsigned int size)
    {
        return drawText(LX_TTF_SHADED,text.c_str(),r,g,b,size);
    }



    /**
    *   @fn SDL_Surface * LX_Font::draw_BlendedText(std::string text)
    *
    *   Create an UTF-8 encoded text surface in blended mode
    *
    *   @param text The text you want to display
    *
    *   @return An instance of SDL_Surface on success, NULL otherwise
    *
    */
    SDL_Surface * LX_Font::draw_BlendedText(std::string text)
    {
        return draw_BlendedText(text.c_str(),font_size);
    }



    /**
    *
    *   @fn SDL_Surface * LX_Font::draw_BlendedText(std::string text, unsigned int size)
    *
    *   Render the UTF-8 encoded text in blended mode. The size has to be specified.
    *
    *   @param text The text you want to display
    *   @param size The size defined by the user
    *
    *   @return An instance of SDL_Surface on success, NULL otherwise
    *
    */
    SDL_Surface * LX_Font::draw_BlendedText(std::string text, unsigned int size)
    {
        return drawText(LX_TTF_BLENDED,text.c_str(),0,0,0,size);
    }


    /**
    *   @fn SDL_Surface * LX_Font::drawText(LX_TTF_TypeText type, std::string text, Uint8 r, Uint8 g, Uint8 b, unsigned int size)
    *
    *   Create a text surface according to the type, the color bakground, if necessary, and its size
    *
    *   @param type The type of the text(Solid, Shaded, or Blended)
    *   @param text The string you want to draw
    *   @param r The red color of the background
    *   @param g The green color of the background
    *   @param b The blue color of the background
    *   @param size The size of the text on the window
    *
    *   @return An instance of SDL_Surface on success, NULL otherwise
    *
    *   @note If size is 0, then the default faont size is used
    *   @note You can put any value you want if you do not need to use r,g and b
    *
    */
    SDL_Surface * LX_Font::drawText(LX_TTF_TypeText type, std::string text, Uint8 r, Uint8 g, Uint8 b, unsigned int size)
    {
        TTF_Font *ttf = NULL;
        SDL_Surface *loaded = NULL;


        if(size != font_size && size <= 0)
            ttf = TTF_OpenFont(font_str.c_str(), font_size);
        else
            ttf = TTF_OpenFont(font_str.c_str(), size);


        if(ttf == NULL)
        {
            return loaded;
        }

        // Select the text to draw
        switch(type)
        {
            case LX_TTF_SOLID : loaded = TTF_RenderUTF8_Solid(ttf,text.c_str(), font_color);
                                break;

            case LX_TTF_SHADED : loaded = TTF_RenderUTF8_Shaded(ttf,text.c_str(), font_color, {r,g,b});
                                 break;

            case LX_TTF_BLENDED : loaded = TTF_RenderUTF8_Blended(ttf,text.c_str(), font_color);
                                  break;

            default : break;
        }

        TTF_CloseFont(ttf);

        return loaded;
    }


    /**
    *   @fn SDL_Texture * LX_Font::drawTextToTexture(LX_TTF_TypeText type,std::string text, unsigned int size, int idWindow)
    *
    *   Create a Texture from a text according to the type and the size
    *
    *   @param type The type of the text(Solid, Shaded, or Blended)
    *   @param text The string you want to draw
    *   @param size The size of the text on the window
    *   @param idWindow The ID of the window
    *
    *   @return An instance of SDL_Texture on success, NULL if the window is not valid
    *               or if something wrong happened
    *
    */
    SDL_Texture * LX_Font::drawTextToTexture(LX_TTF_TypeText type,std::string text, unsigned int size, int idWindow)
    {
        SDL_Surface *surface =  NULL;
        SDL_Texture *texture = NULL;

        LX_Window * target_window = NULL;
        SDL_Renderer *target_render = NULL;

        if(idWindow < 0 )
            return NULL;

        surface = drawText(type,text.c_str(),0,0,0,size);   // Get the surface

        if(surface == NULL)
            return texture;

        // Get the window to use the renderer
        target_window = LX_WindowManager::getInstance()->getWindow(idWindow);

        if(target_window == NULL)
        {
                SDL_FreeSurface(surface);
                return NULL;
        }

        target_render = target_window->getRenderer();

        // Get the texture
        texture = SDL_CreateTextureFromSurface(target_render,surface);

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
        if( color != NULL )
        {
            font_color.r = color->r;
            font_color.g = color->g;
            font_color.b = color->b;
        }
    }


};



