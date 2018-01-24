
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

inline float sumx_(const LX_Physics::LX_FloatPosition& p, const LX_Physics::LX_FloatPosition& q) noexcept
{
    return static_cast<float>(p.x + q.x);
}

inline float sumy_(const LX_Physics::LX_FloatPosition& p, const LX_Physics::LX_FloatPosition& q) noexcept
{
    return static_cast<float>(p.y + q.y);
}

inline float cross_(const LX_Physics::LX_FloatPosition& p, const LX_Physics::LX_FloatPosition& q) noexcept
{
    return static_cast<float>(p.x * q.y - p.y * q.x);
}

}


namespace LX_Physics
{

const unsigned long TRIANGLE_SIDES = 3;

LX_PolygonException::LX_PolygonException(std::string err) : _string_error(err) {}

LX_PolygonException::LX_PolygonException(const LX_PolygonException& pex)
    : _string_error(pex._string_error) {}

const char * LX_PolygonException::what() const noexcept
{
    return _string_error.c_str();
}

LX_PolygonException::~LX_PolygonException() noexcept {}


/* Polygon - private implementation */

using LX_FloatPositions_ = std::vector<LX_FloatPosition>;

class LX_Polygon_
{
    LX_FloatPositions_ _points;     /* A sequence of LX_FloatPosition objects   */
    bool _convex;           /* If the polygon is convex         */

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

    bool calculateCentroid_(LX_FloatPosition& p) const noexcept
    {
        const Float CMULT{6.0f};
        const auto pbeg = _points.begin();
        const auto pend = _points.end();
        Float sum_x{0.0f}, sum_y{0.0f};
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

        p.x = {sum_x / p6_area};
        p.y = {sum_y / p6_area};
        return true;
    }

public:

    LX_Polygon_() : _convex(false) {}

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
            const LX_FloatPosition& ori1 = *it;
            const LX_FloatPosition& img1 = (it == pbeg ? *(pend - 1) : *(it - 1));
            const LX_FloatPosition& ori2 = (it == pend-1 ? *pbeg : *(it + 1));
            const LX_FloatPosition& img2 = ori1;
            AO = LX_Vector2D{img1.x - ori1.x, img1.y - ori1.y};
            OB = LX_Vector2D{img2.x - ori2.x, img2.y - ori2.y};
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


    void addPoint(const LX_FloatPosition& p)
    {
        _points.push_back(p);
    }

    unsigned long numberOfEdges() const noexcept
    {
        return _points.size();
    }


    LX_FloatPosition getPoint(const unsigned int index) const
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
            const LX_FloatPosition& p0 = _points.at(0);
            aabb.x = p0.x;
            aabb.y = p0.y;
            xm = p0.x;
            ym = p0.y;
        }

        for(const LX_FloatPosition& p: _points)
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


    void _move(const LX_Vector2D& v) noexcept
    {
        std::for_each(_points.begin(), _points.end(), [&v] (LX_FloatPosition& p)
        {
            movePoint(p, v);
        });
    }

    void moveTo(const LX_FloatPosition& p)
    {
        LX_FloatPosition centroid;

        if(!calculateCentroid_(centroid))
        {
            // self-intersecting polygon. The movement is less accurate
            const LX_AABB& box = getEnclosingBox();
            const LX_FloatPosition q{box.x + box.w / 2.0f, box.y + box.h / 2.0f};
            _move(LX_Vector2D{p.x - q.x, p.y - q.y});
        }
        else // Normal case.→ accurate movement
            _move(LX_Vector2D{p.x - centroid.x, p.y - centroid.y});
    }

    ~LX_Polygon_() = default;
};


/* Polygon, public functions */

LX_Polygon::LX_Polygon() noexcept: _polyimpl(new LX_Polygon_()) {}
LX_Polygon::~LX_Polygon() {}

void LX_Polygon::convexity_() noexcept
{
    // Update the convexity when the polygon has at least 3 edges
    if(_polyimpl->numberOfEdges() >= TRIANGLE_SIDES)
        _polyimpl->convexity_();
}

// iIt is used by the function template
void LX_Polygon::addPoint_(const LX_FloatPosition& p)
{
    _polyimpl->addPoint(p);
}

void LX_Polygon::addPoint(const LX_FloatPosition& p)
{
    _polyimpl->addPoint(p);
    convexity_();
}

unsigned long LX_Polygon::numberOfEdges() const noexcept
{
    return _polyimpl->numberOfEdges();
}

LX_FloatPosition LX_Polygon::getPoint(const unsigned int index) const
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

void LX_Polygon::move(const LX_Vector2D& v) noexcept
{
    _polyimpl->_move(v);
}

void LX_Polygon::moveTo(const LX_FloatPosition& p)
{
    _polyimpl->moveTo(p);
}

}
