

#include <cmath>

#include <iostream>

#include "../src/engine/Lunatix_engine.hpp"

using namespace std;
using namespace LX_Physics;


void test_euclide(void);
void test_collisionPointCircle(void);
void test_collisionPointRect(void);
void test_collision2Circle(void);
void test_collision2Rect(void);
void test_collisionRectCircle(void);


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














