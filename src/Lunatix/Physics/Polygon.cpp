
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

PolygonException::PolygonException( std::string err ) : m_msg( err ) {}

PolygonException::PolygonException( const PolygonException& pex )
    : m_msg( pex.m_msg ) {}

const char * PolygonException::what() const noexcept
{
    return m_msg.c_str();
}

PolygonException::~PolygonException() noexcept {}


/* Polygon - private implementation */

class Polygon_ final
{
    std::vector<FloatPosition> m_points;
    bool m_convex;

    Float area_() const noexcept
    {
        Float sum = FNIL;
        const auto PBEG = m_points.begin();
        const auto PEND = m_points.end();

        for ( auto it = PBEG; it != PEND; ++it )
        {
            sum += cross_( *it, ( it == PEND - 1 ) ? *PBEG : * ( it + 1 ) );
        }
        return sum / fbox( 2.0f );
    }

    bool calculateCentroid_( FloatPosition& p ) const noexcept
    {
        const Float CMULT = fbox( 6.0f );
        const auto PBEG = m_points.begin();
        const auto PEND = m_points.end();
        const Float AREA_P6 = CMULT * area_();
        Float sum_x = FNIL;
        Float sum_y = FNIL;

        if ( AREA_P6 <= FNIL ) // self-intersecting polygon
            return false;

        for ( auto it = PBEG; it != PEND; ++it )
        {
            const FloatPosition& next_fpos = ( it == PEND - 1 ) ? *PBEG : *( it + 1 );
            sum_x += sumx_( *it, next_fpos ) * cross_( *it, next_fpos );
            sum_y += sumy_( *it, next_fpos ) * cross_( *it, next_fpos );
        }

        p.x = { sum_x / AREA_P6 };
        p.y = { sum_y / AREA_P6 };
        return true;
    }

public:

    Polygon_() : m_points(), m_convex( false ) {}

    void convexity_() noexcept
    {
        float sign = 0.0f;
        bool have_sign = false;

        const auto PBEG = m_points.begin();
        const auto PEND = m_points.end();

        for ( auto it = PBEG; it != PEND; ++it )
        {
            const FloatPosition& ori1 = *it;
            const FloatPosition& img1 = ( it == PBEG ? * ( PEND - 1 ) : * ( it - 1 ) );
            const FloatPosition& ori2 = ( it == PEND - 1 ? *PBEG : * ( it + 1 ) );
            const FloatPosition& img2 = ori1;

            Vector2D AO = { img1.x - ori1.x, img1.y - ori1.y };
            Vector2D OB = { img2.x - ori2.x, img2.y - ori2.y };
            Float cross_product = vector_product( AO, OB );

            if ( !have_sign )
            {
                if ( cross_product > FNIL )
                    sign = 1.0f;
                else if ( cross_product < FNIL )
                    sign = -1.0f;
                else
                {
                    m_convex = false;
                    return;
                }

                have_sign = true;
            }
            else
            {
                if ( ( sign > 0.0f && cross_product < FNIL )
                        || ( sign < 0.0f && cross_product > FNIL ) )
                {
                    m_convex = false;
                    return;
                }
            }
        }

        m_convex = true;
    }


    inline void addPoint( const FloatPosition& p )
    {
        m_points.push_back( p );
    }

    inline unsigned long numberOfEdges() const noexcept
    {
        return m_points.size();
    }


    inline FloatPosition getPoint( const unsigned long index ) const
    {
        return m_points.at( index );
    }

    FloatingBox getEnclosingBox() const
    {
        if ( m_points.size() < TRIANGLE_SIDES )
            throw PolygonException( "Polygon: Cannot get the enclosing bounding box" );

        FloatPosition point0 = m_points.at( 0 );
        FloatingBox box = { point0, 0, 0 };

        for ( const FloatPosition& p : m_points )
        {
            // X
            if ( p.x < box.p.x )
                box.p.x = p.x;

            if ( p.x > point0.x )
                point0.x = p.x;

            // Y
            if ( p.y < box.p.y )
                box.p.y = p.y;

            if ( p.y > point0.y )
                point0.y = p.y;
        }

        box.w = static_cast<int>( point0.x - box.p.x ) + 1;
        box.h = static_cast<int>( point0.y - box.p.y ) + 1;

        return box;
    }

    inline bool isConvex() const noexcept
    {
        return m_convex;
    }

    void _move( const Vector2D& v ) noexcept
    {
        std::for_each( m_points.begin(), m_points.end(), [&v] ( FloatPosition & p )
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
            constexpr Float TWO = fbox( 2.0f );
            const FloatingBox& box = getEnclosingBox();

            const Float FW = fbox<decltype( box.w )>( box.w );
            const Float FH = fbox<decltype( box.h )>( box.h );
            const FloatPosition q { box.p.x + FW / TWO, box.p.y + FH / TWO };

            _move( Vector2D{p.x - q.x, p.y - q.y} );
        }
        else // Normal case.→ accurate movement
            _move( Vector2D{p.x - centroid.x, p.y - centroid.y} );
    }

    ~Polygon_() = default;
};


/* Polygon, public functions */

Polygon::Polygon() noexcept: m_polyimpl( new Polygon_() ) {}

Polygon::~Polygon()
{
    m_polyimpl.reset();
}

void Polygon::convexity_() noexcept
{
    // Update the convexity when the polygon has at least 3 edges
    if ( m_polyimpl->numberOfEdges() >= TRIANGLE_SIDES )
        m_polyimpl->convexity_();
}

// It is used by the function template
void Polygon::addPoint_( const FloatPosition& p )
{
    m_polyimpl->addPoint( p );
}

void Polygon::addPoint( const FloatPosition& p )
{
    m_polyimpl->addPoint( p );
    convexity_();
}

unsigned long Polygon::numberOfEdges() const noexcept
{
    return m_polyimpl->numberOfEdges();
}

FloatPosition Polygon::getPoint( const unsigned long index ) const
{
    return m_polyimpl->getPoint( index );
}

FloatingBox Polygon::getEnclosingBox() const
{
    return m_polyimpl->getEnclosingBox();
}

bool Polygon::isConvex() const noexcept
{
    return m_polyimpl->isConvex();
}

void Polygon::move( const Vector2D& v ) noexcept
{
    m_polyimpl->_move( v );
}

void Polygon::moveTo( const FloatPosition& p )
{
    m_polyimpl->moveTo( p );
}

}   // physics

}   // lx
