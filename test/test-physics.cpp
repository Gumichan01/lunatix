

#include <LunatiX/Lunatix.hpp>
#include <cmath>
#include <sstream>
#include <stdexcept>

using namespace std;
using namespace LX_Physics;

void test_euclide(void);
void test_collisionPointCircle(void);
void test_collisionPointBox(void);
void test_collision2Circle(void);
void test_collision2Box(void);
void test_collisionBoxCircle(void);

void testLine();
void test_Vector2D(void);
void testPolygon(void);

void test_collisionSeg(void);
void test_collisionPointPolygon(void);
void test_collisionCirclePolygon(void);
void test_collisionBoxPolygon(void);
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

void test_conversion(void);

using namespace LX_Physics;

void displayPoly(LX_Polygon& poly);

int main(int argc, char **argv)
{
    bool err = LX_Init();

    if(!err)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - LX_Init() failed");
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - The LunatiX library has been initialized with success");

    LX_Log::setDebugMode();
    LX_Log::log(" ==== Test Physics ==== \n");

    test_euclide();
    test_collisionPointCircle();
    test_collisionPointBox();
    test_collision2Circle();
    test_collision2Box();
    test_collisionBoxCircle();

    testLine();
    test_Vector2D();
    testPolygon();

    test_collisionSeg();
    test_collisionPointPolygon();
    test_collisionCirclePolygon();
    test_collisionBoxPolygon();
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
    test_conversion();

    LX_Quit();
    LX_Log::log(" ==== END Physics ==== \n");
    return EXIT_SUCCESS;
}


// Test the euclidean functions
void test_euclide(void)
{
    LX_FloatPosition A = {1,1};
    LX_FloatPosition B = {10,1};
    LX_FloatPosition C = {0,0};
    LX_FloatPosition D = {10,10};

    LX_Log::log(" = TEST EUCLIDE = ");
    LX_Log::log("A(%d,%d)",A.x,A.y);
    LX_Log::log("B(%d,%d)",B.x,B.y);
    LX_Log::log("C(%d,%d)",C.x,C.y);
    LX_Log::log("D(%d,%d)",D.x,D.y);
    LX_Log::log("Square distance AB");

    Float d = euclide_square_distance(A,B);

    if(d != fbox(81.0f))
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - Bad square distance AB - expected: 81; Got: %f",d);
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - Good square distance AB: %f",d);

    LX_Log::log("Distance between A and B");
    d = euclide_distance(A,B);

    if(d != fbox(9.0f))
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - Bad distance AB - expected: 9; Got: %f",d);
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - Good distance AB: %f",d);

    // Test CD
    LX_Log::log("Square distance CD");
    d = euclide_square_distance(C,D);

    if(d != fbox(200.0f))
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - Bad square distance CD - expected: 81; Got: %f",d);
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - Good square distance CD: %f",d);

    LX_Log::log("Distance between C and D");
    d = euclide_distance(C,D);

    if(static_cast<int>(d) != static_cast<int>(sqrt(200)))
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - Bad distance CD - expected: %f; Got: %f",
                        static_cast<float>(sqrt(200)),d);
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - Good square distance CD: %f",d);

    LX_Log::log(" = END TEST = ");
}


void test_collisionPointCircle(void)
{
    LX_Circle circle{LX_FloatPosition{100,100},10};

    LX_FloatPosition A{100,100};
    LX_FloatPosition B{50,50};
    LX_FloatPosition C{105,105};
    LX_FloatPosition D{100,125};

    LX_Log::log(" = TEST POINT/CIRCLE = ");
    LX_Log::log("A(%d,%d)",A.x.v, A.y.v);
    LX_Log::log("B(%d,%d)",B.x.v, B.y.v);
    LX_Log::log("C(%d,%d)",C.x.v, C.y.v);
    LX_Log::log("D(%d,%d)",D.x.v, D.y.v);

    LX_Log::log("Collision Point A/Circle");
    bool d = collisionPointCircle(A, circle);

    if(d != true)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - expected: TRUE; Got: %d",d);
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - collision, the point is in the circle: %d",d);

    LX_Log::log("Collision Point B/Circle");
    d = collisionPointCircle(B, circle);

    if(d != false)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - expected: FALSE; Got: TRUE");
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - collision, the point is not in the circle");

    LX_Log::log("Collision Point C/Circle");
    d = collisionPointCircle(C,circle);

    if(d != true)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - expected: TRUE; Got: FALSE");
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - collision, the point is in the circle");

    LX_Log::log("Collision Point D/Circle");
    d = collisionPointCircle(D,circle);

    if(d != false)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - expected: FALSE; Got: TRUE");
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - collision, the point is not in the circle");

    LX_Log::log(" = END TEST = ");
}


void test_collisionPointBox(void)
{
    LX_FloatPosition A{100,100}, B{50,50};
    LX_FloatingBox aabb{LX_FloatPosition{40.0f, 40.0f}, 30, 30};

    LX_Log::log(" = TEST POINT/AABB = ");
    LX_Log::log("A(%f,%f)", A.x.v, A.y.v);
    LX_Log::log("B(%f,%f)", B.x.v, B.y.v);
    LX_Log::log("AABB{(%d,%d),%d,%d}", aabb.fpoint.x.v, aabb.fpoint.y.v, aabb.w, aabb.h);

    LX_Log::log("Collision Point A/AABB");
    bool d = collisionPointBox(A, aabb);

    if(d != false)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - expected: FALSE; Got: TRUE");
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - collision, the point is out of the rectangle");

    LX_Log::log("Collision Point B/AABB");
    d = collisionPointBox(B, aabb);

    if(d != true)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - expected: TRUE; Got: FALSE");
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - collision, the point is into the rectangle");

    LX_Log::log(" = END TEST = ");
}


void test_collision2Circle(void)
{
    LX_Circle A{LX_FloatPosition{10.f, 10.0f}, 5};
    LX_Circle B{LX_FloatPosition{13.0f, 12.0f}, 3};
    LX_Circle C{LX_FloatPosition{100.0f, 100.0f}, 50};

    LX_Log::log(" = TEST CIRCLE/CIRCLE = ");
    LX_Log::log("A{(%d,%d),%d}", A.center.x.v, A.center.y.v, A.radius);
    LX_Log::log("B{(%d,%d),%d}", B.center.x.v, B.center.y.v, B.radius);
    LX_Log::log("C{(%d,%d),%d}", C.center.x.v, C.center.y.v, C.radius);

    LX_Log::log("Collision Circles A/B");
    bool d = collisionCircle(A,B);

    if(d != true)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE -collision A/B expected: TRUE; Got: FALSE");
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - collision between two circles A and B");

    LX_Log::log("Collision Circles C/B");
    d = collisionCircle(C,B);

    if(d != false)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - collisoon C/B expected: FALSE; Got: TRUE");
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - no collision between two circles C and B");

    LX_Log::log("Collision Circles A/C");
    d = collisionCircle(A,C);

    if(d != false)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - collisoon C/B expected: FALSE; Got: TRUE");
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - no collision between two circles A and C");

    LX_Log::log(" = END TEST = ");
}


void test_collision2Box(void)
{
    const LX_FloatingBox R1{LX_FloatPosition{0.0f, 0.0f},50,25};
    const LX_FloatingBox R2{LX_FloatPosition{40.0f, 21.0f},32,25};
    const LX_FloatingBox R3{LX_FloatPosition{64.0f, 32.0f},10,100};

    LX_Log::log(" = TEST RECT/RECT = ");
    LX_Log::log("R1{(%d,%d),%d,%d}", R1.fpoint.x.v, R1.fpoint.y.v, R1.w, R1.h);
    LX_Log::log("R2{(%d,%d),%d,%d}", R2.fpoint.x.v, R2.fpoint.y.v, R2.w, R2.h);
    LX_Log::log("R3{(%d,%d),%d,%d}", R3.fpoint.x.v, R3.fpoint.y.v, R3.w, R3.h);

    LX_Log::log("Collision AABB R1/R2");
    bool d = collisionBox(R1,R2);

    if(d != true)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE -collision R1/R2 expected: TRUE; Got: FALSE");
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - collision R1/R2 OK");

    LX_Log::log("Collision AABB R2/R3");
    d = collisionBox(R2,R3);

    if(d != true)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE -collision R2/R3 expected: TRUE; Got: FALSE");
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - collision R2/R3 OK");

    LX_Log::log("Collision AABB R3/R1");
    d = collisionBox(R3,R1);

    if(d != false)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - collisoon R3/R1 expected: FALSE; Got: TRUE");
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - no collision R3/R1 OK");

    LX_Log::log(" = END TEST = ");
}


void test_collisionBoxCircle(void)
{
    LX_FloatingBox R1{LX_FloatPosition{0.0f, 0.0f},50,25};
    LX_Circle A{LX_FloatPosition{10.0f,10.0f}, 5};
    LX_Circle B{LX_FloatPosition{51.0f,26.0f}, 15};
    LX_Circle C{LX_FloatPosition{100.0f,100.0f}, 40};

    LX_Log::log(" = TEST RECT/CIRCLE = ");
    LX_Log::log("R1{(%d,%d),%d,%d}", R1.fpoint.x.v, R1.fpoint.y.v, R1.w, R1.h);
    LX_Log::log("A{(%f,%f),%u}", A.center.x.v, A.center.y.v, A.radius);
    LX_Log::log("B{(%f,%f),%u}", B.center.x.v, B.center.y.v, B.radius);
    LX_Log::log("C{(%f,%f),%u}", C.center.x.v, C.center.y.v, C.radius);

    LX_Log::log("Collision Circle/Box AABB A/R1");
    bool d = collisionCircleBox(A,R1);

    if(d != true)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - collision A/R1 expected: TRUE; Got: FALSE");
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - collision A/R1 OK");

    LX_Log::log("Collision Circle/Box AABB B/R1");
    d = collisionCircleBox(B,R1);

    if(d != true)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - collision B/R1 expected: TRUE; Got: FALSE");
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - collision B/R1 OK");

    LX_Log::log("Collision Circle/Box AABB C/R1");
    d = collisionCircleBox(C,R1);

    if(d != false)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - collision C/R1 expected: FALSE; Got: TRUE");
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - collision C/R1 OK");

    LX_Log::log(" = END TEST = ");
}


void testPolygon(void)
{
    LX_Polygon poly;
    poly.addPoint(LX_FloatPosition{10.0f, 5.0f});
    poly.addPoint(LX_FloatPosition{10.0f, 10.0f});
    poly.addPoint(LX_FloatPosition{5.0f, 5.0f});

    LX_Log::log(" = TEST POLYGON = ");
    LX_Log::log("Number of edges");
    unsigned long d = poly.numberOfEdges();

    if(d != 3)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - number of real edges expected: 3; Got: %u",
                        d);
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - number of real edges: %u", d);

    displayPoly(poly);

    LX_FloatPosition p = poly.getPoint(0);
    LX_Log::log("poly.getPoint(0): (%d,%d)", p.x.v, p.y.v);

    if(p.x != fbox(10.0f))
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - x position expected: 10; Got: %d",
                        p.x.v);
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - x = %d", p.x.v);

    if(p.y != fbox(5.0f))
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - y position expected: 5; Got: %d",
                        p.y.v);
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - y = %d", p.y.v);

    // Is the triangle convex ?
    LX_Log::log("Test the convexity of the polygon.");
    if(poly.isConvex() == false)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - A triangle is not a non-convex polygon");
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - The triangle is a convex polygon, well done !");

    {
        const LX_FloatingBox& b = poly.getEnclosingBox();
        LX_Log::log("enclosing box {%d, %d, %d, %d}", b.fpoint.x.v, b.fpoint.y.v,
                    b.w, b.h);
    }

    // Now we have a polygon with 4 edges
    LX_FloatPosition q{7.0f, 2.0f};
    LX_Log::log("add point p(%d,%d)", q.x.v, q.y.v);
    poly.addPoint(q);

    // It must be convex
    LX_Log::log("Test the convexity of the polygon with the new point.");
    if(poly.isConvex() == false)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - Expected: convex; Got: non-convex");
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - Added (7,2). This is still a convex polygon, well done !");

    // New edge
    LX_FloatPosition r{6.0f, 5.0f};
    LX_Log::log("add point p(%d,%d)", r.x.v, r.y.v);
    poly.addPoint(r);

    // It must be non-convex
    LX_Log::log("Test the convexity of the polygon with the new point (again).");
    if(poly.isConvex() == true)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - Expected: non-convex; Got: convex");
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - Added (6,5). This is not a convex polygon");

    {
        const LX_FloatingBox& b = poly.getEnclosingBox();
        LX_Log::log("enclosing box {%d, %d, %d, %d}", b.fpoint.x.v, b.fpoint.y.v,
                    b.w, b.h);
    }

    LX_Log::log(" = END TEST = ");
}


void testLine()
{
    LX_Log::log("= TEST Vector2D =");

    LX_Vector2D v{0.0f,4.0f};
    LX_Vector2D u{0.0f,42.0f};
    LX_Vector2D w{21.0f,0.0f};
    LX_Line l1{LX_FloatPosition{1.0f, 1.0f}, v};
    LX_Line l2{LX_FloatPosition{5.0f, 21.0f}, u};
    LX_Line l3{LX_FloatPosition{1.0f, 1.0f}, w};

    LX_Log::log("line #1: (%d, %d) - (%f, %f)", l1.o.x, l1.o.y, l1.v.vx.v, l1.v.vy.v);
    LX_Log::log("line #2: (%d, %d) - (%f, %f)", l2.o.x, l2.o.y, l2.v.vx.v, l2.v.vy.v);
    LX_Log::log("line #3: (%d, %d) - (%f, %f)", l3.o.x, l3.o.y, l3.v.vx.v, l3.v.vy.v);

    if(l1.isParralelWith(l2))
        LX_Log::log("SUCCESS - parralel: l1 and l2");
    else
        LX_Log::log("FAILURE - expected: parralel");

    if(!l1.isParralelWith(l3))
        LX_Log::log("SUCCESS - not parralel: l1 and l3");
    else
        LX_Log::log("FAILURE - expected: not parralel");

    if(l1.isPerpendicularTo(l3))
        LX_Log::log("SUCCESS - perpendicular: l1 and l3");
    else
        LX_Log::log("FAILURE - expected: perpendicular");

    if(!l1.isPerpendicularTo(l2))
        LX_Log::log("SUCCESS - not perpendicular: l1 and l2");
    else
        LX_Log::log("FAILURE - expected: not perpendicular");

    if(intersectLine(l1, l3))
        LX_Log::log("SUCCESS - intersection: l1 and l3");
    else
        LX_Log::log("FAILURE - expected: intersection");

    if(intersectLine(l2, l3))
        LX_Log::log("SUCCESS - intersection: l2 and l3");
    else
        LX_Log::log("FAILURE - expected: intersection");

    LX_Log::log("= END TEST =");
}


void test_Vector2D(void)
{
    LX_FloatPosition p{1.0f, 2.0f}, q{2.0f, -1.0f};

    LX_Vector2D v{1.0f, 2.0f};
    LX_Vector2D u{2.0f, -1.0f};
    LX_Vector2D z{0.0f, 0.0f};
    LX_Vector2D w{q.x - p.x, q.y - p.y};

    LX_Log::log(" = TEST Vector2D = ");
    LX_Log::log("v(%f,%f)", v.vx.v, v.vy.v);
    LX_Log::log("u(%f,%f)", u.vx.v, u.vy.v);
    LX_Log::log("z(%f,%f)", z.vx.v, z.vy.v);
    LX_Log::log("w(%f,%f)", w.vx.v, w.vy.v);
    LX_Log::log("scalar product (v, u)");
    Float d = scalar_product(v,u);

    if(d != fbox(0.0f))
        LX_Log::log("FAILURE - scalar product v(1,2).u(2,-1) expected: 0; Got: %f", d);
    else
        LX_Log::log("SUCCESS - scalar product v(1,2).u(2,-1) = 0");

    LX_Log::log("scalar product (z,z)");
    d = scalar_product(z,z);

    if(d != fbox(0.0f))
        LX_Log::log("FAILURE - scalar product z.z (z is a null vector) expected: 0; Got: %f", d);
    else
        LX_Log::log("SUCCESS - scalar product z.z = 0");

    LX_Log::log("norm of z");
    d = vector_norm(z);

    if(d != fbox(0.0f))
        LX_Log::log("FAILURE - norm of z (z is a null vector) expected: 0; Got: %f", d);
    else
        LX_Log::log("SUCCESS - norm of z = 0");


    LX_Log::log("norm of v");
    d = vector_norm(v);

    if(static_cast<int>(d) != static_cast<int>(sqrtf(5)))
        LX_Log::log("FAILURE - norm of v (z is a null vector) expected: %f; Got: %f",
                    sqrtf(5), d);
    else
        LX_Log::log("SUCCESS - norm of v = %f", d);


    LX_Log::log("vector product (v,u)");
    d = vector_product(v,u);

    if(static_cast<int>(d) != static_cast<int>(-5.0f))
        LX_Log::log("FAILURE - vector product v(1,2).u(2,-1) expected: -5.0; Got: %f", d);
    else
        LX_Log::log("SUCCESS - vector product v(1,2).u(2,-1) = %f", d);


    d = vector_product(u,v);

    if(d != fbox(5.0f))
        LX_Log::log("FAILURE - vector product u(2,-1).v(1,2) expected: 5.0; Got: %f", d);
    else
        LX_Log::log("SUCCESS - vector product u(2,-1).v(1,2) = %f", d);


    d = vector_product(z,z);

    if(d != fbox(0.0f))
        LX_Log::log("FAILURE - vector product z.z (z is a null vector) expected: 0; Got: %f", d);
    else
        LX_Log::log("SUCCESS - vector product z.z = 0");

    LX_Log::log(" = END TEST = ");
}


void test_collisionSeg(void)
{
    LX_FloatPosition A{5.0f, 5.0f}, B{10.0f, 10.0f}, C{5.0f, 10.0f};
    LX_FloatPosition D{10.0f, 5.0f}, E{20.0f, 5.0f}, F{15.0f,5.0f};
    const LX_Segment AB{A, B};
    const LX_Segment AC{A, C};
    const LX_Segment AD{A, D};
    const LX_Segment AE{A, E};
    const LX_Segment FE{F, E};
    const LX_Segment BD{B, D};
    const LX_Segment CD{C, D};

    LX_Log::log(" = TEST Collision Segment = ");
    LX_Log::log("A(%d,%d)", A.x.v, A.y.v);
    LX_Log::log("B(%d,%d)", B.x.v, B.y.v);
    LX_Log::log("C(%d,%d)", C.x.v, C.y.v);
    LX_Log::log("D(%d,%d)", D.x.v, D.y.v);
    LX_Log::log("E(%d,%d)", E.x.v, E.y.v);
    LX_Log::log("F(%d,%d)", F.x.v, F.y.v);
    LX_Log::log("collision segement [AB]/[CD]");

    bool d = intersectSegment(AB, CD);

    if(d != true)
        LX_Log::log("FAILURE - intersect [AB]/[CD] expected: TRUE; Got: FALSE");
    else
        LX_Log::log("SUCCESS - intersect [AB]/[CD] OK");


    LX_Log::log("collision segement [AC]/[BD]");
    d = intersectSegment(AC, BD);

    if(d != false)
        LX_Log::log("FAILURE - intersect [AC]/[BD] expected: FALSE; Got: TRUE");
    else
        LX_Log::log("SUCCESS - no intersect [AC]/[BD] OK");

    LX_Log::log("collision segement [AB]/[AD]");
    d = intersectSegment(AB, AD);

    if(d != true)
        LX_Log::log("FAILURE - intersect [AB]/[AD] expected: TRUE; Got: FALSE");
    else
        LX_Log::log("SUCCESS - intersect [AB]/[AD] OK");

    LX_Log::log("collision segement [AD]/[AE]");
    d = intersectSegment(AD, AE);

    if(d != true)
        LX_Log::log("FAILURE - intersect [AD]/[AE] expected: TRUE; Got: FALSE");
    else
        LX_Log::log("SUCCESS - intersect [AD]/[AE] OK");

    LX_Log::log("collision segement [AD]/[FE]");
    d = intersectSegment(AD, FE);

    if(d != true)
        LX_Log::log("FAILURE - intersect [AD]/[FE] expected: FALSE; Got: TRUE");
    else
        LX_Log::log("SUCCESS - no intersect [AD]/[FE] OK");

    LX_Log::log(" = END TEST = ");
}


void test_collisionPointPolygon(void)
{
    /*
        Be careful, if the coordinates of a point
        are to high, you will have incorrect results
    */
    LX_Polygon poly, polyc2;

    LX_FloatPosition N{12.0f, 7.0f};
    LX_FloatPosition O{9.0f, 7.0f};
    LX_FloatPosition P{6.0f, 5.0f};
    LX_FloatPosition Q{6.0f, 4.0f};
    LX_FloatPosition R{1024.0f, 2048.0f};
    LX_FloatPosition S{2.0f, 2.0f};
    LX_FloatPosition T{10.0f, 5.0f};

    poly.addPoint(LX_FloatPosition{10.0f, 5.0f});
    poly.addPoint(LX_FloatPosition{10.0f, 10.0f});
    poly.addPoint(LX_FloatPosition{5.0f, 5.0f});
    poly.addPoint(LX_FloatPosition{7.0f, 2.0f});
    poly.addPoint(LX_FloatPosition{66.0f, 5.0f});

    polyc2.addPoint(LX_FloatPosition{12.0f, 5.0f});
    polyc2.addPoint(LX_FloatPosition{12.0f, 12.0f});
    polyc2.addPoint(LX_FloatPosition{4.0f, 5.0f});
    polyc2.addPoint(LX_FloatPosition{7.0f, 0.0f});

    LX_Log::log(" = TEST Collision Point/Polygon = ");
    displayPoly(poly);
    LX_Log::log("N(%d,%d)", N.x.v, N.y.v);
    LX_Log::log("O(%d,%d)", O.x.v, O.y.v);
    LX_Log::log("P(%d,%d)", P.x.v, P.y.v);
    LX_Log::log("Q(%d,%d)", Q.x.v, Q.y.v);
    LX_Log::log("R(%d,%d)", R.x.v, R.y.v);
    LX_Log::log("S(%d,%d)", S.x.v, S.y.v);
    LX_Log::log("T(%d,%d)", T.x.v, T.y.v);

    LX_Log::log("collision Point N/Polygon");
    bool d = collisionPointPoly(N,poly);

    if(d != false)
        LX_Log::log("FAILURE - N in the polygon. expected: FALSE; Got: TRUE");
    else
        LX_Log::log("SUCCESS - N not in the polygon OK");

    LX_Log::log("collision Point O/Polygon");
    d = collisionPointPoly(O,poly);

    if(d != true)
        LX_Log::log("FAILURE - O not in the polygon. expected: TRUE; Got: FALSE");
    else
        LX_Log::log("SUCCESS - O in the polygon OK");

    LX_Log::log("collision Point P/Polygon");
    d = collisionPointPoly(P,poly);

    if(d != true)
        LX_Log::log("FAILURE - P not in the polygon. expected: TRUE; Got: FALSE");
    else
        LX_Log::log("SUCCESS - P in the polygon OK");

    LX_Log::log("collision Point Q/Polygon");
    d = collisionPointPoly(Q,poly);

    if(d != true)
        LX_Log::log("FAILURE - Q not in the polygon. expected: TRUE; Got: FALSE");
    else
        LX_Log::log("SUCCESS - Q in the polygon OK");

    LX_Log::log("collision Point R/Polygon");
    d = collisionPointPoly(R,poly);

    if(d != false)
        LX_Log::log("FAILURE - R in the polygon. expected: FALSE; Got: TRUE");
    else
        LX_Log::log("SUCCESS - R not in the polygon OK");

    LX_Log::log("collision Point S/Polygon");
    d = collisionPointPoly(S,poly);

    if(d != false)
        LX_Log::log("FAILURE - S in the polygon. expected: FALSE; Got: TRUE");
    else
        LX_Log::log("SUCCESS - S not in the polygon OK");

    LX_Log::log("collision Point T/Polygon");
    d = collisionPointPoly(T,polyc2);

    if(d != true)
        LX_Log::log("FAILURE - T not in the polygon. expected: TRUE; Got: FALSE");
    else
        LX_Log::log("SUCCESS - T in the polygon OK");

    LX_Log::log(" = END TEST = ");
}


void test_collisionCirclePolygon(void)
{
    LX_Circle M{LX_FloatPosition{12.0f, 7.0f}, 1};
    LX_Circle N{LX_FloatPosition{7.0f, 2.0f}, 2};
    LX_Circle O{LX_FloatPosition{9.0f, 7.0f}, 10};
    LX_Circle S{LX_FloatPosition{2.0f, 2.0f}, 2};
    LX_Polygon poly;

    poly.addPoint(LX_FloatPosition{10.0f, 5.0f});
    poly.addPoint(LX_FloatPosition{10.0f, 10.0f});
    poly.addPoint(LX_FloatPosition{5.0f, 5.0f});
    poly.addPoint(LX_FloatPosition{7.0f, 2.0f});
    poly.addPoint(LX_FloatPosition{6.0f, 5.0f});

    LX_Log::log(" = TEST Collision Circle/Polygon = ");

    LX_Log::log("M{(%d,%d),%d}", M.center.x, M.center.y, M.radius);
    LX_Log::log("N{(%d,%d),%d}", N.center.x, N.center.y, N.radius);
    LX_Log::log("O{(%d,%d),%d}", O.center.x, O.center.y, O.radius);
    LX_Log::log("S{(%d,%d),%d}", S.center.x, S.center.y, S.radius);
    displayPoly(poly);

    LX_Log::log("Collision Circle M/Polygon");
    bool d = collisionCirclePoly(M,poly);

    if(d != false)
        LX_Log::log("FAILURE - Circle M in the polygon. expected: FALSE; Got: TRUE");
    else
        LX_Log::log("SUCCESS - Circle M not in the polygon OK");

    LX_Log::log("Collision Circle S/Polygon");
    d = collisionCirclePoly(S,poly);

    if(d != false)
        LX_Log::log("FAILURE - Circle S in the polygon. expected: FALSE; Got: TRUE");
    else
        LX_Log::log("SUCCESS - Circle S not in the polygon OK");

    LX_Log::log("Collision Circle N/Polygon");
    d = collisionCirclePoly(N,poly);

    if(d != true)
        LX_Log::log("FAILURE - Circle N not in the polygon. expected: TRUE; Got: FALSE");
    else
        LX_Log::log("SUCCESS - Circle N in the polygon OK");

    LX_Log::log("Collision Circle O/Polygon");
    d = collisionCirclePoly(O,poly);

    if(d != true)
        LX_Log::log("FAILURE - Circle O not in the polygon. expected: TRUE; Got: FALSE");
    else
        LX_Log::log("SUCCESS - Circle O in the polygon OK");

    LX_Log::log(" = END TEST = ");
}


void test_collisionBoxPolygon(void)
{
    const LX_FloatingBox R1{LX_FloatPosition{1.0f, 1.0f},2,2};
    const LX_FloatingBox R2{LX_FloatPosition{8.0f, 3.0f},10,4};
    const LX_FloatingBox R3{LX_FloatPosition{2.0f, 7.0f},20,2};
    const LX_FloatingBox R4{LX_FloatPosition{8.0f, 6.0f},1,1};
    const LX_FloatingBox R5{LX_FloatPosition{2.0f, 0.0f},16,16};

    LX_Polygon poly;

    poly.addPoint(LX_FloatPosition{10.0f, 5.0f});
    poly.addPoint(LX_FloatPosition{10.0f, 10.0f});
    poly.addPoint(LX_FloatPosition{5.0f, 5.0f});
    poly.addPoint(LX_FloatPosition{7.0f, 2.0f});
    poly.addPoint(LX_FloatPosition{6.0f, 5.0f});

    LX_Log::log(" = TEST Collision Box/Polygon = ");
    LX_Log::log("R1{(%d,%d),%d,%d}", R1.fpoint.x.v, R1.fpoint.y.v, R1.w, R1.h);
    LX_Log::log("R2{(%d,%d),%d,%d}", R2.fpoint.x.v, R2.fpoint.y.v, R2.w, R2.h);
    LX_Log::log("R3{(%d,%d),%d,%d}", R3.fpoint.x.v, R3.fpoint.y.v, R3.w, R3.h);
    LX_Log::log("R4{(%d,%d),%d,%d}", R4.fpoint.x.v, R4.fpoint.y.v, R4.w, R4.h);
    LX_Log::log("poly");
    displayPoly(poly);

    bool d = collisionBoxPoly(R1,poly);

    if(d != false)
        LX_Log::log("FAILURE - test R1 not in the polygon. expected: FALSE; Got: TRUE");
    else
        LX_Log::log("SUCCESS - R1 not in the polygon OK");

    // A point of R2 in the polygon
    d = collisionBoxPoly(R2,poly);

    if(d != true)
        LX_Log::log("FAILURE - test R2 touch the polygon. expected: TRUE; Got: FALSE");
    else
        LX_Log::log("SUCCESS - R2 touch the polygon OK");

    // Some Segments of R3 in the polygon (no point inside)
    d = collisionBoxPoly(R3,poly);

    if(d != true)
        LX_Log::log("FAILURE - test R3 touch the polygon. expected: TRUE; Got: FALSE");
    else
        LX_Log::log("SUCCESS - R3 touch the polygon OK");

    // R4 into the polygon
    d = collisionBoxPoly(R4,poly);

    if(d != true)
        LX_Log::log("FAILURE - test R4 touch the polygon. expected: TRUE; Got: FALSE");
    else
        LX_Log::log("SUCCESS - R4 touch the polygon OK");

    // The polygon into R5
    d = collisionBoxPoly(R5,poly);

    if(d != true)
        LX_Log::log("FAILURE - test polygon into R5. expected: TRUE; Got: FALSE");
    else
        LX_Log::log("SUCCESS - polygon into R5 OK");

    LX_Log::log(" = END TEST = ");
}

void test_collision2Polygon(void)
{
    LX_Polygon poly_empty1, poly_empty2;
    LX_Polygon polyc, polyc2, polync, polync2;
    LX_Polygon poly, poly2, poly3, poly4;

    // Convex polygon
    polyc.addPoint(LX_FloatPosition{10.0f, 5.0f});
    polyc.addPoint(LX_FloatPosition{10.0f, 10.0f});
    polyc.addPoint(LX_FloatPosition{5.0f, 5.0f});
    polyc.addPoint(LX_FloatPosition{7.0f, 2.0f});

    // Non-convex polygon
    polync.addPoint(LX_FloatPosition{1000.0f, 500.0f});
    polync.addPoint(LX_FloatPosition{1000.0f, 1000.0f});
    polync.addPoint(LX_FloatPosition{500.0f, 500.0f});
    polync.addPoint(LX_FloatPosition{700.0f, 200.0f});
    polync.addPoint(LX_FloatPosition{600.0f, 500.0f});

    // Non-convex polygon (again)
    polync2.addPoint(LX_FloatPosition{10.0f, 5.0f});
    polync2.addPoint(LX_FloatPosition{10.0f, 10.0f});
    polync2.addPoint(LX_FloatPosition{5.0f, 5.0f});
    polync2.addPoint(LX_FloatPosition{7.0f, 2.0f});
    polync2.addPoint(LX_FloatPosition{6.0f, 5.0f});

    polyc2.addPoint(LX_FloatPosition{12.0f, 5.0f});
    polyc2.addPoint(LX_FloatPosition{12.0f, 12.0f});
    polyc2.addPoint(LX_FloatPosition{4.0f, 5.0f});
    polyc2.addPoint(LX_FloatPosition{7.0f, 0.0f});

    poly.addPoint(LX_FloatPosition{10.0f, 5.0f});
    poly.addPoint(LX_FloatPosition{10.0f, 10.0f});
    poly.addPoint(LX_FloatPosition{5.0f, 5.0f});
    poly.addPoint(LX_FloatPosition{7.0f, 2.0f});
    poly.addPoint(LX_FloatPosition{6.0f, 5.0f});

    poly2.addPoint(LX_FloatPosition{9.0f, 6.0f});
    poly2.addPoint(LX_FloatPosition{9.0f, 9.0f});
    poly2.addPoint(LX_FloatPosition{6.0f, 4.0f});
    poly2.addPoint(LX_FloatPosition{6.0f, 3.0f});
    poly2.addPoint(LX_FloatPosition{5.0f, 6.0f});

    poly3.addPoint(LX_FloatPosition{0.0f, 0.0f});
    poly3.addPoint(LX_FloatPosition{32.0f, 32.0f});
    poly3.addPoint(LX_FloatPosition{0.0f, 32.0f});

    poly4.addPoint(LX_FloatPosition{2.0f, 2.0f});
    poly4.addPoint(LX_FloatPosition{2.0f, 3.0f});
    poly4.addPoint(LX_FloatPosition{3.0f, 4.0f});

    LX_Log::log(" = TEST Collision Polygon/Polygon = ");

    LX_Log::log("poly");
    displayPoly(poly);
    LX_Log::log("poly2");
    displayPoly(poly2);
    LX_Log::log("poly3");
    displayPoly(poly3);
    LX_Log::log("poly4");
    displayPoly(poly4);
    LX_Log::log("polyc");
    displayPoly(polyc);
    LX_Log::log("polyc2");
    displayPoly(polyc2);
    LX_Log::log("polync");
    displayPoly(polync);
    LX_Log::log("polync2");
    displayPoly(polync2);

    bool d = collisionPoly(poly,poly2);

    if(d != true)
        LX_Log::log("FAILURE - no collision poly/poly2. expected: TRUE; Got: FALSE");
    else
        LX_Log::log("SUCCESS - collision poly/poly2");


    d = collisionPoly(poly,poly3);

    if(d != true)
        LX_Log::log("FAILURE - no collision poly/poly3. expected: TRUE; Got: FALSE");
    else
        LX_Log::log("SUCCESS - collision poly/poly3");


    d = collisionPoly(poly,poly4);

    if(d != false)
        LX_Log::log("FAILURE - no collision poly/poly4. expected: TRUE; Got: FALSE");
    else
        LX_Log::log("SUCCESS - collision poly/poly4");

    // Empty polygons
    LX_Log::log("collision between two empty polygons");
    try
    {
        collisionPoly(poly_empty1,poly_empty2);
        LX_Log::log("FAILURE - this collision cannot be calculated");
    }
    catch(std::invalid_argument&)
    {
        LX_Log::log("SUCCESS - std::invalid_argument exception occured");
    }
    catch(...)
    {
        LX_Log::log("FAILURE - unknown exception occurred");
    }

    LX_Log::log("collision between two convex polygons");
    d = collisionPoly(polyc,polyc2);

    if(d != true)
        LX_Log::log("FAILURE - no collision polyc/polyc2. expected: TRUE; Got: FALSE");
    else
        LX_Log::log("SUCCESS - collision polyc/polyc2");

    // convex/non-convex
    LX_Log::log("collision between a convex polygon and a non-convex polygon");
    d = collisionPoly(polyc2,polync);

    if(d == true)
        LX_Log::log("FAILURE - collision polyc2/polycnc. expected: FALSE; Got: TRUE");
    else
        LX_Log::log("SUCCESS - no collision polyc2/polync");

    // Another test
    LX_Log::log("collision between a convex polygon and a non-convex polygon (again)");
    d = collisionPoly(polyc2,polync2);

    if(d != true)
        LX_Log::log("FAILURE - no collision polyc2/polync2. expected: TRUE; Got: FALSE");
    else
        LX_Log::log("SUCCESS - collision polyc2/polync2");

    // convex/triangle (that is convex)
    LX_Log::log("collision between a convex polygon and a triangle");
    d = collisionPoly(polyc2,poly3);

    if(d != true)
        LX_Log::log("FAILURE - no collision polyc2/poly3. expected: TRUE; Got: FALSE");
    else
        LX_Log::log("SUCCESS - collision polyc2/poly3");

    LX_Log::log(" = END TEST = ");
}

void test_collision2PolygonAgain(void)
{
    const long N = 100000;
    const long M = 1000;
    LX_Polygon poly1, poly2;
    LX_Polygon poly3, poly4;
    unsigned int t1,t2;

    LX_Log::log(" = TEST Collision BIG Polygon/Polygon = ");
    LX_Random::initRand();

    LX_Log::log("Generate two random polygons with %d sides",N);
    for(unsigned int i = 0; i < N; i++)
    {
        poly1.addPoint(LX_FloatPosition{LX_Random::xorshiftRand()%M, LX_Random::xorshiftRand()%M});
        poly2.addPoint(LX_FloatPosition{LX_Random::xorshiftRand()%M, LX_Random::xorshiftRand()%M});
    }

    LX_Log::log("Calculate the collision #1");
    t1 = SDL_GetTicks();
    bool d = collisionPoly(poly1, poly2);
    t2 = SDL_GetTicks();
    LX_Log::log("Result:%s collision between the two random polygons", (d ? "":" No"));
    LX_Log::log("Calculation done in %d ms", t2-t1);

    LX_Log::log("Generate two other random polygons with %d sides in two different areas",N);
    for(unsigned int i = 0; i < N; i++)
    {
        poly3.addPoint(LX_FloatPosition{LX_Random::xorshiftRand()%M, LX_Random::xorshiftRand()%M});
        poly4.addPoint(LX_FloatPosition{LX_Random::xorshiftRand()%M + N, LX_Random::xorshiftRand()%M + N});
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
    LX_FloatPosition P{{1.0f}, {2.0f}};
    LX_FloatingBox R{LX_FloatPosition{8.f, 4.0f},10,10};

    const float X = {-4.0f};
    const float Y = {8.0f};

    LX_Polygon poly;
    LX_Polygon expoly;

    poly.addPoint(LX_FloatPosition{24.0f, 32.0f});
    poly.addPoint(LX_FloatPosition{48.0f, 32.0f});
    poly.addPoint(LX_FloatPosition{128.0f, 64.0f});
    poly.addPoint(LX_FloatPosition{64.0f, 64.0f});
    poly.addPoint(LX_FloatPosition{32.0f, 32.0f});
    // expected polygon
    expoly.addPoint(LX_FloatPosition{24.0f + X, 32.0f + Y});
    expoly.addPoint(LX_FloatPosition{48.0f + X, 32.0f + Y});
    expoly.addPoint(LX_FloatPosition{128.0f + X, 64.0f + Y});
    expoly.addPoint(LX_FloatPosition{64.0f + X, 64.0f + Y});
    expoly.addPoint(LX_FloatPosition{32.0f + X, 32.0f + Y});

    LX_Log::log(" = TEST Move = ");

    LX_Log::log("P(%d,%d)", P.x.v, P.y.v);
    LX_Log::log("R{(%d,%d),%d,%d}", R.fpoint.x.v, R.fpoint.y.v, R.w, R.h);
    LX_Log::log("poly");
    displayPoly(poly);
    LX_Log::log("expoly");
    displayPoly(expoly);

    LX_Log::log("Point");

    LX_FloatPosition expected_point{P.x.v + 1.0f, P.y.v + 1.0f};
    movePoint(P, LX_Vector2D{{1.0f}, {1.0f}});

    if(P.x == expected_point.x && P.y == expected_point.y)
        LX_Log::log("Point P(%d,%d)", P.x.v, P.y.v);
    else
        LX_Log::log("FAILURE - expected : Point P(2,3); Got: P(%d,%d)", P.x.v, P.y.v);

    LX_Log::log("Rectangle");

    const LX_FloatingBox expected_aabb{R.fpoint.x + 2, R.fpoint.y + 3, R.w, R.h};
    moveBox(R, LX_Vector2D{{2.0f}, {3.0f}});

    if(R.fpoint == expected_aabb.fpoint)
        LX_Log::log("SUCCESS - Rectangle R{(%d,%d),%d,%d}", R.fpoint.x.v, R.fpoint.y.v, R.w, R.h);
    else
        LX_Log::log("FAILURE - expected : Rectangle R(3,6,10,10); got: R{(%d,%d),%d,%d}",
                    R.fpoint.x.v, R.fpoint.y.v, R.w, R.h);

    movePoly(poly, LX_Vector2D{X, Y});
    const unsigned long n = poly.numberOfEdges();
    const unsigned long m = expoly.numberOfEdges();

    LX_Log::log("expected polygon");
    displayPoly(expoly);
    LX_Log::log("got");
    displayPoly(poly);

    if(n != m)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - ≠ degree. #edges expected: %d, got: %d",m,n);
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - these polygons have the same degree");

    try
    {
        bool ok = true;
        for(unsigned long j = 0; j < n; j++)
        {
            LX_FloatPosition p1 = poly.getPoint(j);
            LX_FloatPosition p2 = expoly.getPoint(j);
            if(p1 != p2)
            {
                LX_Log::logInfo(LX_Log::LX_LOG_TEST,
                                "FAILURE - at j = %d → ≠ point; expected: (%d,%d); got: (%d,%d)",
                                j, p2.x.v, p2.y.v, p1.x.v,p1.y.v);
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

    // reset
    movePoly(poly, LX_Vector2D{-X, -Y});
    const LX_FloatingBox& box = expoly.getEnclosingBox();
    const LX_FloatPosition q{box.fpoint.x + box.w / 2.0f, box.fpoint.y + box.h / 2.0f};

    movePolyTo(poly, q);
    const LX_FloatingBox& b = poly.getEnclosingBox();
    LX_FloatPosition s{b.fpoint.x + b.w / 2.0f, b.fpoint.y + b.h / 2.0f};
    LX_Log::log("centroid of poly: s(%d,%d)", s.x.v, s.y.v);
    LX_Log::log("centroid of expoly: q(%d,%d)", q.x.v, q.y.v);

    LX_Log::log(" = END TEST = ");
}


void test_assignment(void)
{
    LX_Log::log(" = TEST Assignement = ");

    LX_FloatPosition P{1.0f, 2.0f};
    LX_FloatPosition Q = P;

    LX_Log::log("P(%d,%d)", P.x.v, P.y.v);

    if(Q == P)
        LX_Log::log("SUCCESS - Point Q(%d,%d)", Q.x.v, Q.y.v);
    else
        LX_Log::log("FAILURE - expected: Q(1,2); Got: Q(%d,%d)", Q.x.v, Q.y.v);

    LX_Circle C{LX_FloatPosition{4.0f, 9.0f},10};

    LX_Log::log("C{(%d,%d),%d}", C.center.x.v, C.center.y.v, C.radius);

    LX_Circle D = C;  // assignment

    if(D == C)
        LX_Log::log("SUCCESS - Circle D{(%d,%d),%d}", D.center.x.v,
                    D.center.y.v, D.radius);
    else
        LX_Log::log("FAILURE - expected: Circle D{{4,9},10}; Got: D{(%d,%d),%d}",
                    D.center.x.v, D.center.y.v, D.radius);

    LX_Vector2D v{3.14f,1.59f};
    LX_Log::log("Vector2D v(%f,%f)", v.vx.v, v.vy.v);

    LX_Vector2D u = v;  // assignment

    if(u == v)
        LX_Log::log("SUCCESS - Vector2D v(%f,%f)", u.vx.v, u.vy.v);
    else
        LX_Log::log("FAILURE - expected: u(3.14,1.59); Got: u(%f,%f)", u.vx.v, u.vy.v);

    LX_Vector2D t{0.0f,0.0f}, w{0.0f,0.0f};

    if(t == w)
        LX_Log::log("SUCCESS - Vector2D t(%f,%f)", t.vx.v, t.vy.v);
    else
        LX_Log::log("FAILURE - expected: w(0.0f,0.0f); Got: u(%f,%f)", w.vx.v, w.vy.v);

    LX_Log::log(" = END TEST = ");
}


void test_operator(void)
{
    LX_Circle C{LX_FloatPosition{2.0f, 3.0f}, 10};
    LX_Circle E{LX_FloatPosition{4.0f, 9.0f}, 32};
    LX_Circle F{LX_FloatPosition{8.0f, 21.0f}, 10};

    LX_Vector2D v{-3.14f, 1.59f};
    LX_Vector2D u = v;
    LX_Vector2D w{3.140001f, 1.590001f};
    LX_Vector2D i{2.56f, 1.59f};
    LX_Vector2D j{-0.14f, -1.28f};

    LX_Log::log(" = TEST operators = ");

    LX_Log::log("Vector2D v(%f,%f)", v.vx.v, v.vy.v);
    LX_Log::log("C{(%d,%d),%d};", C.center.x, C.center.y,C.radius);
    LX_Log::log("E{(%d,%d),%d};", E.center.x, E.center.y, E.radius);
    LX_Log::log("F{(%d,%d),%d};", F.center.x, F.center.y, F.radius);
    LX_Log::log("Vector2D u(%f,%f)", u.vx.v, u.vy.v);
    LX_Log::log("Vector2D v(%f,%f)", v.vx.v, v.vy.v);
    LX_Log::log("Vector2D w(%f,%f)", w.vx.v, w.vy.v);
    LX_Log::log("Vector2D i(%f,%f)", i.vx.v, i.vy.v);
    LX_Log::log("Vector2D j(%f,%f)", j.vx.v, j.vy.v);

    if(E > C)
        LX_Log::log("SUCCESS - E > C");
    else
        LX_Log::log("FAILURE - E ≤ C");

    if(C < E)
        LX_Log::log("SUCCESS - C < E");
    else
        LX_Log::log("FAILURE - C ≥ E");

    if(E >= C)
        LX_Log::log("SUCCESS - E ≥ C");
    else
        LX_Log::log("FAILURE - E < C");

    if(C <= E)
        LX_Log::log("SUCCESS - C ≤ E");
    else
        LX_Log::log("FAILURE - C > E");

    if(F >= C)
        LX_Log::log("SUCCESS - F ≥ C");
    else
        LX_Log::log("FAILURE - F < C");

    if(C <= F)
        LX_Log::log("SUCCESS - C ≤ F");
    else
        LX_Log::log("FAILURE - C > F");

    if(!(E < C))
        LX_Log::log("SUCCESS - !(E < C)");
    else
        LX_Log::log("FAILURE - E < C");

    LX_Log::log("E ≠ C ?");
    if(E != C)
        LX_Log::log("SUCCESS - E ≠ C");
    else
        LX_Log::log("FAILURE - E == C");

    LX_Log::log(" !(E == C) ?");
    if(!(E == C))
        LX_Log::log("SUCCESS - !(E == C)");
    else
        LX_Log::log("FAILURE - E == C");

    if(u == v)
        LX_Log::log("SUCCESS - u == v");
    else
        LX_Log::log("FAILURE - expected: u == v; Got: u(%f,%f) ≠ v(%f,%f)",
                    u.vx.v, u.vy.v, v.vx.v, v.vy.v);

    if(v == w)
        LX_Log::log("FAILURE - expected: v ≠ w; Got: v(%f,%f) ≠ w(%f,%f)",
                    v.vx.v, v.vy.v, w.vx.v, w.vy.v);
    else
        LX_Log::log("SUCCESS - v ≠ w");

    if(v != i)
        LX_Log::log("SUCCESS - v ≠ i");
    else
        LX_Log::log("FAILURE - expected: v ≠ i; Got: v(%f,%f) ≠ i(%f,%f)",
                    v.vx.v, v.vy.v, i.vx.v, i.vy.v);

    if(j != i)
        LX_Log::log("SUCCESS - j ≠ i");
    else
        LX_Log::log("FAILURE - expected: j ≠ i; Got: j(%f,%f) ≠ i(%f,%f)",
                    j.vx.v, j.vy.v, i.vx.v, i.vy.v);

    LX_Log::log(" = END TEST = ");
}


void test_VectorPlusMinusOp(void)
{
    LX_Vector2D u{3.14f, 1.59f};
    LX_Vector2D v{-1.28f, 5.12f};
    LX_Vector2D z{-2.56f, 10.24f};

    LX_Vector2D a{3.14f, 2.048f};
    LX_Vector2D b{1.28f, 0.64f};
    LX_Vector2D c{-2.56f, 10.24f};

    LX_Vector2D exp_sum_vec = {u.vx + v.vx, u.vy + v.vy};
    LX_Vector2D exp_add_vec = {u.vx + z.vx, u.vy + z.vy};

    LX_Vector2D exp_diff_vec = {a.vx - b.vx, a.vy - b.vy};
    LX_Vector2D exp_sub_vec = {a.vx - c.vx, a.vy - c.vy};

    LX_Log::log(" = TEST Vector arithmetic = ");
    LX_Log::log(" '+','+=','-','-='");

    LX_Log::log("Vector2D u(%f,%f)", u.vx.v, u.vy.v);
    LX_Log::log("Vector2D v(%f,%f)", v.vx.v, v.vy.v);
    LX_Log::log("w = u + v;");

    LX_Vector2D w = u + v;
    LX_Log::log("Vector2D w(%f,%f)", w.vx.v, w.vy.v);

    if(w == exp_sum_vec)
        LX_Log::log("SUCCESS - w(%f,%f) as expected", w.vx.v, w.vy.v);
    else
        LX_Log::log("FAILURE - expected: LX_Vector2D(%f,%f) Got: w(%f,%f)",
                    exp_sum_vec.vx.v, exp_sum_vec.vy.v, w.vx.v, w.vy.v);

    LX_Log::log("Vector2D u(%f,%f)", u.vx.v, u.vy.v);
    LX_Log::log("Vector2D v(%f,%f)", v.vx.v, v.vy.v);
    LX_Log::log("u += z;");

    u += z;

    LX_Log::log("Vector2D u(%f,%f)", u.vx.v, u.vy.v);

    if(u == exp_add_vec)
        LX_Log::log("SUCCESS - u(%f,%f) as expected", u.vx.v, u.vy.v);
    else
        LX_Log::log("FAILURE - expected: LX_Vector2D(%f,%f) Got: u(%f,%f)",
                    exp_add_vec.vx.v, exp_add_vec.vy.v, u.vx.v, u.vy.v);

    LX_Log::log("Vector2D a(%f,%f)", a.vx.v, a.vy.v);
    LX_Log::log("Vector2D b(%f,%f)", b.vx.v, b.vy.v);
    LX_Log::log("d = a - b;");

    LX_Vector2D d = a - b;

    LX_Log::log("Vector2D d(%f,%f)", d.vx.v, d.vy.v);

    if(d == exp_diff_vec)
        LX_Log::log("SUCCESS - d(%f,%f) as expected", d.vx.v, d.vy.v);
    else
        LX_Log::log("FAILURE - expected: LX_Vector2D(%f,%f) Got: d(%f,%f)",
                    exp_diff_vec.vx.v, exp_diff_vec.vy.v, d.vx.v, d.vy.v);

    LX_Log::log("Vector2D a(%f,%f)", a.vx.v, a.vy.v);
    LX_Log::log("Vector2D b(%f,%f)", b.vx.v, b.vy.v);
    LX_Log::log("a -= c;");

    a -= c;

    if(a == exp_sub_vec)
        LX_Log::log("SUCCESS - a(%f,%f) as expected", a.vx.v, a.vy.v);
    else
        LX_Log::log("FAILURE - expected: LX_Vector2D(%f,%f) Got: a(%f,%f)",
                    exp_sub_vec.vx.v, exp_sub_vec.vy.v, a.vx.v, a.vy.v);

    LX_Log::log(" = END TEST = ");
}


void test_VectorOpposite(void)
{
    LX_Log::log(" = TEST Vector Opposite = ");

    LX_Vector2D u = {3.14f,-2.56f};
    LX_Vector2D expected_vec = {-u.vx.v,-u.vy};

    LX_Log::log("Vector2D u(%f,%f)", u.vx.v, u.vy.v);
    LX_Log::log("-u;");

    if(expected_vec == (-u) )
        LX_Log::log("SUCCESS - u(%f,%f) as expected", (-u).vx.v, (-u).vy.v);
    else
        LX_Log::log("FAILURE - expected: LX_Vector2D(%f,%f) Got: u(%f,%f)",
                    expected_vec.vx.v, expected_vec.vy.v, (-u).vx.v, (-u).vy.v);

    LX_Log::log(" = END TEST = ");
}


void test_VectorIncDec(void)
{
    LX_Log::log(" = TEST Vector Increment and decrement = ");

    LX_Vector2D u{1.41f,-5.92f};
    LX_Vector2D v = u;
    LX_Vector2D exp_inc_pre_vec{u.vx + 1.0f,u.vy + 1.0f};
    LX_Vector2D exp_inc_post_vec{u.vx + 1.0f,u.vy + 1.0f};
    LX_Vector2D exp_dec_pre_vec{u.vx - 1.0f,u.vy - 1.0f};
    LX_Vector2D exp_dec_post_vec{u.vx - 1.0f,u.vy - 1.0f};

    LX_Log::log("Increment");
    LX_Log::log("Vector2D u(%f,%f)", u.vx.v, u.vy.v);
    LX_Log::log("++u;");

    ++u;

    if(u == exp_inc_pre_vec)
        LX_Log::log("SUCCESS - u(%f,%f) as expected", u.vx.v, u.vy.v);
    else
        LX_Log::log("FAILURE - expected: LX_Vector2D(%f,%f) Got: u(%f,%f)",
                    exp_inc_pre_vec.vx.v, exp_inc_pre_vec.vy.v, u.vx.v, u.vy.v);

    LX_Log::log("Vector2D v(%f,%f)", v.vx.v, v.vy.v);
    LX_Log::log("v++;");

    v++;

    if(v == exp_inc_post_vec)
        LX_Log::log("SUCCESS - v(%f,%f) as expected", v.vx.v, v.vy.v);
    else
        LX_Log::log("FAILURE - expected: LX_Vector2D(%f,%f) Got: v(%f,%f)",
                    exp_inc_post_vec.vx.v, exp_inc_post_vec.vy.v, v.vx.v, v.vy.v);

    u = {1.41f, -5.92f};
    v = u;

    LX_Log::log("Decrement");
    LX_Log::log("Vector2D u(%f,%f)", u.vx.v, u.vy.v);
    LX_Log::log("--u;");

    --u;

    if(u == exp_dec_pre_vec)
        LX_Log::log("SUCCESS - u(%f,%f) as expected", u.vx.v, u.vy.v);
    else
        LX_Log::log("FAILURE - expected: LX_Vector2D(%f,%f) Got: u(%f,%f)",
                    exp_dec_pre_vec.vx.v, exp_dec_pre_vec.vy.v, u.vx.v, u.vy.v);

    LX_Log::log("Vector2D v(%f,%f)", v.vx.v, v.vy.v);
    LX_Log::log("v--;");

    v--;

    if(v == exp_dec_post_vec)
        LX_Log::log("SUCCESS - v(%f,%f) as expected", v.vx.v, v.vy.v);
    else
        LX_Log::log("FAILURE - expected: LX_Vector2D(%f,%f) Got: v(%f,%f)",
                    exp_dec_post_vec.vx.v, exp_dec_post_vec.vy.v, v.vx.v, v.vy.v);

    LX_Log::log(" = END TEST = ");
}


void test_VectorCollinear(void)
{
    LX_Log::log(" = TEST Vector collinearity = ");

    LX_Vector2D u = {1.41f, -2.48f};
    LX_Vector2D v = {u.vx *2.0f, u.vy *2.0f};
    LX_Vector2D w = u;
    LX_Vector2D o = {0.0f, 0.0f};
    LX_Vector2D t = {2.01f, 4.12f};

    LX_Log::log("Vector2D u(%f,%f)", u.vx.v, u.vy.v);
    LX_Log::log("Vector2D v(%f,%f)", v.vx.v, v.vy.v);
    LX_Log::log("Vector2D w(%f,%f)", w.vx.v, w.vy.v);
    LX_Log::log("Vector2D o(%f,%f)", o.vx.v, o.vy.v);
    LX_Log::log("Vector2D t(%f,%f)", t.vx.v, t.vy.v);

    LX_Log::log("test: zero vector");

    if(isNullVector(o))
        LX_Log::log("SUCCESS - o is a zero vector: o(%f,%f)", o.vx.v, o.vy.v);
    else
        LX_Log::log("FAILURE - o is not a zero vector: o(%f,%f)", o.vx.v, o.vy.v);

    if(!isNullVector(t))
        LX_Log::log("SUCCESS - t is not a zero vector: t(%f,%f)", t.vx.v, t.vy.v);
    else
        LX_Log::log("FAILURE - t is a zero vector: t(%f,%f)", t.vx.v, t.vy.v);

    LX_Log::log("test: collinearity between u and v");

    if(collinear(u,v))
        LX_Log::log("SUCCESS - u and v are colinear");
    else
        LX_Log::log("FAILURE - expected: u and v must be colinear; Got: u(%f,%f) and v(%f,%f)",
                    u.vx.v, u.vy.v, v.vx.v, v.vy.v);


    LX_Log::log("test: collinearity between u and w");

    if(collinear(u,w))
        LX_Log::log("SUCCESS - u and w are colinear");
    else
        LX_Log::log("FAILURE - expected: u and w must be colinear; Got: u(%f,%f) and w(%f,%f)",
                    u.vx.v, u.vy.v, w.vx.v, w.vy.v);

    LX_Log::log("test: collinearity between u and o");

    if(collinear(u,o))
        LX_Log::log("SUCCESS - u and o are colinear");
    else
        LX_Log::log("FAILURE - expected: u and o must be colinear; Got: u(%f,%f) and o(%f,%f)",
                    u.vx.v, u.vy.v, o.vx.v, o.vy.v);

    LX_Log::log("test: collinearity between u and t");

    if(!collinear(u,t))
        LX_Log::log("SUCCESS - u and t are colinear");
    else
        LX_Log::log("FAILURE - expected: u and t must be colinear; Got: u(%f,%f) and t(%f,%f)",
                    u.vx.v, u.vy.v, t.vx.v, t.vy.v);

    LX_Log::log(" = END TEST = ");
}


void test_VectorLambda(void)
{
    LX_Log::log(" = TEST Vector, scalar multiplication = ");

    float lambda1 = 2.0f;
    float lambda2 = 0.0f;
    LX_Vector2D v{3.14f,1.59f};
    LX_Vector2D w{v.vx * lambda1,v.vy * lambda1};
    LX_Vector2D t{0.0f, 0.0f};

    LX_Log::log("Vector2D v(%f,%f)", v.vx.v, v.vy.v);

    v = v * lambda1;

    if(v == w)
        LX_Log::log("SUCCESS - Vector2D v(%f,%f)", v.vx.v, v.vy.v);
    else
        LX_Log::log("FAILURE - expected: v(%f,%f); Got: v(%f,%f)", w.vx.v, w.vy.v,
                    v.vx.v, v.vy.v);

    v = v * lambda2;

    if(v == t)
        LX_Log::log("SUCCESS - Vector2D v(%f,%f)", v.vx.v, v.vy.v);
    else
        LX_Log::log("FAILURE - expected: v(%f,%f); Got: v(%f,%f)", t.vx.v, t.vy.v,
                    v.vx.v, v.vy.v);

    // Test normalization
    LX_Log::log("Reset v");

    v = {3.0f,0.0f};
    LX_Log::log("Vector2D v(%f,%f)", v.vx.v, v.vy.v);
    LX_Log::log("Normalize v");

    normalize(v);
    Float n = vector_norm(v);

    if(n == fbox(1.0f))
        LX_Log::log("SUCCESS - Vector2D v(%f,%f) normalized, norm: %f", v.vx.v, v.vy.v, n);
    else
        LX_Log::log("FAILURE - expected: v(%f,%f); Got: v(%f,%f)", t.vx.v, t.vy.v,
                    v.vx.v, v.vy.v);

    LX_Log::logWarning(LX_Log::LX_LOG_TEST,"The previous test may fail with some complex float values in the vector");
    LX_Log::logWarning(LX_Log::LX_LOG_TEST,"Try it with V(3.14,2.56)");

    LX_Log::log("Vector2D t(%f,%f)", t.vx.v, t.vy.v);
    LX_Log::log("Normalize t");

    normalize(t);   // t is a null vector

    if(t == t)
        LX_Log::log("SUCCESS - Vector2D t(%f,%f) normalized, norm: %f", v.vx.v, v.vy.v, n);
    else
        LX_Log::log("FAILURE - a zero vector must be normalized to 0");

    LX_Log::log(" = END TEST = ");
}

#define i32(x) static_cast<int>(x)

void test_conversion(void)
{
    LX_Log::log(" = TEST conversion = ");

    LX_FloatPosition fp1{0.0f, 0.0f};
    LX_FloatPosition fp2{64.0f, 128.0f};
    LX_Point exp1{i32(fp1.x.v), i32(fp1.y.v)};
    LX_Point exp2{i32(fp2.x.v), i32(fp2.y.v)};

    LX_Point p1 = toPixelPosition(fp1);
    LX_Point p2 = toPixelPosition(fp2);

    if(p1 == exp1)
        LX_Log::log("SUCCESS - p1(%d, %d)", p1.x, p1.y);
    else
        LX_Log::log("FAILURE - p1");

    if(p2 == exp2)
        LX_Log::log("SUCCESS - p2(%d, %d)", p2.x, p2.y);
    else
        LX_Log::log("FAILURE - p2");

    LX_Log::log(" = END TEST = ");
}

void displayPoly(LX_Polygon& poly)
{
    ostringstream os;
    os << "{";
    const unsigned long n = poly.numberOfEdges();
    for(unsigned long i = 0; i < n; ++i)
    {
        os << "(" << (poly.getPoint(i)).x << ","
           << (poly.getPoint(i)).y << ")";
        if(i != n)
            os << ";";
    }
    os << "}";
    LX_Log::log("%s",os.str().c_str());
}
