

#include <Lunatix/Lunatix.hpp>
#include <cmath>
#include <sstream>
#include <stdexcept>

using namespace std;
using namespace lx::Physics;
using namespace FloatBox;

void test_euclide( void );
void test_collisionPointCircle( void );
void test_collisionPointBox( void );
void test_collision2Circle( void );
void test_collision2Box( void );
void test_collisionBoxCircle( void );

void testLine();
void test_Vector2D( void );
void testPolygon( void );

void test_collisionSeg( void );
void test_collisionPointPolygon( void );
void test_collisionCirclePolygon( void );
void test_collisionBoxPolygon( void );
void test_collision2Polygon( void );
void test_collision2PolygonAgain( void );

void test_move( void );
void test_assignment( void );
void test_operator( void );

void test_VectorPlusMinusOp( void );
void test_VectorOpposite( void );
void test_VectorIncDec( void );
void test_VectorCollinear( void );
void test_VectorLambda( void );

void test_conversion( void );

using namespace lx::Physics;

void displayPoly( Polygon& poly );

int main( int argc, char ** argv )
{
    bool err = lx::init();

    if ( !err )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - lx::init() failed" );
    else
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - The LunatiX library has been initialized with success" );

    lx::Log::setDebugMode();
    lx::Log::log( " ==== Test Physics ==== \n" );

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

    lx::quit();
    lx::Log::log( " ==== END Physics ==== \n" );
    return EXIT_SUCCESS;
}


// Test the euclidean functions
void test_euclide( void )
{
    FloatPosition A = {1, 1};
    FloatPosition B = {10, 1};
    FloatPosition C = {0, 0};
    FloatPosition D = {10, 10};

    lx::Log::log( " = TEST EUCLIDE = " );
    lx::Log::log( "A(%d,%d)", A.x, A.y );
    lx::Log::log( "B(%d,%d)", B.x, B.y );
    lx::Log::log( "C(%d,%d)", C.x, C.y );
    lx::Log::log( "D(%d,%d)", D.x, D.y );
    lx::Log::log( "Square distance AB" );

    Float d = euclide_square_distance( A, B );

    if ( d != fbox( 81.0f ) )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - Bad square distance AB - expected: 81; Got: %f", d );
    else
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - Good square distance AB: %f", d );

    lx::Log::log( "Distance between A and B" );
    d = euclide_distance( A, B );

    if ( d != fbox( 9.0f ) )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - Bad distance AB - expected: 9; Got: %f", d );
    else
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - Good distance AB: %f", d );

    // Test CD
    lx::Log::log( "Square distance CD" );
    d = euclide_square_distance( C, D );

    if ( d != fbox( 200.0f ) )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - Bad square distance CD - expected: 81; Got: %f", d );
    else
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - Good square distance CD: %f", d );

    lx::Log::log( "Distance between C and D" );
    d = euclide_distance( C, D );

    if ( static_cast<int>( d ) != static_cast<int>( sqrt( 200 ) ) )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - Bad distance CD - expected: %f; Got: %f",
                          static_cast<float>( sqrt( 200 ) ), d );
    else
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - Good square distance CD: %f", d );

    lx::Log::log( " = END TEST = " );
}


void test_collisionPointCircle( void )
{
    Circle circle{FloatPosition{100, 100}, 10};

    FloatPosition A{100, 100};
    FloatPosition B{50, 50};
    FloatPosition C{105, 105};
    FloatPosition D{100, 125};

    lx::Log::log( " = TEST POINT/CIRCLE = " );
    lx::Log::log( "A(%d,%d)", A.x.v, A.y.v );
    lx::Log::log( "B(%d,%d)", B.x.v, B.y.v );
    lx::Log::log( "C(%d,%d)", C.x.v, C.y.v );
    lx::Log::log( "D(%d,%d)", D.x.v, D.y.v );

    lx::Log::log( "Collision Point A/Circle" );
    bool d = collisionPointCircle( A, circle );

    if ( d != true )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - expected: TRUE; Got: %d", d );
    else
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - collision, the point is in the circle: %d", d );

    lx::Log::log( "Collision Point B/Circle" );
    d = collisionPointCircle( B, circle );

    if ( d != false )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - expected: FALSE; Got: TRUE" );
    else
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - collision, the point is not in the circle" );

    lx::Log::log( "Collision Point C/Circle" );
    d = collisionPointCircle( C, circle );

    if ( d != true )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - expected: TRUE; Got: FALSE" );
    else
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - collision, the point is in the circle" );

    lx::Log::log( "Collision Point D/Circle" );
    d = collisionPointCircle( D, circle );

    if ( d != false )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - expected: FALSE; Got: TRUE" );
    else
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - collision, the point is not in the circle" );

    lx::Log::log( " = END TEST = " );
}


void test_collisionPointBox( void )
{
    FloatPosition A{100, 100}, B{50, 50};
    FloatingBox aabb{FloatPosition{40.0f, 40.0f}, 30, 30};

    lx::Log::log( " = TEST POINT/AABB = " );
    lx::Log::log( "A(%f,%f)", A.x.v, A.y.v );
    lx::Log::log( "B(%f,%f)", B.x.v, B.y.v );
    lx::Log::log( "AABB{(%d,%d),%d,%d}", aabb.p.x.v, aabb.p.y.v, aabb.w, aabb.h );

    lx::Log::log( "Collision Point A/AABB" );
    bool d = collisionPointBox( A, aabb );

    if ( d != false )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - expected: FALSE; Got: TRUE" );
    else
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - collision, the point is out of the rectangle" );

    lx::Log::log( "Collision Point B/AABB" );
    d = collisionPointBox( B, aabb );

    if ( d != true )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - expected: TRUE; Got: FALSE" );
    else
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - collision, the point is into the rectangle" );

    lx::Log::log( " = END TEST = " );
}


void test_collision2Circle( void )
{
    Circle A{FloatPosition{10.f, 10.0f}, 5};
    Circle B{FloatPosition{13.0f, 12.0f}, 3};
    Circle C{FloatPosition{100.0f, 100.0f}, 50};

    lx::Log::log( " = TEST CIRCLE/CIRCLE = " );
    lx::Log::log( "A{(%d,%d),%d}", A.center.x.v, A.center.y.v, A.radius );
    lx::Log::log( "B{(%d,%d),%d}", B.center.x.v, B.center.y.v, B.radius );
    lx::Log::log( "C{(%d,%d),%d}", C.center.x.v, C.center.y.v, C.radius );

    lx::Log::log( "Collision Circles A/B" );
    bool d = collisionCircle( A, B );

    if ( d != true )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE -collision A/B expected: TRUE; Got: FALSE" );
    else
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - collision between two circles A and B" );

    lx::Log::log( "Collision Circles C/B" );
    d = collisionCircle( C, B );

    if ( d != false )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - collisoon C/B expected: FALSE; Got: TRUE" );
    else
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - no collision between two circles C and B" );

    lx::Log::log( "Collision Circles A/C" );
    d = collisionCircle( A, C );

    if ( d != false )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - collisoon C/B expected: FALSE; Got: TRUE" );
    else
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - no collision between two circles A and C" );

    lx::Log::log( " = END TEST = " );
}


void test_collision2Box( void )
{
    const FloatingBox R1{FloatPosition{0.0f, 0.0f}, 50, 25};
    const FloatingBox R2{FloatPosition{40.0f, 21.0f}, 32, 25};
    const FloatingBox R3{FloatPosition{64.0f, 32.0f}, 10, 100};

    lx::Log::log( " = TEST RECT/RECT = " );
    lx::Log::log( "R1{(%d,%d),%d,%d}", R1.p.x.v, R1.p.y.v, R1.w, R1.h );
    lx::Log::log( "R2{(%d,%d),%d,%d}", R2.p.x.v, R2.p.y.v, R2.w, R2.h );
    lx::Log::log( "R3{(%d,%d),%d,%d}", R3.p.x.v, R3.p.y.v, R3.w, R3.h );

    lx::Log::log( "Collision AABB R1/R2" );
    bool d = collisionBox( R1, R2 );

    if ( d != true )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE -collision R1/R2 expected: TRUE; Got: FALSE" );
    else
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - collision R1/R2 OK" );

    lx::Log::log( "Collision AABB R2/R3" );
    d = collisionBox( R2, R3 );

    if ( d != true )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE -collision R2/R3 expected: TRUE; Got: FALSE" );
    else
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - collision R2/R3 OK" );

    lx::Log::log( "Collision AABB R3/R1" );
    d = collisionBox( R3, R1 );

    if ( d != false )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - collisoon R3/R1 expected: FALSE; Got: TRUE" );
    else
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - no collision R3/R1 OK" );

    lx::Log::log( " = END TEST = " );
}


void test_collisionBoxCircle( void )
{
    FloatingBox R1{FloatPosition{0.0f, 0.0f}, 50, 25};
    Circle A{FloatPosition{10.0f, 10.0f}, 5};
    Circle B{FloatPosition{51.0f, 26.0f}, 15};
    Circle C{FloatPosition{100.0f, 100.0f}, 40};

    lx::Log::log( " = TEST RECT/CIRCLE = " );
    lx::Log::log( "R1{(%d,%d),%d,%d}", R1.p.x.v, R1.p.y.v, R1.w, R1.h );
    lx::Log::log( "A{(%f,%f),%u}", A.center.x.v, A.center.y.v, A.radius );
    lx::Log::log( "B{(%f,%f),%u}", B.center.x.v, B.center.y.v, B.radius );
    lx::Log::log( "C{(%f,%f),%u}", C.center.x.v, C.center.y.v, C.radius );

    lx::Log::log( "Collision Circle/Box AABB A/R1" );
    bool d = collisionCircleBox( A, R1 );

    if ( d != true )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - collision A/R1 expected: TRUE; Got: FALSE" );
    else
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - collision A/R1 OK" );

    lx::Log::log( "Collision Circle/Box AABB B/R1" );
    d = collisionCircleBox( B, R1 );

    if ( d != true )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - collision B/R1 expected: TRUE; Got: FALSE" );
    else
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - collision B/R1 OK" );

    lx::Log::log( "Collision Circle/Box AABB C/R1" );
    d = collisionCircleBox( C, R1 );

    if ( d != false )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - collision C/R1 expected: FALSE; Got: TRUE" );
    else
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - collision C/R1 OK" );

    lx::Log::log( " = END TEST = " );
}


void testPolygon( void )
{
    Polygon poly;
    poly.addPoint( FloatPosition{10.0f, 5.0f} );
    poly.addPoint( FloatPosition{10.0f, 10.0f} );
    poly.addPoint( FloatPosition{5.0f, 5.0f} );

    lx::Log::log( " = TEST POLYGON = " );
    lx::Log::log( "Number of edges" );
    unsigned long d = poly.numberOfEdges();

    if ( d != 3 )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - number of real edges expected: 3; Got: %u",
                          d );
    else
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - number of real edges: %u", d );

    displayPoly( poly );

    FloatPosition p = poly.getPoint( 0 );
    lx::Log::log( "poly.getPoint(0): (%d,%d)", p.x.v, p.y.v );

    if ( p.x != fbox( 10.0f ) )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - x position expected: 10; Got: %d",
                          p.x.v );
    else
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - x = %d", p.x.v );

    if ( p.y != fbox( 5.0f ) )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - y position expected: 5; Got: %d",
                          p.y.v );
    else
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - y = %d", p.y.v );

    // Is the triangle convex ?
    lx::Log::log( "Test the convexity of the polygon." );
    if ( poly.isConvex() == false )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - A triangle is not a non-convex polygon" );
    else
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - The triangle is a convex polygon, well done !" );

    {
        const FloatingBox& b = poly.getEnclosingBox();
        lx::Log::log( "enclosing box {%d, %d, %d, %d}", b.p.x.v, b.p.y.v,
                      b.w, b.h );
    }

    // Now we have a polygon with 4 edges
    FloatPosition q{7.0f, 2.0f};
    lx::Log::log( "add point p(%d,%d)", q.x.v, q.y.v );
    poly.addPoint( q );

    // It must be convex
    lx::Log::log( "Test the convexity of the polygon with the new point." );
    if ( poly.isConvex() == false )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - Expected: convex; Got: non-convex" );
    else
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - Added (7,2). This is still a convex polygon, well done !" );

    // New edge
    FloatPosition r{6.0f, 5.0f};
    lx::Log::log( "add point p(%d,%d)", r.x.v, r.y.v );
    poly.addPoint( r );

    // It must be non-convex
    lx::Log::log( "Test the convexity of the polygon with the new point (again)." );
    if ( poly.isConvex() == true )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - Expected: non-convex; Got: convex" );
    else
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - Added (6,5). This is not a convex polygon" );

    {
        const FloatingBox& b = poly.getEnclosingBox();
        lx::Log::log( "enclosing box {%d, %d, %d, %d}", b.p.x.v, b.p.y.v,
                      b.w, b.h );
    }

    lx::Log::log( " = END TEST = " );
}


void testLine()
{
    lx::Log::log( "= TEST Vector2D =" );

    Vector2D v{0.0f, 4.0f};
    Vector2D u{0.0f, 42.0f};
    Vector2D w{21.0f, 0.0f};
    Line l1{FloatPosition{1.0f, 1.0f}, v};
    Line l2{FloatPosition{5.0f, 21.0f}, u};
    Line l3{FloatPosition{1.0f, 1.0f}, w};

    lx::Log::log( "line #1: (%d, %d) - (%f, %f)", l1.o.x, l1.o.y, l1.v.vx.v, l1.v.vy.v );
    lx::Log::log( "line #2: (%d, %d) - (%f, %f)", l2.o.x, l2.o.y, l2.v.vx.v, l2.v.vy.v );
    lx::Log::log( "line #3: (%d, %d) - (%f, %f)", l3.o.x, l3.o.y, l3.v.vx.v, l3.v.vy.v );

    if ( l1.isParralelWith( l2 ) )
        lx::Log::log( "SUCCESS - parralel: l1 and l2" );
    else
        lx::Log::log( "FAILURE - expected: parralel" );

    if ( !l1.isParralelWith( l3 ) )
        lx::Log::log( "SUCCESS - not parralel: l1 and l3" );
    else
        lx::Log::log( "FAILURE - expected: not parralel" );

    if ( l1.isPerpendicularTo( l3 ) )
        lx::Log::log( "SUCCESS - perpendicular: l1 and l3" );
    else
        lx::Log::log( "FAILURE - expected: perpendicular" );

    if ( !l1.isPerpendicularTo( l2 ) )
        lx::Log::log( "SUCCESS - not perpendicular: l1 and l2" );
    else
        lx::Log::log( "FAILURE - expected: not perpendicular" );

    if ( intersectLine( l1, l3 ) )
        lx::Log::log( "SUCCESS - intersection: l1 and l3" );
    else
        lx::Log::log( "FAILURE - expected: intersection" );

    if ( intersectLine( l2, l3 ) )
        lx::Log::log( "SUCCESS - intersection: l2 and l3" );
    else
        lx::Log::log( "FAILURE - expected: intersection" );

    lx::Log::log( "= END TEST =" );
}


void test_Vector2D( void )
{
    FloatPosition p{1.0f, 2.0f}, q{2.0f, -1.0f};

    Vector2D v{1.0f, 2.0f};
    Vector2D u{2.0f, -1.0f};
    Vector2D z{0.0f, 0.0f};
    Vector2D w{q.x - p.x, q.y - p.y};

    lx::Log::log( " = TEST Vector2D = " );
    lx::Log::log( "v(%f,%f)", v.vx.v, v.vy.v );
    lx::Log::log( "u(%f,%f)", u.vx.v, u.vy.v );
    lx::Log::log( "z(%f,%f)", z.vx.v, z.vy.v );
    lx::Log::log( "w(%f,%f)", w.vx.v, w.vy.v );
    lx::Log::log( "scalar product (v, u)" );
    Float d = scalar_product( v, u );

    if ( d != FNIL )
        lx::Log::log( "FAILURE - scalar product v(1,2).u(2,-1) expected: 0; Got: %f", d );
    else
        lx::Log::log( "SUCCESS - scalar product v(1,2).u(2,-1) = 0" );

    lx::Log::log( "scalar product (z,z)" );
    d = scalar_product( z, z );

    if ( d != FNIL )
        lx::Log::log( "FAILURE - scalar product z.z (z is a null vector) expected: 0; Got: %f", d );
    else
        lx::Log::log( "SUCCESS - scalar product z.z = 0" );

    lx::Log::log( "norm of z" );
    d = vector_norm( z );

    if ( d != FNIL )
        lx::Log::log( "FAILURE - norm of z (z is a null vector) expected: 0; Got: %f", d );
    else
        lx::Log::log( "SUCCESS - norm of z = 0" );


    lx::Log::log( "norm of v" );
    d = vector_norm( v );

    if ( static_cast<int>( d ) != static_cast<int>( sqrtf( 5 ) ) )
        lx::Log::log( "FAILURE - norm of v (z is a null vector) expected: %f; Got: %f",
                      sqrtf( 5 ), d );
    else
        lx::Log::log( "SUCCESS - norm of v = %f", d );


    lx::Log::log( "vector product (v,u)" );
    d = vector_product( v, u );

    if ( static_cast<int>( d ) != static_cast<int>( -5.0f ) )
        lx::Log::log( "FAILURE - vector product v(1,2).u(2,-1) expected: -5.0; Got: %f", d );
    else
        lx::Log::log( "SUCCESS - vector product v(1,2).u(2,-1) = %f", d );


    d = vector_product( u, v );

    if ( d != fbox( 5.0f ) )
        lx::Log::log( "FAILURE - vector product u(2,-1).v(1,2) expected: 5.0; Got: %f", d );
    else
        lx::Log::log( "SUCCESS - vector product u(2,-1).v(1,2) = %f", d );


    d = vector_product( z, z );

    if ( d != FNIL )
        lx::Log::log( "FAILURE - vector product z.z (z is a null vector) expected: 0; Got: %f", d );
    else
        lx::Log::log( "SUCCESS - vector product z.z = 0" );

    lx::Log::log( " = END TEST = " );
}


void test_collisionSeg( void )
{
    FloatPosition A{5.0f, 5.0f}, B{10.0f, 10.0f}, C{5.0f, 10.0f};
    FloatPosition D{10.0f, 5.0f}, E{20.0f, 5.0f}, F{15.0f, 5.0f};
    const Segment AB{A, B};
    const Segment AC{A, C};
    const Segment AD{A, D};
    const Segment AE{A, E};
    const Segment FE{F, E};
    const Segment BD{B, D};
    const Segment CD{C, D};

    lx::Log::log( " = TEST Collision Segment = " );
    lx::Log::log( "A(%d,%d)", A.x.v, A.y.v );
    lx::Log::log( "B(%d,%d)", B.x.v, B.y.v );
    lx::Log::log( "C(%d,%d)", C.x.v, C.y.v );
    lx::Log::log( "D(%d,%d)", D.x.v, D.y.v );
    lx::Log::log( "E(%d,%d)", E.x.v, E.y.v );
    lx::Log::log( "F(%d,%d)", F.x.v, F.y.v );
    lx::Log::log( "collision segement [AB]/[CD]" );

    bool d = intersectSegment( AB, CD );

    if ( d != true )
        lx::Log::log( "FAILURE - intersect [AB]/[CD] expected: TRUE; Got: FALSE" );
    else
        lx::Log::log( "SUCCESS - intersect [AB]/[CD] OK" );


    lx::Log::log( "collision segement [AC]/[BD]" );
    d = intersectSegment( AC, BD );

    if ( d != false )
        lx::Log::log( "FAILURE - intersect [AC]/[BD] expected: FALSE; Got: TRUE" );
    else
        lx::Log::log( "SUCCESS - no intersect [AC]/[BD] OK" );

    lx::Log::log( "collision segement [AB]/[AD]" );
    d = intersectSegment( AB, AD );

    if ( d != true )
        lx::Log::log( "FAILURE - intersect [AB]/[AD] expected: TRUE; Got: FALSE" );
    else
        lx::Log::log( "SUCCESS - intersect [AB]/[AD] OK" );

    lx::Log::log( "collision segement [AD]/[AE]" );
    d = intersectSegment( AD, AE );

    if ( d != true )
        lx::Log::log( "FAILURE - intersect [AD]/[AE] expected: TRUE; Got: FALSE" );
    else
        lx::Log::log( "SUCCESS - intersect [AD]/[AE] OK" );

    lx::Log::log( "collision segement [AD]/[FE]" );
    d = intersectSegment( AD, FE );

    if ( d != true )
        lx::Log::log( "FAILURE - intersect [AD]/[FE] expected: FALSE; Got: TRUE" );
    else
        lx::Log::log( "SUCCESS - no intersect [AD]/[FE] OK" );

    lx::Log::log( " = END TEST = " );
}


void test_collisionPointPolygon( void )
{
    /*
        Be careful, if the coordinates of a point
        are to high, you will have incorrect results
    */
    Polygon poly, polyc2;

    FloatPosition N{12.0f, 7.0f};
    FloatPosition O{9.0f, 7.0f};
    FloatPosition P{6.0f, 5.0f};
    FloatPosition Q{6.0f, 4.0f};
    FloatPosition R{1024.0f, 2048.0f};
    FloatPosition S{2.0f, 2.0f};
    FloatPosition T{10.0f, 5.0f};

    poly.addPoint( FloatPosition{10.0f, 5.0f} );
    poly.addPoint( FloatPosition{10.0f, 10.0f} );
    poly.addPoint( FloatPosition{5.0f, 5.0f} );
    poly.addPoint( FloatPosition{7.0f, 2.0f} );
    poly.addPoint( FloatPosition{66.0f, 5.0f} );

    polyc2.addPoint( FloatPosition{12.0f, 5.0f} );
    polyc2.addPoint( FloatPosition{12.0f, 12.0f} );
    polyc2.addPoint( FloatPosition{4.0f, 5.0f} );
    polyc2.addPoint( FloatPosition{7.0f, 0.0f} );

    lx::Log::log( " = TEST Collision Point/Polygon = " );
    displayPoly( poly );
    lx::Log::log( "N(%d,%d)", N.x.v, N.y.v );
    lx::Log::log( "O(%d,%d)", O.x.v, O.y.v );
    lx::Log::log( "P(%d,%d)", P.x.v, P.y.v );
    lx::Log::log( "Q(%d,%d)", Q.x.v, Q.y.v );
    lx::Log::log( "R(%d,%d)", R.x.v, R.y.v );
    lx::Log::log( "S(%d,%d)", S.x.v, S.y.v );
    lx::Log::log( "T(%d,%d)", T.x.v, T.y.v );

    lx::Log::log( "collision Point N/Polygon" );
    bool d = collisionPointPoly( N, poly );

    if ( d != false )
        lx::Log::log( "FAILURE - N in the polygon. expected: FALSE; Got: TRUE" );
    else
        lx::Log::log( "SUCCESS - N not in the polygon OK" );

    lx::Log::log( "collision Point O/Polygon" );
    d = collisionPointPoly( O, poly );

    if ( d != true )
        lx::Log::log( "FAILURE - O not in the polygon. expected: TRUE; Got: FALSE" );
    else
        lx::Log::log( "SUCCESS - O in the polygon OK" );

    lx::Log::log( "collision Point P/Polygon" );
    d = collisionPointPoly( P, poly );

    if ( d != true )
        lx::Log::log( "FAILURE - P not in the polygon. expected: TRUE; Got: FALSE" );
    else
        lx::Log::log( "SUCCESS - P in the polygon OK" );

    lx::Log::log( "collision Point Q/Polygon" );
    d = collisionPointPoly( Q, poly );

    if ( d != true )
        lx::Log::log( "FAILURE - Q not in the polygon. expected: TRUE; Got: FALSE" );
    else
        lx::Log::log( "SUCCESS - Q in the polygon OK" );

    lx::Log::log( "collision Point R/Polygon" );
    d = collisionPointPoly( R, poly );

    if ( d != false )
        lx::Log::log( "FAILURE - R in the polygon. expected: FALSE; Got: TRUE" );
    else
        lx::Log::log( "SUCCESS - R not in the polygon OK" );

    lx::Log::log( "collision Point S/Polygon" );
    d = collisionPointPoly( S, poly );

    if ( d != false )
        lx::Log::log( "FAILURE - S in the polygon. expected: FALSE; Got: TRUE" );
    else
        lx::Log::log( "SUCCESS - S not in the polygon OK" );

    lx::Log::log( "collision Point T/Polygon" );
    d = collisionPointPoly( T, polyc2 );

    if ( d != true )
        lx::Log::log( "FAILURE - T not in the polygon. expected: TRUE; Got: FALSE" );
    else
        lx::Log::log( "SUCCESS - T in the polygon OK" );

    lx::Log::log( " = END TEST = " );
}


void test_collisionCirclePolygon( void )
{
    Circle M{FloatPosition{12.0f, 7.0f}, 1};
    Circle N{FloatPosition{7.0f, 2.0f}, 2};
    Circle O{FloatPosition{9.0f, 7.0f}, 10};
    Circle S{FloatPosition{2.0f, 2.0f}, 2};
    Polygon poly;

    poly.addPoint( FloatPosition{10.0f, 5.0f} );
    poly.addPoint( FloatPosition{10.0f, 10.0f} );
    poly.addPoint( FloatPosition{5.0f, 5.0f} );
    poly.addPoint( FloatPosition{7.0f, 2.0f} );
    poly.addPoint( FloatPosition{6.0f, 5.0f} );

    lx::Log::log( " = TEST Collision Circle/Polygon = " );

    lx::Log::log( "M{(%d,%d),%d}", M.center.x, M.center.y, M.radius );
    lx::Log::log( "N{(%d,%d),%d}", N.center.x, N.center.y, N.radius );
    lx::Log::log( "O{(%d,%d),%d}", O.center.x, O.center.y, O.radius );
    lx::Log::log( "S{(%d,%d),%d}", S.center.x, S.center.y, S.radius );
    displayPoly( poly );

    lx::Log::log( "Collision Circle M/Polygon" );
    bool d = collisionCirclePoly( M, poly );

    if ( d != false )
        lx::Log::log( "FAILURE - Circle M in the polygon. expected: FALSE; Got: TRUE" );
    else
        lx::Log::log( "SUCCESS - Circle M not in the polygon OK" );

    lx::Log::log( "Collision Circle S/Polygon" );
    d = collisionCirclePoly( S, poly );

    if ( d != false )
        lx::Log::log( "FAILURE - Circle S in the polygon. expected: FALSE; Got: TRUE" );
    else
        lx::Log::log( "SUCCESS - Circle S not in the polygon OK" );

    lx::Log::log( "Collision Circle N/Polygon" );
    d = collisionCirclePoly( N, poly );

    if ( d != true )
        lx::Log::log( "FAILURE - Circle N not in the polygon. expected: TRUE; Got: FALSE" );
    else
        lx::Log::log( "SUCCESS - Circle N in the polygon OK" );

    lx::Log::log( "Collision Circle O/Polygon" );
    d = collisionCirclePoly( O, poly );

    if ( d != true )
        lx::Log::log( "FAILURE - Circle O not in the polygon. expected: TRUE; Got: FALSE" );
    else
        lx::Log::log( "SUCCESS - Circle O in the polygon OK" );

    lx::Log::log( " = END TEST = " );
}


void test_collisionBoxPolygon( void )
{
    const FloatingBox R1{FloatPosition{1.0f, 1.0f}, 2, 2};
    const FloatingBox R2{FloatPosition{8.0f, 3.0f}, 10, 4};
    const FloatingBox R3{FloatPosition{2.0f, 7.0f}, 20, 2};
    const FloatingBox R4{FloatPosition{8.0f, 6.0f}, 1, 1};
    const FloatingBox R5{FloatPosition{2.0f, 0.0f}, 16, 16};

    Polygon poly;

    poly.addPoint( FloatPosition{10.0f, 5.0f} );
    poly.addPoint( FloatPosition{10.0f, 10.0f} );
    poly.addPoint( FloatPosition{5.0f, 5.0f} );
    poly.addPoint( FloatPosition{7.0f, 2.0f} );
    poly.addPoint( FloatPosition{6.0f, 5.0f} );

    lx::Log::log( " = TEST Collision Box/Polygon = " );
    lx::Log::log( "R1{(%d,%d),%d,%d}", R1.p.x.v, R1.p.y.v, R1.w, R1.h );
    lx::Log::log( "R2{(%d,%d),%d,%d}", R2.p.x.v, R2.p.y.v, R2.w, R2.h );
    lx::Log::log( "R3{(%d,%d),%d,%d}", R3.p.x.v, R3.p.y.v, R3.w, R3.h );
    lx::Log::log( "R4{(%d,%d),%d,%d}", R4.p.x.v, R4.p.y.v, R4.w, R4.h );
    lx::Log::log( "poly" );
    displayPoly( poly );

    bool d = collisionBoxPoly( R1, poly );

    if ( d != false )
        lx::Log::log( "FAILURE - test R1 not in the polygon. expected: FALSE; Got: TRUE" );
    else
        lx::Log::log( "SUCCESS - R1 not in the polygon OK" );

    // A point of R2 in the polygon
    d = collisionBoxPoly( R2, poly );

    if ( d != true )
        lx::Log::log( "FAILURE - test R2 touch the polygon. expected: TRUE; Got: FALSE" );
    else
        lx::Log::log( "SUCCESS - R2 touch the polygon OK" );

    // Some Segments of R3 in the polygon (no point inside)
    d = collisionBoxPoly( R3, poly );

    if ( d != true )
        lx::Log::log( "FAILURE - test R3 touch the polygon. expected: TRUE; Got: FALSE" );
    else
        lx::Log::log( "SUCCESS - R3 touch the polygon OK" );

    // R4 into the polygon
    d = collisionBoxPoly( R4, poly );

    if ( d != true )
        lx::Log::log( "FAILURE - test R4 touch the polygon. expected: TRUE; Got: FALSE" );
    else
        lx::Log::log( "SUCCESS - R4 touch the polygon OK" );

    // The polygon into R5
    d = collisionBoxPoly( R5, poly );

    if ( d != true )
        lx::Log::log( "FAILURE - test polygon into R5. expected: TRUE; Got: FALSE" );
    else
        lx::Log::log( "SUCCESS - polygon into R5 OK" );

    lx::Log::log( " = END TEST = " );
}

void test_collision2Polygon( void )
{
    Polygon poly_empty1, poly_empty2;
    Polygon polyc, polyc2, polync, polync2;
    Polygon poly, poly2, poly3, poly4;

    // Convex polygon
    polyc.addPoint( FloatPosition{10.0f, 5.0f} );
    polyc.addPoint( FloatPosition{10.0f, 10.0f} );
    polyc.addPoint( FloatPosition{5.0f, 5.0f} );
    polyc.addPoint( FloatPosition{7.0f, 2.0f} );

    // Non-convex polygon
    polync.addPoint( FloatPosition{1000.0f, 500.0f} );
    polync.addPoint( FloatPosition{1000.0f, 1000.0f} );
    polync.addPoint( FloatPosition{500.0f, 500.0f} );
    polync.addPoint( FloatPosition{700.0f, 200.0f} );
    polync.addPoint( FloatPosition{600.0f, 500.0f} );

    // Non-convex polygon (again)
    polync2.addPoint( FloatPosition{10.0f, 5.0f} );
    polync2.addPoint( FloatPosition{10.0f, 10.0f} );
    polync2.addPoint( FloatPosition{5.0f, 5.0f} );
    polync2.addPoint( FloatPosition{7.0f, 2.0f} );
    polync2.addPoint( FloatPosition{6.0f, 5.0f} );

    polyc2.addPoint( FloatPosition{12.0f, 5.0f} );
    polyc2.addPoint( FloatPosition{12.0f, 12.0f} );
    polyc2.addPoint( FloatPosition{4.0f, 5.0f} );
    polyc2.addPoint( FloatPosition{7.0f, 0.0f} );

    poly.addPoint( FloatPosition{10.0f, 5.0f} );
    poly.addPoint( FloatPosition{10.0f, 10.0f} );
    poly.addPoint( FloatPosition{5.0f, 5.0f} );
    poly.addPoint( FloatPosition{7.0f, 2.0f} );
    poly.addPoint( FloatPosition{6.0f, 5.0f} );

    poly2.addPoint( FloatPosition{9.0f, 6.0f} );
    poly2.addPoint( FloatPosition{9.0f, 9.0f} );
    poly2.addPoint( FloatPosition{6.0f, 4.0f} );
    poly2.addPoint( FloatPosition{6.0f, 3.0f} );
    poly2.addPoint( FloatPosition{5.0f, 6.0f} );

    poly3.addPoint( FloatPosition{0.0f, 0.0f} );
    poly3.addPoint( FloatPosition{32.0f, 32.0f} );
    poly3.addPoint( FloatPosition{0.0f, 32.0f} );

    poly4.addPoint( FloatPosition{2.0f, 2.0f} );
    poly4.addPoint( FloatPosition{2.0f, 3.0f} );
    poly4.addPoint( FloatPosition{3.0f, 4.0f} );

    lx::Log::log( " = TEST Collision Polygon/Polygon = " );

    lx::Log::log( "poly" );
    displayPoly( poly );
    lx::Log::log( "poly2" );
    displayPoly( poly2 );
    lx::Log::log( "poly3" );
    displayPoly( poly3 );
    lx::Log::log( "poly4" );
    displayPoly( poly4 );
    lx::Log::log( "polyc" );
    displayPoly( polyc );
    lx::Log::log( "polyc2" );
    displayPoly( polyc2 );
    lx::Log::log( "polync" );
    displayPoly( polync );
    lx::Log::log( "polync2" );
    displayPoly( polync2 );

    bool d = collisionPoly( poly, poly2 );

    if ( d != true )
        lx::Log::log( "FAILURE - no collision poly/poly2. expected: TRUE; Got: FALSE" );
    else
        lx::Log::log( "SUCCESS - collision poly/poly2" );


    d = collisionPoly( poly, poly3 );

    if ( d != true )
        lx::Log::log( "FAILURE - no collision poly/poly3. expected: TRUE; Got: FALSE" );
    else
        lx::Log::log( "SUCCESS - collision poly/poly3" );


    d = collisionPoly( poly, poly4 );

    if ( d != false )
        lx::Log::log( "FAILURE - no collision poly/poly4. expected: TRUE; Got: FALSE" );
    else
        lx::Log::log( "SUCCESS - collision poly/poly4" );

    // Empty polygons
    lx::Log::log( "collision between two empty polygons" );
    try
    {
        collisionPoly( poly_empty1, poly_empty2 );
        lx::Log::log( "FAILURE - this collision cannot be calculated" );
    }
    catch ( std::invalid_argument& )
    {
        lx::Log::log( "SUCCESS - std::invalid_argument exception occured" );
    }
    catch ( ... )
    {
        lx::Log::log( "FAILURE - unknown exception occurred" );
    }

    lx::Log::log( "collision between two convex polygons" );
    d = collisionPoly( polyc, polyc2 );

    if ( d != true )
        lx::Log::log( "FAILURE - no collision polyc/polyc2. expected: TRUE; Got: FALSE" );
    else
        lx::Log::log( "SUCCESS - collision polyc/polyc2" );

    // convex/non-convex
    lx::Log::log( "collision between a convex polygon and a non-convex polygon" );
    d = collisionPoly( polyc2, polync );

    if ( d == true )
        lx::Log::log( "FAILURE - collision polyc2/polycnc. expected: FALSE; Got: TRUE" );
    else
        lx::Log::log( "SUCCESS - no collision polyc2/polync" );

    // Another test
    lx::Log::log( "collision between a convex polygon and a non-convex polygon (again)" );
    d = collisionPoly( polyc2, polync2 );

    if ( d != true )
        lx::Log::log( "FAILURE - no collision polyc2/polync2. expected: TRUE; Got: FALSE" );
    else
        lx::Log::log( "SUCCESS - collision polyc2/polync2" );

    // convex/triangle (that is convex)
    lx::Log::log( "collision between a convex polygon and a triangle" );
    d = collisionPoly( polyc2, poly3 );

    if ( d != true )
        lx::Log::log( "FAILURE - no collision polyc2/poly3. expected: TRUE; Got: FALSE" );
    else
        lx::Log::log( "SUCCESS - collision polyc2/poly3" );

    lx::Log::log( " = END TEST = " );
}

void test_collision2PolygonAgain( void )
{
#define FP(x) lx::Random::fxrand() * x

    const float N = 100000.0f;
    const float M = 1000.0f;
    Polygon poly1, poly2;
    Polygon poly3, poly4;
    unsigned int t1, t2;

    lx::Log::log( " = TEST Collision BIG Polygon/Polygon = " );
    lx::Random::initRand();

    lx::Log::log( "Generate two random polygons with %d sides", N );
    for ( unsigned long i = 0L; i < N; ++i )
    {
        poly1.addPoint( FloatPosition{FP( M ), FP( M )} );
        poly2.addPoint( FloatPosition{FP( M ), FP( M )} );
    }

    lx::Log::log( "Calculate the collision #1" );
    t1 = SDL_GetTicks();
    bool d = collisionPoly( poly1, poly2 );
    t2 = SDL_GetTicks();
    lx::Log::log( "Result:%s collision between the two random polygons", ( d ? "" : " No" ) );
    lx::Log::log( "Calculation done in %d ms", t2 - t1 );

    lx::Log::log( "Generate two other random polygons with %d sides in two different areas", N );
    for ( unsigned long i = 0; i < N; ++i )
    {
        poly3.addPoint( FloatPosition{FP( M ), FP( M )} );
        poly4.addPoint( FloatPosition{FP( M + N ), FP( M + N )} );
    }

    lx::Log::log( "Calculate the collision #2" );
    t1 = SDL_GetTicks();
    d = collisionPoly( poly3, poly4 );
    t2 = SDL_GetTicks();
    lx::Log::log( "t1: %d; t2: %d", t1, t2 );
    lx::Log::log( "Result:%s collision between the two random polygons", ( d ? "" : " No" ) );
    lx::Log::log( "Calculation done in %d ms", t2 - t1 );

    lx::Log::log( " = END TEST = " );
}


void test_move( void )
{
    FloatPosition P{{1.0f}, {2.0f}};
    FloatingBox R{FloatPosition{8.f, 4.0f}, 10, 10};

    const float X = { -4.0f};
    const float Y = {8.0f};

    Polygon poly;
    Polygon expoly;

    poly.addPoint( FloatPosition{24.0f, 32.0f} );
    poly.addPoint( FloatPosition{48.0f, 32.0f} );
    poly.addPoint( FloatPosition{128.0f, 64.0f} );
    poly.addPoint( FloatPosition{64.0f, 64.0f} );
    poly.addPoint( FloatPosition{32.0f, 32.0f} );
    // expected polygon
    expoly.addPoint( FloatPosition{24.0f + X, 32.0f + Y} );
    expoly.addPoint( FloatPosition{48.0f + X, 32.0f + Y} );
    expoly.addPoint( FloatPosition{128.0f + X, 64.0f + Y} );
    expoly.addPoint( FloatPosition{64.0f + X, 64.0f + Y} );
    expoly.addPoint( FloatPosition{32.0f + X, 32.0f + Y} );

    lx::Log::log( " = TEST Move = " );

    lx::Log::log( "P(%d,%d)", P.x.v, P.y.v );
    lx::Log::log( "R{(%d,%d),%d,%d}", R.p.x.v, R.p.y.v, R.w, R.h );
    lx::Log::log( "poly" );
    displayPoly( poly );
    lx::Log::log( "expoly" );
    displayPoly( expoly );

    lx::Log::log( "Point" );

    FloatPosition expected_point{P.x.v + 1.0f, P.y.v + 1.0f};
    movePoint( P, Vector2D{{1.0f}, {1.0f}} );

    if ( P.x == expected_point.x && P.y == expected_point.y )
        lx::Log::log( "Point P(%d,%d)", P.x.v, P.y.v );
    else
        lx::Log::log( "FAILURE - expected : Point P(2,3); Got: P(%d,%d)", P.x.v, P.y.v );

    lx::Log::log( "Rectangle" );

    const FloatingBox expected_aabb{R.p.x + 2, R.p.y + 3, R.w, R.h};
    moveBox( R, Vector2D{{2.0f}, {3.0f}} );

    if ( R.p == expected_aabb.p )
        lx::Log::log( "SUCCESS - Rectangle R{(%d,%d),%d,%d}", R.p.x.v, R.p.y.v, R.w, R.h );
    else
        lx::Log::log( "FAILURE - expected : Rectangle R(3,6,10,10); got: R{(%d,%d),%d,%d}",
                      R.p.x.v, R.p.y.v, R.w, R.h );

    movePoly( poly, Vector2D{X, Y} );
    const unsigned long n = poly.numberOfEdges();
    const unsigned long m = expoly.numberOfEdges();

    lx::Log::log( "expected polygon" );
    displayPoly( expoly );
    lx::Log::log( "got" );
    displayPoly( poly );

    if ( n != m )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - ≠ degree. #edges expected: %d, got: %d", m, n );
    else
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - these polygons have the same degree" );

    try
    {
        bool ok = true;
        for ( unsigned long j = 0; j < n; j++ )
        {
            FloatPosition p1 = poly.getPoint( j );
            FloatPosition p2 = expoly.getPoint( j );
            if ( p1 != p2 )
            {
                lx::Log::logInfo( lx::Log::TEST,
                                  "FAILURE - at j = %d → ≠ point; expected: (%d,%d); got: (%d,%d)",
                                  j, p2.x.v, p2.y.v, p1.x.v, p1.y.v );
                ok = false;
                break;
            }
        }

        if ( ok )
            lx::Log::logInfo( lx::Log::TEST, "SUCCESS - The 2 polygons are identical" );
    }
    catch ( ... )
    {
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - uncaught exception at %s:%d", __FILE__, __LINE__ );
    }

    // reset
    movePoly( poly, Vector2D{ -X, -Y} );
    const FloatingBox& box = expoly.getEnclosingBox();
    const FloatPosition q{box.p.x + box.w / 2.0f, box.p.y + box.h / 2.0f};

    movePolyTo( poly, q );
    const FloatingBox& b = poly.getEnclosingBox();
    FloatPosition s{b.p.x + b.w / 2.0f, b.p.y + b.h / 2.0f};
    lx::Log::log( "centroid of poly: s(%d,%d)", s.x.v, s.y.v );
    lx::Log::log( "centroid of expoly: q(%d,%d)", q.x.v, q.y.v );

    lx::Log::log( " = END TEST = " );
}


void test_assignment( void )
{
    lx::Log::log( " = TEST Assignement = " );

    FloatPosition P{1.0f, 2.0f};
    FloatPosition Q = P;

    lx::Log::log( "P(%d,%d)", P.x.v, P.y.v );

    if ( Q == P )
        lx::Log::log( "SUCCESS - Point Q(%d,%d)", Q.x.v, Q.y.v );
    else
        lx::Log::log( "FAILURE - expected: Q(1,2); Got: Q(%d,%d)", Q.x.v, Q.y.v );

    Circle C{FloatPosition{4.0f, 9.0f}, 10};

    lx::Log::log( "C{(%d,%d),%d}", C.center.x.v, C.center.y.v, C.radius );

    Circle D = C;  // assignment

    if ( D == C )
        lx::Log::log( "SUCCESS - Circle D{(%d,%d),%d}", D.center.x.v,
                      D.center.y.v, D.radius );
    else
        lx::Log::log( "FAILURE - expected: Circle D{{4,9},10}; Got: D{(%d,%d),%d}",
                      D.center.x.v, D.center.y.v, D.radius );

    Vector2D v{3.14f, 1.59f};
    lx::Log::log( "Vector2D v(%f,%f)", v.vx.v, v.vy.v );

    Vector2D u = v;  // assignment

    if ( u == v )
        lx::Log::log( "SUCCESS - Vector2D v(%f,%f)", u.vx.v, u.vy.v );
    else
        lx::Log::log( "FAILURE - expected: u(3.14,1.59); Got: u(%f,%f)", u.vx.v, u.vy.v );

    Vector2D t{0.0f, 0.0f}, w{0.0f, 0.0f};

    if ( t == w )
        lx::Log::log( "SUCCESS - Vector2D t(%f,%f)", t.vx.v, t.vy.v );
    else
        lx::Log::log( "FAILURE - expected: w(0.0f,0.0f); Got: u(%f,%f)", w.vx.v, w.vy.v );

    lx::Log::log( " = END TEST = " );
}


void test_operator( void )
{
    Circle C{FloatPosition{2.0f, 3.0f}, 10};
    Circle E{FloatPosition{4.0f, 9.0f}, 32};
    Circle F{FloatPosition{8.0f, 21.0f}, 10};

    Vector2D v{ -3.14f, 1.59f};
    Vector2D u = v;
    Vector2D w{3.140001f, 1.590001f};
    Vector2D i{2.56f, 1.59f};
    Vector2D j{ -0.14f, -1.28f};

    lx::Log::log( " = TEST operators = " );

    lx::Log::log( "Vector2D v(%f,%f)", v.vx.v, v.vy.v );
    lx::Log::log( "C{(%d,%d),%d};", C.center.x, C.center.y, C.radius );
    lx::Log::log( "E{(%d,%d),%d};", E.center.x, E.center.y, E.radius );
    lx::Log::log( "F{(%d,%d),%d};", F.center.x, F.center.y, F.radius );
    lx::Log::log( "Vector2D u(%f,%f)", u.vx.v, u.vy.v );
    lx::Log::log( "Vector2D v(%f,%f)", v.vx.v, v.vy.v );
    lx::Log::log( "Vector2D w(%f,%f)", w.vx.v, w.vy.v );
    lx::Log::log( "Vector2D i(%f,%f)", i.vx.v, i.vy.v );
    lx::Log::log( "Vector2D j(%f,%f)", j.vx.v, j.vy.v );

    if ( E > C )
        lx::Log::log( "SUCCESS - E > C" );
    else
        lx::Log::log( "FAILURE - E ≤ C" );

    if ( C < E )
        lx::Log::log( "SUCCESS - C < E" );
    else
        lx::Log::log( "FAILURE - C ≥ E" );

    if ( E >= C )
        lx::Log::log( "SUCCESS - E ≥ C" );
    else
        lx::Log::log( "FAILURE - E < C" );

    if ( C <= E )
        lx::Log::log( "SUCCESS - C ≤ E" );
    else
        lx::Log::log( "FAILURE - C > E" );

    if ( F >= C )
        lx::Log::log( "SUCCESS - F ≥ C" );
    else
        lx::Log::log( "FAILURE - F < C" );

    if ( C <= F )
        lx::Log::log( "SUCCESS - C ≤ F" );
    else
        lx::Log::log( "FAILURE - C > F" );

    if ( !( E < C ) )
        lx::Log::log( "SUCCESS - !(E < C)" );
    else
        lx::Log::log( "FAILURE - E < C" );

    lx::Log::log( "E ≠ C ?" );
    if ( E != C )
        lx::Log::log( "SUCCESS - E ≠ C" );
    else
        lx::Log::log( "FAILURE - E == C" );

    lx::Log::log( " !(E == C) ?" );
    if ( !( E == C ) )
        lx::Log::log( "SUCCESS - !(E == C)" );
    else
        lx::Log::log( "FAILURE - E == C" );

    if ( u == v )
        lx::Log::log( "SUCCESS - u == v" );
    else
        lx::Log::log( "FAILURE - expected: u == v; Got: u(%f,%f) ≠ v(%f,%f)",
                      u.vx.v, u.vy.v, v.vx.v, v.vy.v );

    if ( v == w )
        lx::Log::log( "FAILURE - expected: v ≠ w; Got: v(%f,%f) ≠ w(%f,%f)",
                      v.vx.v, v.vy.v, w.vx.v, w.vy.v );
    else
        lx::Log::log( "SUCCESS - v ≠ w" );

    if ( v != i )
        lx::Log::log( "SUCCESS - v ≠ i" );
    else
        lx::Log::log( "FAILURE - expected: v ≠ i; Got: v(%f,%f) ≠ i(%f,%f)",
                      v.vx.v, v.vy.v, i.vx.v, i.vy.v );

    if ( j != i )
        lx::Log::log( "SUCCESS - j ≠ i" );
    else
        lx::Log::log( "FAILURE - expected: j ≠ i; Got: j(%f,%f) ≠ i(%f,%f)",
                      j.vx.v, j.vy.v, i.vx.v, i.vy.v );

    lx::Log::log( " = END TEST = " );
}


void test_VectorPlusMinusOp( void )
{
    Vector2D u{3.14f, 1.59f};
    Vector2D v{ -1.28f, 5.12f};
    Vector2D z{ -2.56f, 10.24f};

    Vector2D a{3.14f, 2.048f};
    Vector2D b{1.28f, 0.64f};
    Vector2D c{ -2.56f, 10.24f};

    Vector2D exp_sum_vec = {u.vx + v.vx, u.vy + v.vy};
    Vector2D exp_add_vec = {u.vx + z.vx, u.vy + z.vy};

    Vector2D exp_diff_vec = {a.vx - b.vx, a.vy - b.vy};
    Vector2D exp_sub_vec = {a.vx - c.vx, a.vy - c.vy};

    lx::Log::log( " = TEST Vector arithmetic = " );
    lx::Log::log( " '+','+=','-','-='" );

    lx::Log::log( "Vector2D u(%f,%f)", u.vx.v, u.vy.v );
    lx::Log::log( "Vector2D v(%f,%f)", v.vx.v, v.vy.v );
    lx::Log::log( "w = u + v;" );

    Vector2D w = u + v;
    lx::Log::log( "Vector2D w(%f,%f)", w.vx.v, w.vy.v );

    if ( w == exp_sum_vec )
        lx::Log::log( "SUCCESS - w(%f,%f) as expected", w.vx.v, w.vy.v );
    else
        lx::Log::log( "FAILURE - expected: Vector2D(%f,%f) Got: w(%f,%f)",
                      exp_sum_vec.vx.v, exp_sum_vec.vy.v, w.vx.v, w.vy.v );

    lx::Log::log( "Vector2D u(%f,%f)", u.vx.v, u.vy.v );
    lx::Log::log( "Vector2D v(%f,%f)", v.vx.v, v.vy.v );
    lx::Log::log( "u += z;" );

    u += z;

    lx::Log::log( "Vector2D u(%f,%f)", u.vx.v, u.vy.v );

    if ( u == exp_add_vec )
        lx::Log::log( "SUCCESS - u(%f,%f) as expected", u.vx.v, u.vy.v );
    else
        lx::Log::log( "FAILURE - expected: Vector2D(%f,%f) Got: u(%f,%f)",
                      exp_add_vec.vx.v, exp_add_vec.vy.v, u.vx.v, u.vy.v );

    lx::Log::log( "Vector2D a(%f,%f)", a.vx.v, a.vy.v );
    lx::Log::log( "Vector2D b(%f,%f)", b.vx.v, b.vy.v );
    lx::Log::log( "d = a - b;" );

    Vector2D d = a - b;

    lx::Log::log( "Vector2D d(%f,%f)", d.vx.v, d.vy.v );

    if ( d == exp_diff_vec )
        lx::Log::log( "SUCCESS - d(%f,%f) as expected", d.vx.v, d.vy.v );
    else
        lx::Log::log( "FAILURE - expected: Vector2D(%f,%f) Got: d(%f,%f)",
                      exp_diff_vec.vx.v, exp_diff_vec.vy.v, d.vx.v, d.vy.v );

    lx::Log::log( "Vector2D a(%f,%f)", a.vx.v, a.vy.v );
    lx::Log::log( "Vector2D b(%f,%f)", b.vx.v, b.vy.v );
    lx::Log::log( "a -= c;" );

    a -= c;

    if ( a == exp_sub_vec )
        lx::Log::log( "SUCCESS - a(%f,%f) as expected", a.vx.v, a.vy.v );
    else
        lx::Log::log( "FAILURE - expected: Vector2D(%f,%f) Got: a(%f,%f)",
                      exp_sub_vec.vx.v, exp_sub_vec.vy.v, a.vx.v, a.vy.v );

    lx::Log::log( " = END TEST = " );
}


void test_VectorOpposite( void )
{
    lx::Log::log( " = TEST Vector Opposite = " );

    Vector2D u = {3.14f, -2.56f};
    Vector2D expected_vec = { -u.vx.v, -u.vy};

    lx::Log::log( "Vector2D u(%f,%f)", u.vx.v, u.vy.v );
    lx::Log::log( "-u;" );

    if ( expected_vec == ( -u ) )
        lx::Log::log( "SUCCESS - u(%f,%f) as expected", ( -u ).vx.v, ( -u ).vy.v );
    else
        lx::Log::log( "FAILURE - expected: Vector2D(%f,%f) Got: u(%f,%f)",
                      expected_vec.vx.v, expected_vec.vy.v, ( -u ).vx.v, ( -u ).vy.v );

    lx::Log::log( " = END TEST = " );
}


void test_VectorIncDec( void )
{
    lx::Log::log( " = TEST Vector Increment and decrement = " );

    Vector2D u{1.41f, -5.92f};
    Vector2D v = u;
    Vector2D exp_inc_pre_vec{u.vx + 1.0f, u.vy + 1.0f};
    Vector2D exp_inc_post_vec{u.vx + 1.0f, u.vy + 1.0f};
    Vector2D exp_dec_pre_vec{u.vx - 1.0f, u.vy - 1.0f};
    Vector2D exp_dec_post_vec{u.vx - 1.0f, u.vy - 1.0f};

    lx::Log::log( "Increment" );
    lx::Log::log( "Vector2D u(%f,%f)", u.vx.v, u.vy.v );
    lx::Log::log( "++u;" );

    ++u;

    if ( u == exp_inc_pre_vec )
        lx::Log::log( "SUCCESS - u(%f,%f) as expected", u.vx.v, u.vy.v );
    else
        lx::Log::log( "FAILURE - expected: Vector2D(%f,%f) Got: u(%f,%f)",
                      exp_inc_pre_vec.vx.v, exp_inc_pre_vec.vy.v, u.vx.v, u.vy.v );

    lx::Log::log( "Vector2D v(%f,%f)", v.vx.v, v.vy.v );
    lx::Log::log( "v++;" );

    v++;

    if ( v == exp_inc_post_vec )
        lx::Log::log( "SUCCESS - v(%f,%f) as expected", v.vx.v, v.vy.v );
    else
        lx::Log::log( "FAILURE - expected: Vector2D(%f,%f) Got: v(%f,%f)",
                      exp_inc_post_vec.vx.v, exp_inc_post_vec.vy.v, v.vx.v, v.vy.v );

    u = {1.41f, -5.92f};
    v = u;

    lx::Log::log( "Decrement" );
    lx::Log::log( "Vector2D u(%f,%f)", u.vx.v, u.vy.v );
    lx::Log::log( "--u;" );

    --u;

    if ( u == exp_dec_pre_vec )
        lx::Log::log( "SUCCESS - u(%f,%f) as expected", u.vx.v, u.vy.v );
    else
        lx::Log::log( "FAILURE - expected: Vector2D(%f,%f) Got: u(%f,%f)",
                      exp_dec_pre_vec.vx.v, exp_dec_pre_vec.vy.v, u.vx.v, u.vy.v );

    lx::Log::log( "Vector2D v(%f,%f)", v.vx.v, v.vy.v );
    lx::Log::log( "v--;" );

    v--;

    if ( v == exp_dec_post_vec )
        lx::Log::log( "SUCCESS - v(%f,%f) as expected", v.vx.v, v.vy.v );
    else
        lx::Log::log( "FAILURE - expected: Vector2D(%f,%f) Got: v(%f,%f)",
                      exp_dec_post_vec.vx.v, exp_dec_post_vec.vy.v, v.vx.v, v.vy.v );

    lx::Log::log( " = END TEST = " );
}


void test_VectorCollinear( void )
{
    lx::Log::log( " = TEST Vector collinearity = " );

    Vector2D u = {1.41f, -2.48f};
    Vector2D v = {u.vx * 2.0f, u.vy * 2.0f};
    Vector2D w = u;
    Vector2D o = {0.0f, 0.0f};
    Vector2D t = {2.01f, 4.12f};

    lx::Log::log( "Vector2D u(%f,%f)", u.vx.v, u.vy.v );
    lx::Log::log( "Vector2D v(%f,%f)", v.vx.v, v.vy.v );
    lx::Log::log( "Vector2D w(%f,%f)", w.vx.v, w.vy.v );
    lx::Log::log( "Vector2D o(%f,%f)", o.vx.v, o.vy.v );
    lx::Log::log( "Vector2D t(%f,%f)", t.vx.v, t.vy.v );

    lx::Log::log( "test: zero vector" );

    if ( isNullVector( o ) )
        lx::Log::log( "SUCCESS - o is a zero vector: o(%f,%f)", o.vx.v, o.vy.v );
    else
        lx::Log::log( "FAILURE - o is not a zero vector: o(%f,%f)", o.vx.v, o.vy.v );

    if ( !isNullVector( t ) )
        lx::Log::log( "SUCCESS - t is not a zero vector: t(%f,%f)", t.vx.v, t.vy.v );
    else
        lx::Log::log( "FAILURE - t is a zero vector: t(%f,%f)", t.vx.v, t.vy.v );

    lx::Log::log( "test: collinearity between u and v" );

    if ( collinear( u, v ) )
        lx::Log::log( "SUCCESS - u and v are colinear" );
    else
        lx::Log::log( "FAILURE - expected: u and v must be colinear; Got: u(%f,%f) and v(%f,%f)",
                      u.vx.v, u.vy.v, v.vx.v, v.vy.v );


    lx::Log::log( "test: collinearity between u and w" );

    if ( collinear( u, w ) )
        lx::Log::log( "SUCCESS - u and w are colinear" );
    else
        lx::Log::log( "FAILURE - expected: u and w must be colinear; Got: u(%f,%f) and w(%f,%f)",
                      u.vx.v, u.vy.v, w.vx.v, w.vy.v );

    lx::Log::log( "test: collinearity between u and o" );

    if ( collinear( u, o ) )
        lx::Log::log( "SUCCESS - u and o are colinear" );
    else
        lx::Log::log( "FAILURE - expected: u and o must be colinear; Got: u(%f,%f) and o(%f,%f)",
                      u.vx.v, u.vy.v, o.vx.v, o.vy.v );

    lx::Log::log( "test: collinearity between u and t" );

    if ( !collinear( u, t ) )
        lx::Log::log( "SUCCESS - u and t are colinear" );
    else
        lx::Log::log( "FAILURE - expected: u and t must be colinear; Got: u(%f,%f) and t(%f,%f)",
                      u.vx.v, u.vy.v, t.vx.v, t.vy.v );

    lx::Log::log( " = END TEST = " );
}


void test_VectorLambda( void )
{
    lx::Log::log( " = TEST Vector, scalar multiplication = " );

    float lambda1 = 2.0f;
    float lambda2 = 0.0f;
    Vector2D v{3.14f, 1.59f};
    Vector2D w{v.vx * lambda1, v.vy * lambda1};
    Vector2D t{0.0f, 0.0f};

    lx::Log::log( "Vector2D v(%f,%f)", v.vx.v, v.vy.v );

    v = v * lambda1;

    if ( v == w )
        lx::Log::log( "SUCCESS - Vector2D v(%f,%f)", v.vx.v, v.vy.v );
    else
        lx::Log::log( "FAILURE - expected: v(%f,%f); Got: v(%f,%f)", w.vx.v, w.vy.v,
                      v.vx.v, v.vy.v );

    v = v * lambda2;

    if ( v == t )
        lx::Log::log( "SUCCESS - Vector2D v(%f,%f)", v.vx.v, v.vy.v );
    else
        lx::Log::log( "FAILURE - expected: v(%f,%f); Got: v(%f,%f)", t.vx.v, t.vy.v,
                      v.vx.v, v.vy.v );

    // Test normalization
    lx::Log::log( "Reset v" );

    v = {3.0f, 0.0f};
    lx::Log::log( "Vector2D v(%f,%f)", v.vx.v, v.vy.v );
    lx::Log::log( "Normalize v" );

    normalize( v );
    Float n = vector_norm( v );

    if ( n == fbox( 1.0f ) )
        lx::Log::log( "SUCCESS - Vector2D v(%f,%f) normalized, norm: %f", v.vx.v, v.vy.v, n );
    else
        lx::Log::log( "FAILURE - expected: v(%f,%f); Got: v(%f,%f)", t.vx.v, t.vy.v,
                      v.vx.v, v.vy.v );

    lx::Log::logWarning( lx::Log::TEST, "The previous test may fail with some complex float values in the vector" );
    lx::Log::logWarning( lx::Log::TEST, "Try it with V(3.14,2.56)" );

    lx::Log::log( "Vector2D t(%f,%f)", t.vx.v, t.vy.v );
    lx::Log::log( "Normalize t" );

    normalize( t ); // t is a null vector

    if ( t == t )
        lx::Log::log( "SUCCESS - Vector2D t(%f,%f) normalized, norm: %f", v.vx.v, v.vy.v, n );
    else
        lx::Log::log( "FAILURE - a zero vector must be normalized to 0" );

    lx::Log::log( " = END TEST = " );
}

#define i32(x) static_cast<int>(x)

void test_conversion( void )
{
    lx::Log::log( " = TEST conversion = " );

    FloatPosition fp1{0.0f, 0.0f};
    FloatPosition fp2{64.0f, 128.0f};
    lx::Graphics::ImgCoord exp1{i32( fp1.x.v ), i32( fp1.y.v )};
    lx::Graphics::ImgCoord exp2{i32( fp2.x.v ), i32( fp2.y.v )};

    lx::Graphics::ImgCoord p1 = lx::Graphics::toPixelPosition( fp1 );
    lx::Graphics::ImgCoord p2 = lx::Graphics::toPixelPosition( fp2 );

    if ( p1 == exp1 )
        lx::Log::log( "SUCCESS - p1(%d, %d)", p1.x, p1.y );
    else
        lx::Log::log( "FAILURE - p1" );

    if ( p2 == exp2 )
        lx::Log::log( "SUCCESS - p2(%d, %d)", p2.x, p2.y );
    else
        lx::Log::log( "FAILURE - p2" );

    lx::Log::log( " = END TEST = " );
}

void displayPoly( Polygon& poly )
{
    ostringstream os;
    os << "{";
    const unsigned long n = poly.numberOfEdges();
    for ( unsigned long i = 0; i < n; ++i )
    {
        os << "(" << ( poly.getPoint( i ) ).x << ","
           << ( poly.getPoint( i ) ).y << ")";
        if ( i != n )
            os << ";";
    }
    os << "}";
    lx::Log::log( "%s", os.str().c_str() );
}
