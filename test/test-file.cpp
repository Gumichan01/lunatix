


#include <iostream>
#include <cstdio>
#include <cstring>

#include "../src/engine/Lunatix_engine.hpp"


#define N 4

using namespace std;
using namespace LX_FileIO;


void test_open(void);
void test_read(void);
void test_write(void);
void test_tell(void);

string str = "tmpFile";

int main(int argc, char **argv)
{
    bool err = false;

    cout << " ==== Test File ==== " << endl;

    err = LX_Init();

    if(!err)
        cerr << "FAILURE - Init does not work" << endl;
    else
        cout << "SUCCESS - LunatiX Engine have been initialized with success" << endl;


    test_open();
    test_write();
    test_read();

    //remove(str.c_str());

    cout << " ==== End File ==== " << endl;
}



void test_open(void)
{
    LX_File *f1 = NULL;
    LX_File *invalidString = NULL;
    LX_File *notExistFile = NULL;

    string str1 = "data/explosion.png";
    char * null = NULL;
    string str3 = "invalid_file";

    cout << " = TEST open = " << endl;


    // valid file
    try{

        f1 = new LX_File(str1.c_str(),LX_FILEIO_RDONLY);

        cout << "SUCCESS - The following file was loaded : " << str1 << endl;

        f1->close();

        delete f1;
        f1 = NULL;

    }catch(IOException &e)
    {
        cerr << "FAILURE - Cannot load " << str1 << "; Expected : a valid refence; Got : " << e.what() << endl;
    }

    // null string
    try{

        invalidString = new LX_File(null,LX_FILEIO_RDONLY);

        cerr << "FAILURE - NULL was loaded (o_o); Expected : IOexception; got : a valid reference " << endl;

    }catch(IOException &ex)
    {
        cout << "SUCCESS - Exception occured : " << ex.what() << endl;
    }

    // bad mode
    try{

        f1 = new LX_File(str1.c_str(),0x00000000);

        cerr << "FAILURE - mode was not set (o_o); Expected : IOexception; got : a valid reference " << endl;

    }catch(IOException &exe)
    {
        cout << "SUCCESS - Exception occured : " << exe.what() << endl;
    }

    // invalid file
    try{

        notExistFile = new LX_File(str3.c_str(),LX_FILEIO_RDONLY);

        cout << "FAILURE - An invalid file was loaded (o_o); Expected : IOexception; got : a valid reference " << endl;

    }catch(IOException &ioe)
    {
        cout << "SUCCESS - Exception occured : " << ioe.what() << endl;
    }

    cout << " = END TEST = " << endl;

}

void test_read(void)
{
    cout << " = TEST read = " << endl;

    int lus = 0;
    char buf[N + 1];
    LX_File f(str.c_str(),LX_FILEIO_RDONLY);

    lus = f.read(buf,sizeof(char),N);

    if(lus == -1)
        cerr << "FAILURE - Expected : a positive value or zero; got : -1 " << endl;
    else
    {
        cout << "SUCCESS - Received " << lus << " bytes from " << str << endl;
        buf[lus] = 0;
        cout << "INFO - data received : " << buf << endl;
    }

    f.close();

    cout << " = END TEST = " << endl;
}


void test_write(void)
{
    cout << " = TEST write = " << endl;

    int lus = 0;
    char buf[N];
    LX_File f(str.c_str(),LX_FILEIO_WRONLY);

    strncpy(buf,"GUMI",N);

    lus = f.write(buf,sizeof(char),N);

    if(lus == -1)
        cerr << "FAILURE - Expected : a positive value or zero; got : -1 " << endl;
    else
        cout << "SUCCESS - Wrote " << lus << " bytes on " << str << endl;


    lus = f.write("CHAN01");

    if(lus == -1)
        cerr << "FAILURE - Expected : a positive value or zero; got : -1 " << endl;
    else
        cout << "SUCCESS - Wrote " << lus << " bytes on " << str << endl;

    f.close();

    cout << " = END TEST = " << endl;
}













