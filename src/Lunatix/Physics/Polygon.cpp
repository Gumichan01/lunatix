
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
*   @file Polygon.cpp
*   @brief The Implementation of the polygon
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*/

#include <Lunatix/Polygon.hpp>
#include <Lunatix/Physics.hpp>
#include <Lunatix/Vector2D.hpp>
#include <vector>

using namespace std;
using namespace FloatBox;


namespace
{

inline constexpr Float sumx_( const lx::Physics::FloatPosition& p,
                              const lx::Physics::FloatPosition& q ) noexcept
{
    return p.x + q.x;
}

inline constexpr Float sumy_( const lx::Physics::FloatPosition& p,
                              const lx::Physics::FloatPosition& q ) noexcept
{
    return p.y + q.y;
}

inline constexpr Float cross_( const lx::Physics::FloatPosition& p,
                               const lx::Physics::FloatPosition& q ) noexcept
{
    return p.x * q.y - p.y * q.x;
}

}

namespace lx
{

namespace Physics
{

const unsigned long TRIANGLE_SIDES = 3UL;

PolygonException::PolygonException( std::string err ) : _string_error( err ) {}

PolygonException::PolygonException( const PolygonException& pex )
    : _string_error( pex._string_error ) {}

const char * PolygonException::what() const noexcept
{
    return _string_error.c_str();
}

PolygonException::~PolygonException() noexcept {}


/* Polygon - private implementation */

using FloatPositions_ = std::vector<FloatPosition>;

class Polygon_ final
{
    FloatPositions_ _points;     /* A sequence of FloatPosition objects   */
    bool _convex;                   /* If the polygon is convex                 */

    Float area_() const noexcept
    {
        Float sum = FNIL;
        const auto pbeg = _points.begin();
        const auto pend = _points.end();

        for ( auto it = pbeg; it != pend; ++it )
        {
            sum += cross_( *it, ( it == pend - 1 ) ? *pbeg : * ( it + 1 ) );
        }
        return sum / fbox( 2.0f );
    }

    bool calculateCentroid_( FloatPosition& p ) const noexcept
    {
        const Float CMULT = fbox( 6.0f );
        const auto pbeg = _points.begin();
        const auto pend = _points.end();
        const Float p6_area = CMULT * area_();
        Float sum_x = FNIL, sum_y = FNIL;

        if ( p6_area <= FNIL ) // self-intersecting polygon
            return false;

        for ( auto it = pbeg; it != pend; ++it )
        {
            const FloatPosition& next_fpos = ( it == pend - 1 ) ? *pbeg : *( it + 1 );
            sum_x += sumx_( *it, next_fpos ) * cross_( *it, next_fpos );
            sum_y += sumy_( *it, next_fpos ) * cross_( *it, next_fpos );
        }

        p.x = { sum_x / p6_area };
        p.y = { sum_y / p6_area };
        return true;
    }

public:

    Polygon_() : _points(), _convex( false ) {}

    void convexity_() noexcept
    {
        float sign = 0.0f;
        bool have_sign = false;

        const auto pbeg = _points.begin();
        const auto pend = _points.end();

        for ( auto it = pbeg; it != pend; ++it )
        {
            const FloatPosition& ori1 = *it;
            const FloatPosition& img1 = ( it == pbeg ? * ( pend - 1 ) : * ( it - 1 ) );
            const FloatPosition& ori2 = ( it == pend - 1 ? *pbeg : * ( it + 1 ) );
            const FloatPosition& img2 = ori1;

            Vector2D AO = Vector2D{img1.x - ori1.x, img1.y - ori1.y};
            Vector2D OB = Vector2D{img2.x - ori2.x, img2.y - ori2.y};
            Float cross_product = vector_product( AO, OB );

            if ( !have_sign )
            {
                if ( cross_product > FNIL )
                    sign = 1.0f;
                else if ( cross_product < FNIL )
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
                if ( ( sign > 0.0f && cross_product < FNIL )
                        || ( sign < 0.0f && cross_product > FNIL ) )
                {
                    _convex = false;
                    return;
                }
            }
        }

        _convex = true;
    }


    inline void addPoint( const FloatPosition& p )
    {
        _points.push_back( p );
    }

    inline unsigned long numberOfEdges() const noexcept
    {
        return _points.size();
    }


    inline FloatPosition getPoint( const unsigned long index ) const
    {
        return _points.at( index );
    }

    FloatingBox getEnclosingBox() const
    {
        if ( _points.size() < TRIANGLE_SIDES )
            throw PolygonException( "Polygon: Cannot get the enclosing bounding box" );

        FloatPosition p0 = _points.at( 0 );
        FloatingBox box{p0, 0, 0}; ;

        for ( const FloatPosition& p : _points )
        {
            // X
            if ( p.x < box.p.x )
                box.p.x = p.x;

            if ( p.x > p0.x )
                p0.x = p.x;

            // Y
            if ( p.y < box.p.y )
                box.p.y = p.y;

            if ( p.y > p0.y )
                p0.y = p.y;
        }

        box.w = static_cast<int>( p0.x - box.p.x ) + 1;
        box.h = static_cast<int>( p0.y - box.p.y ) + 1;

        return box;
    }

    inline bool isConvex() const noexcept
    {
        return _convex;
    }

    void _move( const Vector2D& v ) noexcept
    {
        std::for_each( _points.begin(), _points.end(), [&v] ( FloatPosition & p )
        {
            movePoint( p, v );
        } );
    }

    void moveTo( const FloatPosition& p )
    {
        FloatPosition centroid;

        if ( !calculateCentroid_( centroid ) )
        {
            // self-intersecting polygon. The movement is less accurate
            constexpr Float TWO{2.0f};
            const FloatingBox& box = getEnclosingBox();
            const Float FW = fbox<decltype( box.w )>( box.w );
            const Float FH = fbox<decltype( box.h )>( box.h );
            const FloatPosition q{box.p.x + FW / TWO, box.p.y + FH / TWO};
            _move( Vector2D{p.x - q.x, p.y - q.y} );
        }
        else // Normal case.→ accurate movement
            _move( Vector2D{p.x - centroid.x, p.y - centroid.y} );
    }

    ~Polygon_() = default;
};


/* Polygon, public functions */

Polygon::Polygon() noexcept: _polyimpl( new Polygon_() ) {}

Polygon::~Polygon()
{
    _polyimpl.reset();
}

void Polygon::convexity_() noexcept
{
    // Update the convexity when the polygon has at least 3 edges
    if ( _polyimpl->numberOfEdges() >= TRIANGLE_SIDES )
        _polyimpl->convexity_();
}

// It is used by the function template
void Polygon::addPoint_( const FloatPosition& p )
{
    _polyimpl->addPoint( p );
}

void Polygon::addPoint( const FloatPosition& p )
{
    _polyimpl->addPoint( p );
    convexity_();
}

unsigned long Polygon::numberOfEdges() const noexcept
{
    return _polyimpl->numberOfEdges();
}

FloatPosition Polygon::getPoint( const unsigned long index ) const
{
    return _polyimpl->getPoint( index );
}

FloatingBox Polygon::getEnclosingBox() const
{
    return _polyimpl->getEnclosingBox();
}

bool Polygon::isConvex() const noexcept
{
    return _polyimpl->isConvex();
}

void Polygon::move( const Vector2D& v ) noexcept
{
    _polyimpl->_move( v );
}

void Polygon::moveTo( const FloatPosition& p )
{
    _polyimpl->moveTo( p );
}

}   // physics

}   // lx
