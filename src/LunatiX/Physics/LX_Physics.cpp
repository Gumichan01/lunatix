

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
#include <LunatiX/LX_Vector2D.hpp>
#include <LunatiX/LX_Polygon.hpp>
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
    int p1_xmin, p1_xmax, p1_ymin, p1_ymax;
    int p2_xmin, p2_xmax, p2_ymin, p2_ymax;
    LX_AABB box1 = poly1.getEnclosingBox();
    LX_AABB box2 = poly2.getEnclosingBox();

    // min values
    p1_xmin = box1.x;
    p1_ymin = box1.y;
    p2_xmin = box2.x;
    p2_ymin = box2.y;
    // max values
    p1_xmax = box1.x + box1.w;
    p1_ymax = box1.y + box1.h;
    p2_xmax = box2.x + box2.w;
    p2_ymax = box2.y + box2.h;

    return intersetInterval(p1_xmin, p1_xmax, p2_xmin, p2_xmax)
           && intersetInterval(p1_ymin, p1_ymax, p2_ymin, p2_ymax);
}

// Collision detection between polygons using their AABB
bool approximativeCollisionPoly(const LX_Physics::LX_Polygon& poly1,
                                const LX_Physics::LX_Polygon& poly2)
{
    LX_AABB box1 = poly1.getEnclosingBox();
    LX_AABB box2 = poly2.getEnclosingBox();
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

    LX_Physics::LX_FloatPosition origin1 = poly1.getPoint(0);
    LX_Physics::LX_FloatPosition origin2 = poly2.getPoint(0);

    return (collisionPointPoly(origin1, poly2)
            || collisionPointPoly(origin2, poly1));
}

}


namespace LX_Physics
{

const int RECT_SIDES = 4;   // The number of sides of a rectangle (AABB)

unsigned int euclide_square_distance(const int x1, const int y1,
                                     const int x2, const int y2) noexcept
{
    return static_cast<unsigned int>( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) );
}


float euclide_distance(const int x1, const int y1,
                       const int x2, const int y2) noexcept
{
    return static_cast<float>(sqrt(euclide_square_distance(x1, y1, x2, y2)));
}


unsigned int euclide_square_distance(const LX_FloatPosition& p1,
                                     const LX_FloatPosition& p2) noexcept
{
    return euclide_square_distance(p1.x, p1.y, p2.x, p2.y);
}


float euclide_distance(const LX_FloatPosition& p1, const LX_FloatPosition& p2) noexcept
{
    return static_cast<float>(sqrt(euclide_square_distance(p1, p2)));
}


bool collisionPointRect(const int xpos, const int ypos, const LX_AABB& rect) noexcept
{
    return !(xpos <= rect.x || ypos >= (rect.y + rect.h) || ypos <= rect.y
             || xpos >= (rect.x + rect.w));
}


bool collisionPointRect(const LX_FloatPosition& p,const LX_AABB& rect) noexcept
{
    return collisionPointRect(p.x, p.y, rect);
}


bool collisionPointCircle(const int xpos, const int ypos, const LX_Circle& circle) noexcept
{
    return collisionPointCircle(LX_FloatPosition{xpos, ypos}, circle);
}


bool collisionPointCircle(const LX_FloatPosition& p, const LX_Circle& circle) noexcept
{
    return(euclide_square_distance(p, circle.center) <= (circle.square_radius));
}


bool collisionRect(const LX_AABB& rect1, const LX_AABB& rect2) noexcept
{
    return !((rect1.x >= (rect2.x + rect2.w)) || (rect1.y >= (rect2.y + rect2.h))
             || ((rect1.x + rect1.w) <= rect2.x) || ((rect1.y + rect1.h) <= rect2.y));
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

    LX_FloatPosition O = circle.center;
    LX_Vector2D AB = LX_Vector2D{B.x - A.x, B.y - A.y};
    LX_Vector2D AO = LX_Vector2D{O.x - A.x, O.y - A.y};
    LX_Vector2D BO = LX_Vector2D{O.x - B.x, O.y - B.y};

    // Using the opposite value of vx for scal2
    Float scal_ab_ao = scalar_product(AB, AO);
    Float scal_mab_bo = ((-AB.vx) * BO.vx) + ((-AB.vy) * BO.vy);

    if(scal_ab_ao < 0 || scal_mab_bo < 0)
        return false;

    // Find the projection point of O
    Float scalp = scalar_product(AB, AB);

    if(scalp == 0.0f)        // A and B are the same point
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

bool collisionCircleRect(const LX_Circle& circle, const LX_AABB& rect) noexcept
{
    // Check if the center of the circle is in the AABB
    if(collisionPointRect(circle.center, rect))
        return true;

    LX_Line sides[RECT_SIDES];
    sides[0] = LX_Line(LX_FloatPosition{rect.x, rect.y}, LX_Vector2D{0.0f, PFL(rect.h)});
    sides[1] = LX_Line(LX_FloatPosition{rect.x, rect.y + rect.h}, LX_Vector2D{PFL(rect.w), 0.0f});
    sides[2] = LX_Line(LX_FloatPosition{rect.x + rect.w, rect.y}, LX_Vector2D{0.0f, PFL(rect.h)});
    sides[3] = LX_Line(LX_FloatPosition{rect.x, rect.y}, LX_Vector2D{PFL(rect.w), 0.0f});

    for(int i = 0; i < RECT_SIDES; i++)
    {
        if(collisionLineCircle(circle, sides[i]))
            return true;
    }

    return false;
}


bool intersectSegLine(const LX_FloatPosition& A, const LX_FloatPosition& B,
                      const LX_FloatPosition& C, const LX_FloatPosition& D) noexcept
{
    LX_Vector2D AC, AD, AB;
    float d;

    AB = LX_Vector2D{B.x - A.x, B.y - A.y};
    AC = LX_Vector2D{C.x - A.x, C.y - A.y};
    AD = LX_Vector2D{D.x - A.x, D.y - A.y};
    d = vector_product(AB, AD) * vector_product(AB, AC);

    return (d <= 0.0f);
}


bool intersectSegment(const LX_FloatPosition& A, const LX_FloatPosition& B,
                      const LX_FloatPosition& C, const LX_FloatPosition& D) noexcept
{
    return (intersectSegLine(A, B, C, D) && intersectSegLine(C, D, A, B));
}


bool intersectLine(const LX_Line& L1, const LX_Line& L2) noexcept
{
    return !L1.isParralelWith(L2) && !L2.isParralelWith(L1);
}


bool collisionPointPoly(const LX_FloatPosition& P, const LX_Polygon& poly)
{
    int nb_intersections = 0;

    const int v = 10000;
    const unsigned long n = poly.numberOfEdges();

    const float rix = static_cast<float>(LX_Random::crand100());
    const float riy = static_cast<float>(LX_Random::crand100());
    LX_FloatPosition I{v + rix, v + riy};

    for(unsigned int i = 0; i < n; i++)
    {
        if(i == n-1)
        {
            LX_FloatPosition p1 = poly.getPoint(0);
            LX_FloatPosition p2 = poly.getPoint(i);

            if(intersectSegment(P, I, p1, p2))
                nb_intersections++;
        }
        else
        {
            LX_FloatPosition p3 = poly.getPoint(i+1);
            LX_FloatPosition p4 = poly.getPoint(i);

            if(intersectSegment(P, I, p3, p4))
                nb_intersections++;
        }
    }

    return (nb_intersections % 2 == 1);
}


bool collisionCirclePoly(const LX_Circle& C, const LX_Polygon& poly)
{
    LX_FloatPosition A, B;
    const LX_FloatPosition P = C.center;
    const unsigned long n = poly.numberOfEdges();

    if(collisionPointPoly(P, poly) == true)
        return true;

    for(unsigned int i = 0; i < n; i++)
    {
        A = poly.getPoint(i);

        if(i == n-1)
            B = poly.getPoint(0);
        else
            B = poly.getPoint(i+1);

        if(collisionSegCircle(C, A, B) == true)
            return true;
    }

    return false;
}


bool collisionRectPoly(const LX_AABB& rect, const LX_Polygon& poly)
{
    LX_FloatPosition A = LX_FloatPosition{rect.x, rect.y};
    LX_FloatPosition B = LX_FloatPosition{rect.x + rect.w, rect.y};
    LX_FloatPosition C = LX_FloatPosition{rect.x + rect.w, rect.y + rect.h};
    LX_FloatPosition D = LX_FloatPosition{rect.x, rect.y + rect.h};

    LX_FloatPosition E, F;
    const unsigned long n = poly.numberOfEdges();

    for(unsigned int j = 0; j < n; j++)
    {
        E = poly.getPoint(j);

        if(j == n-1)
            F = poly.getPoint(0);
        else
            F = poly.getPoint(j+1);

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


void movePoint(LX_FloatPosition& P, const int vx, const int vy) noexcept
{
    P.x += vx;
    P.y += vy;
}

void movePoint(LX_FloatPosition& P, const LX_Vector2D& v) noexcept
{
    movePoint(P, static_cast<int>(v.vx), static_cast<int>(v.vy));
}


void moveRect(LX_AABB& rect, const int vx, const int vy) noexcept
{
    rect.x += vx;
    rect.y += vy;
}

void moveRect(LX_AABB& rect, const LX_Vector2D& v) noexcept
{
    moveRect(rect, static_cast<int>(v.vx), static_cast<int>(v.vy));
}


void moveCircle(LX_Circle& C, const int vx, const int vy) noexcept
{
    movePoint(C.center, vx, vy);
}

void moveCircle(LX_Circle& C, const LX_Vector2D& v) noexcept
{
    moveCircle(C, static_cast<int>(v.vx), static_cast<int>(v.vy));
}


void movePoly(LX_Polygon& poly, const float vx, const float vy) noexcept
{
    poly.move(vx, vy);
}

void movePoly(LX_Polygon& poly, const LX_Vector2D& v) noexcept
{
    poly.move(v);
}


void movePointTo(LX_FloatPosition& P, const int xpos, const int ypos) noexcept
{
    P.x = {xpos};
    P.y = {ypos};
}


void moveRectTo(LX_AABB& rect, const int xpos, const int ypos) noexcept
{
    rect.x = xpos;
    rect.y = ypos;
}

void moveRectTo(LX_AABB& rect, const LX_FloatPosition& P) noexcept
{
    moveRectTo(rect, P.x, P.y);
}

void moveCircleTo(LX_Circle& C, const int xpos, const int ypos) noexcept
{
    movePointTo(C.center, xpos, ypos);
}

void moveCircleTo(LX_Circle& C, const LX_FloatPosition& P) noexcept
{
    moveCircleTo(C, P.x, P.y);
}

void movePolyTo(LX_Polygon& poly, const int xpos, const int ypos)
{
    poly.moveTo(xpos, ypos);
}

void movePolyTo(LX_Polygon& poly, const LX_FloatPosition& P)
{
    movePolyTo(poly, P.x, P.y);
}

}
