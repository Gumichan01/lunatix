
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


using namespace FloatBox;

namespace
{
/// @todo fix non-constexpr
constexpr bool intersetInterval(const Float& min1, const Float& max1,
                                const Float& min2, const Float& max2) noexcept
{
    return (min1 < min2) ? max1 > min2 : max2 > min1;
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
bool collisionPolySAT(const LX_Physics::LX_Polygon& poly1,
                      const LX_Physics::LX_Polygon& poly2) noexcept
{
    const LX_Physics::LX_FloatingBox& box1 = poly1.getEnclosingBox();
    const LX_Physics::LX_FloatingBox& box2 = poly2.getEnclosingBox();

    LX_Physics::LX_FloatPosition P1_min = box1.p;
    LX_Physics::LX_FloatPosition P2_min = box2.p;
    LX_Physics::LX_FloatPosition P1_max = box1.p;
    LX_Physics::LX_FloatPosition P2_max = box2.p;

    P1_max.x += fbox<decltype(box1.w)>(box1.w);
    P1_max.y += fbox<decltype(box1.h)>(box1.h);
    P2_max.x += fbox<decltype(box2.w)>(box2.w);
    P2_max.y += fbox<decltype(box2.h)>(box2.h);

    return intersetInterval(P1_min.x, P1_max.x, P2_min.x, P2_max.x)
           && intersetInterval(P1_min.y, P1_max.y, P2_min.y, P2_max.y);
}

/*
*   Calculate the collision detection between two polygons
*   by using their encloging box.
*
*   See LX_Polygon::getEnclosingBox()
*
*   It can be used to check collision betwwen polygons (including triangles)
*
*   Hypothesis/pre-condition: poly1 and poly2 must have at least 3 sides
*
*   Complexity: O(m + n) — m >= 3 is the number of vertices in poly1,
*                          n >= 3 is the number of vertices in poly2
*/
bool approximativeCollisionPoly(const LX_Physics::LX_Polygon& poly1,
                                const LX_Physics::LX_Polygon& poly2)
{
    const LX_Physics::LX_FloatingBox& box1 = poly1.getEnclosingBox();
    const LX_Physics::LX_FloatingBox& box2 = poly2.getEnclosingBox();
    return LX_Physics::collisionBox(box1, box2);
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
bool basicCollisionPoly(const LX_Physics::LX_Polygon& poly1,
                        const LX_Physics::LX_Polygon& poly2)
{
    using LX_Physics::LX_FloatPosition;
    using LX_Physics::LX_Segment;
    const unsigned long S1 = poly1.numberOfEdges();
    const unsigned long S2 = poly2.numberOfEdges();

    for(unsigned int i = 0; i < S1; i++)
    {
        const LX_FloatPosition& A = poly1.getPoint(i);
        const LX_FloatPosition& B = poly1.getPoint((i == S1 - 1) ? 0 : i + 1);

        for(unsigned int j = 0; j < S2; j++)
        {
            const LX_FloatPosition&C = poly2.getPoint(j);
            const LX_FloatPosition&D = poly2.getPoint((j == S2 - 1) ? 0 : j + 1);


            if(intersectSegment(LX_Segment{A, B}, LX_Segment{C, D}))
                return true;
        }
    }

    const LX_FloatPosition& origin1 = poly1.getPoint(0);
    const LX_FloatPosition& origin2 = poly2.getPoint(0);

    return (collisionPointPoly(origin1, poly2)
            || collisionPointPoly(origin2, poly1));
}

bool intersectSeg_(const LX_Physics::LX_FloatPosition& A,
                   const LX_Physics::LX_FloatPosition& B,
                   const LX_Physics::LX_FloatPosition& C,
                   const LX_Physics::LX_FloatPosition& D) noexcept
{
    LX_Physics::LX_Vector2D AB{B.x - A.x, B.y - A.y};
    LX_Physics::LX_Vector2D AC{C.x - A.x, C.y - A.y};
    LX_Physics::LX_Vector2D AD{D.x - A.x, D.y - A.y};

    return (vector_product(AB, AD) * vector_product(AB, AC)) <= FNIL;
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
    return FloatMath::sqrt(euclide_square_distance(p1, p2));
}


bool collisionPointBox(const LX_FloatPosition& p, const LX_FloatingBox& box) noexcept
{
    return !(p.x <= box.p.x || p.y >= (box.p.y + fbox<decltype(box.h)>(box.h))
             || p.y <= box.p.y || p.x >= (box.p.x + fbox<decltype(box.w)>(box.w)));
}


bool collisionPointCircle(const LX_FloatPosition& p, const LX_Circle& circle) noexcept
{
    return(euclide_square_distance(p, circle.center) <= (circle.radius * circle.radius));
}


bool collisionBox(const LX_FloatingBox& rect1, const LX_FloatingBox& rect2) noexcept
{
    return !((rect1.p.x >= (rect2.p.x + fbox<decltype(rect2.w)>(rect2.w)))
             || (rect1.p.y >= (rect2.p.y + fbox<decltype(rect2.h)>(rect2.h)))
             || ((rect1.p.x + fbox<decltype(rect1.w)>(rect1.w)) <= rect2.p.x)
             || ((rect1.p.y + fbox<decltype(rect1.h)>(rect1.h)) <= rect2.p.y));
}


bool collisionCircle(const LX_Circle& circle1, const LX_Circle& circle2) noexcept
{
    const uint32_t TMP_R = circle1.radius + circle2.radius;
    return euclide_square_distance(circle1.center,
                                   circle2.center) <= fbox<decltype(TMP_R)>(TMP_R * TMP_R);
}


bool collisionSegCircle(const LX_Circle& circle, const LX_Segment& S) noexcept
{
    const LX_Vector2D V{ S.q.x - S.p.x, S.q.y - S.p.y };
    return collisionLineCircle(circle, LX_Line{ S.p, V });
}

bool collisionLineCircle(const LX_Circle& circle, const LX_Line& L) noexcept
{
    const LX_FloatPosition A = L.o;
    const LX_FloatPosition B{L.o.x + L.v.vx, L.o.y + L.v.vy};

    if(collisionPointCircle(A, circle) || collisionPointCircle(B, circle))
        return true;

    const LX_FloatPosition O = circle.center;
    LX_Vector2D AB{B.x - A.x, B.y - A.y};
    LX_Vector2D AO{O.x - A.x, O.y - A.y};
    LX_Vector2D BO{O.x - B.x, O.y - B.y};

    // Using the opposite value of vx for scal2
    const Float& scal_ab_ao  = scalar_product(AB, AO);
    const Float& scal_mab_bo = ((-AB.vx) * BO.vx) + ((-AB.vy) * BO.vy);

    if(scal_ab_ao < FNIL || scal_mab_bo < FNIL)
        return false;

    // Find the projection point of O
    const Float& scalp = scalar_product(AB, AB);

    if(scalp == FNIL)        // A and B are the same point
        return false;

    const Float& T = scal_ab_ao / scalp;
    const Float& x = A.x + (T * AB.vx);
    const Float& y = A.y + (T * AB.vy);

    // Ok I can calculate the collision by using ↓ the projection point
    return collisionPointCircle(LX_FloatPosition{x, y}, circle);
}


bool collisionCircleBox(const LX_Circle& circle, const LX_FloatingBox& box) noexcept
{
    // Check if the center of the circle is in the AABB
    if(collisionPointBox(circle.center, box))
        return true;
    const Float BOX_W = fbox<decltype(box.w)>(box.w);
    const Float BOX_H = fbox<decltype(box.h)>(box.h);
    const LX_Line sides[] =
    {
        LX_Line{ box.p, LX_Vector2D{ FNIL, BOX_H } },

        LX_Line{
            LX_FloatPosition{ box.p.x, box.p.y + BOX_H },
            LX_Vector2D{ BOX_W, FNIL }
        },

        LX_Line{
            LX_FloatPosition{ box.p.x + BOX_W, box.p.y },
            LX_Vector2D{ FNIL, BOX_H }
        },

        LX_Line{ box.p, LX_Vector2D{ BOX_W, FNIL } }
    };

    for(const LX_Line& l : sides)
    {
        if(collisionLineCircle(circle, l))
            return true;
    }

    return false;
}


bool intersectSegment(const LX_Segment& S, const LX_Segment& T) noexcept
{
    return intersectSeg_(S.p, S.q, T.p, T.q) && intersectSeg_(T.p, T.q, S.p, S.q);
}

bool intersectLine(const LX_Line& L1, const LX_Line& L2) noexcept
{
    return !L1.isParralelWith(L2) && !L2.isParralelWith(L1);
}


bool collisionPointPoly(const LX_FloatPosition& P, const LX_Polygon& poly)
{
    const int v = 10000;
    const unsigned long N = poly.numberOfEdges();
    const float RIX = LX_Random::fxrand(0.0f, 100.0f);
    const float RIY = LX_Random::fxrand(0.0f, 100.0f);

    LX_FloatPosition I{v + RIX, v + RIY};
    unsigned long nb_intersections = 0;

    for(unsigned long i = 0UL; i < N; ++i)
    {
        const LX_FloatPosition& A = poly.getPoint(i);
        const LX_FloatPosition& B = poly.getPoint((i == N - 1UL) ? 0UL: i + 1UL);

        if(P == A)
            return true;

        if(intersectSegment(LX_Segment{P, I}, LX_Segment{A, B}))
            nb_intersections++;
    }

    return (nb_intersections % 2UL == 1UL);
}


bool collisionCirclePoly(const LX_Circle& C, const LX_Polygon& poly)
{
    const LX_FloatPosition P = C.center;
    const unsigned long N = poly.numberOfEdges();

    if(collisionPointPoly(P, poly))
        return true;

    for(unsigned long i = 0UL; i < N; ++i)
    {
        const LX_FloatPosition& A = poly.getPoint(i);
        const LX_FloatPosition& B = poly.getPoint((i == N - 1UL) ? 0UL: i + 1UL);

        if(collisionSegCircle(C, LX_Segment{A, B}))
            return true;
    }

    return false;
}


bool collisionBoxPoly(const LX_FloatingBox& box, const LX_Polygon& poly)
{
    const unsigned long n = poly.numberOfEdges();
    const Float BOX_W = fbox<decltype(box.w)>(box.w);
    const Float BOX_H = fbox<decltype(box.h)>(box.h);
    const LX_FloatPosition A = box.p;
    const LX_FloatPosition B = { box.p.x + BOX_W, box.p.y };
    const LX_FloatPosition C = { box.p.x + BOX_W, box.p.y + BOX_H };
    const LX_FloatPosition D = { box.p.x, box.p.y + BOX_H };

    for(unsigned long j = 0UL; j < n; ++j)
    {
        const LX_FloatPosition& E = poly.getPoint(j);
        const LX_FloatPosition& F = poly.getPoint((j == n - 1UL) ? 0UL : j + 1UL);
        const LX_Segment AB{A, B};
        const LX_Segment EF{E, F};

        if(intersectSegment(AB, EF) || intersectSegment(LX_Segment{B, C}, EF)
                || intersectSegment(LX_Segment{C, D}, EF)
                || intersectSegment(LX_Segment{D, A}, EF))
            return true;

        if(collisionPointBox(E, box))
            return true;
    }

    return(collisionPointPoly(A, poly) || collisionPointPoly(B, poly)
           || collisionPointPoly(C, poly) || collisionPointPoly(D, poly));
}


bool collisionPoly(const LX_Polygon& poly1, const LX_Polygon& poly2)
{
    const unsigned long NUM_SIDES = 3UL;
    const unsigned long N = poly1.numberOfEdges();
    const unsigned long M = poly2.numberOfEdges();

    if(N < NUM_SIDES || M < NUM_SIDES)
        throw std::invalid_argument("The polygons must have at least "
                                    "3 sides to calculate the collision");

    // Detect the collision by using the AABB of the polygons -> O(n)
    if(!approximativeCollisionPoly(poly1, poly2))
        return false;

    // If the two polygons are convex and have at least 4 sides,
    // use the SAT to detect the collision between then. -> O(n)
    if(poly1.isConvex() && poly2.isConvex() && N > NUM_SIDES && M > NUM_SIDES)
        return collisionPolySAT(poly1, poly2);

    // On of the polygons is not convex -> naive algorithm, -> O(n²)
    return basicCollisionPoly(poly1, poly2);
}


void movePoint(LX_FloatPosition& P, const LX_Vector2D& v) noexcept
{
    P.x += v.vx;
    P.y += v.vy;
}

void moveBox(LX_FloatingBox& box, const LX_Vector2D& v) noexcept
{
    box.p.x += v.vx;
    box.p.y += v.vy;
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

void moveBoxTo(LX_FloatingBox& box, const LX_FloatPosition& P) noexcept
{
    box.p = P;
}

void moveCircleTo(LX_Circle& C, const LX_FloatPosition& P) noexcept
{
    movePointTo(C.center, P);
}

void movePolyTo(LX_Polygon& poly, const LX_FloatPosition& P) noexcept
{
    poly.moveTo(P);
}

}
