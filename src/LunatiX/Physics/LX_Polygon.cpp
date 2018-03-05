
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
#include <vector>

using namespace std;

/// @todo code review polygon

namespace
{

inline Float sumx_(const LX_Physics::LX_FloatPosition& p, const LX_Physics::LX_FloatPosition& q) noexcept
{
    return p.x + q.x;
}

inline Float sumy_(const LX_Physics::LX_FloatPosition& p, const LX_Physics::LX_FloatPosition& q) noexcept
{
    return p.y + q.y;
}

inline Float cross_(const LX_Physics::LX_FloatPosition& p, const LX_Physics::LX_FloatPosition& q) noexcept
{
    return p.x * q.y - p.y * q.x;
}

}


namespace LX_Physics
{

const unsigned long TRIANGLE_SIDES = 3UL;

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
    bool _convex;                   /* If the polygon is convex                 */

    Float area_() const noexcept
    {
        Float sum{0.0f};
        const auto pbeg = _points.begin();
        const auto pend = _points.end();

        for(auto it = pbeg; it != pend; ++it)
        {
            sum += cross_(*it, (it == pend - 1) ? *pbeg : *(it + 1));
        }
        return sum / fbox(2.0f);
    }

    bool calculateCentroid_(LX_FloatPosition& p) const noexcept
    {
        const Float CMULT{6.0f};
        const auto pbeg = _points.begin();
        const auto pend = _points.end();
        const Float p6_area = CMULT * area_();
        Float sum_x{0.0f}, sum_y{0.0f};

        if(p6_area <= 0.0f) // self-intersecting polygon
            return false;

        for(auto it = pbeg; it != pend; ++it)
        {
            const LX_FloatPosition& next_fpos = (it == pend - 1) ? *pbeg : *(it + 1);
            sum_x += sumx_(*it, next_fpos) * cross_(*it, next_fpos);
            sum_y += sumy_(*it, next_fpos) * cross_(*it, next_fpos);
        }

        p.x = {sum_x / p6_area};
        p.y = {sum_y / p6_area};
        return true;
    }

public:

    LX_Polygon_() : _points(),_convex(false) {}

    void convexity_() noexcept
    {
        float sign = 0.0f;
        bool have_sign = false;

        const Float FNULL{0.0f};
        const auto pbeg = _points.begin();
        const auto pend = _points.end();

        for(auto it = pbeg; it != pend; ++it)
        {
            const LX_FloatPosition& ori1 = *it;
            const LX_FloatPosition& img1 = (it == pbeg ? *(pend - 1) : *(it - 1));
            const LX_FloatPosition& ori2 = (it == pend-1 ? *pbeg : *(it + 1));
            const LX_FloatPosition& img2 = ori1;

            LX_Vector2D AO = LX_Vector2D{img1.x - ori1.x, img1.y - ori1.y};
            LX_Vector2D OB = LX_Vector2D{img2.x - ori2.x, img2.y - ori2.y};
            Float cross_product = vector_product(AO, OB);

            if(!have_sign)
            {
                if(cross_product > FNULL)
                    sign = 1.0f;
                else if(cross_product < FNULL)
                    sign = -1.0f;
                else
                {
                    _convex = false;
                    return;
                }

                have_sign = true;
            }
            else
            {
                if((sign > 0.0f && cross_product < FNULL)
                        || (sign < 0.0f && cross_product > FNULL))
                {
                    _convex = false;
                    return;
                }
            }
        }

        _convex = true;
    }


    inline void addPoint(const LX_FloatPosition& p)
    {
        _points.push_back(p);
    }

    inline unsigned long numberOfEdges() const noexcept
    {
        return _points.size();
    }


    inline LX_FloatPosition getPoint(const unsigned long index) const
    {
        return _points.at(index);
    }

    LX_FloatingBox getEnclosingBox() const
    {
        if(_points.size() < TRIANGLE_SIDES)
            throw LX_PolygonException("LX_Polygon: Cannot get the enclosing bounding box");

        LX_FloatPosition p0 = _points.at(0);
        LX_FloatingBox box{p0, 0, 0}; ;

        for(const LX_FloatPosition& p: _points)
        {
            // X
            if(p.x < box.p.x)
                box.p.x = p.x;

            if(p.x > p0.x)
                p0.x = p.x;

            // Y
            if(p.y < box.p.y)
                box.p.y = p.y;

            if(p.y > p0.y)
                p0.y = p.y;
        }

        box.w = static_cast<int>(p0.x - box.p.x) + 1;
        box.h = static_cast<int>(p0.y - box.p.y) + 1;

        return box;
    }


    inline bool isConvex() const noexcept
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
            const LX_FloatingBox& box = getEnclosingBox();
            const float fw = static_cast<float>(box.w);
            const float fh = static_cast<float>(box.h);
            const LX_FloatPosition q{box.p.x + fw / 2.0f, box.p.y + fh / 2.0f};
            _move(LX_Vector2D{p.x - q.x, p.y - q.y});
        }
        else // Normal case.→ accurate movement
            _move(LX_Vector2D{p.x - centroid.x, p.y - centroid.y});
    }

    ~LX_Polygon_() = default;
};


/* Polygon, public functions */

LX_Polygon::LX_Polygon() noexcept: _polyimpl(new LX_Polygon_()) {}

LX_Polygon::~LX_Polygon()
{
    _polyimpl.reset();
}

void LX_Polygon::convexity_() noexcept
{
    // Update the convexity when the polygon has at least 3 edges
    if(_polyimpl->numberOfEdges() >= TRIANGLE_SIDES)
        _polyimpl->convexity_();
}

// It is used by the function template
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

LX_FloatPosition LX_Polygon::getPoint(const unsigned long index) const
{
    return _polyimpl->getPoint(index);
}

LX_FloatingBox LX_Polygon::getEnclosingBox() const
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
