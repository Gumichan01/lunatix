#include <cstdio>
#include <cstring>
#include <iostream>
#include <stdexcept>

#include <LunatiX/Lunatix_engine.hpp>


#define N 4

using namespace std;
using namespace LX_FileIO;


void test_open(void);
void test_read(void);
void test_read2(void);
void test_write(void);
void test_tellSeek(void);
void test_getSurface(void);
void test_buffer(void);
void test_getSurface2(void);
void test_getChunk(void);


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wglobal-constructors"

static string str = "tmpFile";

#pragma clang diagnostic pop
#pragma clang diagnostic pop


int main()
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
    test_read2();
    test_tellSeek();
    test_getSurface();
    test_buffer();
    test_getSurface2();
    test_getChunk();

    remove(str.c_str());

    cout << " ==== End File ==== " << endl;

    return EXIT_SUCCESS;
}



void test_open(void)
{
    LX_File *f1 = nullptr;
    LX_File *invalidString = nullptr;
    LX_File *notExistFile = nullptr;

    const char * str1 = "data/bullet.png";
    const char * null = nullptr;
    const char * str3 = "invalid_file";

    cout << " = TEST open = " << endl;


    // valid file
    try
    {

        f1 = new LX_File(str1,LX_FILEIO_RDONLY);

        cout << "SUCCESS - The following file was loaded : " << str1 << endl;

        f1->close();

        delete f1;
        f1 = nullptr;

    }
    catch(IOException &e)
    {
        cerr << "FAILURE - Cannot load " << str1 << "; Expected : a valid refence; Got : " << e.what() << endl;
    }

    // null string
    try
    {

        invalidString = new LX_File(null,LX_FILEIO_RDONLY);

        cerr << "FAILURE - nullptr was loaded (o_o); Expected : IOexception; got : a valid reference " << endl;
        delete invalidString;

    }
    catch(logic_error le)
    {
        cout << "SUCCESS - std::logic_error occured : -> " << le.what() << endl;
    }


    // bad mode
    try
    {

        f1 = new LX_File(str1,0x00000000);

        cerr << "FAILURE - mode was not set (o_o); Expected : IOexception; got : a valid reference " << endl;
        delete f1;

    }
    catch(IOException &exe)
    {
        cout << "SUCCESS - IOException occured : Mode 0x00 -> " << exe.what() << endl;
    }

    // invalid file
    try
    {

        notExistFile = new LX_File(str3,LX_FILEIO_RDONLY);

        cout << "FAILURE - An invalid file was loaded (o_o); Expected : IOexception; got : a valid reference " << endl;
        delete notExistFile;

    }
    catch(IOException &ioe)
    {
        cout << "SUCCESS - IOException occured : " << str3 << " -> " << ioe.what() << endl;
    }

    cout << " = END TEST = " << endl;

}

void test_read(void)
{
    cout << " = TEST read = " << endl;

    size_t read_data = 0;
    char buf[N + 1];
    LX_File f(str.c_str(),LX_FILEIO_RDONLY);


    cout << "INFO - " << f.getFilename() << " was opened. Its size is "
         << f.size() << " byte(s)" << endl;
    read_data = f.read(buf,sizeof(char),N);

    if(read_data == 0)
        cerr << "FAILURE - Expected : a positive value or zero; got : -1 " << endl;
    else
    {
        cout << "SUCCESS - Received " << read_data << " bytes from " << str << endl;
        buf[read_data] = 0;
        cout << "INFO - data received : " << buf << endl;
    }

    f.close();

    cout << " = END TEST = " << endl;
}


void test_read2(void)
{
    cout << " = TEST read2 = " << endl;

    const char * strex = "data/bullet.png";

    Sint64 beg, end;
    size_t read_data = 0;
    char *buff = nullptr;
    LX_File f(strex,LX_FILEIO_RDONLY);

    cout << "INFO - " << f.getFilename() << " was opened. Its size is "
         << f.size() << " byte(s)" << endl;

    end = f.seek(0,LX_SEEK_END);

    if(end == -1)
        cerr << "FAILURE - Cannot go at the end of the file " << endl;

    Sint64 size = f.tell();

    if(size == -1)
        cerr << "FAILURE - Cannot get the size of the file " << endl;

    beg = f.seek(LX_SEEK_SET,0);

    if(beg == -1)
        cerr << "FAILURE - Cannot go at the beginning of the file " << endl;

    buff = new char[size];

    read_data = f.read(buff,sizeof(char),static_cast<size_t>(size));

    if(read_data == 0)
        cerr << "FAILURE - Expected : a positive value or zero; got : -1 " << endl;
    else
    {
        cout << "SUCCESS - Received " << read_data << " bytes from " << strex << endl;
    }


    delete [] buff;
    f.close();

    cout << " = END TEST = " << endl;
}



void test_write(void)
{
    cout << " = TEST write = " << endl;

    size_t read_data = 0;
    char buf[N];
    LX_File f(str.c_str(),LX_FILEIO_WRONLY);

    strncpy(buf,"GUMI",N);

    cout << "INFO - " << f.getFilename() << " was opened. Its size is "
         << f.size() << " byte(s)" << endl;

    read_data = f.write(buf,sizeof(char),N);

    if(read_data == 0)
        cerr << "FAILURE - Expected : a positive value or zero; got : -1 " << endl;
    else
        cout << "SUCCESS - Wrote " << read_data << " bytes on " << str << endl;


    read_data = f.write("CHAN01");

    if(read_data == 0)
        cerr << "FAILURE - Expected : a positive value or zero; got : -1 " << endl;
    else
        cout << "SUCCESS - Wrote " << read_data << " bytes on " << str << endl;

    f.close();

    cout << " = END TEST = " << endl;
}


void test_tellSeek(void)
{
    cout << " = TEST tellSeek = " << endl;

    LX_File f(str.c_str(),LX_FILEIO_RDONLY);

    cout << "INFO - " << f.getFilename() << " was opened. Its size is "
         << f.size() << " byte(s)" << endl;

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
        cout << "SUCCESS - seek position : 3 " << endl;
    }


    f.close();


    cout << " = END TEST = " << endl;
}



void test_getSurface(void)
{
    cout << " = TEST getSurface = " << endl;

    string str_ex = "data/bullet.png";
    SDL_Surface * surface = nullptr;

    LX_File f(str_ex.c_str(),LX_FILEIO_RDONLY);

    cout << "INFO - " << f.getFilename() << " was opened. Its size is "
         << f.size() << " byte(s)" << endl;

    surface = f.getSurfaceFromData();

    if(surface == nullptr)
        cerr << "FAILURE - getSurfaceFromData() Expected : non-nullptr pointer; got : nullptr -> " << LX_GetError() << endl;
    else
    {
        cout << "SUCCESS - getSurfaceFromData() : got a valid surface from " << f.getFilename() << endl;
        SDL_FreeSurface(surface);
    }


    surface = LX_Graphics::loadSurface(&f);

    if(surface == nullptr)
        cerr << "FAILURE - LX_Graphics::loadSurface from file Expected : non-nullptr pointer; got : nullptr -> " << LX_GetError() << endl;
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
    LX_FileBuffer *f = nullptr;
    LX_FileBuffer *invalid = nullptr;

    const char *null = nullptr;
    string str1 = "data/bullet.png";

    cout << " = TEST Buffer = " << endl;

    try
    {

        invalid = new LX_FileBuffer(null);

        cerr << "FAILURE - nullptr was loaded (o_o); Expected : IOexception; got : a valid reference " << endl;
        delete invalid;

    }
    catch(logic_error ex)
    {
        cout << "SUCCESS - IOException occured : nullptr -> " << ex.what() << endl;
    }


    // Valid file
    try
    {

        f = new LX_FileBuffer(str1.c_str());

        cout << "SUCCESS - The following file was loaded : " << str1 << endl;

        delete f;
        f = nullptr;

    }
    catch(IOException &e)
    {
        cerr << "FAILURE - Cannot load " << str1 << "; Expected : a valid refence; Got : " << e.what() << endl;
    }

    cout << " = END TEST = " << endl;

}


void test_getSurface2(void)
{
    LX_FileBuffer f("data/bullet.png");
    SDL_Surface * surface = nullptr;


    cout << " = TEST Surface from buffer = " << endl;

    surface = f.getSurfaceFromBuffer();

    if(surface == nullptr)
        cerr << "FAILURE - getsurface from buffer Expected : non-nullptr pointer; got : nullptr -> " << LX_GetError() << endl;
    else
    {
        cout << "SUCCESS - getSurfaceFromBuffer : got a valid surface from " << f.getFilename() << endl;
        SDL_FreeSurface(surface);
    }

    surface = LX_Graphics::loadSurfaceFromFileBuffer(&f);

    if(surface == nullptr)
        cerr << "FAILURE - loadSurfaceFromFileBuffer Expected : non-nullptr pointer; got : nullptr -> " << LX_GetError() << endl;
    else
    {
        cout << "SUCCESS - loadSurfaceFromFileBuffer : got a valid surface from " << f.getFilename() << endl;
        SDL_FreeSurface(surface);
    }


    cout << " = END TEST = " << endl;
}


void test_getChunk(void)
{
    LX_FileBuffer f("data/explosion.wav");
    Mix_Chunk * mix = nullptr;
    LX_Mixer::LX_Chunk * lxmix = nullptr;

    cout << " = TEST Chunk from buffer = " << endl;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-exception-parameter"

    try
    {
        LX_Mixer::LX_Chunk dump(&f);
        cout << "SUCCESS - LX_Chunk instanciation done : " << LX_GetError() << endl;
    }
    catch(IOException & ioe)
    {
        cerr << "FAILURE - Cannot instanciate LX_Chunk with a file buffer as argument" << LX_GetError() << endl;
    }

#pragma clang diagnostic pop

    mix = f.getChunkFromBuffer();

    if(mix == nullptr)
        cerr << "FAILURE - getChunkFromBuffer() from buffer Expected : non-nullptr pointer; got : nullptr -> "
             << LX_GetError() << endl;
    else
    {
        cout << "SUCCESS - getChunkFromBuffer() : got a valid chunk from "
             << f.getFilename() << endl;
        Mix_FreeChunk(mix);
    }

    lxmix = LX_Mixer::loadSample(&f);

    if(lxmix == nullptr)
        cerr << "FAILURE - LX_Mixer::loadSample() Expected : non-nullptr pointer; got : nullptr -> "
             << LX_GetError() << endl;
    else
    {
        cout << "SUCCESS - LX_Mixer::loadSample() : got a valid chunk from " << f.getFilename() << endl;
        delete lxmix;
    }


    cout << " = END TEST = " << endl;
}

