


#include <iostream>

#include "../src/engine/Lunatix_engine.hpp"

using namespace std;
using namespace LX_Physics;


void test_euclide(void);
void test_boxes(void);
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


    LX_Quit();

    cout << " ==== END Physics ==== " << endl;

    return EXIT_SUCCESS;
}



void test_euclide(void)
{

    LX_Point A = {1,1};
    LX_Point B = {10,1};

    LX_Point C = {1,1};
    LX_Point D = {10,10};

    int d;

    d = euclide_square_distance(&A,&B);

    if(d != 81)
        cerr << "FAILURE - Bad square distance AB - expected : 81; got : " << d << endl;
    else
        cout << "SUCCESS - Good square distance AB : " << d << endl;

    d = euclide_distance(&A,&B);

    if(d != 9)
        cerr << "FAILURE - Bad distance of AB - expected : 9; got : " << d << endl;
    else
        cout << "SUCCESS - Good distance of AB : " << d << endl;


}




















