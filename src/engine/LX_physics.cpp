

/*
*	Copyright (C) 2014 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX-engine is a SDL-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_physics.cpp
*	@brief The LX_physics file. It contains all definitions of member functions
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.1
*	@date July 14th, 2014
*
*/
#include "LX_physics.h"


/**
*
*	@fn int LX_physics::euclide_square_distance( int x1, int y1, int x2, int y2)
*
*	This function calculates the Euclide square distance
*
*	@param	x1 The x location of the first hitbox
*   @param  y1 The y location of the first hitbox
*	@param	x2 The x location of the second hitbox
*   @param	y2 The y location of the second hitbox
*
*	@return an integer value
*
*/
int LX_physics::euclide_square_distance( int x1, int y1, int x2, int y2)
{
    return( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) );
}


/**
*
*	@fn int LX_physics::euclide_distance( int x1, int y1, int x2, int y2)
*
*	This function calculates the Euclide distance
*
*	@param	x1 The x location of the first hitbox
*   @param  y1 The y location of the first hitbox
*	@param	x2 The x location of the second hitbox
*   @param	y2 The y location of the second hitbox
*
*	@return an integer value
*
*/
int LX_physics::euclide_distance( int x1, int y1, int x2, int y2)
{
    return sqrt(euclide_square_distance(x1,y1,x2,y2));
}



/**
*
*	@fn bool LX_physics::collision(int x_pos, int y_pos, const LX_AABB *rect)
*
*	Check the collision between a point and an Axis Aligned Bouding Box (AABB)
*
*	@param	x_pos the x position of the point
*   @param  y_pos the y position of the point
*   @param	rect the AABB
*
*	@return TRUE if there is a collision, FALSE otherwise
*
*/
bool LX_physics::collision(int x_pos, int y_pos, const LX_AABB *rect)
{

    if( x_pos <= rect->x || y_pos >= (rect->y + rect->h) ||
            y_pos <= rect->y || x_pos >= (rect->x + rect->w) )
        return false;

    return true;

}


/**
*
*	@fn bool LX_physics::collision(int x_pos, int y_pos, const LX_Circle *circle)
*
*	Check the collision between a point and a circle
*
*	@param	x_pos the x position of the point
*   @param  y_pos the y position of the point
*   @param	circle the circle
*
*	@return TRUE if there is a collision, FALSE otherwise
*
*/
bool LX_physics::collision(int x_pos, int y_pos, const LX_Circle *circle)
{

    if (euclide_square_distance( x_pos,y_pos, circle->xCenter, circle->yCenter) > (circle->square_radius) )
        return false;

    return true;
}



/**
*
*	@fn bool LX_physics::collision(const LX_AABB *rect1, const LX_AABB *rect2)
*
*	Check the collision between two Axis Aligned Bouding Box (AABB)
*
*	@param	rect1 the first AABB
*   @param	rect2 the second AABB
*
*	@return TRUE if there is a collision, FALSE otherwise
*
*/
bool LX_physics::collision(const LX_AABB *rect1, const LX_AABB *rect2)
{

    if( (rect1->x >= (rect2->x + rect2->w) ) || ( rect1->y >= (rect2->y + rect2->h) ) ||
        ( (rect1->x + rect1->w ) <= rect2->x ) || ( (rect1->y + rect1->h ) <= rect2->y ) )
        return false;

    return true;
}

/**
*
*	@fn bool LX_physics::collision(const LX_Circle *circle1, const LX_Circle *circle2)
*
*	Check the collision between two circles
*
*	@param	circle1 the circle
*   @param	circle2 the circle
*
*	@return TRUE if there is a collision, FALSE otherwise
*
*/
bool LX_physics::collision(const LX_Circle *circle1, const LX_Circle *circle2)
{
    if (euclide_square_distance( circle1->xCenter, circle1->yCenter, circle2->xCenter, circle2->yCenter) > circle1->square_radius )
        return false;

    return true;
}


/**
*
*	@fn bool LX_physics::collision(const LX_Circle *circle, const LX_Point *A, const LX_Point *B)
*
*	Check the collision between a circle and the [AB] segment
*
*	@param	circle the circle
*   @param	A one of the two point segment
*   @param	B another one of the two point segment
*
*	@return TRUE if there is a collision, FALSE otherwise
*
*/
bool LX_physics::collision(const LX_Circle *circle, const LX_Point *A, const LX_Point *B)
{
    LX_Point O= {circle->xCenter, circle->yCenter};

    double dx0 = O.x - A->x;
    double dy0 = O.y - A->y;

    double dx = B->x - A->x;
    double dy = B->y - A->y;

    int som = (int) ((dx*dx)+(dy*dy));  // som must be an integer to avoid a value like 0.5

    if(som == 0)        //this test is necessary because we divide the next expression by it
        return false;

    double t = (double) ( ((dx0*dx) + (dy0*dy))/som );  // casting in double value to avoid the accuracy loss

    double x = A->x + (t*dx);
    double y = A->y + (t*dy);

    // The projected point
    LX_Point M = {(int) x,(int) y};
    int AB_distance = euclide_square_distance(A->x, A->y, B->x, B->y);

    //int radius = circle->getRadius();


    //If M is not into the [AB] segment, check if A or B is into the circle
    if( euclide_square_distance(A->x, A->y, M.x, M.y) > AB_distance || euclide_square_distance(B->x, B->y, M.x, M.y) > AB_distance )
    {
        return( ( euclide_square_distance(O.x, O.y, A->x, A->y) < circle->square_radius ) || ( euclide_square_distance(O.x, O.y, B->x, B->y) < circle->square_radius ) );
    }

    //If M is into the [AB] segment, check if M is into the circle
    return ( euclide_square_distance(O.x, O.y, M.x, M.y) <  circle->square_radius );
}


/**
*
*	@fn bool LX_physics::collision(const LX_Circle *circle, const LX_AABB *rect)
*
*	Check the collision between a circle and a AABB
*
*	@param	circle the circle
*   @param	rect the AABB
*
*	@return TRUE if there is a collision, FALSE otherwise
*
*/
bool LX_physics::collision(const LX_Circle *circle, const LX_AABB *rect)
{
    //check if the circle is completly into the AABB
    if( collision(circle->xCenter, circle->yCenter,rect))
    {
        return true;
    }

    LX_Point sides[RECT_SIDES][2]; //4 segments

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


/**
*
*	@fn bool LX_physics::collision(const LX_Circle *circle, LX_Polygon *polygon)
*
*	Check the collision between a circle and a polygon
*
*	@param	circle the circle
*   @param	polygon the LX_Polygon
*
*	@return TRUE if there is a collision, FALSE otherwise
*
*/
bool LX_physics::collision(const LX_Circle *circle, LX_Polygon *polygon)
{
    /// @todo Check the circle into the polygon

    int size = polygon->getSize();

    LX_Point A;
    LX_Point B;
    LX_Point *tmp=NULL;

    for(int i=0; i<size;i++)
    {
        tmp = polygon->getLX_PointAt(i);

        if(tmp == NULL)
        {
            fprintf(stderr,"ERROR occured in LX_physics::collision(Circle *circle, LX_Polygon *polygon) \n");
            return false;
        }

        A.x = tmp->x;
        A.y = tmp->y;

        if(i == size-1 )
        {
            tmp = polygon->getLX_PointAt(0);
            B.x = tmp->x;
            B.y = tmp->y;
        }
        else
        {
            tmp = polygon->getLX_PointAt(i+1);
            B.x = tmp->x;
            B.y = tmp->y;
        }

        //free(tmp);

        if(collision(circle,&A,&B))
            return true;
    }

    return false;
}
























