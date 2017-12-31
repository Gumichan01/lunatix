
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

/**
*   @file LX_Polygon.cpp
*   @brief The Implementation of the polygon
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.12
*/

#include <LunatiX/LX_Polygon.hpp>
#include <LunatiX/LX_Physics.hpp>
#include <LunatiX/LX_Vector2D.hpp>
#include <LunatiX/LX_Hitbox.hpp>
#include <vector>

using namespace std;


namespace
{

inline float sumx_(const LX_Physics::LX_Point& p, const LX_Physics::LX_Point& q) noexcept
{
    return static_cast<float>(p.x + q.x);
}

inline float sumy_(const LX_Physics::LX_Point& p, const LX_Physics::LX_Point& q) noexcept
{
    return static_cast<float>(p.y + q.y);
}

inline float cross_(const LX_Physics::LX_Point& p, const LX_Physics::LX_Point& q) noexcept
{
    return static_cast<float>(p.x * q.y - p.y * q.x);
}

}


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

    void convexity_() noexcept
    {
        LX_Vector2D AO;
        LX_Vector2D OB;

        float sign = 0.0f;
        bool haveSign = false;
        const auto pbeg = _points.begin();
        const auto pend = _points.end();

        for(auto it = pbeg; it != pend; ++it)
        {
            AO = LX_Vector2D(*it, (it == pbeg ? *(pend - 1) : *(it - 1)));
            OB = LX_Vector2D((it == pend-1 ? *pbeg : *(it + 1)), *it);
            int cross_product = static_cast<int>(vector_product(AO, OB));

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

    float area_() const noexcept
    {
        float sum = 0.0f;
        const auto pbeg = _points.begin();
        const auto pend = _points.end();

        for(auto it = pbeg; it != pend; ++it)
        {
            if(it == pend - 1)
                sum += cross_(*it, *pbeg);
            else
                sum += cross_(*it, *(it + 1));
        }
        return (sum / 2.0f);
    }

    bool calculateCentroid_(LX_Point& p) const noexcept
    {
        const float CMULT = 6.0f;
        const auto pbeg = _points.begin();
        const auto pend = _points.end();
        float sum_x = 0, sum_y = 0;
        const float p6_area = CMULT * area_();

        if(p6_area <= 0.0f) // self-intersecting polygon
            return false;

        for(auto it = pbeg; it != pend; ++it)
        {
            if(it == pend - 1)
            {
                sum_x += sumx_(*it, *pbeg) * cross_(*it, *pbeg);
                sum_y += sumy_(*it, *pbeg) * cross_(*it, *pbeg);
            }
            else
            {
                sum_x += sumx_(*it, *(it + 1)) * cross_(*it, *(it + 1));
                sum_y += sumy_(*it, *(it + 1)) * cross_(*it, *(it + 1));
            }
        }

        p.x = static_cast<int>(sum_x / p6_area);
        p.y = static_cast<int>(sum_y / p6_area);
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

    unsigned long numberOfEdges() const noexcept
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

        {
            const LX_Point& p0 = _points.at(0);
            aabb.x = p0.x;
            aabb.y = p0.y;
            xm = p0.x;
            ym = p0.y;
        }

        for(const LX_Point& p: _points)
        {
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


    bool isConvex() const noexcept
    {
        return _convex;
    }


    void move(const float vx, const float vy) noexcept
    {
        const int nvx = static_cast<int>(vx);
        const int nvy = static_cast<int>(vy);

        std::for_each(_points.begin(), _points.end(), [nvx, nvy] (LX_Point& p)
        {
            movePoint(p, nvx, nvy);
        });
    }

    void moveTo(int xpos, int ypos)
    {
        const LX_Point p(xpos, ypos);
        LX_Vector2D v;
        LX_Point centroid;

        if(!calculateCentroid_(centroid))
        {
            // self-intersecting polygon. The movement is less accurate
            const LX_AABB box = getEnclosingBox();
            const LX_Point q(box.x + box.w/2, box.y + box.h/2);
            v = LX_Vector2D(q, p);
        }
        else // Normal case.→ accurate movement
            v = LX_Vector2D(centroid, p);

        move(v.vx, v.vy);
    }

    ~LX_Polygon_() = default;
};


/* Polygon, public functions */

LX_Polygon::LX_Polygon() noexcept: _polyimpl(new LX_Polygon_()) {}
LX_Polygon::~LX_Polygon() {}


void LX_Polygon::addPoint(const int x, const int y)
{
    _polyimpl->addPoint(LX_Point(x, y));
}


void LX_Polygon::addPoint(const LX_Point& p)
{
    _polyimpl->addPoint(p);
}


unsigned long LX_Polygon::numberOfEdges() const noexcept
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


bool LX_Polygon::isConvex() const noexcept
{
    return _polyimpl->isConvex();
}


void LX_Polygon::move(const float vx, const float vy) noexcept
{
    _polyimpl->move(vx, vy);
}


void LX_Polygon::move(const LX_Vector2D& v) noexcept
{
    _polyimpl->move(v.vx, v.vy);
}


void LX_Polygon::moveTo(int xpos, int ypos)
{
    _polyimpl->moveTo(xpos, ypos);
}

void LX_Polygon::moveTo(const LX_Point& p)
{
    _polyimpl->moveTo(p.x, p.y);
}

}
