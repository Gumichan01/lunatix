
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
*   @file Physics.cpp
*   @brief The implementation of the physics library
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*
*/

#include <Lunatix/Physics.hpp>
#include <Lunatix/Polygon.hpp>
#include <Lunatix/Vector2D.hpp>
#include <Lunatix/Hitbox.hpp>
#include <Lunatix/Random.hpp>
#include <stdexcept>


using namespace FloatBox;

namespace
{

constexpr bool intersetInterval( const Float& min1, const Float& max1,
                                 const Float& min2, const Float& max2 ) noexcept
{
    return ( min1 < min2 ) ? max1 > min2 : max2 > min1;
}

/*
*   Calculate the collision between two polygons
*   by using the Separating Axis Theorem (SAT).
*
*   http://www.dyn4j.org/2010/01/sat/
*
*   Thanks to the SAT, it is possible to calculate the collision between two polygons
*   in linear time. But it does not work on triangles or non-convex polygons
*
*   Hypothesis/pre-condition : poly1 and poly2 must be convex with at least 4 edges
*
*   Complexity: O(m + n) — m > 3 is the number of vertices in poly1,
*                          n > 3 is the number of vertices in poly2
*/
bool collisionPolySAT( const lx::Physics::Polygon& poly1,
                       const lx::Physics::Polygon& poly2 ) noexcept
{
    const lx::Physics::FloatingBox& box1 = poly1.getEnclosingBox();
    const lx::Physics::FloatingBox& box2 = poly2.getEnclosingBox();

    lx::Physics::FloatPosition P1_min = box1.p;
    lx::Physics::FloatPosition P2_min = box2.p;
    lx::Physics::FloatPosition P1_max = box1.p;
    lx::Physics::FloatPosition P2_max = box2.p;

    P1_max.x += fbox<decltype( box1.w )>( box1.w );
    P1_max.y += fbox<decltype( box1.h )>( box1.h );
    P2_max.x += fbox<decltype( box2.w )>( box2.w );
    P2_max.y += fbox<decltype( box2.h )>( box2.h );

    return intersetInterval( P1_min.x, P1_max.x, P2_min.x, P2_max.x )
           && intersetInterval( P1_min.y, P1_max.y, P2_min.y, P2_max.y );
}

/*
*   Calculate the collision detection between two polygons
*   by using their encloging box.
*
*   See Polygon::getEnclosingBox()
*
*   It can be used to check collision betwwen polygons (including triangles)
*
*   Hypothesis/pre-condition: poly1 and poly2 must have at least 3 sides
*
*   Complexity: O(m + n) — m >= 3 is the number of vertices in poly1,
*                          n >= 3 is the number of vertices in poly2
*/
bool approximativeCollisionPoly( const lx::Physics::Polygon& poly1,
                                 const lx::Physics::Polygon& poly2 )
{
    const lx::Physics::FloatingBox& BOX1 = poly1.getEnclosingBox();
    const lx::Physics::FloatingBox& BOX2 = poly2.getEnclosingBox();
    return lx::Physics::collisionBox( BOX1, BOX2 );
}

/*
*   The basic (and naive) collision detection
*
*   This naive implementation is only used for non-convex polygons.
*
*   pre-condition: poly1 and poly2 must have at least 3 sides
*
*   Complexity: O(n²)
*               m is the number of vertices in poly1,
*               n is the number of vertices in poly2
*/
bool basicCollisionPoly( const lx::Physics::Polygon& poly1,
                         const lx::Physics::Polygon& poly2 )
{
    using lx::Physics::FloatPosition;
    using lx::Physics::Segment;
    const unsigned long S1 = poly1.numberOfEdges();
    const unsigned long S2 = poly2.numberOfEdges();

    for ( unsigned int i = 0; i < S1; i++ )
    {
        const FloatPosition& A = poly1.getPoint( i );
        const FloatPosition& B = poly1.getPoint( ( i == S1 - 1 ) ? 0 : i + 1 );

        for ( unsigned int j = 0; j < S2; j++ )
        {
            const FloatPosition& C = poly2.getPoint( j );
            const FloatPosition& D = poly2.getPoint( ( j == S2 - 1 ) ? 0 : j + 1 );


            if ( intersectSegment( Segment{A, B}, Segment{C, D} ) )
                return true;
        }
    }

    const FloatPosition& origin1 = poly1.getPoint( 0 );
    const FloatPosition& origin2 = poly2.getPoint( 0 );

    return ( collisionPointPoly( origin1, poly2 )
             || collisionPointPoly( origin2, poly1 ) );
}

bool intersectSeg_( const lx::Physics::FloatPosition& A,
                    const lx::Physics::FloatPosition& B,
                    const lx::Physics::FloatPosition& C,
                    const lx::Physics::FloatPosition& D ) noexcept
{
    const lx::Physics::Vector2D AB = { B.x - A.x, B.y - A.y };
    const lx::Physics::Vector2D AC = { C.x - A.x, C.y - A.y };
    const lx::Physics::Vector2D AD = { D.x - A.x, D.y - A.y };

    return ( vector_product( AB, AD ) * vector_product( AB, AC ) ) <= FNIL;
}

}

namespace lx
{

namespace Physics
{

Float euclide_square_distance( const FloatPosition& p1,
                               const FloatPosition& p2 ) noexcept
{
    return ( p2.x - p1.x ) * ( p2.x - p1.x ) + ( p2.y - p1.y ) * ( p2.y - p1.y );
}

Float euclide_distance( const FloatPosition& p1, const FloatPosition& p2 ) noexcept
{
    return FloatMath::sqrt( euclide_square_distance( p1, p2 ) );
}


bool collisionPointBox( const FloatPosition& p, const FloatingBox& box ) noexcept
{
    return !( p.x <= box.p.x || p.y >= ( box.p.y + fbox<decltype( box.h )>( box.h ) )
              || p.y <= box.p.y || p.x >= ( box.p.x + fbox<decltype( box.w )>( box.w ) ) );
}


bool collisionPointCircle( const FloatPosition& p, const Circle& circle ) noexcept
{
    return ( euclide_square_distance( p, circle.center ) <= ( circle.radius * circle.radius ) );
}


bool collisionBox( const FloatingBox& rect1, const FloatingBox& rect2 ) noexcept
{
    return !( ( rect1.p.x >= ( rect2.p.x + fbox<decltype( rect2.w )>( rect2.w ) ) )
              || ( rect1.p.y >= ( rect2.p.y + fbox<decltype( rect2.h )>( rect2.h ) ) )
              || ( ( rect1.p.x + fbox<decltype( rect1.w )>( rect1.w ) ) <= rect2.p.x )
              || ( ( rect1.p.y + fbox<decltype( rect1.h )>( rect1.h ) ) <= rect2.p.y ) );
}


bool collisionCircle( const Circle& circle1, const Circle& circle2 ) noexcept
{
    const uint32_t TMP_R = circle1.radius + circle2.radius;
    return euclide_square_distance( circle1.center,
                                    circle2.center ) <= fbox<decltype( TMP_R )>( TMP_R * TMP_R );
}


bool collisionSegCircle( const Circle& circle, const Segment& S ) noexcept
{
    const Vector2D V = { S.q.x - S.p.x, S.q.y - S.p.y };
    return collisionLineCircle( circle, Line{ S.p, V } );
}

bool collisionLineCircle( const Circle& circle, const Line& L ) noexcept
{
    const FloatPosition A = L.o;
    const FloatPosition B = { L.o.x + L.v.vx, L.o.y + L.v.vy };

    if ( collisionPointCircle( A, circle ) || collisionPointCircle( B, circle ) )
        return true;

    const FloatPosition O = circle.center;
    const Vector2D AB = {B.x - A.x, B.y - A.y};
    const Vector2D AO = {O.x - A.x, O.y - A.y};
    const Vector2D BO = {O.x - B.x, O.y - B.y};

    // Using the opposite value of vx for scal2
    const Float& scal_ab_ao  = scalar_product( AB, AO );
    const Float& scal_mab_bo = ( ( -AB.vx ) * BO.vx ) + ( ( -AB.vy ) * BO.vy );

    if ( scal_ab_ao < FNIL || scal_mab_bo < FNIL )
        return false;

    // Find the projection point of O
    const Float& scalp = scalar_product( AB, AB );

    if ( scalp == FNIL )     // A and B are the same point
        return false;

    const Float& T = scal_ab_ao / scalp;
    const Float& x = A.x + ( T * AB.vx );
    const Float& y = A.y + ( T * AB.vy );

    // Ok I can calculate the collision by using ↓ the projection point
    return collisionPointCircle( FloatPosition{x, y}, circle );
}


bool collisionCircleBox( const Circle& circle, const FloatingBox& box ) noexcept
{
    if ( collisionPointBox( circle.center, box ) )
        return true;

    const Float BOX_W = fbox<decltype( box.w )>( box.w );
    const Float BOX_H = fbox<decltype( box.h )>( box.h );
    const Line sides[] =
    {
        Line{ box.p, Vector2D{ FNIL, BOX_H } },

        Line{
            FloatPosition{ box.p.x, box.p.y + BOX_H },
            Vector2D{ BOX_W, FNIL }
        },

        Line{
            FloatPosition{ box.p.x + BOX_W, box.p.y },
            Vector2D{ FNIL, BOX_H }
        },

        Line{ box.p, Vector2D{ BOX_W, FNIL } }
    };

    for ( const Line& l : sides )
    {
        if ( collisionLineCircle( circle, l ) )
            return true;
    }

    return false;
}


bool intersectSegment( const Segment& s, const Segment& T ) noexcept
{
    return intersectSeg_( s.p, s.q, T.p, T.q ) && intersectSeg_( T.p, T.q, s.p, s.q );
}

bool intersectLine( const Line& l1, const Line& l2 ) noexcept
{
    return !l1.isParralelWith( l2 ) && !l2.isParralelWith( l1 );
}


bool collisionPointPoly( const FloatPosition& p, const Polygon& poly )
{
    const int V = 10000;
    const unsigned long N = poly.numberOfEdges();
    const float RIX = lx::Random::fxrand( 0.0f, 100.0f );
    const float RIY = lx::Random::fxrand( 0.0f, 100.0f );

    FloatPosition I{ V + RIX, V + RIY };
    unsigned long nb_intersections = 0;

    for ( unsigned long i = 0UL; i < N; ++i )
    {
        const FloatPosition& A = poly.getPoint( i );
        const FloatPosition& B = poly.getPoint( ( i == N - 1UL ) ? 0UL : i + 1UL );

        if ( p == A )
            return true;

        if ( intersectSegment( Segment{ p, I }, Segment{ A, B } ) )
            nb_intersections++;
    }

    return ( nb_intersections % 2UL == 1UL );
}


bool collisionCirclePoly( const Circle& c, const Polygon& poly )
{
    const FloatPosition FOLAT_POS = c.center;
    const unsigned long N = poly.numberOfEdges();

    if ( collisionPointPoly( FOLAT_POS, poly ) )
        return true;

    for ( unsigned long i = 0UL; i < N; ++i )
    {
        const FloatPosition& A = poly.getPoint( i );
        const FloatPosition& B = poly.getPoint( ( i == N - 1UL ) ? 0UL : i + 1UL );

        if ( collisionSegCircle( c, Segment{A, B} ) )
            return true;
    }

    return false;
}


bool collisionBoxPoly( const FloatingBox& box, const Polygon& poly )
{
    const unsigned long n = poly.numberOfEdges();
    const Float BOX_W = fbox<decltype( box.w )>( box.w );
    const Float BOX_H = fbox<decltype( box.h )>( box.h );
    const FloatPosition A = box.p;
    const FloatPosition B = { box.p.x + BOX_W, box.p.y };
    const FloatPosition C = { box.p.x + BOX_W, box.p.y + BOX_H };
    const FloatPosition D = { box.p.x, box.p.y + BOX_H };

    for ( unsigned long j = 0UL; j < n; ++j )
    {
        const FloatPosition& E = poly.getPoint( j );
        const FloatPosition& F = poly.getPoint( ( j == n - 1UL ) ? 0UL : j + 1UL );
        const Segment AB{A, B};
        const Segment EF{E, F};

        if ( intersectSegment( AB, EF ) || intersectSegment( Segment{B, C}, EF )
                || intersectSegment( Segment{C, D}, EF )
                || intersectSegment( Segment{D, A}, EF ) )
            return true;

        if ( collisionPointBox( E, box ) )
            return true;
    }

    return ( collisionPointPoly( A, poly ) || collisionPointPoly( B, poly )
             || collisionPointPoly( C, poly ) || collisionPointPoly( D, poly ) );
}


bool collisionPoly( const Polygon& poly1, const Polygon& poly2 )
{
    const unsigned long NUM_SIDES = 3UL;
    const unsigned long N = poly1.numberOfEdges();
    const unsigned long M = poly2.numberOfEdges();

    if ( N < NUM_SIDES || M < NUM_SIDES )
        throw std::invalid_argument( "The polygons must have at least "
                                     "3 sides to calculate the collision" );

    // Detect the collision by using the AABB of the polygons -> O(n)
    if ( !approximativeCollisionPoly( poly1, poly2 ) )
        return false;

    // If the two polygons are convex and have at least 4 sides,
    // use the SAT to detect the collision between then. -> O(n)
    if ( poly1.isConvex() && poly2.isConvex() && N > NUM_SIDES && M > NUM_SIDES )
        return collisionPolySAT( poly1, poly2 );

    // On of the polygons is not convex -> naive algorithm, -> O(n²)
    return basicCollisionPoly( poly1, poly2 );
}


void movePoint( FloatPosition& p, const Vector2D& v ) noexcept
{
    p.x += v.vx;
    p.y += v.vy;
}

void moveBox( FloatingBox& box, const Vector2D& v ) noexcept
{
    box.p.x += v.vx;
    box.p.y += v.vy;
}

void moveCircle( Circle& c, const Vector2D& v ) noexcept
{
    movePoint( c.center, v );
}

void movePoly( Polygon& poly, const Vector2D& v ) noexcept
{
    poly.move( v );
}

void movePointTo( FloatPosition& p, const FloatPosition& dest ) noexcept
{
    p = dest;
}

void moveBoxTo( FloatingBox& box, const FloatPosition& p ) noexcept
{
    box.p = p;
}

void moveCircleTo( Circle& c, const FloatPosition& p ) noexcept
{
    movePointTo( c.center, p );
}

void movePolyTo( Polygon& poly, const FloatPosition& p ) noexcept
{
    poly.moveTo( p );
}

}   // Physics

}   // lx
