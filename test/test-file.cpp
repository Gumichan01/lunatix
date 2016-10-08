
#include <LunatiX/Lunatix.hpp>
#include <iostream>
#include <stdexcept>
#include <cstdio>
#include <map>


#define N 4

using namespace std;
using namespace LX_FileIO;

void test_open(void);
void test_read(void);
void test_read2(void);
void test_write(void);
void test_tellSeek(void);
void test_buffer(void);
void test_tmp(void);
void test_fs(void);
void test_getChunk(void);

namespace
{
    string str("tmpFile");
}


int main(int argc, char **argv)
{
    bool err = LX_Init();

    if(!err)
        cerr << "FAILURE - Init does not work" << endl;
    else
        cout << "SUCCESS - The LunatiX library has been initialized with success" << endl;

    LX_Log::setDebugMode();
    LX_Log::log(" ==== Test File ==== ");
    test_open();
    test_write();
    test_read();
    test_read2();
    test_tellSeek();
    test_buffer();
    test_tmp();
    test_fs();
    test_getChunk();
    remove(str.c_str());
    LX_Log::log(" ==== End File ==== ");

    LX_Init();
    return EXIT_SUCCESS;
}


void test_open(void)
{
    cout << " = TEST open = " << endl;

    LX_File *f1 = nullptr;
    const char * str1 = "data/bullet.png";
    // valid file
    try
    {
        LX_Log::log("INFO - test open %s ...", str1);
        f1 = new LX_File(str1,LX_FILEIO_RDONLY);
        cout << "SUCCESS - The following file was loaded : " << str1 << endl;
        f1->close();
        delete f1;
        f1 = nullptr;
    }
    catch(IOException &e)
    {
        cerr << "FAILURE - Cannot load " << str1
             << "; Expected : a valid refence; Got : " << e.what() << endl;
    }

    // null string
    try
    {
        LX_Log::log("INFO - test open nullptr ... ");
        const char * null = nullptr;
        LX_File *invalid_str = new LX_File(null,LX_FILEIO_RDONLY);

        cerr << "FAILURE - nullptr was loaded (o_o); "
             << "Expected : IOexception; got : a valid reference " << endl;
        delete invalid_str;
    }
    catch(std::logic_error& le)
    {
        cout << "SUCCESS - std::logic_error occured : -> " << le.what() << endl;
    }


    // bad mode
    try
    {
        LX_Log::log("INFO - test open %s with invalid flag...", str1    );
        f1 = new LX_File(str1,0x00000000);

        cerr << "FAILURE - mode was not set (o_o); Expected : "
             << "IOexception; got : a valid reference " << endl;
        delete f1;
    }
    catch(IOException &exe)
    {
        cout << "SUCCESS - IOException occured : Mode 0x00 -> "
             << exe.what() << endl;
    }

    // invalid file
    const char * str3 = "invalid_file";

    try
    {
        LX_Log::log("INFO - test open %s that does not exist...", str3);
        LX_File *not_exist_file = new LX_File(str3,LX_FILEIO_RDONLY);

        cout << "FAILURE - An invalid file was loaded (o_o); Expected : "
             << "IOexception; got : a valid reference " << endl;
        delete not_exist_file;
    }
    catch(IOException &ioe)
    {
        cout << "SUCCESS - IOException occured : " << str3 << " -> "
             << ioe.what() << endl;
    }

    LX_Log::log(" = END TEST = ");

}

void test_read(void)
{
    LX_Log::log("INFO - test read ...");

    size_t read_data = 0;
    char buf[N + 1];
    LX_File f(str.c_str(),LX_FILEIO_RDONLY);

    cout << "INFO - " << f.getFilename() << " was opened. Its size is "
         << f.size() << " byte(s)" << endl;

    LX_Log::log("Try to read the file");
    read_data = f.read(buf,sizeof(char),f.size());

    if(read_data == 0)
        cerr << "FAILURE - Expected : a positive value or zero; got : -1 "
             << endl;
    else
    {
        cout << "SUCCESS - Received " << read_data << " bytes from " << str
             << endl;
        buf[read_data] = 0;
        cout << "INFO - data received : " << buf << endl;
    }

    f.close();
    LX_Log::log(" = END TEST = ");
}


void test_read2(void)
{
    LX_Log::log(" = TEST read2 = ");
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
        cout << "SUCCESS - Received " << read_data << " bytes from "
             << strex << endl;

    delete [] buff;
    f.close();

    LX_Log::log(" = END TEST = ");
}


void test_write(void)
{
    LX_Log::log(" = TEST write = ");

    LX_Log::log("Open %s ...",str.c_str());
    LX_File f(str.c_str(),LX_FILEIO_WRONLY);
    UTF8string gumi("GUMI");

    LX_Log::log("%s was opened. Its size is %ld byte(s)",f.getFilename(),f.size());
    cout << "INFO - " << f.getFilename() << " was opened. Its size is "
         << f.size() << " byte(s)" << endl;

    LX_Log::log("Writing %s",gumi.utf8_str());
    f << gumi;

    if(f.size() != 4)
        LX_Log::log("FAILURE - expected: 4; got: %ld",f.size());
    else
        LX_Log::log("SUCCESS - ok: 4");

    LX_Log::log("Writing CHAN01");
    f << "CHAN01";

    if(f.size() != 10)
        LX_Log::log("FAILURE - expected: 10; got: %ld",f.size());
    else
        LX_Log::log("SUCCESS - ok: 10");

    f.close();
    LX_Log::log(" = END TEST = ");
}


void test_tellSeek(void)
{
    LX_Log::log(" = TEST tellSeek = ");
    LX_File f(str.c_str(),LX_FILEIO_RDONLY);

    cout << "INFO - " << f.getFilename() << " was opened. Its size is "
         << f.size() << " byte(s)" << endl;

    Sint64 pos = f.seek(4,LX_SEEK_SET);

    if(pos != 4)
        cerr << "FAILURE - seek Expected : 4 got : " << pos << endl;
    else
        cout << "SUCCESS - seek position : 4 " << endl;

    pos = f.tell();

    if(pos != 4)
        cerr << "FAILURE - tell Expected : 4 got : " << pos << endl;
    else
        cout << "SUCCESS - tell position : 4 " << endl;

    pos = f.seek(-1,LX_SEEK_CUR);

    if(pos != 3)
        cerr << "FAILURE - seek Expected : 3 got : " << pos << endl;
    else
        cout << "SUCCESS - seek position : 3 " << endl;

    f.close();
    LX_Log::log(" = END TEST = ");
}


void test_buffer(void)
{
    LX_Log::log(" = TEST Buffer = ");

    try
    {
        const char *null = nullptr;
        cout << "INFO - Open nullptr ..." << endl;
        LX_FileBuffer *invalid = new LX_FileBuffer(null);

        cerr << "FAILURE - nullptr was loaded (o_o); Expected : "
             << "IOexception; got : a valid reference " << endl;
        delete invalid;
    }
    catch(logic_error& ex)
    {
        cout << "SUCCESS - IOException occured : nullptr -> "
             << ex.what() << endl;
    }

    // Valid file
    string str1 = "data/bullet.png";

    try
    {
        cout << "INFO - Open " << str1 << " ..." << endl;
        LX_FileBuffer *f = new LX_FileBuffer(str1.c_str());
        cout << "SUCCESS - The following file was loaded : " << str1 << endl;
        delete f;
    }
    catch(IOException &e)
    {
        cerr << "FAILURE - Cannot load " << str1
             << "; Expected : a valid refence; Got : " << e.what() << endl;
    }

    LX_Log::log(" = END TEST = ");
}


void test_tmp(void)
{
    LX_Log::log(" = TEST Temporary file = ");

    try
    {
        char buf[1024] = {'\0'};
        LX_FileIO::LX_TmpFile tmp;

        LX_Log::log("File created. writing \"→ Gumichan01 ←\" ...");
        tmp << "→ Gumichan01 ←";

        tmp.seek(0,LX_SEEK_SET);
        tmp.read(buf,1024,1);
        LX_Log::log("Read the tmp file from the beginning ...");
        LX_Log::log("got: %s",buf);
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - temporary file done",buf);
    }
    catch(LX_FileIO::IOException &ioe)
    {
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - %s",ioe.what());
    }

    LX_Log::log(" = END TEST = ");
}

using u8map = std::map<UTF8string,UTF8string>;
using u8pair = std::pair<UTF8string,UTF8string>;

void test_fs(void)
{
    LX_Log::log(" = TEST File System (dirname, basename) = ");

#ifdef __WIN32__
    const char * separator = "\\";
#else
    const char * separator = "/";
#endif

    const UTF8string u8empty("");
    const UTF8string current(".");
    const UTF8string parent("..");
    const UTF8string sep(separator);
    const UTF8string root(separator);
    const UTF8string sep2(sep + sep);
    const UTF8string cursep(current + sep);
    const UTF8string scursep(sep + cursep);
    const UTF8string parsep(parent + sep);
    const UTF8string sparsep(sep + parsep);
    const UTF8string usr("usr");
    const UTF8string usrsep(usr + sep);
    const UTF8string susrsep(sep + usrsep);
    const UTF8string tmp("tmp");
    const UTF8string toto("toto");
    const UTF8string lib("lib");
    const UTF8string totopath(sep + tmp + sep + toto);
    const UTF8string libpath(sep + usr + sep + lib + sep);
    const UTF8string libpathex(sep + usr + sep2 + lib + sep2);

    u8map basename_ctest;   // Test suite for basename
    u8map dirname_ctest;    // Test suite for basename

    basename_ctest.insert(u8pair(u8empty,current));
    basename_ctest.insert(u8pair(current,current));
    basename_ctest.insert(u8pair(parent,parent));
    basename_ctest.insert(u8pair(root,root));
    basename_ctest.insert(u8pair(sep2,root));
    basename_ctest.insert(u8pair(cursep,current));
    basename_ctest.insert(u8pair(sep + current,current));
    basename_ctest.insert(u8pair(scursep,current));
    basename_ctest.insert(u8pair(parsep,parent));
    basename_ctest.insert(u8pair(sep + parent,parent));
    basename_ctest.insert(u8pair(sparsep,parent));
    basename_ctest.insert(u8pair(usr,usr));
    basename_ctest.insert(u8pair(usrsep,usr));
    basename_ctest.insert(u8pair(totopath,toto));
    basename_ctest.insert(u8pair(libpath,lib));
    basename_ctest.insert(u8pair(libpathex,lib));

    dirname_ctest.insert(u8pair(u8empty,current));
    dirname_ctest.insert(u8pair(current,current));
    dirname_ctest.insert(u8pair(parent,current));
    dirname_ctest.insert(u8pair(root,root));
    dirname_ctest.insert(u8pair(sep2,root));
    dirname_ctest.insert(u8pair(cursep,current));
    dirname_ctest.insert(u8pair(root + current,root));
    dirname_ctest.insert(u8pair(scursep,current));
    dirname_ctest.insert(u8pair(parsep,current));
    dirname_ctest.insert(u8pair(root + parent,root));
    dirname_ctest.insert(u8pair(sparsep,current));
    dirname_ctest.insert(u8pair(usr,current));
    dirname_ctest.insert(u8pair(usrsep,current));
    dirname_ctest.insert(u8pair(totopath,sep + tmp));
    dirname_ctest.insert(u8pair(libpath,sep + usr));
    dirname_ctest.insert(u8pair(libpathex,sep + usr));


    LX_Log::log(" == TEST basename() == ");

    for(auto it = basename_ctest.begin(); it != basename_ctest.end(); it++)
    {
        LX_Log::logInfo(LX_Log::LX_LOG_TEST," → basename of %s",
                        (it->first.utf8_empty() ? "<empty>" : it->first.utf8_str()) );
        UTF8string u8got = LX_FileSystem::basename(it->first);
        if(u8got != it->second)
        {
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - expected: %s; got: %s",
                            it->second.utf8_str(),u8got.utf8_str());
        }
        else
        {
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - expected: %s; got: %s",
                            it->second.utf8_str(),u8got.utf8_str());
        }
    }

    LX_Log::log(" == END TEST == \n ");
    LX_Log::log(" == TEST dirname() == ");

    for(auto it = dirname_ctest.begin(); it != dirname_ctest.end(); it++)
    {
        LX_Log::logInfo(LX_Log::LX_LOG_TEST," → dirname of %s",
                        (it->first.utf8_empty() ? "<empty>" : it->first.utf8_str()) );
        UTF8string u8got = LX_FileSystem::dirname(it->first);
        if(u8got != it->second)
        {
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - expected: %s; got: %s",
                            it->second.utf8_str(),u8got.utf8_str());
        }
        else
        {
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - expected: %s; got: %s",
                            it->second.utf8_str(),u8got.utf8_str());
        }
    }

    LX_Log::log(" == END TEST == ");
    LX_Log::log(" = END TEST = ");
}


void test_getChunk(void)
{
    LX_Mixer::LX_Chunk * lxmix = nullptr;

    LX_Log::log(" = TEST Chunk from buffer = ");
    cout << " = TEST Chunk from buffer = " << endl;
    cout << "INFO - Open \"data/explosion.wav\" ..." << endl;
    LX_FileBuffer f("data/explosion.wav");

    try
    {
        LX_Mixer::LX_Chunk *dump = f.loadSample();
        cout << "SUCCESS - LX_Chunk instanciation done." << endl;
        delete dump;
    }
    catch(IOException & ioe)
    {
        cerr << "FAILURE - Cannot instanciate LX_Chunk with"
             << " a file buffer as argument" << ioe.what() << endl;
    }

    lxmix = LX_Mixer::loadSample(f);

    if(lxmix == nullptr)
        cerr << "FAILURE - LX_Mixer::loadSample() Expected : "
             << "non-nullptr pointer; got : nullptr -> "
             << LX_GetError() << endl;
    else
    {
        cout << "SUCCESS - LX_Mixer::loadSample() : got a valid chunk from "
             << f.getFilename() << endl;
        delete lxmix;
    }

    LX_Log::log(" = END TEST = ");
}
