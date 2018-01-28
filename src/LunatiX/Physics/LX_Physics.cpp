

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
*   @file LX_Physics.cpp
*   @brief The implementation of the physics library
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.12
*
*/

#include <LunatiX/LX_Physics.hpp>
#include <LunatiX/LX_Polygon.hpp>
#include <LunatiX/LX_Vector2D.hpp>
#include <LunatiX/LX_Hitbox.hpp>
#include <LunatiX/LX_Random.hpp>
#include <stdexcept>
#include <cmath>


namespace
{

bool intersetInterval(const int min1, const int max1, const int min2, const int max2) noexcept
{
    return (min1 < min2) ? max1 > min2 : max2 > min1;
}

// Calcute the collision between two polygons using the Separating Axis Theorem (SAT)
// pre-condition : poly1 and poly2 must be convex with at least 4 sides
bool collisionPolySAT(const LX_Physics::LX_Polygon& poly1,
                      const LX_Physics::LX_Polygon& poly2) noexcept
{
    const LX_Physics::LX_FloatingBox& box1 = poly1.getEnclosingBox();
    const LX_Physics::LX_FloatingBox& box2 = poly2.getEnclosingBox();

    LX_Physics::LX_FloatPosition P1_min = box1.fpoint;
    LX_Physics::LX_FloatPosition P2_min = box2.fpoint;
    LX_Physics::LX_FloatPosition P1_max = box1.fpoint;
    LX_Physics::LX_FloatPosition P2_max = box2.fpoint;


    P1_max.x += Float{static_cast<float>(box1.w)};
    P1_max.y += Float{static_cast<float>(box1.h)};
    P2_max.x += Float{static_cast<float>(box2.w)};
    P2_max.y += Float{static_cast<float>(box2.h)};

    return intersetInterval(P1_min.x, P1_max.x, P2_min.x, P2_max.x)
           && intersetInterval(P1_min.y, P1_max.y, P2_min.y, P2_max.y);
}

// Collision detection between polygons using their AABB
bool approximativeCollisionPoly(const LX_Physics::LX_Polygon& poly1,
                                const LX_Physics::LX_Polygon& poly2)
{
    const LX_Physics::LX_FloatingBox& box1 = poly1.getEnclosingBox();
    const LX_Physics::LX_FloatingBox& box2 = poly2.getEnclosingBox();
    return LX_Physics::collisionRect(box1, box2);
}


bool basicCollisionPoly(const LX_Physics::LX_Polygon& poly1,
                        const LX_Physics::LX_Polygon& poly2)
{
    LX_Physics::LX_FloatPosition A, B, C, D;
    const unsigned long S1 = poly1.numberOfEdges();
    const unsigned long S2 = poly2.numberOfEdges();

    for(unsigned int i = 0; i < S1; i++)
    {
        A = poly1.getPoint(i);

        if(i == S1-1)
            B = poly1.getPoint(0);
        else
            B = poly1.getPoint(i+1);

        for(unsigned int j = 0; j < S2; j++)
        {
            C = poly2.getPoint(j);

            if(j == S2-1)
                D = poly2.getPoint(0);
            else
                D = poly2.getPoint(j+1);

            if(intersectSegment(A, B, C, D))
                return true;
        }
    }

    const LX_Physics::LX_FloatPosition& origin1 = poly1.getPoint(0);
    const LX_Physics::LX_FloatPosition& origin2 = poly2.getPoint(0);

    return (collisionPointPoly(origin1, poly2)
            || collisionPointPoly(origin2, poly1));
}

}


namespace LX_Physics
{

Float euclide_square_distance(const LX_FloatPosition& p1,
                              const LX_FloatPosition& p2) noexcept
{
    return (p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y);
}

Float euclide_distance(const LX_FloatPosition& p1, const LX_FloatPosition& p2) noexcept
{
    return fbox(sqrtf(euclide_square_distance(p1, p2)));
}


bool collisionPointRect(const LX_FloatPosition& p, const LX_FloatingBox& rect) noexcept
{
    return !(p.x <= rect.fpoint.x || p.y >= (rect.fpoint.y + rect.h)
             || p.y <= rect.fpoint.y || p.x >= (rect.fpoint.x + rect.w));
}


bool collisionPointCircle(const LX_FloatPosition& p, const LX_Circle& circle) noexcept
{
    return(euclide_square_distance(p, circle.center) <= (circle.radius * circle.radius));
}


bool collisionRect(const LX_FloatingBox& rect1, const LX_FloatingBox& rect2) noexcept
{
    return !((rect1.fpoint.x >= (rect2.fpoint.x + rect2.w))
             || (rect1.fpoint.y >= (rect2.fpoint.y + rect2.h))
             || ((rect1.fpoint.x + rect1.w) <= rect2.fpoint.x)
             || ((rect1.fpoint.y + rect1.h) <= rect2.fpoint.y));
}


bool collisionCircle(const LX_Circle& circle1, const LX_Circle& circle2) noexcept
{
    const unsigned int sum_radius = circle1.radius + circle2.radius;
    const unsigned int d = sum_radius * sum_radius;

    return (euclide_square_distance(circle1.center, circle2.center) <= d);
}


bool collisionSegCircle(const LX_Circle& circle,
                        const LX_FloatPosition& A, const LX_FloatPosition& B) noexcept
{
    if(collisionPointCircle(A, circle) || collisionPointCircle(B, circle))
        return true;

    const Float ZERO{0.0f};
    LX_FloatPosition O = circle.center;
    LX_Vector2D AB{B.x - A.x, B.y - A.y};
    LX_Vector2D AO{O.x - A.x, O.y - A.y};
    LX_Vector2D BO{O.x - B.x, O.y - B.y};

    // Using the opposite value of vx for scal2
    Float scal_ab_ao = scalar_product(AB, AO);
    Float scal_mab_bo = ((-AB.vx) * BO.vx) + ((-AB.vy) * BO.vy);

    if(scal_ab_ao < ZERO || scal_mab_bo < ZERO)
        return false;

    // Find the projection point of O
    Float scalp = scalar_product(AB, AB);

    if(scalp == ZERO)        // A and B are the same point
        return false;

    Float t = scal_ab_ao / scalp;
    Float x = A.x + (t * AB.vx);
    Float y = A.y + (t * AB.vy);

    // Ok I can calculate the collision by using ↓ the projection point
    return collisionPointCircle(LX_FloatPosition{x, y}, circle);
}

bool collisionLineCircle(const LX_Circle& circle, const LX_Line& L) noexcept
{
    const LX_FloatPosition Q{L.o.x + L.v.vx, L.o.y + L.v.vy};
    return collisionSegCircle(circle, L.o, Q);
}

#define PFL(x) static_cast<float>(x)

bool collisionCircleRect(const LX_Circle& circle, const LX_FloatingBox& rect) noexcept
{
    // Check if the center of the circle is in the AABB
    if(collisionPointRect(circle.center, rect))
        return true;

    const LX_Line sides[] =
    {
        LX_Line{ rect.fpoint, LX_Vector2D{ 0.0f, PFL(rect.h) } },

        LX_Line{
            LX_FloatPosition{ rect.fpoint.x, rect.fpoint.y + rect.h },
            LX_Vector2D{ PFL(rect.w), 0.0f }
        },

        LX_Line{
            LX_FloatPosition{ rect.fpoint.x + rect.w, rect.fpoint.y },
            LX_Vector2D{ 0.0f, PFL(rect.h) }
        },

        LX_Line{ rect.fpoint, LX_Vector2D{ PFL(rect.w), 0.0f } }
    };

    for(const LX_Line& l : sides)
    {
        if(collisionLineCircle(circle, l))
            return true;
    }

    return false;
}


bool intersectSegLine(const LX_FloatPosition& A, const LX_FloatPosition& B,
                      const LX_FloatPosition& C, const LX_FloatPosition& D) noexcept
{
    LX_Vector2D AB{B.x - A.x, B.y - A.y};
    LX_Vector2D AC{C.x - A.x, C.y - A.y};
    LX_Vector2D AD{D.x - A.x, D.y - A.y};

    return (vector_product(AB, AD) * vector_product(AB, AC)) <= Float{0.0f};
}


bool intersectSegment(const LX_FloatPosition& A, const LX_FloatPosition& B,
                      const LX_FloatPosition& C, const LX_FloatPosition& D) noexcept
{
    return intersectSegLine(A, B, C, D) && intersectSegLine(C, D, A, B);
}


bool intersectLine(const LX_Line& L1, const LX_Line& L2) noexcept
{
    return !L1.isParralelWith(L2) && !L2.isParralelWith(L1);
}


bool collisionPointPoly(const LX_FloatPosition& P, const LX_Polygon& poly)
{
    const int v = 10000;
    const unsigned long N = poly.numberOfEdges();
    const float RIX = static_cast<float>(LX_Random::crand100());
    const float RIY = static_cast<float>(LX_Random::crand100());

    LX_FloatPosition I{v + RIX, v + RIY};
    unsigned long nb_intersections = 0;

    for(unsigned long i = 0UL; i < N; i++)
    {
        const LX_FloatPosition& A = poly.getPoint(i);
        const LX_FloatPosition& B = poly.getPoint((i == N - 1UL) ? 0UL: i + 1UL);

        if(P == A)
            return true;

        if(intersectSegment(P, I, A, B))
            nb_intersections++;
    }

    return (nb_intersections % 2UL == 1UL);
}


bool collisionCirclePoly(const LX_Circle& C, const LX_Polygon& poly)
{
    const LX_FloatPosition P = C.center;
    const unsigned long N = poly.numberOfEdges();

    if(collisionPointPoly(P, poly) == true)
        return true;

    for(unsigned long i = 0UL; i < N; i++)
    {
        const LX_FloatPosition& A = poly.getPoint(i);
        const LX_FloatPosition& B = poly.getPoint((i == N - 1UL) ? 0UL: i + 1UL);

        if(collisionSegCircle(C, A, B) == true)
            return true;
    }

    return false;
}


bool collisionRectPoly(const LX_FloatingBox& rect, const LX_Polygon& poly)
{
    const unsigned long n = poly.numberOfEdges();
    const LX_FloatPosition A{rect.fpoint.x, rect.fpoint.y};
    const LX_FloatPosition B{rect.fpoint.x + rect.w, rect.fpoint.y};
    const LX_FloatPosition C{rect.fpoint.x + rect.w, rect.fpoint.y + rect.h};
    const LX_FloatPosition D{rect.fpoint.x, rect.fpoint.y + rect.h};

    for(unsigned long j = 0UL; j < n; j++)
    {
        const LX_FloatPosition& E = poly.getPoint(j);
        const LX_FloatPosition& F = poly.getPoint((j == n - 1UL) ? 0UL : j + 1UL);

        /*if()
            const LX_FloatPosition& F = poly.getPoint(0UL);
        else
            F = poly.getPoint(j + 1UL);*/

        if(intersectSegment(A, B, E, F) || intersectSegment(B, C, E, F) ||
                intersectSegment(C, D, E, F) || intersectSegment(D, A, E, F))
            return true;

        if(collisionPointRect(E, rect))
            return true;
    }

    return(collisionPointPoly(A, poly) || collisionPointPoly(B, poly)
           || collisionPointPoly(C, poly) || collisionPointPoly(D, poly));
}


bool collisionPoly(const LX_Polygon& poly1, const LX_Polygon& poly2)
{
    const unsigned int NUM_SIDES = 3;
    const unsigned long N = poly1.numberOfEdges();
    const unsigned long M = poly2.numberOfEdges();

    if(N < NUM_SIDES || M < NUM_SIDES)
        throw std::invalid_argument("The polygons must have at least 3 sides to calculate the collision");

    // Detect the collision using the AABB of the polygons
    if(!approximativeCollisionPoly(poly1, poly2))
        return false;

    // If the two polygons are convex and have at least 4 sides,
    // use the SAT to detect the collision between then.
    if(poly1.isConvex() && poly2.isConvex() && N > NUM_SIDES && M > NUM_SIDES)
        return collisionPolySAT(poly1, poly2);

    return basicCollisionPoly(poly1, poly2);
}


void movePoint(LX_FloatPosition& P, const LX_Vector2D& v) noexcept
{
    P.x += v.vx;
    P.y += v.vy;
}

void moveRect(LX_FloatingBox& rect, const LX_Vector2D& v) noexcept
{
    rect.fpoint.x += v.vx;
    rect.fpoint.y += v.vy;
}

void moveCircle(LX_Circle& C, const LX_Vector2D& v) noexcept
{
    movePoint(C.center, v);
}

void movePoly(LX_Polygon& poly, const LX_Vector2D& v) noexcept
{
    poly.move(v);
}

void movePointTo(LX_FloatPosition& P, const LX_FloatPosition& dest) noexcept
{
    P = dest;
}

void moveRectTo(LX_FloatingBox& rect, const LX_FloatPosition& P) noexcept
{
    rect.fpoint = P;
}

void moveCircleTo(LX_Circle& C, const LX_FloatPosition& P) noexcept
{
    movePointTo(C.center, P);
}

void movePolyTo(LX_Polygon& poly, const LX_FloatPosition& P)
{
    poly.moveTo(P);
}

}
