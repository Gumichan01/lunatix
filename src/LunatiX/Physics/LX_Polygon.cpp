
/*
*   Copyright © 2017 Luxon Jean-Pierre
*   https://gumichan01.github.io/
*
*   LunatiX is a free, SDL2-based library.
*   It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*   luxon.jean.pierre@gmail.com
*/

/**
*   @file LX_Polygon.cpp
*   @brief The Implementation of the polygon
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.10
*/

#include <LunatiX/LX_Polygon.hpp>
#include <LunatiX/LX_Physics.hpp>
#include <LunatiX/LX_Vector2D.hpp>
#include <LunatiX/LX_Hitbox.hpp>
#include <vector>

using namespace std;


namespace
{
inline int sumx_(const LX_Physics::LX_Point& p, const LX_Physics::LX_Point& q)
{
    return p.x + q.x;
}

inline int sumy_(const LX_Physics::LX_Point& p, const LX_Physics::LX_Point& q)
{
    return p.y + q.y;
}

inline int cross_(const LX_Physics::LX_Point& p, const LX_Physics::LX_Point& q)
{
    return p.x * q.y - p.y * q.x;
}
};


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
    LX_Points_ _points;     /* A sequence of LX_Point objects   */
    bool _convex;           /* If the polygon is convex         */

    void convexity_()
    {
        LX_Vector2D AO;
        LX_Vector2D OB;

        float sign = 0.0f;
        bool haveSign = false;
        const auto pbeg =_points.begin();
        const auto pend =_points.end();

        for(auto it = pbeg; it != pend; it++)
        {
            AO = LX_Vector2D(*it,(it == pbeg ? *(pend - 1) : *(it - 1)));
            OB = LX_Vector2D((it == pend-1 ? *pbeg : *(it + 1)),*it);
            int cross_product = static_cast<int>(vector_product(AO,OB));

            if(!haveSign)
            {
                if(cross_product > 0)
                    sign = 1.0f;
                else if(cross_product < 0)
                    sign = -1.0f;
                else
                {
                    _convex = false;
                    return;
                }

                haveSign = true;
            }
            else
            {
                if((sign > 0.0f && cross_product < 0)
                        || (sign < 0.0f && cross_product > 0))
                {
                    _convex = false;
                    return;
                }
            }
        }

        _convex = true;
    }

    float area_() const
    {
        float sum = 0.0f;
        const auto pbeg = _points.begin();
        const auto pend = _points.end();

        for(auto it = pbeg; it != pend; it++)
        {
            if(it == pend - 1)
            {
                sum += cross_(*it,*pbeg);
            }
            else
            {
                sum += cross_(*it,*(it + 1));
            }
        }
        return (sum / 2.0f);
    }

    bool calculateCentroid_(LX_Point& p) const
    {
        const auto pbeg = _points.begin();
        const auto pend = _points.end();
        float sum_x = 0, sum_y = 0;
        const float p6_area = 6 * area_();

        if(p6_area <= 0.0f) // self-intersecting polygon
            return false;

        for(auto it = pbeg; it != pend; it++)
        {
            if(it == pend - 1)
            {
                sum_x += sumx_(*it,*pbeg) * cross_(*it,*pbeg);
                sum_y += sumy_(*it,*pbeg) * cross_(*it,*pbeg);
            }
            else
            {
                sum_x += sumx_(*it,*(it + 1)) * cross_(*it,*(it + 1));
                sum_y += sumy_(*it,*(it + 1)) * cross_(*it,*(it + 1));
            }
        }

        p.x = static_cast<int>(sum_x/p6_area);
        p.y = static_cast<int>(sum_y/p6_area);
        return true;
    }

public:

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

    LX_AABB getEnclosingBox() const
    {
        if(_points.size() < 3)
            throw LX_PolygonException("LX_Polygon: Cannot get the enclosing bounding box");

        int xm, ym;
        LX_AABB aabb = {0,0,0,0};
        aabb.x = _points.at(0).x;
        aabb.y = _points.at(0).y;
        xm = _points.at(0).x;
        ym = _points.at(0).y;

        for(auto it = _points.begin(); it != _points.end(); it++)
        {
            LX_Physics::LX_Point p(*it);

            // X
            if(p.x < aabb.x)
                aabb.x = p.x;

            if(p.x > xm)
                xm = p.x;

            // Y
            if(p.y < aabb.y)
                aabb.y = p.y;

            if(p.y > ym)
                ym = p.y;
        }

        aabb.w = xm - aabb.x;
        aabb.h = ym - aabb.y;

        return aabb;
    }


    bool isConvex() const
    {
        return _convex;
    }


    void move(const float vx, const float vy)
    {
        const int nvx = static_cast<int>(vx);
        const int nvy = static_cast<int>(vy);
        const auto pend = _points.end();

        for(auto it = _points.begin(); it != pend; it++)
        {
            movePoint(*it,nvx,nvy);
        }
    }

    void moveTo(int xpos, int ypos)
    {
        const LX_Point p(xpos,ypos);
        LX_Point centroid;

        if(!calculateCentroid_(centroid))
        {
            // self-intersecting polygon. The movement is less accurate
            const auto pend = _points.end();
            /// @todo fix it — incorrect
            for(auto it = _points.begin(); it != pend; it++)
            {
                const LX_Vector2D iv(*it,p);
                move(iv.vx,iv.vy);
            }
        }
        else
        {
            // Normal case.→ accurate movement
            const LX_Vector2D v(centroid,p);
            move(v.vx,v.vy);
        }
    }

    ~LX_Polygon_() = default;
};


/* Polygon, public functions */

LX_Polygon::LX_Polygon() : _polyimpl(new LX_Polygon_()) {}
LX_Polygon::~LX_Polygon() {}


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

LX_AABB LX_Polygon::getEnclosingBox() const
{
    return _polyimpl->getEnclosingBox();
}


bool LX_Polygon::isConvex() const
{
    return _polyimpl->isConvex();
}


void LX_Polygon::move(const float vx, const float vy)
{
    _polyimpl->move(vx,vy);
}


void LX_Polygon::move(const LX_Vector2D& v)
{
    _polyimpl->move(v.vx,v.vy);
}


void LX_Polygon::moveTo(int xpos, int ypos)
{
    _polyimpl->moveTo(xpos,ypos);
}

};
