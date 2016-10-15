

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
#include <LunatiX/LX_Physics.hpp>
#include <LunatiX/LX_Vector2D.hpp>
#include <LunatiX/LX_Hitbox.hpp>
#include <vector>

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


/* Polygon - private implementation */

using LX_Points_ = std::vector<LX_Point>;

class LX_Polygon_
{
    LX_Points_ _points;    /* A sequence of LX_Point objects   */
    bool _convex;                     /* If the polygon is convex         */

    void generateSegments(int i, const int n, LX_Vector2D& AO, LX_Vector2D& OB)
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
    }

    void convexity_()
    {
        // Vectors
        LX_Vector2D AO;
        LX_Vector2D OB;

        bool haveSign = false;
        enum Sign {POSITIVE,NEGATIVE,NONE} s = NONE;
        const unsigned long n = _points.size();

        for(unsigned int i = 0; i < n; i++)
        {
            generateSegments(i,n,AO,OB);
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

public :

    LX_Polygon_() : _convex(false) {}

    void addPoint(const LX_Point& p)
    {
        _points.push_back(p);
        // Update the convexity when the polygon has at least 3 edges
        if(_points.size() >= 3)
            convexity_();
    }

    unsigned long numberOfEdges() const
    {
        return _points.size();
    }


    LX_Point getPoint(const unsigned int index) const
    {
        return _points.at(index);
    }


    bool isConvex() const
    {
        return _convex;
    }


    void move(const float vx, const float vy)
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

    void moveTo(int vx, int vy)
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

    ~LX_Polygon_() = default;
};


/* Polygon, public functions */

LX_Polygon::LX_Polygon() : _polyimpl(new LX_Polygon_()) {}


void LX_Polygon::addPoint(const int x, const int y)
{
    _polyimpl->addPoint(LX_Point(x,y));
}


void LX_Polygon::addPoint(const LX_Point& p)
{
    _polyimpl->addPoint(p);
}


unsigned long LX_Polygon::numberOfEdges() const
{
    return _polyimpl->numberOfEdges();
}


LX_Point LX_Polygon::getPoint(const unsigned int index) const
{
    return _polyimpl->getPoint(index);
}


bool LX_Polygon::isConvex() const
{
    _polyimpl->isConvex();
}


void LX_Polygon::move(const float vx, const float vy)
{
    _polyimpl->move(vx,vy);
}


void LX_Polygon::move(const LX_Vector2D& v)
{
    _polyimpl->move(v.vx,v.vy);
}


void LX_Polygon::moveTo(int vx, int vy)
{
    _polyimpl->moveTo(vx,vy);
}

};
