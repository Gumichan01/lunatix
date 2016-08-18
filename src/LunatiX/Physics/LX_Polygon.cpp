

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
*    @file LX_Polygon.cpp
*    @brief The Implementation of the polygon
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.8
*
*/

#include <LunatiX/LX_Polygon.hpp>
#include <LunatiX/LX_Vector2D.hpp>
#include <LunatiX/LX_Physics.hpp>

using namespace std;

namespace LX_Physics
{

LX_PolygonException::LX_PolygonException(std::string err) : _string_error(err) {}

LX_PolygonException::LX_PolygonException(const LX_PolygonException& pex)
    : _string_error(pex._string_error) {}

const char * LX_PolygonException::what() const noexcept
{
    return _string_error.c_str();
}

LX_PolygonException::~LX_PolygonException() noexcept {}


/* Polygon */

LX_Polygon::LX_Polygon() : _convex(false) {}


void LX_Polygon::addPoint(const int x, const int y)
{
    addPoint(LX_Point(x,y));
}


void LX_Polygon::addPoint(const LX_Point& p)
{
    _points.push_back(p);
    // Update the convexity when the polygon has at least 3 edges
    if(_points.size() >= 3)
        convexity_();
}


unsigned long LX_Polygon::numberOfEdges(void) const
{
    return _points.size();
}


LX_Point LX_Polygon::getPoint(const unsigned int index) const
{
    return _points.at(index);
}


bool LX_Polygon::isConvex(void) const
{
    return _convex;
}


// Evaluate the convexity of the polygon
void LX_Polygon::convexity_(void)
{
    // Vectors
    LX_Vector2D AO;
    LX_Vector2D OB;

    bool haveSign = false;
    enum Sign {POSITIVE,NEGATIVE,NONE} s = NONE;
    const unsigned long n = _points.size();

    for(unsigned int i = 0; i < n; i++)
    {
        if(i == 0)
        {
            AO = LX_Vector2D(_points[i].x - _points[n-1].x,
                             _points[i].y - _points[n-1].y);
        }
        else
        {
            AO = LX_Vector2D(_points[i].x - _points[i-1].x,
                             _points[i].y - _points[i-1].y);
        }

        if(i == n-1)
        {
            OB = LX_Vector2D(_points[0].x - _points[i].x,
                             _points[0].y - _points[i].y);
        }
        else
        {
            OB = LX_Vector2D(_points[i+1].x - _points[i].x,
                             _points[i+1].y - _points[i].y);
        }

        // Vector product
        int cross_product = static_cast<int>(vector_product(AO,OB));

        if(!haveSign)
        {
            if(cross_product > 0)
                s = POSITIVE;
            else if(cross_product < 0)
                s = NEGATIVE;
            else
            {
                _convex = false;
                return;
            }

            haveSign = true;
        }
        else
        {
            switch(s)
            {
            case POSITIVE :
                if(cross_product < 0)
                {
                    _convex = false;
                    return;
                }
                break;

            case NEGATIVE :
                if(cross_product > 0)
                {
                    _convex = false;
                    return;
                }
                break;

            case NONE :
                break;
            }
        }
    }

    _convex = true;
}


void LX_Polygon::move(const float vx, const float vy)
{
    const int nvx = static_cast<int>(vx), nvy = static_cast<int>(vy);
    const unsigned long n = numberOfEdges();

    movePoint(_points[0],nvx,nvy);
    movePoint(_points[1],nvx,nvy);
    movePoint(_points[2],nvx,nvy);

    for(unsigned int i = 3; i < n; i++)
    {
        movePoint(_points[i],nvx,nvy);
    }
}


void LX_Polygon::move(const LX_Vector2D& v)
{
    move(v.vx, v.vy);
}


void LX_Polygon::moveTo(int vx, int vy)
{
    movePointTo(_points[0],vx,vy);
    movePointTo(_points[1],vx,vy);
    movePointTo(_points[2],vx,vy);

    const unsigned long n = numberOfEdges();

    for(unsigned int i = 3; i < n; i++)
    {
        movePointTo(_points[i],vx,vy);
    }
}

};
