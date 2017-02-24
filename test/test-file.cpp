
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
void test_buffer2(void);
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
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - LX_Init() failed");
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - The LunatiX library has been initialized with success");

    LX_Log::setDebugMode();
    LX_Log::log(" ==== Test File ==== ");
    test_open();
    test_write();
    test_read();
    test_read2();
    test_tellSeek();
    test_buffer();
    test_buffer2();
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
    LX_Log::log(" = TEST open = ");

    LX_File *f1 = nullptr;
    const char * str1 = "data/bullet.png";
    // valid file
    try
    {
        LX_Log::log("test open %s ...", str1);
        f1 = new LX_File(str1,LX_FILEIO_RDONLY);
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - The following file was loaded : %s", str1);
        f1->close();
        delete f1;
        f1 = nullptr;
    }
    catch(IOException &e)
    {
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - Cannot load %s; Expected : a valid refence; Got : %s",
                        str1, e.what());
    }

    // null string
    try
    {
        LX_Log::log("test open nullptr ... ");
        const char * null = nullptr;
        LX_File *invalid_str = new LX_File(null,LX_FILEIO_RDONLY);

        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - nullptr was loaded (o_o); Expected: IOexception; got: a valid reference");
        delete invalid_str;
    }
    catch(std::logic_error& le)
    {
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - std::logic_error occured : -> ",
                        le.what());
    }

    // bad mode
    try
    {
        LX_Log::log("test open %s with invalid flag...", str1    );
        f1 = new LX_File(str1,0x00000000);

        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - open with an invalid mode (o_o); Expected: IOexception; got: a valid reference ");
        delete f1;
    }
    catch(IOException &exe)
    {
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - IOException occured : Mode 0x00 -> ", exe.what());
    }

    // invalid file
    const char * str3 = "invalid_file";

    try
    {
        LX_Log::log("test open %s that does not exist...", str3);
        LX_File *not_exist_file = new LX_File(str3,LX_FILEIO_RDONLY);

        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - An invalid file was loaded (o_o); Expected: IOexception; got: a valid reference");
        delete not_exist_file;
    }
    catch(IOException &ioe)
    {
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - IOException occured: %s -> ",
        str3, ioe.what());
    }

    LX_Log::log(" = END TEST = ");
}

void test_read(void)
{
    LX_Log::log("test read ...");

    size_t read_data = 0;
    char buf[N + 1];
    LX_File f(str.c_str(),LX_FILEIO_RDONLY);

    LX_Log::log("%s is opened. Its size is %d byte(s)", f.getFilename(), f.size());
    LX_Log::log("Try to read the file");
    read_data = f.read(buf,sizeof(char), static_cast<size_t>(f.size()));

    if(read_data == 0)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - Expected : a positive value or zero; got : -1 ");
    else
    {
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - Received %d bytes from %s", read_data, str.c_str());
        buf[read_data] = 0;
        LX_Log::log("data received : ", buf);
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

    LX_Log::log("%s is opened. Its size is %ld byte(s)", f.getFilename(),f.size());
    end = f.seek(0,LX_SEEK_END);

    if(end == -1)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - Cannot go at the end of the file");

    Sint64 size = f.tell();

    if(size == -1)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - Cannot get the size of the file");

    beg = f.seek(LX_SEEK_SET,0);

    if(beg == -1)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - Cannot go at the beginning of the file");

    buff = new char[size];

    read_data = f.read(buff,sizeof(char),static_cast<size_t>(size));

    if(read_data == 0)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - Expected: non-zero value; got : 0");
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - Received %u bytes from %s",
                        read_data,strex);

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

    LX_Log::log("%s is opened. Its size is %ld byte(s)", f.getFilename(),f.size());
    LX_Log::log("Writing %s",gumi.utf8_str());
    f << gumi;

    if(f.size() != 4)
        LX_Log::log("FAILURE - expected: 4; got: %ld",f.size());
    else
        LX_Log::log("SUCCESS - ok: 4");

    LX_Log::log("Writing the following text: CHAN01");
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

    LX_Log::log("%s is opened. Its size is %ld byte(s)", f.getFilename(),f.size());
    Sint64 pos = f.seek(4,LX_SEEK_SET);

    if(pos != 4)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - seek() Expected: 4; got: ", pos);
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - seek() position: 4");

    pos = f.tell();

    if(pos != 4)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - tell() Expected: 4; got: ", pos);
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - tell() position: 4");

    pos = f.seek(-1,LX_SEEK_CUR);

    if(pos != 3)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - seek() Expected: 3; got: ", pos);
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - seek() position: 3");

    f.close();
    LX_Log::log(" = END TEST = ");
}


void test_buffer(void)
{
    LX_Log::log(" = TEST Buffer #1 = ");

    try
    {
        const char *null = nullptr;
        LX_Log::log("Open nullptr ...");
        LX_FileBuffer *invalid = new LX_FileBuffer(null);

        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - nullptr was loaded (o_o); Expected : IOexception");
        delete invalid;
    }
    catch(logic_error& ex)
    {
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - IOException occured as expected: nullptr -> %s", ex.what());
    }

    // Valid file
    string str1 = "data/bullet.png";

    try
    {
        LX_Log::log("Open %s ...", str1.c_str());
        LX_FileBuffer *f = new LX_FileBuffer(str1.c_str());
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - The following file was loaded: ", str1.c_str());
        delete f;
    }
    catch(IOException &e)
    {
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - Cannot load %s; Expected : a valid refence; Got : %s",
                        str1.c_str(), e.what());
    }

    LX_Log::log(" = END TEST = ");
}

void test_buffer2(void)
{
    LX_Log::log(" = TEST Buffer #2 = ");

    // Valid file
    string str1 = "data/lunatix-logo.png";
    string str2 = "data/bullet.png";
    uint32_t off1 = 112, sz1 = 20;
    uint32_t off2 = 65536, sz2 = 20;

    try
    {
        LX_Log::log("Open %s at %u and read %u bytes ...", str1.c_str(),off1,sz1);
        LX_FileBuffer *f = new LX_FileBuffer(str1.c_str(),off1, sz1);
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - The following file was loaded: ", str1.c_str());
        delete f;
    }
    catch(IOException &e)
    {
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - Cannot load %s; %s",
                        e.what(), str1.c_str());
    }

    // Offset too big
    try
    {
        LX_Log::log("Open %s at %u and read %u bytes ...", str2.c_str(),off2,sz2);
        LX_FileBuffer *f = new LX_FileBuffer(str2.c_str(),off2, sz2);
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - it should fail: %s",str2.c_str());
        delete f;
    }
    catch(IOException &)
    {
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - IOException occurred as expected");
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
    const char * fname = "data/explosion.wav";

    LX_Log::log(" = TEST Chunk from buffer = ");
    LX_Log::log("Open \"%s\" ...", fname);
    LX_FileBuffer f("data/explosion.wav");

    try
    {
        LX_Mixer::LX_Chunk *dump = f.loadSample();
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - LX_Chunk instanciation done.");
        delete dump;
    }
    catch(IOException & ioe)
    {
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - Cannot instanciate LX_Chunk with a file buffer as argument");
    }

    lxmix = LX_Mixer::loadSample(f);

    if(lxmix == nullptr)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - nullptr -> %s",LX_GetError());
    else
    {
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - loaded from %s",f.getFilename());
        delete lxmix;
    }

    LX_Log::log(" = END TEST = ");
}
