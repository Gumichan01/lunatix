


#include <iostream>
#include <cstdio>
#include <cstring>

#include <LunatiX/Lunatix_engine.hpp>


#define N 4

using namespace std;
using namespace LX_FileIO;


void test_open(void);
void test_read(void);
void test_write(void);
void test_tellSeek(void);
void test_getSurface(void);
void test_buffer(void);
void test_getSurface2(void);

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
    test_tellSeek();
    test_getSurface();
    test_buffer();
    test_getSurface2();

    remove(str.c_str());

    cout << " ==== End File ==== " << endl;

    return EXIT_SUCCESS;
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
        delete invalidString;

    }catch(IOException &ex)
    {
        cout << "SUCCESS - IOException occured : NULL -> " << ex.what() << endl;
    }

    // bad mode
    try{

        f1 = new LX_File(str1.c_str(),0x00000000);

        cerr << "FAILURE - mode was not set (o_o); Expected : IOexception; got : a valid reference " << endl;
        delete f1;

    }catch(IOException &exe)
    {
        cout << "SUCCESS - IOException occured : Mode 0x00 -> " << exe.what() << endl;
    }

    // invalid file
    try{

        notExistFile = new LX_File(str3.c_str(),LX_FILEIO_RDONLY);

        cout << "FAILURE - An invalid file was loaded (o_o); Expected : IOexception; got : a valid reference " << endl;
        delete notExistFile;

    }catch(IOException &ioe)
    {
        cout << "SUCCESS - IOException occured : " << str3 << " -> " << ioe.what() << endl;
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


void test_tellSeek(void)
{
    cout << " = TEST write = " << endl;

    LX_File f(str.c_str(),LX_FILEIO_RDONLY);

    Sint64 pos = f.seek(4,LX_SEEK_SET);

    if(pos != 4)
        cerr << "FAILURE - seek Expected : 4 got : " << pos << endl;
    else
    {
        cout << "SUCCESS - seek position : 4 " << endl;
    }

    pos = f.tell();

    if(pos != 4)
        cerr << "FAILURE - tell Expected : 4 got : " << pos << endl;
    else
    {
        cout << "SUCCESS - tell position : 4 " << endl;
    }

    pos = f.seek(-1,LX_SEEK_CUR);

    if(pos != 3)
        cerr << "FAILURE - seek Expected : 3 got : " << pos << endl;
    else
    {
        cout << "SUCCESS - seek -1 position : 3 " << endl;
    }


    f.close();


    cout << " = END TEST = " << endl;
}



void test_getSurface(void)
{
    cout << " = TEST getSurface = " << endl;

    string str_ex = "data/explosion.png";
    SDL_Surface * surface = NULL;

    LX_File f(str_ex.c_str(),LX_FILEIO_RDONLY);

    surface = f.getSurfaceFromData();

    if(surface == NULL)
        cerr << "FAILURE - getSurfaceFromData() Expected : non-NULL pointer; got : NULL -> " << LX_GetError() << endl;
    else
    {
        cout << "SUCCESS - getSurfaceFromData() : got a valid surface from " << f.getFilename() << endl;
        SDL_FreeSurface(surface);
    }


    surface = LX_Graphics::loadSurface(&f);

    if(surface == NULL)
        cerr << "FAILURE - LX_Graphics::loadSurface from file Expected : non-NULL pointer; got : NULL -> " << LX_GetError() << endl;
    else
    {
        cout << "SUCCESS - loadSurface() : got a valid surface from " << f.getFilename() << endl;
        SDL_FreeSurface(surface);
    }


    f.close();

    cout << " = END TEST = " << endl;
}



void test_buffer(void)
{
    LX_FileBuffer *f = NULL;
    LX_FileBuffer *invalid = NULL;

    const char *null = NULL;
    string str1 = "data/explosion.png";

    cout << " = TEST Buffer = " << endl;

    try{

        invalid = new LX_FileBuffer(null);

        cerr << "FAILURE - NULL was loaded (o_o); Expected : IOexception; got : a valid reference " << endl;
        delete invalid;

    }catch(IOException &ex)
    {
        cout << "SUCCESS - IOException occured : NULL -> " << ex.what() << endl;
    }


    // Valid file
    try{

        f = new LX_FileBuffer(str1.c_str());

        cout << "SUCCESS - The following file was loaded : " << str1 << endl;

        delete f;
        f = NULL;

    }catch(IOException &e)
    {
        cerr << "FAILURE - Cannot load " << str1 << "; Expected : a valid refence; Got : " << e.what() << endl;
    }

    cout << " = END TEST = " << endl;

}


void test_getSurface2(void)
{
    LX_FileBuffer f("data/explosion.png");
    SDL_Surface * surface = NULL;


    cout << " = TEST Surface from buffer = " << endl;

    surface = f.getSurfaceFromBuffer();

    if(surface == NULL)
        cerr << "FAILURE - getsurface from buffer Expected : non-NULL pointer; got : NULL -> " << LX_GetError() << endl;
    else
    {
        cout << "SUCCESS - getSurfaceFromBuffer : got a valid surface from " << f.getFilename() << endl;
        SDL_FreeSurface(surface);
    }

    surface = LX_Graphics::loadSurfaceFromFileBuffer(&f);

    if(surface == NULL)
        cerr << "FAILURE - loadSurfaceFromFileBuffer Expected : non-NULL pointer; got : NULL -> " << LX_GetError() << endl;
    else
    {
        cout << "SUCCESS - loadSurfaceFromFileBuffer : got a valid surface from " << f.getFilename() << endl;
        SDL_FreeSurface(surface);
    }


    cout << " = END TEST = " << endl;
}




