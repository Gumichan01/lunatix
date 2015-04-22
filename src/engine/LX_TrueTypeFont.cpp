

/*
*	Copyright (C) 2014-2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX-engine is a SDL-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_Font.cpp
*	@brief The LunatiX_engine True type Font (TTF) modules.
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.2
*	@date July 15th, 2014
*
*
*
*/

#include <SDL2/SDL.h>

#include "LX_Config.hpp"
#include "LX_Renderer.hpp"
#include "LX_TrueTypeFont.hpp"



namespace LX_TrueTypeFont{


    /**
    *
    *   @fn LX_Font::LX_Font(SDL_Color *color)
    *
    *   This constructor initializes The font with a color.
    *
    *   @param color the default color font
    *
    *   @note If you do not need to specify the font color, you may put NULL instead of this color
    *   @warning You must initialize the SDL_TTF library setting the ttf flag to 1 in lxsdl.cfg.
    *            Otherwise, a LX_TTF_exception will be occured.
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
    *   This constructor initializes The LX_TTF module with a font file and color.
    *
    *   @param font_file the font file you want to use
    *   @param color the default color font
    *
    *   @note If you do not need to specify the font color, you may put NULL
    *   @warning You must initialize the SDL_TTF library setting the ttf flag to 1 in lxsdl.cfg.
    *            Otherwise, a LX_TTF_exception will be occured.
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
    *   This constructor initializes The LX_TTF module with a font file, a color and the size.
    *
    *   @param font_file the font file you want to load
    *   @param color the color font needed
    *   @param size the size of the text you will display
    *
    *   @note If you do not need to specify the font color, you may put NULL instead of this color
    *   @note If you do not need to specify the size, put 0
    *   @warning You must initialize the SDL_TTF library setting the ttf flag to 1 in lxsdl.cfg.
    *            Otherwise, a LX_TTF_exception will be occured.
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
    *   @param font_file the font file you want to load
    *   @param color the color font needed
    *   @param size the size of the text you will display
    *
    *   @note If you do not need to specify the font color, you may put NULL
    *   @note If you do not need to specify the size, put 0
    *   @warning You must initialize the SDL_TTF library setting the ttf flag to 1 in lxsdl.cfg.
    *            Otherwise, a LX_TTF_exception will be occured.
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
    *   @param text the texte string to size up
    *   @param w the pointer to int in which to fille the text width
    *   @param h he pointer to int in which to fille the text height
    *
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
    *   given in in parameter
    *
    *   @param ttf the font you use for the text
    *   @param text the texte string to size up
    *   @param w the pointer to int in which to fille the text width
    *   @param h he pointer to int in which to fille the text height
    *
    *   @warning If the ttf font is NULL, then a segmentation fault will occur
    *
    */
    int LX_Font::sizeOfText(TTF_Font *ttf, std::string text, int *w, int *h)
    {
        return TTF_SizeUTF8(ttf,text.c_str(),w,h);
    }


    /**
    *
    *   @fn SDL_Surface * LX_Font::draw_SolidText(std::string text)
    *
    *   Create an UTF-8 encoded text in solid mode
    *
    *   @param text the text you want to display
    *
    *   @return a SDL_surface on success , NULL otherwise
    *
    */
    SDL_Surface * LX_Font::draw_SolidText(std::string text)
    {
        return draw_SolidText(text.c_str(),font_size);
    }


    /**
    *
    *   @fn SDL_Surface * LX_Font::draw_SolidText(std::string text, unsigned int size)
    *
    *   Render the UTF-8 encoded text in solid mode. The size has to be specified.
    *
    *   @param text the text you want to display
    *   @param size the size defined by the user
    *
    *   @return a SDL_surface on success, NULL otherwise
    *
    */
    SDL_Surface * LX_Font::draw_SolidText(std::string text, unsigned int size)
    {
        return drawText(LX_TTF_SOLID,text.c_str(),0,0,0,size);
    }



    /**
    *
    *   @fn SDL_Surface * LX_Font::draw_ShadedText(std::string text, SDL_Color bg)
    *
    *   Create an UTF-8 encoded text in shaded mode
    *
    *   @param text the text you want to display
    *   @param bg the background color
    *
    *   @return a SDL_surface on success , NULL otherwise on errors
    *
    */
    SDL_Surface * LX_Font::draw_ShadedText(std::string text, SDL_Color bg)
    {
        return draw_ShadedText(text.c_str(), bg.r, bg.g, bg.b);
    }


    /**
    *
    *   @fn SDL_Surface * LX_Font::draw_ShadedText(std::string text, Uint8 r, Uint8 g, Uint8 b)
    *
    *   Create an UTF-8 encoded text in shaded mode
    *
    *   @param text the text you want to display
    *   @param r the red channel
    *   @param g the green channel
    *   @param b the blue channel
    *
    *   @return a SDL_surface on success , NULL otherwise on errors
    *
    */
    SDL_Surface * LX_Font::draw_ShadedText(std::string text, Uint8 r, Uint8 g, Uint8 b)
    {
        return draw_ShadedText(text.c_str(),{r,g,b});
    }


    /**
    *
    *   @fn SDL_Surface * LX_Font::draw_ShadedText(std::string text, Uint8 r, Uint8 g, Uint8 b, unsigned int size)
    *
    *   Render the UTF-8 encoded text in solid mode. The size has to be specified.
    *
    *   @param text the text you want to display
    *   @param r the red color of the background
    *   @param g the green color of the background
    *   @param b the blue color of the background
    *   @param size the size defined by the user
    *
    *   @return a SDL_surface on success, NULL otherwise
    *
    */
    SDL_Surface * LX_Font::draw_ShadedText(std::string text, Uint8 r, Uint8 g, Uint8 b, unsigned int size)
    {
        return drawText(LX_TTF_SHADED,text.c_str(),r,g,b,size);
    }



    /**
    *
    *   @fn SDL_Surface * LX_Font::draw_BlendedText(std::string text)
    *
    *   Create an UTF-8 encoded text surface in blended mode
    *
    *   @param text the text you want to display
    *
    *   @return a SDL_surface on success , NULL otherwise
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
    *   Render the UTF-8 encoded text in solid mode. The size has to be specified.
    *
    *   @param text the text you want to display
    *   @param size the size defined by the user
    *
    *   @return a SDL_surface on success, NULL otherwise
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
    *   @param type the type of the text(Solid, Shaded, or Blended)
    *   @param text the string you want to draw
    *   @param r the red color of the background
    *   @param g the green color of the background
    *   @param b the blue color of the background
    *   @param size the size of the text on the window
    *
    *   @return a SDL_surface on success, NULL otherwise
    *
    *   @note : if size is 0, then the font_size is used
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

        // What kind of text do you want to draw ?
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
    *   @fn SDL_Texture * LX_Font::drawTextToTexture(LX_TTF_TypeText type,std::string text, unsigned int size)
    *
    *   Create a Texture from a text according to the type and the size
    *
    *   @param type the type of the text(Solid, Shaded, or Blended)
    *   @param text the string you want to draw
    *   @param size the size of the text on the window
    *
    *   @return a SDL_Texture on success, NULL otherwise
    *
    */
    SDL_Texture * LX_Font::drawTextToTexture(LX_TTF_TypeText type,std::string text, unsigned int size)
    {
        SDL_Surface *surface =  NULL;
        SDL_Texture *texture = NULL;

        surface = drawText(type,text.c_str(),0,0,0,size);   // Get the surface

        if(surface == NULL)
            return texture;

        // Get the texture
        texture = SDL_CreateTextureFromSurface(LX_Graphics::LX_Renderer::getInstance()->getRenderer(),surface);

        SDL_FreeSurface(surface);   // Clean the surface

        return texture;
    }


    /**
    *
    *   @fn void LX_Font::setColor(SDL_Color *color)
    *
    *   This function sets the new color of texts.
    *
    *   @param color the new color
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


























