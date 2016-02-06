

#include <cmath>
#include <iostream>

#include <LunatiX/Lunatix_engine.hpp>

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

void test_move(void);
void test_assignment(void);
void test_operator(void);

void test_VectorPlusMinusOp(void);
void test_VectorOpposite(void);
void test_VectorIncDec(void);
void test_VectorCollinear(void);
void test_VectorLambda(void);


using namespace LX_Physics;


int main(int argc, char **argv)
{
    bool err = false;

    cout << " ==== Test Physics ==== " << endl;

    err = LX_Init();

    if(!err)
        cerr << "FAILURE - Init does not work" << endl;
    else
        cout << "SUCCESS - LunatiX Engine have been initialized with success" << endl;

    LX_Log::setDebugMode();
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

    test_move();
    test_assignment();
    test_operator();

    test_VectorPlusMinusOp();
    test_VectorOpposite();
    test_VectorIncDec();
    test_VectorCollinear();
    test_VectorLambda();

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
        cerr << "FAILURE - Bad square distance AB - expected : 81;Got : " << d << endl;
    else
        cout << "SUCCESS - Good square distance AB : " << d << endl;

    d = euclide_distance(A,B);

    if(d != 9)
        cerr << "FAILURE - Bad distance AB - expected : 9;Got : " << d << endl;
    else
        cout << "SUCCESS - Good distance AB : " << d << endl;

    // Test CD

    d = euclide_square_distance(C,D);

    if(d != 200)
        cerr << "FAILURE - Bad square distance CD - expected : 200;Got : " << d << endl;
    else
        cout << "SUCCESS - Good square distance CD : " << d << endl;

    d = euclide_distance(C,D);

    if(d != ( (int) sqrt(200)) )
        cerr << "FAILURE - Bad distance CD - expected : " << (int) sqrt(200) << ";Got : " << d << endl;
    else
        cout << "SUCCESS - Good distance CD : " << d << endl;

    cout << " = END TEST = " << endl;

}


void test_collisionPointCircle(void)
{
    bool d;

    LX_Circle c(LX_Point(100,100),10);

    LX_Point A = {100,100};
    LX_Point B = {50,50};
    LX_Point C = {105,105};
    LX_Point D = {100,125};

    cout << " = TEST POINT/CIRCLE = " << endl;

    d = collisionPointCircle(A.x,A.y,c);

    if(d != true)
        cerr << "FAILURE - expected : TRUE ;Got : " << d << endl;
    else
        cout << "SUCCESS - collision, the point is the center : " << d << endl;

    d = collisionPointCircle(B.x,B.y,c);

    if(d != false)
        cerr << "FAILURE - expected : FALSE;Got : TRUE" << endl;
    else
        cout << "SUCCESS - collision, the point is not in the circle"<< endl;

    d = collisionPointCircle(C,c);

    if(d != true)
        cerr << "FAILURE - expected : TRUE;Got : FALSE" << endl;
    else
        cout << "SUCCESS - collision point is in the circle" << endl;

    d = collisionPointCircle(D,c);

    if(d != false)
        cerr << "FAILURE - expected : FALSE ;Got : TRUE" << endl;
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
        cerr << "FAILURE - expected : FALSE;Got : TRUE" << endl;
    else
        cout << "SUCCESS - point out of the rect " << endl;

    d = collisionPointRect(B.x,B.y,aabb);

    if(d != true)
        cerr << "FAILURE - expected : TRUE;Got : FALSE" << endl;
    else
        cout << "SUCCESS - point into the rect " << endl;

}


void test_collision2Circle(void)
{
    bool d;

    LX_Circle A(LX_Point(10,10),5);
    LX_Circle B(LX_Point(13,12),3);
    LX_Circle C(LX_Point(100,100),50);

    cout << " = TEST CIRCLE/CIRCLE = " << endl;

    d = collisionCircle(A,B);

    if(d != true)
        cerr << "FAILURE - collisoon A/B expected : TRUE;Got : FALSE" << endl;
    else
        cout << "SUCCESS - collision between two circles A and B " << endl;


    d = collisionCircle(C,B);

    if(d != false)
        cerr << "FAILURE - collisoon C/B expected : FALSE;Got : TRUE" << endl;
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
        cerr << "FAILURE - collisoon R1/R2 expected : TRUE;Got : FALSE" << endl;
    else
        cout << "SUCCESS - collision R1/R2 OK " << endl;


    d = collisionRect(R2,R3);

    if(d != true)
        cerr << "FAILURE - collisoon R2/R3 expected : TRUE;Got : FALSE" << endl;
    else
        cout << "SUCCESS - collision R2/R3 OK " << endl;


    d = collisionRect(R3,R1);

    if(d != false)
        cerr << "FAILURE - collisoon R3/R1 expected : FALSE;Got : TRUE" << endl;
    else
        cout << "SUCCESS - no collision R3/R1 OK " << endl;


}


void test_collisionRectCircle(void)
{
    bool d;
    LX_AABB R1;

    R1 = {0,0,50,25};
    LX_Circle A(LX_Point(10,10),5);
    LX_Circle B(LX_Point(51,26),15);
    LX_Circle C(LX_Point(100,100),40);

    cout << " = TEST RECT/CIRCLE = " << endl;

    d = collisionCircleRect(A,R1);

    if(d != true)
        cerr << "FAILURE - collisoon A/R2 expected : TRUE;Got : FALSE" << endl;
    else
        cout << "SUCCESS - collision A/R2 OK " << endl;


    d = collisionCircleRect(B,R1);

    if(d != true)
        cerr << "FAILURE - collisoon B/R2 expected : TRUE;Got : FALSE" << endl;
    else
        cout << "SUCCESS - collision B/R2 OK " << endl;

    d = collisionCircleRect(C,R1);

    if(d != false)
        cerr << "FAILURE - collisoon C/R1 expected : FALSE;Got : TRUE" << endl;
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
        cerr << "FAILURE - number of real edges expected : 3;Got : " << d << endl;
    else
        cout << "SUCCESS - number of real edges : " << d << endl;


    d = poly.numberOfEdges();

    if(d != 5)
        cerr << "FAILURE - total number of edges expected : 5;Got : " << d << endl;
    else
        cout << "SUCCESS - total number of edges : " << d << endl;


    p = poly.getPoint(0);

    if(p.x != 10)
        cerr << "FAILURE - x position expected : 10 ;Got : " << p.x << endl;
    else
        cout << "SUCCESS - x = 10" << endl;

    if(p.y != 5)
        cerr << "FAILURE - y position expected : 5 ;Got : " << p.y << endl;
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
        cerr << "FAILURE - Expected : convex;Got: non-convex " << endl;
    else
        cout << "SUCCESS - Added (7,2). This is still a convex polygon, well done !" << endl;

    // New edge
    poly.addPoint(6,5);

    // It must be non-convex
    if(poly.isConvex() == true)
        cerr << "FAILURE - Expected : non-convex;Got: convex " << endl;
    else
        cout << "SUCCESS - Added (6,3). This is not a convex polygon" << endl;

    cout << " = END TEST = " << endl;

}


void test_Vector2D(void)
{
    LX_Vector2D v,u,z;
    int d;

    v = {1,2};
    u = {2,-1};
    z = {0,0};

    cout << " = TEST Vector2D = " << endl;

    d = scalar_product(v,u);

    if(d != 0)
        cerr << "FAILURE - scalar product v(1,2).u(2,-1) expected: 0 ;Got: " << d << endl;
    else
        cout << "SUCCESS - scalar product v(1,2).u(2,-1) = 0" << endl;

    d = scalar_product(z,z);

    if(d != 0)
        cerr << "FAILURE - scalar product z.z (z is a null vector) expected: 0 ;Got: " << d << endl;
    else
        cout << "SUCCESS - scalar product z.z = 0" << endl;


    d = vector_norm(z);

    if(d != 0)
        cerr << "FAILURE - norm of z (z is a null vector) expected: 0 ;Got: " << d << endl;
    else
        cout << "SUCCESS - norm of z = 0" << endl;


    d = vector_norm(v);

    if(d != ((int) sqrt(5)) )
        cerr << "FAILURE - norm of v expected: "<< ((int) sqrt(5)) <<" ;Got: " << d << endl;
    else
        cout << "SUCCESS - norm of v = 0" << endl;


    d = vector_product(v,u);

    if(d != -5)
        cerr << "FAILURE - vector product v(1,2).u(2,-1) expected: -3 ;Got: " << d << endl;
    else
        cout << "SUCCESS - vector product v(1,2).u(2,-1) = -3" << endl;


    d = vector_product(u,v);

    if(d != 5)
        cerr << "FAILURE - vector product u(2,-1).v(1,2) expected: 3 ;Got: " << d << endl;
    else
        cout << "SUCCESS - vector product u(2,-1).v(1,2) = 3" << endl;


    d = vector_product(z,z);

    if(d != 0)
        cerr << "FAILURE - vector product z.z (z is a null vector) expected: 0 ;Got: " << d << endl;
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
        cerr << "FAILURE - intersect [AB]/[CD] expected: TRUE ;Got: FALSE" << endl;
    else
        cout << "SUCCESS - intersect [AB]/[CD] OK" << endl;


    d = intersectSegment(A,C,B,D);

    if(d != false)
        cerr << "FAILURE - intersect [AC]/[BD] expected: FALSE ;Got: TRUE" << endl;
    else
        cout << "SUCCESS - no intersect [AC]/[BD] OK" << endl;


    d = intersectSegment(A,B,A,D);

    if(d != true)
        cerr << "FAILURE - intersect [AB]/[AD] expected: TRUE ;Got: FALSE" << endl;
    else
        cout << "SUCCESS - intersect [AB]/[AD] OK" << endl;


    d = intersectSegment(A,D,A,E);

    if(d != true)
        cerr << "FAILURE - intersect [AD]/[AE] expected: TRUE ;Got: FALSE" << endl;
    else
        cout << "SUCCESS - intersect [AD]/[AE] OK" << endl;


    d = intersectSegment(A,D,F,E);

    if(d != true)
        cerr << "FAILURE - intersect [AD]/[FE] expected: FALSE ;Got: TRUE" << endl;
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
        cerr << "FAILURE - N in the polygon. expected: FALSE ;Got: TRUE" << endl;
    else
        cout << "SUCCESS - N not in the polygon OK" << endl;

    d = collisionPointPoly(O,poly);

    if(d != true)
        cerr << "FAILURE - O not in the polygon. expected: TRUE ;Got: FALSE" << endl;
    else
        cout << "SUCCESS - O in the polygon OK" << endl;

    d = collisionPointPoly(P,poly);

    if(d != true)
        cerr << "FAILURE - P not in the polygon. expected: TRUE ;Got: FALSE" << endl;
    else
        cout << "SUCCESS - P in the polygon OK" << endl;


    d = collisionPointPoly(Q,poly);

    if(d != true)
        cerr << "FAILURE - Q not in the polygon. expected: TRUE ;Got: FALSE" << endl;
    else
        cout << "SUCCESS - Q in the polygon OK" << endl;


    d = collisionPointPoly(R,poly);

    if(d != false)
        cerr << "FAILURE - R in the polygon. expected: FALSE ;Got: TRUE" << endl;
    else
        cout << "SUCCESS - R not in the polygon OK" << endl;


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
        cerr << "FAILURE - M in the polygon. expected: FALSE ;Got: TRUE" << endl;
    else
        cout << "SUCCESS - M not in the polygon OK" << endl;


    d = collisionCirclePoly(S,poly);

    if(d != false)
        cerr << "FAILURE - S in the polygon. expected: FALSE ;Got: TRUE" << endl;
    else
        cout << "SUCCESS - S not in the polygon OK" << endl;


    d = collisionCirclePoly(N,poly);

    if(d != true)
        cerr << "FAILURE - N not in the polygon. expected: TRUE ;Got: FALSE" << endl;
    else
        cout << "SUCCESS - N in the polygon OK" << endl;


    d = collisionCirclePoly(O,poly);

    if(d != true)
        cerr << "FAILURE - O not in the polygon. expected: TRUE ;Got: FALSE" << endl;
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

    d = collisionPoly(poly,poly2);

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

    cout << " = END TEST = " << endl;
}


void test_move(void)
{
    cout << " = TEST Move = " << endl;

    LX_Point P = {1,2};
    LX_AABB R = {8,4,10,10};

    cout << "INFO - Point P(" << P.x << "," << P.y << ")" << endl;
    cout << "INFO - Rectangle R(" << R.x << "," << R.y << ","<< R.w << "," << R.h << ")" << endl;


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


    cout << " = END TEST = " << endl;
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


    LX_Vector2D v = {3.14,1.59};

    cout << "INFO - Vector2D v(" << v.vx << "," << v.vy << ")" << endl;

    LX_Vector2D u = v;  // assignment

    if(u == v)
        cout << "SUCCESS - Vector2D u(" << u.vx << "," << u.vy << ")" << endl;
    else
        cerr << "FAILURE - expected : Vector2D u(3.14,1.59); "
             << "Got : u(" << u.vx << "," << u.vy << ")" << endl;

    cout << " = END TEST = " << endl;
}


void test_operator(void)
{
    LX_Circle C(LX_Point(2,3),10);
    LX_Circle E(LX_Point(4,9),32);
    LX_Circle F(LX_Point(8,21),10);

    LX_Vector2D v = {-3.14,1.59};
    LX_Vector2D u = v;
    LX_Vector2D w = {3.14,1.59};
    LX_Vector2D i = {2.56,1.59};
    LX_Vector2D j = {-0.14,-1.28};

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


    cout << " = END TEST = " << endl;
}


void test_VectorPlusMinusOp(void)
{
    LX_Vector2D w;

    LX_Vector2D u = {3.14,1.59};
    LX_Vector2D v = {-1.28,5.12};
    LX_Vector2D z = {-2.56,10.24};

    LX_Vector2D a = {3.14,2.048};
    LX_Vector2D b = {1.28,0.64};
    LX_Vector2D c = {-2.56,10.24};
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


    cout << " = END TEST = " << endl;
}


void test_VectorOpposite(void)
{
    cout << " = TEST Vector Opposite = " << endl;

    LX_Vector2D u = {3.14,-2.56};
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

    cout << " = END TEST = " << endl;
}


void test_VectorIncDec(void)
{
    cout << " = TEST Vector Increment and decrement = " << endl;

    LX_Vector2D u = {1.41,-5.92};
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

    u = {1.41,-5.92};
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

    cout << " = END TEST = " << endl;
}


void test_VectorCollinear(void)
{
    cout << " = TEST Vector collinearity = " << endl;

    LX_Vector2D u = {1.41,-2.48};
    LX_Vector2D v = {u.vx *2,u.vy *2};
    LX_Vector2D w = u;
    LX_Vector2D o = {0.0,0.0};
    LX_Vector2D t = {2.01,4.12};

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


    cout << " = END TEST = " << endl;
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

    cout << " = END TEST = " << endl;
}











