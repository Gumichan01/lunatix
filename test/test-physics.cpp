

#include <cmath>

#include <iostream>

#include "../src/engine/Lunatix_engine.hpp"
#include "../src/engine/LX_Vector2D.hpp"

using namespace std;
using namespace LX_Physics;


void test_euclide(void);
void test_collisionPointCircle(void);
void test_collisionPointRect(void);
void test_collision2Circle(void);
void test_collision2Rect(void);
void test_collisionRectCircle(void);

void test_Vector2D(void);
void testPolygon(void);


int main(int argc, char **argv)
{
    bool err = false;

    cout << " ==== Test Physics ==== " << endl;

    err = LX_Init();

    if(!err)
        cerr << "FAILURE - Init does not work" << endl;
    else
        cout << "SUCCESS - LunatiX Engine have been initialized with success" << endl;

    test_euclide();
    test_collisionPointCircle();
    test_collisionPointRect();
    test_collision2Circle();
    test_collision2Rect();
    test_collisionRectCircle();

    test_Vector2D();
    testPolygon();

    LX_Quit();

    cout << " ==== END Physics ==== " << endl;

    return EXIT_SUCCESS;
}


// Test the euclidean functions
void test_euclide(void)
{

    LX_Point A = {1,1};
    LX_Point B = {10,1};

    LX_Point C = {0,0};
    LX_Point D = {10,10};

    int d;

    cout << " = TEST EUCLIDE = " << endl;

    d = euclide_square_distance(&A,&B);

    if(d != 81)
        cerr << "FAILURE - Bad square distance of AB - expected : 81; got : " << d << endl;
    else
        cout << "SUCCESS - Good square distance of AB : " << d << endl;

    d = euclide_distance(&A,&B);

    if(d != 9)
        cerr << "FAILURE - Bad distance of AB - expected : 9; got : " << d << endl;
    else
        cout << "SUCCESS - Good distance of AB : " << d << endl;

    // Test CD

    d = euclide_square_distance(&C,&D);

    if(d != 200)
        cerr << "FAILURE - Bad square distance of CD - expected : 200; got : " << d << endl;
    else
        cout << "SUCCESS - Good square distance of CD : " << d << endl;

    d = euclide_distance(&C,&D);

    if(d != ( (int) sqrt(200)) )
        cerr << "FAILURE - Bad distance of CD - expected : " << (int) sqrt(200) << "; got : " << d << endl;
    else
        cout << "SUCCESS - Good distance of CD : " << d << endl;

    cout << " = END TEST = " << endl;

}


void test_collisionPointCircle(void)
{
    LX_Point A,B,C,D;
    LX_Circle c;

    bool d;

    c = {100,100,10,100};

    A = {100,100};
    B = {50,50};
    C = {105,105};
    D = {100,125};

    cout << " = TEST POINT/CIRCLE = " << endl;

    d = collision(A.x,A.y,&c);

    if(d != true)
        cerr << "FAILURE - expected : TRUE ; got : " << d << endl;
    else
        cout << "SUCCESS - collision, the point is the center : " << d << endl;

    d = collision(B.x,B.y,&c);

    if(d != false)
        cerr << "FAILURE - expected : FALSE; got : TRUE" << endl;
    else
        cout << "SUCCESS - collision, the point is not in the circle"<< endl;

    d = collision(C.x,C.y,&c);

    if(d != true)
        cerr << "FAILURE - expected : TRUE; got : FALSE" << endl;
    else
        cout << "SUCCESS - collision point is in the circle" << endl;

    d = collision(D.x,D.y,&c);

    if(d != false)
        cerr << "FAILURE - expected : FALSE ; got : TRUE" << endl;
    else
        cout << "SUCCESS - collision, the point is not in the circle"<< endl;

    cout << " = END TEST = " << endl;
}


void test_collisionPointRect(void)
{
    LX_Point A,B;
    LX_AABB aabb;

    bool d;

    A = {100,100};
    B = {50,50};
    aabb = {40,40,30,30};

    d = collision(A.x,A.y,&aabb);

    if(d != false)
        cerr << "FAILURE - expected : FALSE; got : TRUE" << endl;
    else
        cout << "SUCCESS - point out of the rect " << endl;

    d = collision(B.x,B.y,&aabb);

    if(d != true)
        cerr << "FAILURE - expected : TRUE; got : FALSE" << endl;
    else
        cout << "SUCCESS - point into the rect " << endl;

}


void test_collision2Circle(void)
{
    LX_Circle A,B,C;
    bool d;

    A = {10,10,5,25};
    B = {13,12,3,9};
    C = {100,100,50,50*50};

    cout << " = TEST CIRCLE/CIRCLE = " << endl;

    d = collision(&A,&B);

    if(d != true)
        cerr << "FAILURE - collisoon A/B expected : TRUE; got : FALSE" << endl;
    else
        cout << "SUCCESS - collision between two circles A and B " << endl;


    d = collision(&C,&B);

    if(d != false)
        cerr << "FAILURE - collisoon C/B expected : FALSE; got : TRUE" << endl;
    else
        cout << "SUCCESS - no collision between two circles C and B " << endl;

    cout << " = END TEST = " << endl;
}



void test_collision2Rect(void)
{
    LX_AABB R1,R2,R3;
    bool d;

    R1 = {0,0,50,25};
    R2 = {40,21,32,25};
    R3 = {64,32,10,100};

    cout << " = TEST RECT/RECT = " << endl;

    d = collision(&R1,&R2);

    if(d != true)
        cerr << "FAILURE - collisoon R1/R2 expected : TRUE; got : FALSE" << endl;
    else
        cout << "SUCCESS - collision R1/R2 OK " << endl;


    d = collision(&R2,&R3);

    if(d != true)
        cerr << "FAILURE - collisoon R2/R3 expected : TRUE; got : FALSE" << endl;
    else
        cout << "SUCCESS - collision R2/R3 OK " << endl;


    d = collision(&R3,&R1);

    if(d != false)
        cerr << "FAILURE - collisoon R3/R1 expected : FALSE; got : TRUE" << endl;
    else
        cout << "SUCCESS - no collision R3/R1 OK " << endl;


}


void test_collisionRectCircle(void)
{
    LX_AABB R1;
    LX_Circle A,B,C;
    bool d;

    R1 = {0,0,50,25};
    A = {10,10,5,25};
    B = {51,26,15,15*15};
    C = {100,100,40,40*40};

    cout << " = TEST RECT/CIRCLE = " << endl;

    d = collision(&A,&R1);

    if(d != true)
        cerr << "FAILURE - collisoon A/R2 expected : TRUE; got : FALSE" << endl;
    else
        cout << "SUCCESS - collision A/R2 OK " << endl;


    d = collision(&B,&R1);

    if(d != true)
        cerr << "FAILURE - collisoon B/R2 expected : TRUE; got : FALSE" << endl;
    else
        cout << "SUCCESS - collision B/R2 OK " << endl;

    d = collision(&C,&R1);

    if(d != false)
        cerr << "FAILURE - collisoon C/R1 expected : FALSE; got : TRUE" << endl;
    else
        cout << "SUCCESS - no collision C/R1 OK " << endl;

    cout << " = END TEST = " << endl;
}


void testPolygon(void)
{
    int d;
    LX_Polygon poly(5);
    LX_Point *p = NULL;

    poly.addPoint(10,5);
    poly.addPoint(10,10);
    poly.addPoint(5,5);


    cout << " = TEST POLYGON = " << endl;


    d = poly.numberOfRealEdges();

    if(d != 3)
        cerr << "FAILURE - number of real edges expected : 3; got : " << d << endl;
    else
        cout << "SUCCESS - number of real edges : " << d << endl;


    d = poly.numberOfEdges();

    if(d != 5)
        cerr << "FAILURE - total number of edges expected : 5; got : " << d << endl;
    else
        cout << "SUCCESS - total number of edges : " << d << endl;

    p = poly.getPoint(5);

    if(p != NULL)
        cerr << "FAILURE - expected : NULL ; got : " << p << endl;
    else
        cout << "SUCCESS - no Point at 5" << endl;


    p = poly.getPoint(0);

    if(p == NULL)
        cerr << "FAILURE - getoint at 0 expected : Not NULL value ; got :  NULL" << endl;
    else
    {
        cout << "SUCCESS - there is a Point at 0" << endl;

        if(p->x != 10)
            cerr << "FAILURE - x position expected : 10 ; got : " << p->x << endl;
        else
            cout << "SUCCESS - x = 10" << endl;

        if(p->y != 5)
            cerr << "FAILURE - y position expected : 5 ; got : " << p->x << endl;
        else
            cout << "SUCCESS - y = 5" << endl;
    }

    // Is the triangle convex ?
    if(poly.isConvex() == false)
        cerr << "FAILURE - A triangle is not a non-convex polygon " << endl;
    else
        cout << "SUCCESS - The triangle is a convex polygon, well done !" << endl;

    // Now we have a polygon with 4 edges
    poly.addPoint(7,2);

    // It must be convex
    if(poly.isConvex() == false)
        cerr << "FAILURE - Expected : convex; got: non-convex " << endl;
    else
        cout << "SUCCESS - Added (7,2). This is still a convex polygon, well done !" << endl;

    // New edge
    poly.addPoint(6,5);

    // It must be non-convex
    if(poly.isConvex() == true)
        cerr << "FAILURE - Expected : non-convex; got: convex " << endl;
    else
        cout << "SUCCESS - Added (6,3). This is not a convex polygon" << endl;

    cout << " = END TEST = " << endl;

}


void test_Vector2D(void)
{
    LX_Vector2D v,u,z;
    int d;

    v.vx = 1;
    v.vy = 2;

    u.vx = 2;
    u.vy = -1;

    z.vx = 0;
    z.vy = 0;


    cout << " = TEST Vector2D = " << endl;

    d = scalar_product(&v,&u);

    if(d != 0)
        cerr << "FAILURE - scalar product v(1,2).u(2,-1) expected: 0 ; got: " << d << endl;
    else
        cout << "SUCCESS - scalar product v(1,2).u(2,-1) = 0" << endl;

    d = scalar_product(&z,&z);

    if(d != 0)
        cerr << "FAILURE - scalar product z.z (z is a null vector) expected: 0 ; got: " << d << endl;
    else
        cout << "SUCCESS - scalar product z.z = 0" << endl;


    d = vector_norm(&z);

    if(d != 0)
        cerr << "FAILURE - norm of z (z is a null vector) expected: 0 ; got: " << d << endl;
    else
        cout << "SUCCESS - norm of z = 0" << endl;


    d = vector_norm(&v);

    if(d != ((int) sqrt(5)) )
        cerr << "FAILURE - norm of v expected: "<< ((int) sqrt(5)) <<" ; got: " << d << endl;
    else
        cout << "SUCCESS - norm of v = 0" << endl;


    d = vector_product(&v,&u);

    if(d != -5)
        cerr << "FAILURE - vector product v(1,2).u(2,-1) expected: -3 ; got: " << d << endl;
    else
        cout << "SUCCESS - vector product v(1,2).u(2,-1) = -3" << endl;


    d = vector_product(&u,&v);

    if(d != 5)
        cerr << "FAILURE - vector product u(2,-1).v(1,2) expected: 3 ; got: " << d << endl;
    else
        cout << "SUCCESS - vector product u(2,-1).v(1,2) = 3" << endl;


    d = vector_product(&z,&z);

    if(d != 0)
        cerr << "FAILURE - vector product z.z (z is a null vector) expected: 0 ; got: " << d << endl;
    else
        cout << "SUCCESS - vector product z.z = 0" << endl;

    cout << " = END TEST = " << endl;
}





















