

/*
*    Copyright (C) 2016 Luxon Jean-Pierre
*    gumichan01.olympe.in
*
*    LunatiX is a free, SDL2-based library.
*    It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*    Luxon Jean-Pierre (Gumichan01)
*    luxon.jean.pierre@gmail.com
*/

/**
*    @file LX_Physics.cpp
*    @brief The implementation of the physics library
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.8
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
const int RECT_SIDES = 4;   // The number of sides of a rectangle (AABB)

bool intersetInterval(const int min1, const int max1, const int min2, const int max2)
{
    return (min1 < min2) ? max1 > min2 : max2 > min1;
}

void getInterval(const LX_Physics::LX_Polygon& poly1,
                 const LX_Physics::LX_Polygon& poly2,
                 int& p1_xmin, int& p1_xmax, int& p1_ymin, int& p1_ymax,
                 int& p2_xmin, int& p2_xmax, int& p2_ymin, int& p2_ymax)
{
    const unsigned long N = poly1.numberOfEdges();
    const unsigned long M = poly2.numberOfEdges();

    p1_xmin = poly1.getPoint(0).x;
    p1_xmax = poly1.getPoint(0).x;
    p1_ymin = poly1.getPoint(0).y;
    p1_ymax = poly1.getPoint(0).y;
    p2_xmin = poly2.getPoint(0).x;
    p2_xmax = poly2.getPoint(0).x;
    p2_ymin = poly2.getPoint(0).y;
    p2_ymax = poly2.getPoint(0).y;

    for(unsigned int i = 1; i < N; i++)
    {
        LX_Physics::LX_Point p = poly1.getPoint(i);

        // X
        if(p.x < p1_xmin)
            p1_xmin = p.x;

        if(p.x > p1_xmax)
            p1_xmax = p.x;

        // Y
        if(p.y < p1_ymin)
            p1_ymin = p.y;

        if(p.y > p1_ymax)
            p1_ymax = p.y;
    }

    for(unsigned int j = 1; j < M; j++)
    {
        LX_Physics::LX_Point q = poly2.getPoint(j);

        if(q.x < p2_xmin)
            p2_xmin = q.x;

        if(q.x > p2_xmax)
            p2_xmax = q.x;

        if(q.y < p2_ymin)
            p2_ymin = q.y;

        if(q.y > p2_ymax)
            p2_ymax = q.y;
    }
}

// Calcute the collision between two polygons using the Separating Axis Theorem (SAT)
// pre-condition : poly1 and poly2 must be convex with at least 4 sides
bool collisionPolySAT(const LX_Physics::LX_Polygon& poly1,
                      const LX_Physics::LX_Polygon& poly2)
{
    int p1_xmin, p1_xmax, p1_ymin, p1_ymax;
    int p2_xmin, p2_xmax, p2_ymin, p2_ymax;

    getInterval(poly1,poly2,
                p1_xmin,p1_xmax,p1_ymin,p1_ymax,
                p2_xmin,p2_xmax,p2_ymin,p2_ymax);

    return intersetInterval(p1_xmin,p1_xmax,p2_xmin,p2_xmax)
           && intersetInterval(p1_ymin,p1_ymax,p2_ymin,p2_ymax);
}

// Collision detection between polygons using their AABB
bool approximativeCollisionPoly(const LX_Physics::LX_Polygon& poly1,
                                const LX_Physics::LX_Polygon& poly2)
{
    int p1_xmin, p1_xmax, p1_ymin, p1_ymax;
    int p2_xmin, p2_xmax, p2_ymin, p2_ymax;

    getInterval(poly1,poly2,p1_xmin,p1_xmax,p1_ymin,p1_ymax,
                p2_xmin,p2_xmax,p2_ymin,p2_ymax);

    LX_AABB box1 = {p1_xmin, p1_ymin, p1_xmax-p1_xmin, p1_ymax-p1_ymin};
    LX_AABB box2 = {p2_xmin, p2_ymin, p2_xmax-p2_xmin, p2_ymax-p2_ymin};

    return LX_Physics::collisionRect(box1,box2);
}


bool basicCollisionPoly(const LX_Physics::LX_Polygon& poly1,
                        const LX_Physics::LX_Polygon& poly2)
{
    LX_Physics::LX_Point A,B,C,D;
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

            if(intersectSegment(A,B,C,D))
                return true;
        }
    }

    LX_Physics::LX_Point origin1 = poly1.getPoint(0);
    LX_Physics::LX_Point origin2 = poly2.getPoint(0);

    return (collisionPointPoly(origin1,poly2)
            || collisionPointPoly(origin2,poly1));
}

};


namespace LX_Physics
{

unsigned int euclide_square_distance(const int x1, const int y1,
                                     const int x2, const int y2)
{
    return static_cast<unsigned int>( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) );
}


float euclide_distance(const int x1, const int y1,
                       const int x2, const int y2)
{
    return static_cast<float>(sqrt(euclide_square_distance(x1,y1,x2,y2)));
}


unsigned int euclide_square_distance(const LX_Point& p1,
                                     const LX_Point& p2)
{
    return euclide_square_distance(p1.x,p1.y,p2.x,p2.y);
}


float euclide_distance(const LX_Point& p1, const LX_Point& p2)
{
    return static_cast<float>(sqrt(euclide_square_distance(p1,p2)));
}


bool collisionPointRect(const int x_pos, const int y_pos, const LX_AABB& rect)
{

    if(x_pos <= rect.x || y_pos >= (rect.y + rect.h)
            || y_pos <= rect.y || x_pos >= (rect.x + rect.w))
    {
        return false;
    }

    return true;
}


bool collisionPointRect(const LX_Point& p,const LX_AABB& rect)
{
    return collisionPointRect(p.x,p.y,rect);
}


bool collisionPointCircle(const int x_pos, const int y_pos,
                          const LX_Circle& circle)
{
    return collisionPointCircle(LX_Point(x_pos,y_pos),circle);
}


bool collisionPointCircle(const LX_Point& p, const LX_Circle& circle)
{
    return(euclide_square_distance(p,circle.center) <= (circle.square_radius));
}


bool collisionRect(const LX_AABB& rect1, const LX_AABB& rect2)
{
    if((rect1.x >= (rect2.x + rect2.w)) || (rect1.y >= (rect2.y + rect2.h))
            || ((rect1.x + rect1.w) <= rect2.x) || ((rect1.y + rect1.h) <= rect2.y))
    {
        return false;
    }

    return true;
}


bool collisionCircle(const LX_Circle& circle1, const LX_Circle& circle2)
{
    const unsigned int sum_radius = circle1.radius + circle2.radius;
    const unsigned int d = sum_radius * sum_radius;

    return (euclide_square_distance(circle1.center,circle2.center) <= d);
}


bool collisionSegCircle(const LX_Circle& circle,
                        const LX_Point& A, const LX_Point& B)
{
    int sum;
    double t;
    double x,y;
    float scal,scal1,scal2;

    LX_Vector2D AB,AO,BO;
    LX_Point O = circle.center;

    if(collisionPointCircle(A,circle) || collisionPointCircle(B,circle))
        return true;

    AB = LX_Vector2D(B.x - A.x,B.y - A.y);
    AO = LX_Vector2D(O.x - A.x,O.y - A.y);
    BO = LX_Vector2D(O.x - B.x,O.y - B.y);

    // Using the opposite value of vx for scal2
    scal1 = scalar_product(AB,AO);
    scal2 = ((-AB.vx) * BO.vx) + ((-AB.vy) * BO.vy);

    if(scal1 < 0 || scal2 < 0)
        return false;

    // Find the projection point of O
    scal = scalar_product(AB,AB);
    sum = static_cast<int>(scal);

    if(sum == 0)        // A and B are the same point
        return false;

    t = scal1/scal;
    x = A.x + (t*AB.vx);
    y = A.y + (t*AB.vy);

    // M is the projection point of O
    LX_Point M = LX_Point(static_cast<int>(x), static_cast<int>(y));

    return collisionPointCircle(M,circle);
}


bool collisionCircleRect(const LX_Circle& circle, const LX_AABB& rect)
{
    // Check if the center of the circle is in the AABB
    if(collisionPointRect(circle.center,rect))
        return true;

    LX_Point sides[RECT_SIDES][2];  //4 segments

    // 1st segment
    sides[0][0] = LX_Point(rect.x , rect.y);
    sides[0][1] = LX_Point(rect.x , rect.y + rect.h);

    // 2nd segment
    sides[1][0] = sides[0][1];
    sides[1][1] = LX_Point(rect.x + rect.w , rect.y + rect.h);

    // 3rd segment
    sides[2][0] = sides[1][1];
    sides[2][1] = LX_Point(rect.x + rect.w, rect.y);

    // 4th segment
    sides[3][0] = sides[2][1];
    sides[3][1] = sides[0][0];

    for(int i=0; i< RECT_SIDES ; i++)
    {
        if(collisionSegCircle(circle, sides[i][0], sides[i][1]))
            return true;
    }

    return false;
}


bool intersectSegLine(const LX_Point& A, const LX_Point& B,
                      const LX_Point& C, const LX_Point& D)
{
    LX_Vector2D AC,AD,AB;
    float d;

    AB = LX_Vector2D(B.x - A.x,B.y - A.y);
    AC = LX_Vector2D(C.x - A.x,C.y - A.y);
    AD = LX_Vector2D(D.x - A.x,D.y - A.y);
    d = vector_product(AB,AD) * vector_product(AB,AC);

    return (d <= 0.0f);
}


bool intersectSegment(const LX_Point& A, const LX_Point& B,
                      const LX_Point& C, const LX_Point& D)
{
    return (intersectSegLine(A,B,C,D) && intersectSegLine(C,D,A,B));
}


bool collisionPointPoly(const LX_Point& P, const LX_Polygon& poly)
{
    int count = 0;
    LX_Point I;

    const int v = 10000;
    const unsigned long n = poly.numberOfEdges();

    I.x = v + LX_Random::crand100();
    I.y = v + LX_Random::crand100();

    for(unsigned int i = 0; i < n; i++)
    {
        if(i == n-1)
        {
            LX_Point p1 = poly.getPoint(0);
            LX_Point p2 = poly.getPoint(i);

            if(intersectSegment(P,I,p1,p2))
                count++;
        }
        else
        {
            LX_Point p3 = poly.getPoint(i+1);
            LX_Point p4 = poly.getPoint(i);

            if(intersectSegment(P,I,p3,p4))
                count++;
        }
    }

    return (count%2 == 1);
}


bool collisionCirclePoly(const LX_Circle& C, const LX_Polygon& poly)
{
    LX_Point A,B;
    const LX_Point P = C.center;
    const unsigned long n = poly.numberOfEdges();

    if(collisionPointPoly(P,poly) == true)
        return true;

    for(unsigned int i = 0; i < n; i++)
    {
        A = poly.getPoint(i);

        if(i == n-1)
            B = poly.getPoint(0);
        else
            B = poly.getPoint(i+1);

        if(collisionSegCircle(C,A,B) == true)
            return true;
    }

    return false;
}


bool collisionRectPoly(const LX_AABB& rect, const LX_Polygon& poly)
{
    LX_Point E,F;

    LX_Point A = LX_Point(rect.x,rect.y);
    LX_Point B = LX_Point(rect.x + rect.w,rect.y);
    LX_Point C = LX_Point(rect.x + rect.w,rect.y + rect.h);
    LX_Point D = LX_Point(rect.x,rect.y + rect.h);

    const unsigned long n = poly.numberOfEdges();

    for(unsigned int j = 0; j < n; j++)
    {
        E = poly.getPoint(j);

        if(j == n-1)
            F = poly.getPoint(0);
        else
            F = poly.getPoint(j+1);

        if(intersectSegment(A,B,E,F) || intersectSegment(B,C,E,F) ||
                intersectSegment(C,D,E,F) || intersectSegment(D,A,E,F))
            return true;

        if(collisionPointRect(E,rect))
            return true;
    }

    return(collisionPointPoly(A,poly) || collisionPointPoly(B,poly)
           || collisionPointPoly(C,poly) || collisionPointPoly(A,poly));
}


bool collisionPoly(const LX_Polygon& poly1, const LX_Polygon& poly2)
{
    const unsigned int NUM_SIDES = 3;
    const unsigned long N = poly1.numberOfEdges();
    const unsigned long M = poly2.numberOfEdges();

    if(N < NUM_SIDES || M < NUM_SIDES)
        throw std::invalid_argument("The polygons must have at least 3 sides to calculate the collision");

    // Detect the collision using the AABB of the polygons
    if(!approximativeCollisionPoly(poly1,poly2))
        return false;

    // If the two polygons are convex and have at least 4 sides,
    // use the SAT to detect the collision between then.
    if(poly1.isConvex() && poly2.isConvex() && N > NUM_SIDES && M > NUM_SIDES)
        return collisionPolySAT(poly1,poly2);

    return basicCollisionPoly(poly1,poly2);
}


void movePoint(LX_Point& P, const int vx, const int vy)
{
    P.x += vx;
    P.y += vy;
}


void moveRect(LX_AABB& rect, const int vx, const int vy)
{
    rect.x += vx;
    rect.y += vy;
}


void moveCircle(LX_Circle& C, const int vx, const int vy)
{
    movePoint(C.center,vx,vy);
}


void movePoly(LX_Polygon& poly, const float vx, const float vy)
{
    poly.move(vx,vy);
}


void movePoint(LX_Point& P, const LX_Vector2D& v)
{
    movePoint(P,static_cast<int>(v.vx),static_cast<int>(v.vy));
}


void moveRect(LX_AABB& rect, const LX_Vector2D& v)
{
    moveRect(rect,static_cast<int>(v.vx),static_cast<int>(v.vy));
}


void moveCircle(LX_Circle& C, const LX_Vector2D& v)
{
    moveCircle(C,static_cast<int>(v.vx),static_cast<int>(v.vy));
}


void movePoly(LX_Polygon& poly, const LX_Vector2D& v)
{
    poly.move(v);
}


void movePointTo(LX_Point& P, const int xpos, const int ypos)
{
    P = LX_Point(xpos,ypos);
}


void moveRectTo(LX_AABB& rect, const int xpos, const int ypos)
{
    rect.x = xpos;
    rect.y = ypos;
}


void moveCircleTo(LX_Circle& C, const int xpos, const int ypos)
{
    movePointTo(C.center,xpos,ypos);
}


void movePolyTo(LX_Polygon& poly, const int xpos, const int ypos)
{
    poly.moveTo(xpos,ypos);
}

};
