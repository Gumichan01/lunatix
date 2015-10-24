

#include <cmath>

#include <iostream>

#include <LunatiX/Lunatix_engine.hpp>
#include <LunatiX/LX_Vector2D.hpp>

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

void test_collisionSeg(void);
void test_collisionPointPolygon(void);
void test_collisionCirclePolygon(void);
void test_collisionRectPolygon(void);
void test_collision2Polygon(void);

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

    test_collisionSeg();
    test_collisionPointPolygon();
    test_collisionCirclePolygon();
    test_collisionRectPolygon();
    test_collision2Polygon();

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

    d = euclide_square_distance(A,B);

    if(d != 81)
        cerr << "FAILURE - Bad square distance AB - expected : 81; got : " << d << endl;
    else
        cout << "SUCCESS - Good square distance AB : " << d << endl;

    d = euclide_distance(A,B);

    if(d != 9)
        cerr << "FAILURE - Bad distance AB - expected : 9; got : " << d << endl;
    else
        cout << "SUCCESS - Good distance AB : " << d << endl;

    // Test CD

    d = euclide_square_distance(C,D);

    if(d != 200)
        cerr << "FAILURE - Bad square distance CD - expected : 200; got : " << d << endl;
    else
        cout << "SUCCESS - Good square distance CD : " << d << endl;

    d = euclide_distance(C,D);

    if(d != ( (int) sqrt(200)) )
        cerr << "FAILURE - Bad distance CD - expected : " << (int) sqrt(200) << "; got : " << d << endl;
    else
        cout << "SUCCESS - Good distance CD : " << d << endl;

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

    d = collisionPointCircle(A.x,A.y,c);

    if(d != true)
        cerr << "FAILURE - expected : TRUE ; got : " << d << endl;
    else
        cout << "SUCCESS - collision, the point is the center : " << d << endl;

    d = collisionPointCircle(B.x,B.y,c);

    if(d != false)
        cerr << "FAILURE - expected : FALSE; got : TRUE" << endl;
    else
        cout << "SUCCESS - collision, the point is not in the circle"<< endl;

    d = collisionPointCircle(C,c);

    if(d != true)
        cerr << "FAILURE - expected : TRUE; got : FALSE" << endl;
    else
        cout << "SUCCESS - collision point is in the circle" << endl;

    d = collisionPointCircle(D,c);

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

    d = collisionPointRect(A.x,A.y,aabb);

    if(d != false)
        cerr << "FAILURE - expected : FALSE; got : TRUE" << endl;
    else
        cout << "SUCCESS - point out of the rect " << endl;

    d = collisionPointRect(B.x,B.y,aabb);

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

    d = collisionCircle(A,B);

    if(d != true)
        cerr << "FAILURE - collisoon A/B expected : TRUE; got : FALSE" << endl;
    else
        cout << "SUCCESS - collision between two circles A and B " << endl;


    d = collisionCircle(C,B);

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

    d = collisionRect(R1,R2);

    if(d != true)
        cerr << "FAILURE - collisoon R1/R2 expected : TRUE; got : FALSE" << endl;
    else
        cout << "SUCCESS - collision R1/R2 OK " << endl;


    d = collisionRect(R2,R3);

    if(d != true)
        cerr << "FAILURE - collisoon R2/R3 expected : TRUE; got : FALSE" << endl;
    else
        cout << "SUCCESS - collision R2/R3 OK " << endl;


    d = collisionRect(R3,R1);

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

    d = collisionCircleRect(A,R1);

    if(d != true)
        cerr << "FAILURE - collisoon A/R2 expected : TRUE; got : FALSE" << endl;
    else
        cout << "SUCCESS - collision A/R2 OK " << endl;


    d = collisionCircleRect(B,R1);

    if(d != true)
        cerr << "FAILURE - collisoon B/R2 expected : TRUE; got : FALSE" << endl;
    else
        cout << "SUCCESS - collision B/R2 OK " << endl;

    d = collisionCircleRect(C,R1);

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
    LX_Point p;

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


    p = poly.getPoint(0);

    if(p.x != 10)
        cerr << "FAILURE - x position expected : 10 ; got : " << p.x << endl;
    else
        cout << "SUCCESS - x = 10" << endl;

    if(p.y != 5)
        cerr << "FAILURE - y position expected : 5 ; got : " << p.y << endl;
    else
        cout << "SUCCESS - y = 5" << endl;


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

    d = scalar_product(v,u);

    if(d != 0)
        cerr << "FAILURE - scalar product v(1,2).u(2,-1) expected: 0 ; got: " << d << endl;
    else
        cout << "SUCCESS - scalar product v(1,2).u(2,-1) = 0" << endl;

    d = scalar_product(z,z);

    if(d != 0)
        cerr << "FAILURE - scalar product z.z (z is a null vector) expected: 0 ; got: " << d << endl;
    else
        cout << "SUCCESS - scalar product z.z = 0" << endl;


    d = vector_norm(z);

    if(d != 0)
        cerr << "FAILURE - norm of z (z is a null vector) expected: 0 ; got: " << d << endl;
    else
        cout << "SUCCESS - norm of z = 0" << endl;


    d = vector_norm(v);

    if(d != ((int) sqrt(5)) )
        cerr << "FAILURE - norm of v expected: "<< ((int) sqrt(5)) <<" ; got: " << d << endl;
    else
        cout << "SUCCESS - norm of v = 0" << endl;


    d = vector_product(v,u);

    if(d != -5)
        cerr << "FAILURE - vector product v(1,2).u(2,-1) expected: -3 ; got: " << d << endl;
    else
        cout << "SUCCESS - vector product v(1,2).u(2,-1) = -3" << endl;


    d = vector_product(u,v);

    if(d != 5)
        cerr << "FAILURE - vector product u(2,-1).v(1,2) expected: 3 ; got: " << d << endl;
    else
        cout << "SUCCESS - vector product u(2,-1).v(1,2) = 3" << endl;


    d = vector_product(z,z);

    if(d != 0)
        cerr << "FAILURE - vector product z.z (z is a null vector) expected: 0 ; got: " << d << endl;
    else
        cout << "SUCCESS - vector product z.z = 0" << endl;

    cout << " = END TEST = " << endl;
}


void test_collisionSeg(void)
{
    LX_Point A,B,C,D,E,F;
    bool d;

    A.x = 5;
    A.y = 5;

    B.x = 10;
    B.y = 10;

    C.x = 5;
    C.y = 10;

    D.x = 10;
    D.y = 5;

    E.x = 20;
    E.y = 5;

    F.x = 15;
    F.y = 5;

    cout << " = TEST Collision Segment = " << endl;

    d = intersectSegment(A,B,C,D);

    if(d != true)
        cerr << "FAILURE - intersect [AB]/[CD] expected: TRUE ; got: FALSE" << endl;
    else
        cout << "SUCCESS - intersect [AB]/[CD] OK" << endl;


    d = intersectSegment(A,C,B,D);

    if(d != false)
        cerr << "FAILURE - intersect [AC]/[BD] expected: FALSE ; got: TRUE" << endl;
    else
        cout << "SUCCESS - no intersect [AC]/[BD] OK" << endl;


    d = intersectSegment(A,B,A,D);

    if(d != true)
        cerr << "FAILURE - intersect [AB]/[AD] expected: TRUE ; got: FALSE" << endl;
    else
        cout << "SUCCESS - intersect [AB]/[AD] OK" << endl;


    d = intersectSegment(A,D,A,E);

    if(d != true)
        cerr << "FAILURE - intersect [AD]/[AE] expected: TRUE ; got: FALSE" << endl;
    else
        cout << "SUCCESS - intersect [AD]/[AE] OK" << endl;


    d = intersectSegment(A,D,F,E);

    if(d != true)
        cerr << "FAILURE - intersect [AD]/[FE] expected: FALSE ; got: TRUE" << endl;
    else
        cout << "SUCCESS - no intersect [AD]/[FE] OK" << endl;

    cout << " = END TEST = " << endl;
}


void test_collisionPointPolygon(void)
{
    /*
        Be careful, if the coordinates of a point
        are to high, you will have incorrect results
    */
    LX_Polygon poly(5);
    int d;

    LX_Point N = {12,7};
    LX_Point O = {9,7};
    LX_Point P = {6,5};
    LX_Point Q = {6,4};
    LX_Point R = {1024,2048};
    LX_Point S = {2,2};


    poly.addPoint(10,5);
    poly.addPoint(10,10);
    poly.addPoint(5,5);
    poly.addPoint(7,2);
    poly.addPoint(6,5);

    cout << " = TEST Collision Point/Polygon = " << endl;

    d = collisionPointPoly(N,poly);

    if(d != false)
        cerr << "FAILURE - N in the polygon. expected: FALSE ; got: TRUE" << endl;
    else
        cout << "SUCCESS - N not in the polygon OK" << endl;

    d = collisionPointPoly(O,poly);

    if(d != true)
        cerr << "FAILURE - O not in the polygon. expected: TRUE ; got: FALSE" << endl;
    else
        cout << "SUCCESS - O in the polygon OK" << endl;

    d = collisionPointPoly(P,poly);

    if(d != true)
        cerr << "FAILURE - P not in the polygon. expected: TRUE ; got: FALSE" << endl;
    else
        cout << "SUCCESS - P in the polygon OK" << endl;


    d = collisionPointPoly(Q,poly);

    if(d != true)
        cerr << "FAILURE - Q not in the polygon. expected: TRUE ; got: FALSE" << endl;
    else
        cout << "SUCCESS - Q in the polygon OK" << endl;


    d = collisionPointPoly(R,poly);

    if(d != false)
        cerr << "FAILURE - R in the polygon. expected: FALSE ; got: TRUE" << endl;
    else
        cout << "SUCCESS - R not in the polygon OK" << endl;


    d = collisionPointPoly(S,poly);

    if(d != false)
        cerr << "FAILURE - S in the polygon. expected: FALSE ; got: TRUE" << endl;
    else
        cout << "SUCCESS - S not in the polygon OK" << endl;

}


void test_collisionCirclePolygon(void)
{
    LX_Circle M = {12,7,1,1};
    LX_Circle N = {12,7,2,4};
    LX_Circle O = {9,7,10,100};
    LX_Circle S = {2,2,2,4};

    bool d;
    LX_Polygon poly(5);

    poly.addPoint(10,5);
    poly.addPoint(10,10);
    poly.addPoint(5,5);
    poly.addPoint(7,2);
    poly.addPoint(6,5);

    cout << " = TEST Collision Circle/Polygon = " << endl;

    d = collisionCirclePoly(M,poly);

    if(d != false)
        cerr << "FAILURE - M in the polygon. expected: FALSE ; got: TRUE" << endl;
    else
        cout << "SUCCESS - M not in the polygon OK" << endl;


    d = collisionCirclePoly(S,poly);

    if(d != false)
        cerr << "FAILURE - S in the polygon. expected: FALSE ; got: TRUE" << endl;
    else
        cout << "SUCCESS - S not in the polygon OK" << endl;


    d = collisionCirclePoly(N,poly);

    if(d != true)
        cerr << "FAILURE - N not in the polygon. expected: TRUE ; got: FALSE" << endl;
    else
        cout << "SUCCESS - N in the polygon OK" << endl;


    d = collisionCirclePoly(O,poly);

    if(d != true)
        cerr << "FAILURE - O not in the polygon. expected: TRUE ; got: FALSE" << endl;
    else
        cout << "SUCCESS - O in the polygon OK" << endl;

    cout << " = END TEST = " << endl;
}


void test_collisionRectPolygon(void)
{
    bool d;
    LX_AABB R1,R2,R3,R4,R5;

    R1 = {1,1,2,2};
    R2 = {8,3,10,4};
    R3 = {2,7,20,2};
    R4 = {8,6,1,1};
    R5 = {2,0,16,16};

    LX_Polygon poly(5);

    poly.addPoint(10,5);
    poly.addPoint(10,10);
    poly.addPoint(5,5);
    poly.addPoint(7,2);
    poly.addPoint(6,5);


    cout << " = TEST Collision Rect/Polygon = " << endl;

    d = collisionRectPoly(R1,poly);

    if(d != false)
        cerr << "FAILURE - test R1 not in the polygon. expected: FALSE ; got: TRUE" << endl;
    else
        cout << "SUCCESS - R1 not in the polygon OK" << endl;

    // A point of R2 in the polygon
    d = collisionRectPoly(R2,poly);

    if(d != true)
        cerr << "FAILURE - test R2 touch the polygon. expected: TRUE ; got: FALSE" << endl;
    else
        cout << "SUCCESS - R2 touch the polygon OK" << endl;


    // Some Segments of R3 in the polygon (no point inside)
    d = collisionRectPoly(R3,poly);

    if(d != true)
        cerr << "FAILURE - test R3 touch the polygon. expected: TRUE ; got: FALSE" << endl;
    else
        cout << "SUCCESS - R3 touch the polygon OK" << endl;


    // R4 into the polygon
    d = collisionRectPoly(R4,poly);

    if(d != true)
        cerr << "FAILURE - test R4 into the polygon. expected: TRUE ; got: FALSE" << endl;
    else
        cout << "SUCCESS - R4 into the polygon OK" << endl;


    // The polygon into R5
    d = collisionRectPoly(R5,poly);

    if(d != true)
        cerr << "FAILURE - test polygon into R5. expected: TRUE ; got: FALSE" << endl;
    else
        cout << "SUCCESS - polygon into R5 OK" << endl;


    cout << " = END TEST = " << endl;
}

void test_collision2Polygon(void)
{
    bool d;
    LX_Polygon poly(5);
    LX_Polygon poly2(5);
    LX_Polygon poly3(3);
    LX_Polygon poly4(3);

    poly.addPoint(10,5);
    poly.addPoint(10,10);
    poly.addPoint(5,5);
    poly.addPoint(7,2);
    poly.addPoint(6,5);

    poly2.addPoint(9,6);
    poly2.addPoint(9,9);
    poly2.addPoint(6,4);
    poly2.addPoint(6,3);
    poly2.addPoint(5,6);

    poly3.addPoint(0,0);
    poly3.addPoint(32,32);
    poly3.addPoint(0,32);

    poly4.addPoint(2,2);
    poly4.addPoint(2,3);
    poly4.addPoint(3,4);


    cout << " = TEST Collision Polygon/Polygon = " << endl;

    d = collisionPoly(&poly,&poly2);

    if(d != true)
        cerr << "FAILURE - collision poly/poly2. expected: TRUE ; got: FALSE" << endl;
    else
        cout << "SUCCESS - collision poly/poly2 OK" << endl;


    d = collisionPoly(&poly,&poly3);

    if(d != true)
        cerr << "FAILURE - collision poly/poly3. expected: TRUE ; got: FALSE" << endl;
    else
        cout << "SUCCESS - collision poly/poly3 OK" << endl;


    d = collisionPoly(&poly,&poly4);

    if(d != false)
        cerr << "FAILURE - collision poly/poly4. expected: FALSE ; got: TRUE" << endl;
    else
        cout << "SUCCESS - collision poly/poly4 OK" << endl;

    cout << " = END TEST = " << endl;
}





