

#include <LunatiX/Lunatix_engine.hpp>
#include <cmath>
#include <iostream>
#include <stdexcept>

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
void test_collision2PolygonAgain(void);

void test_move(void);
void test_assignment(void);
void test_operator(void);

void test_VectorPlusMinusOp(void);
void test_VectorOpposite(void);
void test_VectorIncDec(void);
void test_VectorCollinear(void);
void test_VectorLambda(void);

using namespace LX_Physics;

void displayPoly(LX_Polygon& poly);

int main(int argc, char **argv)
{
    bool err = LX_Init();

    if(!err)
        cerr << "FAILURE - Init does not work" << endl;
    else
        cout << "SUCCESS - LunatiX Engine have been initialized with success" << endl;

    LX_Log::setDebugMode();
    LX_Log::log(" ==== Test Physics ==== \n");

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
    test_collision2PolygonAgain();

    test_move();
    test_assignment();
    test_operator();

    test_VectorPlusMinusOp();
    test_VectorOpposite();
    test_VectorIncDec();
    test_VectorCollinear();
    test_VectorLambda();

    LX_Quit();
    LX_Log::log(" ==== END Physics ==== \n");
    return EXIT_SUCCESS;
}


// Test the euclidean functions
void test_euclide(void)
{
    LX_Point A = {1,1};
    LX_Point B = {10,1};
    LX_Point C = {0,0};
    LX_Point D = {10,10};

    cout << " = TEST EUCLIDE = " << endl;

    cout << "INFO - A(" << A.x << "," << A.y << ")" << endl
         << "INFO - B(" << B.x << "," << B.y << ")" << endl
         << "INFO - C(" << C.x << "," << C.y << ")" << endl
         << "INFO - D(" << D.x << "," << D.y << ")" << endl
         << "INFO - Square distance AB" << endl;

    float d = euclide_square_distance(A,B);

    if(d != 81.0f)
        cerr << "FAILURE - Bad square distance AB - expected : 81;Got : " << d << endl;
    else
        cout << "SUCCESS - Good square distance AB : " << d << endl;

    cout << "INFO - Distance between A and B" << endl;
    d = euclide_distance(A,B);

    if(d != 9.0f)
        cerr << "FAILURE - Bad distance AB - expected : 9;Got : " << d << endl;
    else
        cout << "SUCCESS - Good distance AB : " << d << endl;

    // Test CD
    cout << "INFO - Square distance CD" << endl;
    d = euclide_square_distance(C,D);

    if(d != 200.0f)
        cerr << "FAILURE - Bad square distance CD - expected : 200;Got : " << d << endl;
    else
        cout << "SUCCESS - Good square distance CD : " << d << endl;

    cout << "INFO - Distance between C and D" << endl;
    d = euclide_distance(C,D);

    if(d != static_cast<float>(sqrt(200)))
        cerr << "FAILURE - Bad distance CD - expected : "
             << static_cast<float>(sqrt(200)) << ";Got : " << d << endl;
    else
        cout << "SUCCESS - Good distance CD : " << d << endl;

    LX_Log::log(" = END TEST = ");
}


void test_collisionPointCircle(void)
{
    LX_Circle circle(LX_Point(100,100),10);

    LX_Point A = {100,100};
    LX_Point B = {50,50};
    LX_Point C = {105,105};
    LX_Point D = {100,125};

    cout << " = TEST POINT/CIRCLE = " << endl;

    cout << "INFO - A(" << A.x << "," << A.y << ")" << endl
         << "INFO - B(" << B.x << "," << B.y << ")" << endl
         << "INFO - C(" << C.x << "," << C.y << ")" << endl
         << "INFO - D(" << D.x << "," << D.y << ")" << endl
         << "INFO - circle {(" << circle.center.x << "," << circle.center.x
         << ")," << circle.radius << "}" << "" << endl;

    cout << "INFO - Collision Point A/Circle" << endl;
    bool d = collisionPointCircle(A.x,A.y,circle);

    if(d != true)
        cerr << "FAILURE - expected : TRUE ;Got : " << d << endl;
    else
        cout << "SUCCESS - collision, the point is the center : " << d << endl;

    cout << "INFO - Collision Point B/Circle" << endl;
    d = collisionPointCircle(B.x,B.y,circle);

    if(d != false)
        cerr << "FAILURE - expected : FALSE;Got : TRUE" << endl;
    else
        cout << "SUCCESS - collision, the point is not in the circle"<< endl;

    cout << "INFO - Collision Point C/Circle" << endl;
    d = collisionPointCircle(C,circle);

    if(d != true)
        cerr << "FAILURE - expected : TRUE;Got : FALSE" << endl;
    else
        cout << "SUCCESS - collision point is in the circle" << endl;

    cout << "INFO - Collision Point D/Circle" << endl;
    d = collisionPointCircle(D,circle);

    if(d != false)
        cerr << "FAILURE - expected : FALSE ;Got : TRUE" << endl;
    else
        cout << "SUCCESS - collision, the point is not in the circle"<< endl;

    LX_Log::log(" = END TEST = ");
}


void test_collisionPointRect(void)
{
    LX_Point A,B;
    LX_AABB aabb;

    A = {100,100};
    B = {50,50};
    aabb = {40,40,30,30};

    cout << " = TEST POINT/AABB = " << endl;

    cout << "INFO - A(" << A.x << "," << A.y << ")" << endl
         << "INFO - B(" << B.x << "," << B.y << ")" << endl
         << "INFO - AABB{(" << aabb.x << "," << aabb.y << "),"
         << aabb.w << "," << aabb.h << "}" << endl;

    cout << "INFO - Collision Point A/AABB" << endl;
    bool d = collisionPointRect(A.x,A.y,aabb);

    if(d != false)
        cerr << "FAILURE - expected : FALSE; Got : TRUE" << endl;
    else
        cout << "SUCCESS - point out of the rect " << endl;

    cout << "INFO - Collision Point B/AABB" << endl;
    d = collisionPointRect(B.x,B.y,aabb);

    if(d != true)
        cerr << "FAILURE - expected : TRUE; Got : FALSE" << endl;
    else
        cout << "SUCCESS - point into the rect " << endl;

    LX_Log::log(" = END TEST = ");
}


void test_collision2Circle(void)
{
    LX_Circle A(LX_Point(10,10),5);
    LX_Circle B(LX_Point(13,12),3);
    LX_Circle C(LX_Point(100,100),50);

    cout << " = TEST CIRCLE/CIRCLE = " << endl;

    cout << "INFO - circle A {(" << A.center.x << "," << A.center.x << "),"
         << A.radius << "}" << "" << endl
         << "INFO - circle B {(" << B.center.x << "," << B.center.x << "),"
         << B.radius << "}" << "" << endl
         << "INFO - circle C {(" << C.center.x << "," << C.center.x << "),"
         << C.radius << "}" << "" << endl;

    cout << "INFO - Collision Circles A/B" << endl;
    bool d = collisionCircle(A,B);

    if(d != true)
        cerr << "FAILURE - collisoon A/B expected : TRUE;Got : FALSE" << endl;
    else
        cout << "SUCCESS - collision between two circles A and B " << endl;

    cout << "INFO - Collision Circles C/B" << endl;
    d = collisionCircle(C,B);

    if(d != false)
        cerr << "FAILURE - collisoon C/B expected : FALSE;Got : TRUE" << endl;
    else
        cout << "SUCCESS - no collision between two circles C and B " << endl;

    cout << "INFO - Collision Circles A/C" << endl;
    d = collisionCircle(A,C);

    if(d != false)
        cerr << "FAILURE - collisoon A/C expected : FALSE;Got : TRUE" << endl;
    else
        cout << "SUCCESS - no collision between two circles A and C " << endl;

    LX_Log::log(" = END TEST = ");
}


void test_collision2Rect(void)
{
    LX_AABB R1,R2,R3;

    R1 = {0,0,50,25};
    R2 = {40,21,32,25};
    R3 = {64,32,10,100};

    cout << " = TEST RECT/RECT = " << endl;

    cout << "INFO - R1{(" << R1.x << "," << R1.y << "),"
         << R1.w << "," << R1.h << "}" << endl;
    cout << "INFO - R2{(" << R2.x << "," << R2.y << "),"
         << R2.w << "," << R2.h << "}" << endl;
    cout << "INFO - R3{(" << R3.x << "," << R3.y << "),"
         << R3.w << "," << R3.h << "}" << endl;

    cout << "INFO - Collision AABB R1/R2" << endl;
    bool d = collisionRect(R1,R2);

    if(d != true)
        cerr << "FAILURE - collisoon R1/R2 expected : TRUE;Got : FALSE" << endl;
    else
        cout << "SUCCESS - collision R1/R2 OK " << endl;

    cout << "INFO - Collision AABB R2/R3" << endl;
    d = collisionRect(R2,R3);

    if(d != true)
        cerr << "FAILURE - collisoon R2/R3 expected : TRUE;Got : FALSE" << endl;
    else
        cout << "SUCCESS - collision R2/R3 OK " << endl;

    cout << "INFO - Collision AABB R3/R1" << endl;
    d = collisionRect(R3,R1);

    if(d != false)
        cerr << "FAILURE - collisoon R3/R1 expected : FALSE;Got : TRUE" << endl;
    else
        cout << "SUCCESS - no collision R3/R1 OK " << endl;

    LX_Log::log(" = END TEST = ");
}


void test_collisionRectCircle(void)
{
    LX_AABB R1;

    R1 = {0,0,50,25};
    LX_Circle A(LX_Point(10,10),5);
    LX_Circle B(LX_Point(51,26),15);
    LX_Circle C(LX_Point(100,100),40);

    cout << " = TEST RECT/CIRCLE = " << endl;

    cout << "INFO - R1{(" << R1.x << "," << R1.y << "),"
         << R1.w << "," << R1.h << "}" << endl
         << "INFO - circle A {(" << A.center.x << "," << A.center.x << "),"
         << A.radius << "}" << "" << endl
         << "INFO - circle B {(" << B.center.x << "," << B.center.x << "),"
         << B.radius << "}" << "" << endl
         << "INFO - circle C {(" << C.center.x << "," << C.center.x << "),"
         << C.radius << "}" << "" << endl;

    cout << "INFO - Collision Circle/Rect AABB A/R1" << endl;
    bool d = collisionCircleRect(A,R1);

    if(d != true)
        cerr << "FAILURE - collisoon A/R2 expected : TRUE;Got : FALSE" << endl;
    else
        cout << "SUCCESS - collision A/R2 OK " << endl;

    cout << "INFO - Collision Circle/Rect AABB B/R1" << endl;
    d = collisionCircleRect(B,R1);

    if(d != true)
        cerr << "FAILURE - collisoon B/R2 expected : TRUE;Got : FALSE" << endl;
    else
        cout << "SUCCESS - collision B/R2 OK " << endl;

    cout << "INFO - Collision Circle/Rect AABB C/R1" << endl;
    d = collisionCircleRect(C,R1);

    if(d != false)
        cerr << "FAILURE - collisoon C/R1 expected : FALSE;Got : TRUE" << endl;
    else
        cout << "SUCCESS - no collision C/R1 OK " << endl;

    LX_Log::log(" = END TEST = ");
}


void testPolygon(void)
{
    LX_Polygon poly;
    LX_Point p;

    poly.addPoint(10,5);
    poly.addPoint(10,10);
    poly.addPoint(5,5);

    cout << " = TEST POLYGON = " << endl;

    cout << "INFO - Number of edges" << endl;
    unsigned int d = poly.numberOfEdges();

    if(d != 3)
        cerr << "FAILURE - number of real edges expected : 3;Got : " << d << endl;
    else
        cout << "SUCCESS - number of real edges : " << d << endl;

    displayPoly(poly);

    p = poly.getPoint(0);
    cout << "INFO - poly.getPoint(0) : (" << p.x << "," << p.y << ")" << endl;

    if(p.x != 10)
        cerr << "FAILURE - x position expected : 10 ;Got : " << p.x << endl;
    else
        cout << "SUCCESS - x = 10" << endl;

    if(p.y != 5)
        cerr << "FAILURE - y position expected : 5 ;Got : " << p.y << endl;
    else
        cout << "SUCCESS - y = 5" << endl;

    // Is the triangle convex ?
    cout << "INFO - test the convexity of the polygon." << endl;
    if(poly.isConvex() == false)
        cerr << "FAILURE - A triangle is not a non-convex polygon " << endl;
    else
        cout << "SUCCESS - The triangle is a convex polygon, well done !" << endl;

    // Now we have a polygon with 4 edges
    p = {7,2};
    cout << "INFO - add point p(" << p.x << "," << p.y << ")" << endl;
    poly.addPoint(p);

    // It must be convex
    cout << "INFO - test the convexity of the polygon with the new point." << endl;
    if(poly.isConvex() == false)
        cerr << "FAILURE - Expected : convex; Got: non-convex " << endl;
    else
        cout << "SUCCESS - Added (7,2). This is still a convex polygon, well done !" << endl;

    // New edge
    p = {6,5};
    cout << "INFO - add point p(" << p.x << "," << p.y << ")" << endl;
    poly.addPoint(6,5);

    // It must be non-convex
    cout << "INFO - test the non-convexity of the polygon "
         << "with the new point (again)" << endl;
    if(poly.isConvex() == true)
        cerr << "FAILURE - Expected : non-convex; Got: convex " << endl;
    else
        cout << "SUCCESS - Added (6,3). This is not a convex polygon" << endl;

    LX_Log::log(" = END TEST = ");
}


void test_Vector2D(void)
{
    LX_Vector2D v,u,z;

    v = {1.0f,2.0f};
    u = {2.0f,-1.0f};
    z = {0.0f,0.0f};

    cout << " = TEST Vector2D = " << endl;

    cout << "INFO - v(" << v.vx << "," << v.vy << ")" << endl
         << "INFO - u(" << u.vx << "," << u.vy << ")" << endl
         << "INFO - z(" << z.vx << "," << z.vy << ")" << endl;

    cout << "INFO - scalar product (v,u)" << endl;
    float d = scalar_product(v,u);

    if(d != 0.0f)
        cerr << "FAILURE - scalar product v(1,2).u(2,-1) expected: 0 ;Got: " << d << endl;
    else
        cout << "SUCCESS - scalar product v(1,2).u(2,-1) = 0" << endl;

    cout << "INFO - scalar product (z,z)" << endl;
    d = scalar_product(z,z);

    if(d != 0.0f)
        cerr << "FAILURE - scalar product z.z (z is a null vector) expected: 0 ;Got: " << d << endl;
    else
        cout << "SUCCESS - scalar product z.z = 0" << endl;

    cout << "INFO - norm of z" << endl;
    d = vector_norm(z);

    if(d != 0.0f)
        cerr << "FAILURE - norm of z (z is a null vector) expected: 0 ;Got: " << d << endl;
    else
        cout << "SUCCESS - norm of z = 0" << endl;

    cout << "INFO - norm of v" << endl;
    d = vector_norm(v);

    if(static_cast<int>(d) != static_cast<int>(sqrt(5)))
        cerr << "FAILURE - norm of v expected: "<< static_cast<int>(sqrt(5))
             <<" ; Got: " << d << endl;
    else
        cout << "SUCCESS - norm of v = 0" << endl;

    cout << "INFO - vector product (v,u)" << endl;
    d = vector_product(v,u);
    cout << "INFO - " << d << endl;
    if(d != -5.0f)
        cerr << "FAILURE - vector product v(1,2).u(2,-1) expected: -5 ;Got: " << d << endl;
    else
        cout << "SUCCESS - vector product v(1,2).u(2,-1) = -5" << endl;


    d = vector_product(u,v);

    if(d != 5.0f)
        cerr << "FAILURE - vector product u(2,-1).v(1,2) expected: 5 ;Got: " << d << endl;
    else
        cout << "SUCCESS - vector product u(2,-1).v(1,2) = 5" << endl;


    d = vector_product(z,z);

    if(d != 0.0f)
        cerr << "FAILURE - vector product z.z (z is a null vector) expected: 0 ;Got: " << d << endl;
    else
        cout << "SUCCESS - vector product z.z = 0" << endl;

    LX_Log::log(" = END TEST = ");
}


void test_collisionSeg(void)
{
    LX_Point A,B,C,D,E,F;
    bool d;

    A.x =  5; A.y =  5;
    B.x = 10; B.y = 10;
    C.x =  5; C.y = 10;
    D.x = 10; D.y =  5;
    E.x = 20; E.y =  5;
    F.x = 15; F.y =  5;

    cout << " = TEST Collision Segment = " << endl;

    cout << "INFO - A(" << A.x << "," << A.y << ")" << endl
         << "INFO - B(" << B.x << "," << B.y << ")" << endl
         << "INFO - C(" << C.x << "," << C.y << ")" << endl
         << "INFO - D(" << D.x << "," << D.y << ")" << endl
         << "INFO - E(" << E.x << "," << E.y << ")" << endl
         << "INFO - F(" << F.x << "," << F.y << ")" << endl;

    cout << "INFO - collision segement [AB]/[CD]" << endl;
    d = intersectSegment(A,B,C,D);

    if(d != true)
        cerr << "FAILURE - intersect [AB]/[CD] expected: TRUE ;Got: FALSE" << endl;
    else
        cout << "SUCCESS - intersect [AB]/[CD] OK" << endl;

    cout << "INFO - collision segement [AC]/[BD]" << endl;
    d = intersectSegment(A,C,B,D);

    if(d != false)
        cerr << "FAILURE - intersect [AC]/[BD] expected: FALSE ;Got: TRUE" << endl;
    else
        cout << "SUCCESS - no intersect [AC]/[BD] OK" << endl;

    cout << "INFO - collision segement [AB]/[AD]" << endl;
    d = intersectSegment(A,B,A,D);

    if(d != true)
        cerr << "FAILURE - intersect [AB]/[AD] expected: TRUE ;Got: FALSE" << endl;
    else
        cout << "SUCCESS - intersect [AB]/[AD] OK" << endl;

    cout << "INFO - collision segement [AD]/[AE]" << endl;
    d = intersectSegment(A,D,A,E);

    if(d != true)
        cerr << "FAILURE - intersect [AD]/[AE] expected: TRUE ;Got: FALSE" << endl;
    else
        cout << "SUCCESS - intersect [AD]/[AE] OK" << endl;

    cout << "INFO - collision segement [AD]/[FE]" << endl;
    d = intersectSegment(A,D,F,E);

    if(d != true)
        cerr << "FAILURE - intersect [AD]/[FE] expected: FALSE ;Got: TRUE" << endl;
    else
        cout << "SUCCESS - no intersect [AD]/[FE] OK" << endl;

    LX_Log::log(" = END TEST = ");
}


void test_collisionPointPolygon(void)
{
    /*
        Be careful, if the coordinates of a point
        are to high, you will have incorrect results
    */
    LX_Polygon poly;

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

    {
        cout << "INFO - poly {";
        const unsigned int n = poly.numberOfEdges();
        for(unsigned int i = 0; i < n; i++)
        {
            cout << "(" << (poly.getPoint(i)).x << ","
                 << (poly.getPoint(i)).y << ")";
            if(i != n)
                cout << ";";
        }
        cout << "}" << endl;
    }

    cout << "INFO - A(" << N.x << "," << N.y << ")" << endl
         << "INFO - B(" << O.x << "," << O.y << ")" << endl
         << "INFO - C(" << P.x << "," << P.y << ")" << endl
         << "INFO - D(" << Q.x << "," << Q.y << ")" << endl
         << "INFO - E(" << R.x << "," << R.y << ")" << endl
         << "INFO - F(" << S.x << "," << S.y << ")" << endl;

    cout << "INFO - collision Point N/Polygon" << endl;
    bool d = collisionPointPoly(N,poly);

    if(d != false)
        cerr << "FAILURE - N in the polygon. expected: FALSE ;Got: TRUE" << endl;
    else
        cout << "SUCCESS - N not in the polygon OK" << endl;

    cout << "INFO - collision Point O/Polygon" << endl;
    d = collisionPointPoly(O,poly);

    if(d != true)
        cerr << "FAILURE - O not in the polygon. expected: TRUE ;Got: FALSE" << endl;
    else
        cout << "SUCCESS - O in the polygon OK" << endl;

    cout << "INFO - collision Point P/Polygon" << endl;
    d = collisionPointPoly(P,poly);

    if(d != true)
        cerr << "FAILURE - P not in the polygon. expected: TRUE ;Got: FALSE" << endl;
    else
        cout << "SUCCESS - P in the polygon OK" << endl;

    cout << "INFO - collision Point Q/Polygon" << endl;
    d = collisionPointPoly(Q,poly);

    if(d != true)
        cerr << "FAILURE - Q not in the polygon. expected: TRUE ;Got: FALSE" << endl;
    else
        cout << "SUCCESS - Q in the polygon OK" << endl;

    cout << "INFO - collision Point R/Polygon" << endl;
    d = collisionPointPoly(R,poly);

    if(d != false)
        cerr << "FAILURE - R in the polygon. expected: FALSE ;Got: TRUE" << endl;
    else
        cout << "SUCCESS - R not in the polygon OK" << endl;

    cout << "INFO - collision Point S/Polygon" << endl;
    d = collisionPointPoly(S,poly);

    if(d != false)
        cerr << "FAILURE - S in the polygon. expected: FALSE ;Got: TRUE" << endl;
    else
        cout << "SUCCESS - S not in the polygon OK" << endl;
}


void test_collisionCirclePolygon(void)
{
    LX_Circle M(LX_Point(12,7),1);
    LX_Circle N(LX_Point(12,7),2);
    LX_Circle O(LX_Point(9,7),10);
    LX_Circle S(LX_Point(2,2),2);
    LX_Polygon poly;

    poly.addPoint(10,5);
    poly.addPoint(10,10);
    poly.addPoint(5,5);
    poly.addPoint(7,2);
    poly.addPoint(6,5);

    cout << " = TEST Collision Circle/Polygon = " << endl;

    cout << "INFO - circle M {(" << M.center.x << "," << M.center.x << "),"
         << M.radius << "}" << "" << endl
         << "INFO - circle N {(" << N.center.x << "," << N.center.x << "),"
         << N.radius << "}" << "" << endl
         << "INFO - circle O {(" << O.center.x << "," << N.center.x << "),"
         << O.radius << "}" << "" << endl
         << "INFO - circle S {(" << S.center.x << "," << S.center.x << "),"
         << S.radius << "}" << "" << endl;

    {
        cout << "INFO - poly {";
        const unsigned int n = poly.numberOfEdges();
        for(unsigned int i = 0; i < n; i++)
        {
            cout << "(" << (poly.getPoint(i)).x << ","
                 << (poly.getPoint(i)).y << ")";
            if(i != n)
                cout << ";";
        }
        cout << "}" << endl;
    }

    cout << "INFO - collision Circle M/Polygon" << endl;
    bool d = collisionCirclePoly(M,poly);

    if(d != false)
        cerr << "FAILURE - M in the polygon. expected: FALSE ;Got: TRUE" << endl;
    else
        cout << "SUCCESS - M not in the polygon OK" << endl;

    cout << "INFO - collision Point S/Polygon" << endl;
    d = collisionCirclePoly(S,poly);

    if(d != false)
        cerr << "FAILURE - S in the polygon. expected: FALSE ;Got: TRUE" << endl;
    else
        cout << "SUCCESS - S not in the polygon OK" << endl;

    cout << "INFO - collision Point N/Polygon" << endl;
    d = collisionCirclePoly(N,poly);

    if(d != true)
        cerr << "FAILURE - N not in the polygon. expected: TRUE ;Got: FALSE" << endl;
    else
        cout << "SUCCESS - N in the polygon OK" << endl;

    cout << "INFO - collision Point O/Polygon" << endl;
    d = collisionCirclePoly(O,poly);

    if(d != true)
        cerr << "FAILURE - O not in the polygon. expected: TRUE ;Got: FALSE" << endl;
    else
        cout << "SUCCESS - O in the polygon OK" << endl;

    LX_Log::log(" = END TEST = ");
}


void test_collisionRectPolygon(void)
{
    LX_AABB R1,R2,R3,R4,R5;
    LX_Polygon poly;

    R1 = {1,1,2,2};
    R2 = {8,3,10,4};
    R3 = {2,7,20,2};
    R4 = {8,6,1,1};
    R5 = {2,0,16,16};

    poly.addPoint(10,5);
    poly.addPoint(10,10);
    poly.addPoint(5,5);
    poly.addPoint(7,2);
    poly.addPoint(6,5);

    cout << " = TEST Collision Rect/Polygon = " << endl;

    cout << "INFO - R1{(" << R1.x << "," << R1.y << "),"
         << R1.w << "," << R1.h << "}" << endl
         << "INFO - R2{(" << R2.x << "," << R1.y << "),"
         << R2.w << "," << R2.h << "}" << endl
         << "INFO - R3{(" << R3.x << "," << R1.y << "),"
         << R3.w << "," << R3.h << "}" << endl
         << "INFO - R4{(" << R4.x << "," << R1.y << "),"
         << R4.w << "," << R4.h << "}" << endl;

    {
        cout << "INFO - poly {";
        const unsigned int n = poly.numberOfEdges();
        for(unsigned int i = 0; i < n; i++)
        {
            cout << "(" << (poly.getPoint(i)).x << ","
                 << (poly.getPoint(i)).y << ")";
            if(i != n)
                cout << ";";
        }
        cout << "}" << endl;
    }

    bool d = collisionRectPoly(R1,poly);

    if(d != false)
        cerr << "FAILURE - test R1 not in the polygon. expected: FALSE ;Got: TRUE" << endl;
    else
        cout << "SUCCESS - R1 not in the polygon OK" << endl;

    // A point of R2 in the polygon
    d = collisionRectPoly(R2,poly);

    if(d != true)
        cerr << "FAILURE - test R2 touch the polygon. expected: TRUE ;Got: FALSE" << endl;
    else
        cout << "SUCCESS - R2 touch the polygon OK" << endl;

    // Some Segments of R3 in the polygon (no point inside)
    d = collisionRectPoly(R3,poly);

    if(d != true)
        cerr << "FAILURE - test R3 touch the polygon. expected: TRUE ;Got: FALSE" << endl;
    else
        cout << "SUCCESS - R3 touch the polygon OK" << endl;

    // R4 into the polygon
    d = collisionRectPoly(R4,poly);

    if(d != true)
        cerr << "FAILURE - test R4 into the polygon. expected: TRUE ;Got: FALSE" << endl;
    else
        cout << "SUCCESS - R4 into the polygon OK" << endl;

    // The polygon into R5
    d = collisionRectPoly(R5,poly);

    if(d != true)
        cerr << "FAILURE - test polygon into R5. expected: TRUE ;Got: FALSE" << endl;
    else
        cout << "SUCCESS - polygon into R5 OK" << endl;


    LX_Log::log(" = END TEST = ");
}

void test_collision2Polygon(void)
{
    LX_Polygon poly_empty1, poly_empty2;
    LX_Polygon polyc, polyc2, polync, polync2;
    LX_Polygon poly, poly2, poly3, poly4;

    // Convex polygon
    polyc.addPoint(10,5);
    polyc.addPoint(10,10);
    polyc.addPoint(5,5);
    polyc.addPoint(7,2);

    // Non-convex polygon
    polync.addPoint(1000,500);
    polync.addPoint(1000,1000);
    polync.addPoint(500,500);
    polync.addPoint(700,200);
    polync.addPoint(600,500);

    // Non-convex polygon (again)
    polync2.addPoint(10,5);
    polync2.addPoint(10,10);
    polync2.addPoint(5,5);
    polync2.addPoint(7,2);
    polync2.addPoint(6,5);

    polyc2.addPoint(12,5);
    polyc2.addPoint(12,12);
    polyc2.addPoint(4,5);
    polyc2.addPoint(7,0);

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

    cout << "INFO - poly" << endl;
    displayPoly(poly);
    cout << "INFO - poly2" << endl;
    displayPoly(poly2);
    cout << "INFO - poly3" << endl;
    displayPoly(poly3);
    cout << "INFO - poly4" << endl;
    displayPoly(poly4);
    cout << "INFO - polyc" << endl;
    displayPoly(polyc);
    cout << "INFO - polyc2" << endl;
    displayPoly(polyc2);
    cout << "INFO - polync" << endl;
    displayPoly(polync);
    cout << "INFO - polync2" << endl;
    displayPoly(polync2);

    bool d = collisionPoly(poly,poly2);

    if(d != true)
        cerr << "FAILURE - no collision poly/poly2. expected: TRUE ;Got: FALSE" << endl;
    else
        cout << "SUCCESS - collision poly/poly2" << endl;


    d = collisionPoly(poly,poly3);

    if(d != true)
        cerr << "FAILURE - no collision poly/poly3. expected: TRUE ;Got: FALSE" << endl;
    else
        cout << "SUCCESS - collision poly/poly3 OK" << endl;


    d = collisionPoly(poly,poly4);

    if(d != false)
        cerr << "FAILURE - collision poly/poly4. expected: FALSE ;Got: TRUE" << endl;
    else
        cout << "SUCCESS - no collision poly/poly4 OK" << endl;

    // Empty olygons
    cout << "INFO - collision between two empty polygons" << endl;
    try
    {
        collisionPoly(poly_empty1,poly_empty2);
        cerr << "FAILURE - this collision cannot be calculated" << endl;
    }
    catch(std::invalid_argument&)
    {
        cout << "SUCCESS - std::invalid_argument exception occured" << endl;
    }
    catch(...)
    {
        cerr << "FAILURE - unknown exception occurred" << endl;
    }

    cout << "INFO - collision between two convex polygons" << endl;
    d = collisionPoly(polyc,polyc2);

    if(d != true)
        cerr << "FAILURE - no collision polyc/polyc2. expected: TRUE ;Got: FALSE" << endl;
    else
        cout << "SUCCESS - collision polyc/polyc2 OK" << endl;

    // convex/non-convex
    cout << "INFO - collision between a convex polygon and a non-convex polygon" << endl;
    d = collisionPoly(polyc2,polync);

    if(d == true)
        cerr << "FAILURE - collision polyc2/polync. expected: FALSE ;Got: TRUE" << endl;
    else
        cout << "SUCCESS - no collision polyc2/polync OK" << endl;

    // Another test
    cout << "INFO - collision between a convex polygon and a non-convex polygon (again)" << endl;
    d = collisionPoly(polyc2,polync2);

    if(d != false)
        cerr << "FAILURE - no collision polyc2/polync2. expected: FALSE ;Got: TRUE" << endl;
    else
        cout << "SUCCESS - collision polyc2/polync2 OK" << endl;

    // convex/triangle (that is convex)
    cout << "INFO - collision between a convex polygon and a triangle" << endl;
    d = collisionPoly(polyc2,poly3);

    if(d != true)
        cerr << "FAILURE - no collision polyc2/poly3. expected: TRUE ;Got: FALSE" << endl;
    else
        cout << "SUCCESS - collision polyc2/poly3 OK" << endl;

    LX_Log::log(" = END TEST = ");
}

void test_collision2PolygonAgain(void)
{
    const long N = 10000;
    const long M = 1000;
    LX_Polygon poly1, poly2;
    LX_Polygon poly3, poly4;
    unsigned int t1,t2;

    LX_Log::log(" = TEST Collision BIG Polygon/Polygon = ");
    LX_Random::initRand();

    LX_Log::log("Generate two random polygons with %d sides",N);
    for(unsigned int i = 0; i < N; i++)
    {
        poly1.addPoint(LX_Random::xorshiftRand()%M,LX_Random::xorshiftRand()%M);
        poly2.addPoint(LX_Random::xorshiftRand()%M,LX_Random::xorshiftRand()%M);
    }

    LX_Log::log("Calculate the collision #1");
    t1 = SDL_GetTicks();
    bool d = collisionPoly(poly1,poly2);
    t2 = SDL_GetTicks();
    LX_Log::log("Result:%s collision between the two random polygons",(d ? "":" No"));
    LX_Log::log("Calculation done in %d ms",t2-t1);

    LX_Log::log("Generate two other random polygons with %d sides in two different areas",N);
    for(unsigned int i = 0; i < N; i++)
    {
        poly3.addPoint(LX_Random::xorshiftRand()%M,LX_Random::xorshiftRand()%M);
        poly4.addPoint(LX_Random::xorshiftRand()%M+N,LX_Random::xorshiftRand()%M+N);
    }

    LX_Log::log("Calculate the collision #2");
    t1 = SDL_GetTicks();
    d = collisionPoly(poly3,poly4);
    t2 = SDL_GetTicks();
    LX_Log::log("t1: %d; t2: %d",t1,t2);
    LX_Log::log("Result:%s collision between the two random polygons",(d ? "":" No"));
    LX_Log::log("Calculation done in %d ms",t2-t1);

    LX_Log::log(" = END TEST = ");
}


void test_move(void)
{
    cout << " = TEST Move = " << endl;

    LX_Point P = {1,2};
    LX_AABB R = {8,4,10,10};

    const int X = -4;
    const int Y = 8;
    LX_Vector2D v(X,Y);
    LX_Polygon poly;
    LX_Polygon expoly;

    poly.addPoint(24,32);
    poly.addPoint(48,32);
    poly.addPoint(128,64);
    poly.addPoint(64,64);
    poly.addPoint(32,32);
    // expected polygon
    expoly.addPoint(24+X,32+Y);
    expoly.addPoint(48+X,32+Y);
    expoly.addPoint(128+X,64+Y);
    expoly.addPoint(64+X,64+Y);
    expoly.addPoint(32+X,32+Y);

    cout << "INFO - Point P(" << P.x << "," << P.y << ")" << endl;
    cout << "INFO - Rectangle R(" << R.x << "," << R.y << ","<< R.w << ","
         << R.h << ")" << endl;

    cout << "INFO - Point" << endl;

    LX_Point expected_point = {P.x +1, P.y +1};
    movePoint(P,1,1);

    if(P.x == expected_point.x && P.y == expected_point.y)
        cout << "SUCCESS - Point P(" << P.x << "," << P.y << ")" << endl;
    else
        cout << "FAILURE - expected : Point P(2,3)"
             << "Got : (" << P.x << "," << P.y << ")" << endl;

    cout << "INFO - Rectangle" << endl;

    LX_AABB expected_aabb = {R.x +2, R.y +3, R.w, R.h};
    moveRect(R,2,3);

    if(R.x == expected_aabb.x && R.y == expected_aabb.y)
        cout << "SUCCESS - Rectangle R(" << R.x << "," << R.y << ","
             << R.w << "," << R.h << ")" << endl;
    else
        cout << "FAILURE - expected : Rectangle R(3,6,10,10)"
             << "Got : (" << R.x << "," << R.y << ","
             << R.w << "," << R.h << ")" << endl;

    movePoly(poly,X,Y);
    const unsigned int n = poly.numberOfEdges();
    const unsigned int m = expoly.numberOfEdges();

    LX_Log::log("expected polygon");
    displayPoly(expoly);
    LX_Log::log("got");
    displayPoly(poly);

    if(n != m)
    {
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - these polygon have not the same size");
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"number of edges expected: %d, got: %d",m,n);
    }
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - these polygon have the same size");

    try
    {
        bool ok = true;
        for(unsigned int j = 0; j < n; j++)
        {
            LX_Point p1 = poly.getPoint(j);
            LX_Point p2 = expoly.getPoint(j);
            if(p1 != p2)
            {
                LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - at j = %d → not the same point",j);
                LX_Log::logInfo(LX_Log::LX_LOG_TEST,"point expected: (%d,%d) got: (%d,%d)",
                                p2.x,p2.y,p1.x,p1.y);
                ok = false;
                break;
            }
        }

        if(ok)
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - The 2 polygons are identical");
    }
    catch(...)
    {
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - uncaught exception at %s:%d",__FILE__,__LINE__);
    }

    LX_Log::log(" = END TEST = ");
}


void test_assignment(void)
{
    cout << " = TEST Assignement = " << endl;

    LX_Point P = {1,2};
    LX_Point Q;

    cout << "INFO - Point P(" << P.x << "," << P.y << ")" << endl;

    Q = P;  // assignment

    if(Q == P)
        cout << "SUCCESS - Point Q(" << Q.x << "," << Q.y << ")" << endl;
    else
        cerr << "FAILURE - expected : Point Q(1,2); "
             << "Got : Q(" << Q.x << "," << Q.y << ")" << endl;


    LX_Circle C(LX_Point(4,9),10);

    cout << "INFO - Circle C : Center(" << C.center.x << "," << C.center.y
         << ") radius : " << C.radius << "; square radius : " << C.square_radius
         << endl;

    LX_Circle D = C;  // assignment

    if(D == C)
        cout << "SUCCESS - Circle D : Center(" << C.center.x << "," << C.center.y
             << ") radius : " << C.radius << "; square radius : " << C.square_radius
             << endl;
    else
        cerr << "FAILURE - expected : Circle D{{4,9},10,100}; "
             << "Got : Circle D : Center(" << D.center.x << "," << D.center.y
             << ") radius : " << D.radius << "; square radius : " << D.square_radius
             << endl;

    LX_Vector2D v = {3.14f,1.59f};

    cout << "INFO - Vector2D v(" << v.vx << "," << v.vy << ")" << endl;

    LX_Vector2D u = v;  // assignment

    if(u == v)
        cout << "SUCCESS - Vector2D u(" << u.vx << "," << u.vy << ")" << endl;
    else
        cerr << "FAILURE - expected : Vector2D u(3.14,1.59); "
             << "Got : u(" << u.vx << "," << u.vy << ")" << endl;

    LX_Log::log(" = END TEST = ");
}


void test_operator(void)
{
    LX_Circle C(LX_Point(2,3),10);
    LX_Circle E(LX_Point(4,9),32);
    LX_Circle F(LX_Point(8,21),10);

    LX_Vector2D v = {-3.14f,1.59f};
    LX_Vector2D u = v;
    LX_Vector2D w = {3.14f,1.59f};
    LX_Vector2D i = {2.56f,1.59f};
    LX_Vector2D j = {-0.14f,-1.28f};

    cout << " = TEST operators = " << endl;

    cout << "INFO - Circle C - Center(" << C.center.x << "," << C.center.y
         << ") radius : " << C.radius << "; square radius : " << C.square_radius
         << endl;
    cout << "INFO - Circle E - Center(" << E.center.x << "," << E.center.y
         << ") radius : " << E.radius << "; square radius : " << E.square_radius
         << endl;
    cout << "INFO - Circle F - Center(" << F.center.x << "," << F.center.y
         << ") radius : " << F.radius << "; square radius : " << F.square_radius
         << endl;

    if(E > C)
        cout << "SUCCESS - E is greater than C" << endl;
    else
        cerr << "FAILURE - E is not greater than C" << endl;

    if(C < E)
        cout << "SUCCESS - C is smaller than E" << endl;
    else
        cerr << "FAILURE - C is not smaller than E" << endl;

    if(E >= C)
        cout << "SUCCESS - E is greater or equal than C" << endl;
    else
        cerr << "FAILURE - E is not greater or equal than C" << endl;

    if(C <= E)
        cout << "SUCCESS - C is smaller or equal than E" << endl;
    else
        cerr << "FAILURE - C is not smaller or equal than E" << endl;

    if(F >= C)
        cout << "SUCCESS - F is greater or equal than C" << endl;
    else
        cerr << "FAILURE - F is not greater or equal than C" << endl;

    if(C <= F)
        cout << "SUCCESS - C is smaller or equal than F" << endl;
    else
        cerr << "FAILURE - C is not smaller or equal than F" << endl;

    if(!(E < C))
        cout << "SUCCESS - E is not smaller than C" << endl;
    else
        cerr << "FAILURE - E is smaller than C" << endl;

    cout << "INFO -Is E different from C? " << endl;
    if(E != C)
        cout << "SUCCESS - E is not C" << endl;
    else
        cerr << "FAILURE - E is C" << endl;

    cout << "INFO -Is E and C not equal? " << endl;
    if(!(E == C))
        cout << "SUCCESS - E is not C" << endl;
    else
        cerr << "FAILURE - E is C" << endl;

    cout << "INFO - Vector2D u(" << u.vx << "," << u.vy << ")" << endl;
    cout << "INFO - Vector2D v(" << v.vx << "," << v.vy << ")" << endl;
    cout << "INFO - Vector2D w(" << w.vx << "," << w.vy << ")" << endl;
    cout << "INFO - Vector2D i(" << i.vx << "," << i.vy << ")" << endl;
    cout << "INFO - Vector2D j(" << j.vx << "," << j.vy << ")" << endl;

    if(u == v)
        cout << "SUCCESS - u and v are equals" << endl;
    else
        cerr << "FAILURE - expected: u and v equals;Got :"
             << "Vector2D u(" << u.vx << "," << u.vy << "); "
             << "Vector2D v(" << v.vx << "," << v.vy << ")" << endl;

    if(v == w)
        cerr << "FAILURE - expected: v and w are not equals;Got :"
             << "Vector2D v(" << v.vx << "," << v.vy << ")"
             << "Vector2D w(" << w.vx << "," << w.vy << "); " << endl;
    else
        cout << "SUCCESS - v and w are not equals" << endl;

    if(v != i)
        cout << "SUCCESS - v and i are not equals" << endl;
    else
        cerr << "FAILURE - expected: v and i are not equals;Got :"
             << "Vector2D v(" << v.vx << "," << v.vy << ")"
             << "Vector2D i(" << i.vx << "," << i.vy << "); " << endl;

    if(j != i)
        cout << "SUCCESS - j and i are not equals" << endl;

    else
        cerr << "FAILURE - expected: j and i are not equals;Got :"
             << "Vector2D j(" << j.vx << "," << j.vy << ")"
             << "Vector2D i(" << i.vx << "," << i.vy << "); " << endl;


    LX_Log::log(" = END TEST = ");
}


void test_VectorPlusMinusOp(void)
{
    LX_Vector2D w;
    LX_Vector2D u = {3.14f,1.59f};
    LX_Vector2D v = {-1.28f,5.12f};
    LX_Vector2D z = {-2.56f,10.24f};

    LX_Vector2D a = {3.14f,2.048f};
    LX_Vector2D b = {1.28f,0.64f};
    LX_Vector2D c = {-2.56f,10.24f};
    LX_Vector2D d;

    LX_Vector2D exp_sum_vec = {u.vx + v.vx , u.vy + v.vy};
    LX_Vector2D exp_add_vec = {u.vx + z.vx , u.vy + z.vy};

    LX_Vector2D exp_diff_vec = {a.vx - b.vx , a.vy - b.vy};
    LX_Vector2D exp_sub_vec = {a.vx - c.vx , a.vy - c.vy};

    cout << " = TEST Vector arithmetic '+','+=','-','-='  = " << endl;
    cout << "INFO - '+','+=','-','-='" << endl;

    cout << "INFO - Vector2D u(" << u.vx << "," << u.vy << ")" << endl;
    cout << "INFO - Vector2D v(" << v.vx << "," << v.vy << ")" << endl;
    cout << "INFO - w = u + v;" << endl;

    w = u + v;

    cout << "INFO - Vector2D w(" << w.vx << "," << w.vy << ")" << endl;

    if(w == exp_sum_vec)
        cout << "SUCCESS - Vector2D w(" << w.vx << "," << w.vy << ")"
             << " is exactly what the test case expected (" << exp_sum_vec.vx
             << "," << exp_sum_vec.vy << ")" << endl;
    else
        cerr << "FAILURE - expected: LX_Vector2D(" << exp_sum_vec.vx
             << "," << exp_sum_vec.vy << "); "
             << "Got w(" << w.vx << "," << w.vy << "); " << endl;

    cout << "INFO - Vector2D u(" << u.vx << "," << u.vy << ")" << endl;
    cout << "INFO - Vector2D z(" << z.vx << "," << z.vy << ")" << endl;
    cout << "INFO - u += z;" << endl;

    u += z;

    cout << "INFO - Vector2D u(" << u.vx << "," << u.vy << ")" << endl;

    if(u == exp_add_vec)
        cout << "SUCCESS - Vector2D u(" << u.vx << "," << u.vy << ")"
             << " is exactly what the test case expected (" << exp_add_vec.vx
             << "," << exp_add_vec.vy << ")" << endl;
    else
        cerr << "FAILURE - expected: LX_Vector2D(" << exp_add_vec.vx
             << "," << exp_add_vec.vy << "); "
             << "Got u(" << u.vx << "," << u.vy << "); " << endl;


    cout << "INFO - Vector2D a(" << a.vx << "," << a.vy << ")" << endl;
    cout << "INFO - Vector2D b(" << b.vx << "," << b.vy << ")" << endl;
    cout << "INFO - d = a - b;" << endl;

    d = a - b;

    cout << "INFO - Vector2D d("<< d.vx << "," << d.vy << ")" << endl;

    if(d == exp_diff_vec)
        cout << "SUCCESS - Vector2D d(" << d.vx << "," << d.vy << ")"
             << " is exactly what the test case expected (" << exp_diff_vec.vx
             << "," << exp_diff_vec.vy << ")" << endl;
    else
        cerr << "FAILURE - expected: LX_Vector2D(" << exp_diff_vec.vx
             << "," << exp_diff_vec.vy << "); "
             << "Got d(" << d.vx << "," << d.vy << "); " << endl;


    cout << "INFO - Vector2D a(" << a.vx << "," << a.vy << ")" << endl;
    cout << "INFO - Vector2D c(" << c.vx << "," << c.vy << ")" << endl;
    cout << "INFO - a -= c;" << endl;

    a -= c;

    if(a == exp_sub_vec)
        cout << "SUCCESS - Vector2D a(" << a.vx << "," << a.vy << ")"
             << " is exactly what the test case expected (" << exp_sub_vec.vx
             << "," << exp_sub_vec.vy << ")" << endl;
    else
        cerr << "FAILURE - expected: LX_Vector2D(" << exp_sub_vec.vx
             << "," << exp_sub_vec.vy << "); "
             << "Got a(" << a.vx << "," << a.vy << "); " << endl;


    LX_Log::log(" = END TEST = ");
}


void test_VectorOpposite(void)
{
    cout << " = TEST Vector Opposite = " << endl;

    LX_Vector2D u = {3.14f,-2.56f};
    LX_Vector2D expected_vec = {-u.vx,-u.vy};

    cout << "INFO - Vector2D u(" << u.vx << "," << u.vy << ")" << endl;
    cout << "INFO - -u;" << endl;

    if(expected_vec == (-u) )
        cout << "SUCCESS - Vector2D -u(" << (-u).vx << "," << (-u).vy << ")"
             << " is exactly what the test case expected (" << expected_vec.vx
             << "," << expected_vec.vy << ")" << endl;
    else
        cerr << "FAILURE - expected: LX_Vector2D(" << expected_vec.vx
             << "," << expected_vec.vy << "); "
             << "Got -u(" << (-u).vx << "," << (-u).vy << "); " << endl;

    LX_Log::log(" = END TEST = ");
}


void test_VectorIncDec(void)
{
    cout << " = TEST Vector Increment and decrement = " << endl;

    LX_Vector2D u = {1.41f,-5.92f};
    LX_Vector2D v = u;
    LX_Vector2D exp_inc_pre_vec = {u.vx + 1,u.vy + 1};
    LX_Vector2D exp_inc_post_vec = {u.vx + 1,u.vy + 1};
    LX_Vector2D exp_dec_pre_vec = {u.vx - 1,u.vy - 1};
    LX_Vector2D exp_dec_post_vec = {u.vx - 1,u.vy - 1};

    cout << "INFO - Increment" << endl;
    cout << "INFO - Vector2D u(" << u.vx << "," << u.vy << ")" << endl;
    cout << "INFO - ++u;" << endl;

    ++u;

    if(u == exp_inc_pre_vec)
        cout << "SUCCESS - Vector2D u(" << u.vx << "," << u.vy << ")"
             << " is exactly what the test case expected (" << exp_inc_pre_vec.vx
             << "," << exp_inc_pre_vec.vy << ")" << endl;
    else
        cerr << "FAILURE - expected: LX_Vector2D(" << exp_inc_pre_vec.vx
             << "," << exp_inc_pre_vec.vy << "); "
             << "Got -u(" << u.vx << "," << u.vy << "); " << endl;

    cout << "INFO - Vector2D v(" << v.vx << "," << v.vy << ")" << endl;
    cout << "INFO - v++;" << endl;

    v++;

    if(v == exp_inc_post_vec)
        cout << "SUCCESS - Vector2D v(" << v.vx << "," << v.vy << ")"
             << " is exactly what the test case expected ("
             << exp_inc_post_vec.vx << "," << exp_inc_post_vec.vy
             << ")" << endl;
    else
        cerr << "FAILURE - expected: LX_Vector2D("
             << exp_inc_post_vec.vx
             << "," << exp_inc_post_vec.vy << "); "
             << "Got v(" << v.vx << "," << v.vy << "); " << endl;

    u = {1.41f,-5.92f};
    v = u;

    cout << "INFO - Decrement" << endl;
    cout << "INFO - Vector2D u(" << u.vx << "," << u.vy << ")" << endl;
    cout << "INFO - --u;" << endl;

    --u;

    if(u == exp_dec_pre_vec)
        cout << "SUCCESS - Vector2D u(" << u.vx << "," << u.vy << ")"
             << " is exactly what the test case expected (" << exp_dec_pre_vec.vx
             << "," << exp_dec_pre_vec.vy << ")" << endl;
    else
        cerr << "FAILURE - expected: LX_Vector2D(" << exp_dec_pre_vec.vx
             << "," << exp_dec_pre_vec.vy << "); "
             << "Got -u(" << u.vx << "," << u.vy << "); " << endl;

    cout << "INFO - Vector2D v(" << v.vx << "," << v.vy << ")" << endl;
    cout << "INFO - v--;" << endl;

    v--;

    if(v == exp_dec_post_vec)
        cout << "SUCCESS - Vector2D v(" << v.vx << "," << v.vy << ")"
             << " is exactly what the test case expected ("
             << exp_dec_post_vec.vx << "," << exp_dec_post_vec.vy
             << ")" << endl;
    else
        cerr << "FAILURE - expected: LX_Vector2D("
             << exp_dec_post_vec.vx
             << "," << exp_dec_post_vec.vy << "); "
             << "Got v(" << v.vx << "," << v.vy << "); " << endl;

    LX_Log::log(" = END TEST = ");
}


void test_VectorCollinear(void)
{
    cout << " = TEST Vector collinearity = " << endl;

    LX_Vector2D u = {1.41f,-2.48f};
    LX_Vector2D v = {u.vx *2,u.vy *2};
    LX_Vector2D w = u;
    LX_Vector2D o = {0.0f,0.0f};
    LX_Vector2D t = {2.01f,4.12f};

    cout << "INFO - Vector2D u(" << u.vx << "," << u.vy << ")" << endl;
    cout << "INFO - Vector2D v(" << v.vx << "," << v.vy << ")" << endl;
    cout << "INFO - Vector2D w(" << w.vx << "," << w.vy << ")" << endl;
    cout << "INFO - Vector2D o(" << o.vx << "," << o.vy << ")" << endl;
    cout << "INFO - Vector2D t(" << t.vx << "," << t.vy << ")" << endl;

    cout << "INFO - test: zero vector" << endl;

    if(isNullVector(o))
        cout << "SUCCESS - o is a zero vector: o("
             << o.vx << "," << o.vy << "); " << endl;
    else
        cerr << "FAILURE - expected: o must be a zero vector: Got o("
             << o.vx << "," << o.vy << "); " << endl;

    if(!isNullVector(t))
        cout << "SUCCESS - t is not a zero vector: t("
             << t.vx << "," << t.vy << "); " << endl;
    else
        cerr << "FAILURE - expected: t must not be zero vector; Got t("
             << t.vx << "," << t.vy << "); " << endl;

    cout << "INFO - test: collinearity between u and v" << endl;

    if(collinear(u,v))
        cout << "SUCCESS - u and v are colinear" << endl;
    else
        cerr << "FAILURE -  expected: u and v must be colinear; "
             << "Got False : u(" << u.vx << "," << u.vy << "); "
             << "v(" << v.vx << "," << v.vy << "); " << endl;


    cout << "INFO - test: collinearity between u and w" << endl;

    if(collinear(u,w))
        cout << "SUCCESS - u and w are colinear" << endl;
    else
        cerr << "FAILURE -  expected: u and w must be colinear; "
             << "Got False : u(" << u.vx << "," << u.vy << "); "
             << "w(" << w.vx << "," << w.vy << "); " << endl;


    cout << "INFO - test: collinearity between u and o" << endl;

    if(collinear(u,o))
        cout << "SUCCESS - u and o are colinear" << endl;
    else
        cerr << "FAILURE -  expected: u and o must be colinear; "
             << "Got False : u(" << u.vx << "," << u.vy << "); "
             << "o(" << o.vx << "," << o.vy << "); " << endl;


    cout << "INFO - test: collinearity between u and t" << endl;

    if(!collinear(u,t))
        cout << "SUCCESS - u and t are not colinear" << endl;
    else
        cerr << "FAILURE -  expected: u and t must not be colinear; "
             << "Got True : u(" << u.vx << "," << u.vy << "); "
             << "t(" << t.vx << "," << t.vy << "); " << endl;


    LX_Log::log(" = END TEST = ");
}


void test_VectorLambda(void)
{
    cout << " = TEST Vector scalar multiplication = " << endl;

    float lambda1 = 2.0f;
    float lambda2 = 0.0f;
    LX_Vector2D v = {3.14f,1.59f};
    LX_Vector2D w = {v.vx * lambda1,v.vy * lambda1};
    LX_Vector2D t = {0.0f,0.0f};

    cout << "INFO - Vector2D v(" << v.vx << "," << v.vy << ")" << endl;

    multiply(v,lambda1);

    if(v == w)
        cout << "SUCCESS - Vector2D v(" << v.vx << "," << v.vy << ")" << endl;
    else
        cerr << "FAILURE - expected : v(" << w.vx << "," << w.vy << "); "
             << "Got : v(" << v.vx << "," << v.vy << ")" << endl;

    multiply(v,lambda2);

    if(v == t)
        cout << "SUCCESS - Vector2D v(" << v.vx << "," << v.vy << ")" << endl;
    else
        cerr << "FAILURE - expected : v(" << t.vx << "," << t.vy << "); "
             << "Got : v(" << v.vx << "," << v.vy << ")" << endl;

    // Test normalization
    cout << "INFO - Reset v" << endl;

    v = {3.0f,0.0f};
    LX_Vector2D vv = {v.vx/vector_norm(v),v.vy/vector_norm(v)};

    cout << "INFO - Vector2D v(" << v.vx << "," << v.vy << ")" << endl;
    cout << "INFO - Normalize v" << endl;

    normalize(v);
    float n = vector_norm(v);

    if(n == 1.0f)
        cout << "SUCCESS - Vector2D v(" << v.vx << "," << v.vy
             << ") is normalized, norm : " << n << endl;
    else
        cerr << "FAILURE - expected : v(" << vv.vx << "," << vv.vy << "); "
             << "Got : v(" << v.vx << "," << v.vy << ")" << endl;

    cout << "INFO - This test may fail with some complex float values in the vector" << endl;
    cout << "INFO - Try it with V(3.14,2.56)" << endl;

    cout << "INFO - Vector2D t(" << t.vx << "," << t.vy << ")" << endl;
    cout << "INFO - Normalize t" << endl;

    normalize(t);   // t is a null vector

    if(t == t)
        cout << "SUCCESS - Vector2D t(" << t.vx << "," << t.vy << ")" << endl;
    else
        cerr << "FAILURE - a zero vector must be normalized to 0" << endl;

    LX_Log::log(" = END TEST = ");
}

void displayPoly(LX_Polygon& poly)
{
    cout << "INFO - {";
    const unsigned int n = poly.numberOfEdges();
    for(unsigned int i = 0; i < n; i++)
    {
        cout << "(" << (poly.getPoint(i)).x << ","
             << (poly.getPoint(i)).y << ")";
        if(i != n)
            cout << ";";
    }
    cout << "}" << endl;
}
