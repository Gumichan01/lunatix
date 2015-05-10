

/*
*	Copyright (C) 2014-2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	LunatiX Engine is a SDL-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*	Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_Physics.cpp
*	@brief The LX_Physics implementation
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.3
*
*/

#include <cmath>
#include <SDL2/SDL.h>

#include "LX_Physics.hpp"
#include "LX_Vector2D.hpp"
#include "LX_Polygon.hpp"
#include "LX_Error.hpp"


/**
*	@fn unsigned int LX_Physics::euclide_square_distance( int x1, int y1, int x2, int y2)
*
*	This function calculates the euclidean square distance between 2 coordinates
*
*	@param x1 The x location of the first point
*	@param y1 The y location of the first point
*	@param x2 The x location of the second point
*	@param y2 The y location of the second point
*
*	@return An integer value
*
*/
unsigned int LX_Physics::euclide_square_distance( int x1, int y1, int x2, int y2)
{
    return( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) );
}


/**
*	@fn float LX_Physics::euclide_distance( int x1, int y1, int x2, int y2)
*
*	This function calculates the euclidean distance with accuracy
*
*	@param x1 The x location of the first point
*	@param y1 The y location of the first point
*	@param x2 The x location of the second point
*	@param y2 The y location of the second point
*
*	@return An float value
*
*/
float LX_Physics::euclide_distance( int x1, int y1, int x2, int y2)
{
    return sqrt(euclide_square_distance(x1,y1,x2,y2));
}


/**
*	@fn unsigned int LX_Physics::euclide_square_distance( LX_Point *p1, LX_Point *p2)
*
*	This function calculates the euclidean square distance
*
*	@param	p1 The first point
*	@param	p2 The second point
*
*	@return An integer value
*
*/
unsigned int LX_Physics::euclide_square_distance( LX_Point *p1, LX_Point *p2)
{
    return euclide_square_distance(p1->x,p1->y,p2->x,p2->y);
}


/**
*	@fn float LX_Physics::euclide_distance( LX_Point *p1, LX_Point *p2)
*
*	This function calculates the euclidean distance with accuracy
*
*	@param p1 The first point
*	@param p2 The second point
*
*	@return An integer value
*
*/
float LX_Physics::euclide_distance( LX_Point *p1, LX_Point *p2)
{
    return sqrt(euclide_square_distance(p1,p2));
}




/**
*	@fn bool LX_Physics::collision(const int x_pos, const int y_pos, const LX_AABB *rect)
*
*	Check the collision between a point and an Axis Aligned Bouding Box (AABB)
*
*	@param x_pos The x position of the point
*	@param y_pos The y position of the point
*	@param rect The AABB
*
*	@return TRUE if there is a collision, FALSE otherwise
*
*/
bool LX_Physics::collision(const int x_pos, const int y_pos, const LX_AABB *rect)
{

    if( rect == NULL || x_pos <= rect->x || y_pos >= (rect->y + rect->h) ||
            y_pos <= rect->y || x_pos >= (rect->x + rect->w) )
    {
        return false;
    }

    return true;
}



bool LX_Physics::collision(const LX_Point *p,const LX_AABB *rect)
{
    return collision(p->x,p->y,rect);
}


/**
*	@fn bool LX_Physics::collision(const int x_pos, const int y_pos, const LX_Circle *circle)
*
*	Check the collision between a point and a circle
*
*	@param x_pos The x position of the point
*	@param y_pos The y position of the point
*	@param circle The circle
*
*	@return TRUE if there is a collision, FALSE otherwise
*
*/
bool LX_Physics::collision(const int x_pos, const int y_pos, const LX_Circle *circle)
{

    if( circle == NULL ||
        euclide_square_distance( x_pos,y_pos, circle->xCenter, circle->yCenter)
            > (circle->square_radius) )
    {
        return false;
    }

    return true;
}



bool LX_Physics::collision(const LX_Point *p, const LX_Circle *circle)
{
    collision(p->x,p->y,circle);
}




/**
*	@fn bool LX_Physics::collision(const LX_AABB *rect1, const LX_AABB *rect2)
*
*	Check the collision between two Axis Aligned Bouding Box (AABB)
*
*	@param rect1 The first AABB
*	@param rect2 The second AABB
*
*	@return TRUE if there is a collision, FALSE otherwise
*
*/
bool LX_Physics::collision(const LX_AABB *rect1, const LX_AABB *rect2)
{

    if( rect1 == NULL || rect2 == NULL ||
       (rect1->x >= (rect2->x + rect2->w) ) || ( rect1->y >= (rect2->y + rect2->h) ) ||
        ( (rect1->x + rect1->w) <= rect2->x ) || ( (rect1->y + rect1->h) <= rect2->y ) )
    {
        return false;
    }

    return true;
}

/**
*	@fn bool LX_Physics::collision(const LX_Circle *circle1, const LX_Circle *circle2)
*
*	Check the collision between two circles
*
*	@param circle1 The first circle
*	@param circle2 The second circle
*
*	@return TRUE if there is a collision, FALSE otherwise
*
*/
bool LX_Physics::collision(const LX_Circle *circle1, const LX_Circle *circle2)
{
    if(circle1 == NULL || circle2 == NULL)
        return false;

    const unsigned int d = (circle1->radius + circle2->radius) * (circle1->radius + circle2->radius);

    return (euclide_square_distance( circle1->xCenter, circle1->yCenter, circle2->xCenter, circle2->yCenter) <= d );
}


/**
*	@fn bool LX_Physics::collision(const LX_Circle *circle, const LX_Point *A, const LX_Point *B)
*
*	Check the collision between a circle and the [AB] segment
*
*	@param circle The circle
*	@param A The first point of the segment
*	@param B The other point of the segment
*
*	@return TRUE if there is a collision, FALSE otherwise
*
*   @warning If at least one parameter is NULL, the behaviour is undefined
*
*/
bool LX_Physics::collision(const LX_Circle *circle, const LX_Point *A, const LX_Point *B)
{
    LX_Vector2D AB,AC,BC;
    LX_Point M;
    LX_Point O = {circle->xCenter, circle->yCenter};

    float scal1,scal2;
    int sum;
    double t;
    double x,y;

    if( collision(A,circle) || collision(B,circle) )
        return true;


    AB.vx = B->x - A->x;
    AB.vy = B->y - A->y;

    AC.vx = O.x - A->x;
    AC.vy = O.y - A->y;

    BC.vx = O.x - B->x;
    BC.vy = O.y - B->y;


    scal1 = scalar_product(&AB,&AC);
    // I do not change this line because I use the opposite of vx
    scal2 = ( (-AB.vx) * BC.vx) + ( (-AB.vy) * BC.vy);


    if(scal1 < 0 || scal2 < 0)
        return false;

    // Find the projection point of O
    sum = scalar_product(&AB,&AB);

    if(sum == 0)        // A and B are the same point
        return false;

    t = (double) ( scal1/sum );

    x = A->x + (t*AB.vx);
    y = A->y + (t*AB.vy);

    M = {(int) x, (int) y};     // M is the projection point of O

    return collision(&M, circle);

}


/**
*	@fn bool LX_Physics::collision(const LX_Circle *circle, const LX_AABB *rect)
*
*	Check the collision between a circle and a AABB
*
*	@param circle The circle
*	@param rect The AABB
*
*	@return TRUE if there is a collision, FALSE otherwise
*
*   @warning If at least one parameter is NULL, the behaviour is undefined
*
*/
bool LX_Physics::collision(const LX_Circle *circle, const LX_AABB *rect)
{
    // Check if the center of the circle is completly into the AABB
    if( collision(circle->xCenter, circle->yCenter,rect))
    {
        return true;
    }

    LX_Point sides[RECT_SIDES][2];  //4 segments

    //1st segment
    sides[0][0] = {rect->x , rect->y};
    sides[0][1] = {rect->x , rect->y + rect->h};

    //2nd segment
    sides[1][0] = sides[0][1];
    sides[1][1] = {rect->x + rect->w , rect->y + rect->h};

    //3rd segment
    sides[2][0] = sides[1][1];
    sides[2][1] = {rect->x + rect->w, rect->y};

    //4th segment
    sides[3][0] = sides[2][1];
    sides[3][1] = sides[0][0];


    for(int i=0; i< RECT_SIDES ;i++)
    {
        if(collision(circle, &sides[i][0], &sides[i][1]))
            return true;
    }

    return false;
}



bool LX_Physics::intersectSegLine(const LX_Point *A, const LX_Point *B,
                                    const LX_Point *C, const LX_Point *D)
{
    LX_Vector2D AC,AD,AB;
    long d;

    AB.vx = B->x - A->x;
    AB.vy = B->y - A->y;

    AC.vx = C->x - A->x;
    AC.vy = C->y - A->y;

    AD.vx = D->x - A->x;
    AD.vy = D->y - A->y;

    d = vector_product(&AB,&AD) * vector_product(&AB,&AC);

    return (d <= 0);
}



bool LX_Physics::intersectSegment(const LX_Point *A, const LX_Point *B,
                                    const LX_Point *C, const LX_Point *D)
{
    return (intersectSegLine(A,B,C,D) && intersectSegLine(C,D,A,B));
}




bool LX_Physics::collision(const LX_Point *P, const LX_Polygon *poly)
{
    int count = 0;
    LX_Point I;

    const int v = 1;
    const unsigned int n = poly->numberOfEdges();

    I.x = v + rand()%100;
    I.y = v + rand()%100;


    for(int i = 0; i < n; i++)
    {
        if(i == n-1)
        {
            if(intersectSegment(P,&I,poly->getPoint(0),poly->getPoint(i)))
                count++;
        }
        else
        {
            if(intersectSegment(P,&I,poly->getPoint(i+1),poly->getPoint(i)))
                count++;
        }
    }

    return (count%2 == 1);
}



bool LX_Physics::collision(const LX_Circle *C, const LX_Polygon *poly)
{
    const LX_Point P = {C->xCenter,C->yCenter};
    LX_Point A,B;

    if(collision(&P,poly) == true)
        return true;

    const unsigned int n = poly->numberOfEdges();

    for(int i = 0; i < n; i++)
    {
        A.x = poly->getPoint(i)->x;
        A.y = poly->getPoint(i)->y;

        if(i == n-1)
        {
            B.x = poly->getPoint(0)->x;
            B.y = poly->getPoint(0)->y;
        }
        else
        {
            B.x = poly->getPoint(i+1)->x;
            B.y = poly->getPoint(i+1)->y;
        }

        if(collision(C,&A,&B) == true)
            return true;
    }


}


































