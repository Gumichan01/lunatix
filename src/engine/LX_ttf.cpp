

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
*	@file LX_ttf.cpp
*	@brief The LunatiX_engine True type Font (TTF) modules.
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.1
*	@date July 15th, 2014
*
*
*
*/

#include "LX_ttf.h"
#include "LX_graphics.h"

/**
*   @fn LX_TTF_exception(std::string err)
*   Build the LX_TTF_exception class
*   @param err the error string
*/
LX_TTF_exception::LX_TTF_exception(std::string err)
{
    str_err = err;
}


/**
*   @fn const char * what() const throw()
*   Get the error string
*   @return the error string
*/
const char * LX_TTF_exception::what() const throw()
{
    return str_err.c_str();
}


LX_TTF_exception::~LX_TTF_exception() throw(){}



/**
*
*   @fn LX_ttf::LX_ttf(SDL_Color *color)
*
*   This constructor initializes The LX_TTF module with a color.
*
*   @param color the default color font
*
*   @note If you do not need to specify the font color, you may put NULL instead of this color
*   @warning You must initialize the SDL_TTF library setting the ttf flag to 1 in sdl_conf.cfg.
*            Otherwise, a LX_TTF_exception will be occured.
*   @warning An LX_TTF_exception may also be occured if the filename or the font size is invalid
*
*/
LX_ttf::LX_ttf(SDL_Color *color)
{

    // load the configuration
    LX_configuration *ttf_config = LX_configuration::getInstance();

    if( ttf_config == NULL || ttf_config->getTTF_Flag() == 0)
    {
        throw LX_TTF_exception("exception occurred in the LX_ttf constructor : unable to get the instance or invalid flag");
    }

    font_str = ttf_config->getFontFile();
    font_size = ttf_config->getFontSize();

    ttf_config->destroy();

    init(font_str,color,font_size);
}



/**
*
*   @fn LX_ttf::LX_ttf(std::string font_file, SDL_Color *color)
*
*   This constructor initializes The LX_TTF module with a font file and color.
*
*   @param font_file the font file you want to use
*   @param color the default color font
*
*   @note If you do not need to specify the font color, you may put NULL
*   @warning You must initialize the SDL_TTF library setting the ttf flag to 1 in sdl_conf.cfg.
*            Otherwise, a LX_TTF_exception will be occured.
*   @warning An LX_TTF_exception may also be occured if the filename or the font size is invalid
*
*/
LX_ttf::LX_ttf(std::string font_file, SDL_Color *color)
{
    init(font_file.c_str(),color,0);
}


/**
*
*   @fn LX_ttf::LX_ttf(std::string font_file, SDL_Color *color, int size)
*
*   This constructor initializes The LX_TTF module with a font file, a color and the size.
*
*   @param font_file the font file you want to load
*   @param color the color font needed
*   @param size the size of the text you will display
*
*   @note If you do not need to specify the font color, you may put NULL instead of this color
*   @note If you do not need to specify the size, put 0
*   @warning You must initialize the SDL_TTF library setting the ttf flag to 1 in sdl_conf.cfg.
*            Otherwise, a LX_TTF_exception will be occured.
*   @warning An LX_TTF_exception may also be occured if the filename or the font size is invalid
*
*/
LX_ttf::LX_ttf(std::string font_file, SDL_Color *color, int size)
{
    init(font_file.c_str(),color,size);
}



/**
*
*   @fn void LX_ttf::init(std::string font_file, SDL_Color *color, int size)
*
*   This function initializes The LX_TTF instance with a font file, a color and the size.
*
*   @param font_file the font file you want to load
*   @param color the color font needed
*   @param size the size of the text you will display
*
*   @note If you do not need to specify the font color, you may put NULL
*   @note If you do not need to specify the size, put 0
*   @warning You must initialize the SDL_TTF library setting the ttf flag to 1 in sdl_conf.cfg.
*            Otherwise, a LX_TTF_exception will be occured.
*   @warning An LX_TTF_exception may also be occured if the filename or the font size is invalid
*
*/
void LX_ttf::init(std::string font_file, SDL_Color *color, int size)
{
    font = NULL;

    if(size <= 0)
    {
         size = DEFAULT_FONT_SIZE;
    }

    font = TTF_OpenFont(font_file.c_str(), size);

    if(font == NULL)
    {
        throw LX_TTF_exception(TTF_GetError());
    }

    //put color if it is not null
    if( color != NULL )
    {
        font_color.r = color->r;
        font_color.g = color->g;
        font_color.b = color->b;
    }
    else
    {
        font_color.r = WHITE_COLOR;
        font_color.g = WHITE_COLOR;
        font_color.b = WHITE_COLOR;
    }
}



/**
*   @fn LX_ttf::~LX_ttf()
*
*   Destroy the instance
*
*/
LX_ttf::~LX_ttf()
{
    TTF_CloseFont(font);
}


/**
*   @fn int LX_ttf::sizeOfText(std::string text, int *w, int *h)
*
*   Calculate the resulting surface size of the text rendererd using the default font
*
*   @param text the texte string to size up
*   @param w the pointer to int in which to fille the text width
*   @param h he pointer to int in which to fille the text height
*
*   @warning If the default font in LX_ttf is NULL, then a segmentation fault will occur
*
*/
int LX_ttf::sizeOfText(std::string text, int *w, int *h)
{
    return sizeOfText(font,text.c_str(),w,h);
}


/**
*   @fn int LX_ttf::sizeOfText(TTF_Font *ttf, std::string text, int *w, int *h)
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
int LX_ttf::sizeOfText(TTF_Font *ttf, std::string text, int *w, int *h)
{
    return TTF_SizeUTF8(ttf,text.c_str(),w,h);
}


/**
*
*   @fn SDL_Surface * LX_ttf::draw_SolidText(std::string text)
*
*   Create an UTF-8 encoded text in solid mode
*
*   @param text the text you want to display
*
*   @return the new SDL_surface , NULL otherwise
*
*/
SDL_Surface * LX_ttf::draw_SolidText(std::string text)
{
    return TTF_RenderUTF8_Solid(font,text.c_str(), font_color);
}


/**
*
*   @fn SDL_Surface * LX_ttf::draw_SolidText(std::string text, unsigned int size)
*
*   Render the UTF-8 encoded text in solid mode. The size has to be specified.
*
*   @param text the text you want to display
*   @param size the size defined by the user
*
*   @return the new SDL_surface, NULL otherwise
*
*/
SDL_Surface * LX_ttf::draw_SolidText(std::string text, unsigned int size)
{
    return drawText(LX_TTF_SOLID,text.c_str(),0,0,0,size);
}



/**
*
*   @fn SDL_Surface * LX_ttf::draw_ShadedText(std::string text)
*
*   Create an UTF-8 encoded text in shaded mode
*
*   @param text the text you want to display
*   @param bg the background color
*
*   @return the new SDL_surface , NULL otherwise on errors
*
*/
SDL_Surface * LX_ttf::draw_ShadedText(std::string text, SDL_Color bg)
{
    return TTF_RenderUTF8_Shaded(font,text.c_str(), font_color, bg);
}


/**
*
*   @fn SDL_Surface * LX_ttf::draw_ShadedText(std::string text, Uint8 r, Uint8 g, Uint8 b)
*
*   Create an UTF-8 encoded text in shaded mode
*
*   @param text the text you want to display
*   @param r the red channel
*   @param g the green channel
*   @param b the blue channel
*
*   @return the new SDL_surface , NULL otherwise on errors
*
*/
SDL_Surface * LX_ttf::draw_ShadedText(std::string text, Uint8 r, Uint8 g, Uint8 b)
{
    return draw_ShadedText(text.c_str(),{r,g,b});
}


/**
*
*   @fn SDL_Surface * LX_ttf::draw_ShadedText(std::string text, unsigned int size)
*
*   Render the UTF-8 encoded text in solid mode. The size has to be specified.
*
*   @param text the text you want to display
*   @param r the red color of the background
*   @param g the green color of the background
*   @param b the blue color of the background
*   @param size the size defined by the user
*
*   @return the new SDL_surface, NULL otherwise
*
*/
SDL_Surface * LX_ttf::draw_ShadedText(std::string text, Uint8 r, Uint8 g, Uint8 b, unsigned int size)
{
    return drawText(LX_TTF_SHADED,text.c_str(),r,g,b,size);
}



/**
*
*   @fn SDL_Surface * LX_ttf::draw_BlendedText(std::string text)
*
*   Create an UTF-8 encoded text surface in blended mode
*
*   @param text the text you want to display
*
*   @return the new SDL_surface , NULL otherwise
*
*/
SDL_Surface * LX_ttf::draw_BlendedText(std::string text)
{
    return TTF_RenderUTF8_Blended(font,text.c_str(), font_color);
}



/**
*
*   @fn SDL_Surface * LX_ttf::draw_BlendedText(std::string text, unsigned int size)
*
*   Render the UTF-8 encoded text in solid mode. The size has to be specified.
*
*   @param text the text you want to display
*   @param size the size defined by the user
*
*   @return the new SDL_surface, NULL otherwise
*
*/
SDL_Surface * LX_ttf::draw_BlendedText(std::string text, unsigned int size)
{
    return drawText(LX_TTF_BLENDED,text.c_str(),0,0,0,size);
}


/**
*   @fn SDL_Surface * LX_ttf::drawText(Uint8 type,std::string text, Uint8 r, Uint8 g, Uint8 b, unsigned int size)
*
*   Create a text according to the type, the color bakground, if necessary, and its size
*
*   @param type the type of the text(Solid, Shaded, or Blended)
*   @param text the string you want to draw
*   @param r the red color of the background
*   @param g the green color of the background
*   @param b the blue color of the background
*   @param size the size of the text on the window
*
*   @warning If the ttf font is NULL, then a segmentation fault will occur
*
*/
SDL_Surface * LX_ttf::drawText(Uint8 type,std::string text, Uint8 r, Uint8 g, Uint8 b, unsigned int size)
{
    TTF_Font *ttf = NULL;
    SDL_Surface *loaded = NULL;


    ttf = TTF_OpenFont(font_str.c_str(), size);

    if(ttf == NULL)
    {
        std::cerr << "Error occurred in LX_ttf::drawText : " << TTF_GetError() << std::endl;
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

        default :   std::cerr << "Error LX_ttf::drawText :  invalid type - "
                                << type << std::endl;
                    break;
    }

    if(loaded == NULL)
    {
        std::cerr << "Error occurred in LX_ttf::drawText : " << TTF_GetError() << std::endl;
    }

    TTF_CloseFont(ttf);

    return loaded;
}



/**
*
*   @fn void LX_ttf::setTTF_Font(std::string ttf_filename)
*
*   This function resets the font replacing the filen ame and the font.
*
*   @param ttf_filename the new fil name you want to create the font from
*
*/
void LX_ttf::setTTF_Font(std::string ttf_filename)
{
    TTF_Font *newFont = NULL;

    if(!ttf_filename.empty())
    {
        if((newFont = TTF_OpenFont(ttf_filename.c_str(),font_size)) == NULL)
        {
            std::cerr << "Error occurred in LX_ttf::setTTF_Font : "
                        << TTF_GetError() << std::endl;
        }
        else
        {
            font_str.clear();
            font_str.assign(ttf_filename);

            TTF_CloseFont(font);
            font = newFont;
        }
    }

}


/**
*
*   @fn void LX_ttf::setColor(SDL_Color *color)
*
*   This function sets the new color of texts.
*
*   @param color the new color
*
*/
void LX_ttf::setColor(SDL_Color *color)
{
    if( color != NULL )
    {
        font_color.r = color->r;
        font_color.g = color->g;
        font_color.b = color->b;
    }
}





























