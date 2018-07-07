
#include <Lunatix/Lunatix.hpp>
#include <iostream>
#include <stdexcept>
#include <cstdio>
#include <cstring>
#include <map>

#define N 64

using namespace std;
using namespace lx::FileIO;

void test_open( void );
void test_read( void );
void test_read2( void );
void test_read3( void );
void test_read4( void );
void test_write( void );
void test_write2( void );
void test_RW( void );
void test_tellSeek( void );
void test_buffer( void );
void test_buffer2( void );
void test_tmp( void );
void test_fs( void );
void test_getChunk( void );

namespace
{
string str( "./tmpFile" );
string strbin( "./bin_tmpFile" );
}


int main( int argc, char ** argv )
{
    bool err = lx::init();

    if ( !err )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - lx::init() failed" );
    else
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - The LunatiX library has been initialized with success" );

    lx::Log::setDebugMode();
    lx::Log::log( " ==== Test File ==== " );
    test_open();
    test_write();
    test_write2();
    test_read();
    test_read2();
    test_read3();
    test_read4();
    test_RW();
    test_tellSeek();
    test_buffer();
    test_buffer2();
    test_tmp();
    test_fs();
    test_getChunk();
    remove( str.c_str() );
    remove( strbin.c_str() );
    lx::Log::log( " ==== End File ==== " );

    lx::init();
    return EXIT_SUCCESS;
}


void test_open( void )
{
    lx::Log::log( " = TEST open = " );

    File * f1 = nullptr;
    const std::string str1( "data/bullet.png" );
    // valid file
    try
    {
        lx::Log::log( "test open %s ...", str1.c_str() );
        f1 = new File( str1, FileMode::RDONLY );
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - The following file was loaded : %s", str1.c_str() );
        delete f1;
        f1 = nullptr;
    }
    catch ( IOException& e )
    {
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - Cannot load %s; Expected : a valid refence; Got : %s",
                          str1.c_str(), e.what() );
    }

    // invalid file
    const std::string str3( "invalid_file" );

    try
    {
        lx::Log::log( "test open %s that does not exist...", str3.c_str() );
        File * not_exist_file = new File( str3, FileMode::RDONLY );

        lx::Log::logInfo( lx::Log::TEST, "FAILURE - An invalid file was loaded (o_o); Expected: IOexception; got: a valid reference" );
        delete not_exist_file;
    }
    catch ( IOException& ioe )
    {
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - IOException occured: %s -> ",
                          str3.c_str(), ioe.what() );
    }

    lx::Log::log( " = END TEST = " );
}

void test_read( void )
{
    lx::Log::log( " = TEST read #1 = " );

    size_t read_data = 0;
    char buf[N + 1];
    File f( str, FileMode::RDONLY );

    lx::Log::log( "%s is opened. Its size is %d byte(s)", f.getFilename(), f.size() );
    lx::Log::log( "Try to read the file" );
    read_data = f.read( buf, sizeof( char ), static_cast<size_t>( f.size() ) );

    if ( read_data == 0 )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - Expected : a positive value or zero; got : -1 " );
    else
    {
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - Received %d bytes from %s", read_data, str.c_str() );
        buf[read_data] = 0;
        lx::Log::log( "data received : ", buf );
    }

    lx::Log::log( " = END TEST = " );
}


void test_read2( void )
{
    lx::Log::log( " = TEST read #2 = " );
    const std::string strex( "data/bullet.png" );

    bool beg, end;
    size_t read_data = 0;
    char * buff = nullptr;
    File f( strex, FileMode::RDONLY );

    lx::Log::log( "%s is opened. Its size is %ld byte(s)", f.getFilename(), f.size() );
    end = f.seek( 0, FileWhence::END );

    if ( !end )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - Cannot go at the end of the file" );

    long size = f.tell();

    if ( size == -1L )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - Cannot get the size of the file" );

    beg = f.seek( 0, FileWhence::SET );

    if ( !beg )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - Cannot go at the beginning of the file" );

    try
    {
        buff = new char[size];
        read_data = f.read( buff, sizeof( char ), static_cast<size_t>( size ) );

        if ( read_data == 0 )
            lx::Log::logInfo( lx::Log::TEST, "FAILURE - Expected: non-zero value; got : 0" );
        else
            lx::Log::logInfo( lx::Log::TEST, "SUCCESS - Received %u bytes from %s",
                              read_data, strex.c_str() );

        delete [] buff;

    }
    catch ( ... )
    {
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - Exception occured - size: %ld", size );
    }

    lx::Log::log( " = END TEST = " );
}

void test_read3( void )
{
    lx::Log::log( " = TEST read #3 = " );

    size_t read_data = 0;
    int i;
    char c;
    float fl;
    lx::Log::log( "Open %s ...", strbin.c_str() );
    File f( strbin, FileMode::RDONLY );

    lx::Log::log( "%s is opened. Its size is %d byte(s)", f.getFilename(), f.size() );
    lx::Log::log( "Try to read the file" );
    read_data = f.read( &i, sizeof( int ) );

    if ( read_data == 0 )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - Expected : a positive value or zero; got : -1" );
    else
    {
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - Received %d bytes from %s", read_data, str.c_str() );

        if ( i == 42 )
            lx::Log::logInfo( lx::Log::TEST, "SUCCESS - 42" );
    }

    read_data = f.read( &c, sizeof( char ) );

    if ( read_data == 0 )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - Expected : a positive value or zero; got : -1" );
    else
    {
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - Received %d bytes from %s", read_data, str.c_str() );

        if ( c == 'G' )
            lx::Log::logInfo( lx::Log::TEST, "SUCCESS - G" );
    }

    read_data = f.read( &fl, sizeof( float ) );

    if ( read_data == 0 )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - Expected : a positive value or zero; got : -1" );
    else
    {
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - Received %d bytes from %s", read_data, str.c_str() );
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - %f", fl );
    }

    lx::Log::log( " = END TEST = " );
}

void test_read4( void )
{
    lx::Log::log( " = TEST read #4 = " );

    int i = 0;
    char c = '0';
    float fl = 0.0f;
    lx::Log::log( "Open %s ...", strbin.c_str() );
    File f( strbin, FileMode::RDONLY );

    lx::Log::log( "%s is opened. Its size is %d byte(s)", f.getFilename(), f.size() );
    lx::Log::log( "Try to read the file" );

    f >> i;

    lx::Log::logInfo( lx::Log::TEST, "value: %d", i );

    f >> c;

    lx::Log::logInfo( lx::Log::TEST, "value: %c", c );

    f >> fl;

    lx::Log::logInfo( lx::Log::TEST, "value: %f", fl );
    lx::Log::log( " = END TEST = " );
}

void test_write( void )
{
    lx::Log::log( " = TEST write #1 = " );

    lx::Log::log( "Open %s ...", str.c_str() );
    File f( str, FileMode::WRONLY );
    UTF8string gumi( "GUMI" );
    const char * gs = "CHAN01";

    lx::Log::log( "%s is opened. Its size is %ld byte(s)", f.getFilename(), f.size() );
    lx::Log::log( "Writing %s", gumi.utf8_str() );
    f << gumi;

    if ( f.size() != gumi.utf8_length() )
        lx::Log::log( "FAILURE - expected: %u; got: %u", gumi.utf8_length(), f.size() );
    else
        lx::Log::log( "SUCCESS - ok: %u", gumi.utf8_length() );

    lx::Log::log( "Writing the following text: CHAN01" );
    f << gs;

    if ( f.size() != ( gumi.utf8_length() + strlen( "CHAN01" ) ) )
        lx::Log::log( "FAILURE - expected: %u; got: %ld",
                      gumi.utf8_length() + strlen( gs ), f.size() );
    else
        lx::Log::log( "SUCCESS - ok: %u", gumi.utf8_length() + strlen( "CHAN01" ) );

    lx::Log::log( " = END TEST = " );
}

void test_write2( void )
{
    lx::Log::log( " = TEST write #2 = " );

    int i = 42;
    char c = 'G';
    float fl = 3.14f;
    lx::Log::log( "Open %s ...", strbin.c_str() );
    File f( strbin, FileMode::WRONLY );

    lx::Log::log( "%s is opened. Its size is %ld byte(s)", f.getFilename(),
                  f.size() );
    lx::Log::log( "Writing %d", i );
    f << i;

    if ( f.size() != sizeof( i ) )
        lx::Log::log( "FAILURE - expected: %u; got: %u", sizeof( i ), f.size() );
    else
        lx::Log::log( "SUCCESS - ok: %u", sizeof( i ) );

    lx::Log::log( "Writing %c", c );
    f << c;

    if ( f.size() != ( sizeof( i ) + sizeof( c ) ) )
        lx::Log::log( "FAILURE - expected: %u; got: %u", sizeof( i ) + sizeof( c ),
                      f.size() );
    else
        lx::Log::log( "SUCCESS - ok: %u", sizeof( i ) + sizeof( c ) );

    lx::Log::log( "Writing %f", fl );
    f << fl;

    if ( f.size() != ( sizeof( i ) + sizeof( c ) + sizeof( fl ) ) )
        lx::Log::log( "FAILURE - expected: %u; got: %u",
                      sizeof( i ) + sizeof( c ) + sizeof( fl ), f.size() );
    else
        lx::Log::log( "SUCCESS - ok: %u", sizeof( i ) + sizeof( c ) + sizeof( fl ) );


    lx::Log::log( " = END TEST = " );
}


void test_RW()
{
    lx::Log::log( " = TEST RW = " );

    int i = 0;
    char c = '0';
    float fl = 0.0f;
    std::string fs = "fs_tmp";

    lx::Log::log( "Open %s (write)...", fs.c_str() );

    {
        File fw( fs, FileMode::WRONLY );
        fw << 64 << 'a' << 3.14159f;
    }

    // read
    lx::Log::log( "Open %s (read)...", fs.c_str() );
    {
        File fr( fs, FileMode::RDONLY );
        lx::Log::log( "%s is opened. Its size is %d byte(s)", fr.getFilename(), fr.size() );
    }

    {
        File fr( fs, FileMode::RDONLY );
        fr >> i >> c >> fl;
    }
    lx::Log::logInfo( lx::Log::TEST, "fr - value: %d", i );
    lx::Log::logInfo( lx::Log::TEST, "fr - value: %c", c );
    lx::Log::logInfo( lx::Log::TEST, "fr - value: %f", fl );
    remove( fs.c_str() );
    lx::Log::log( " = END TEST = " );
}

void test_tellSeek( void )
{
    lx::Log::log( " = TEST tellSeek = " );
    File f( str, FileMode::RDONLY );

    lx::Log::log( "%s is opened. Its size is %ld byte(s)", f.getFilename(), f.size() );
    f.seek( 4, FileWhence::SET );
    size_t pos = f.tell();

    if ( pos != 4 )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - seek() Expected: 4; got: ", pos );
    else
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - seek() position: 4" );

    f.seek( -1, FileWhence::CUR );
    pos = f.tell();

    if ( pos != 3 )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - seek() Expected: 3; got: ", pos );
    else
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - seek() position: 3" );

    lx::Log::log( " = END TEST = " );
}


void test_buffer( void )
{
    lx::Log::log( " = TEST Buffer #1 = " );

    // Valid file
    string str1 = "data/bullet.png";

    try
    {
        lx::Log::log( "Open %s ...", str1.c_str() );
        FileBuffer * f = new FileBuffer( str1 );
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - The following file was loaded: ", str1.c_str() );
        delete f;
    }
    catch ( IOException& e )
    {
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - Cannot load %s; Expected : a valid refence; Got : %s",
                          str1.c_str(), e.what() );
    }

    lx::Log::log( " = END TEST = " );
}

void test_buffer2( void )
{
    lx::Log::log( " = TEST Buffer #2 = " );

    // Valid file
    string str1 = "data/lunatix-logo.png";
    string str2 = "data/bullet.png";
    uint32_t off1 = 112, sz1 = 20;
    uint32_t off2 = 65536, sz2 = 20;

    try
    {
        lx::Log::log( "Open %s at %u and read %u bytes ...", str1.c_str(), off1, sz1 );
        FileBuffer * f = new FileBuffer( str1, off1, sz1 );
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - The following file was loaded: ", str1.c_str() );
        delete f;
    }
    catch ( IOException& e )
    {
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - Cannot load %s; %s",
                          e.what(), str1.c_str() );
    }

    // Offset too big
    try
    {
        lx::Log::log( "Open %s at %u and read %u bytes ...", str2.c_str(), off2, sz2 );
        FileBuffer * f = new FileBuffer( str2, off2, sz2 );
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - it should fail: %s", str2.c_str() );
        delete f;
    }
    catch ( IOException& )
    {
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - IOException occurred as expected" );
    }

    lx::Log::log( " = END TEST = " );
}


void test_tmp( void )
{
    lx::Log::log( " = TEST Temporary file = " );

    try
    {
        char buf[1024] = {'\0'};
        lx::FileIO::TmpFile tmp;

        lx::Log::log( "File created. writing \"→ Gumichan01 ←\" ..." );
        tmp << "→ Gumichan01 ←";

        tmp.seek( 0, FileWhence::SET );
        tmp.read( buf, 1024 );
        lx::Log::log( "Read the tmp file from the beginning ..." );
        lx::Log::log( "got: %s", buf );
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - temporary file done", buf );
    }
    catch ( lx::FileIO::IOException& ioe )
    {
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - %s", ioe.what() );
    }

    lx::Log::log( " = END TEST = " );
}

using u8map = std::map<UTF8string, UTF8string>;
using u8pair = std::pair<UTF8string, UTF8string>;

void test_fs( void )
{
    lx::Log::log( " = TEST File System (dirname, basename) = " );

#ifdef __WIN32__
    const char * separator = "\\";
#else
    const char * separator = "/";
#endif

    const UTF8string u8empty( "" );
    const UTF8string current( "." );
    const UTF8string parent( ".." );
    const UTF8string sep( separator );
    const UTF8string root( separator );
    const UTF8string sep2( sep + sep );
    const UTF8string cursep( current + sep );
    const UTF8string scursep( sep + cursep );
    const UTF8string parsep( parent + sep );
    const UTF8string sparsep( sep + parsep );
    const UTF8string usr( "usr" );
    const UTF8string usrsep( usr + sep );
    const UTF8string susrsep( sep + usrsep );
    const UTF8string tmp( "tmp" );
    const UTF8string toto( "toto" );
    const UTF8string lib( "lib" );
    const UTF8string totopath( sep + tmp + sep + toto );
    const UTF8string libpath( sep + usr + sep + lib + sep );
    const UTF8string libpathex( sep2 + sep2 + usr + sep2 + sep2 + lib + sep2 );
    const UTF8string lunapath( sep + "d" + sep + "git_dir" + sep + "." + sep +
                               "lunatix_github" + sep + ".." + sep +
                               "lunatix-github" + sep );
    const UTF8string lunabase( "lunatix-github" );
    const UTF8string lunadir( sep + "d" + sep + "git_dir" + sep + "." + sep + "lunatix_github" + sep + ".." );

    u8map basename_ctest;   // Test suite for basename
    u8map dirname_ctest;    // Test suite for basename

    basename_ctest.insert( u8pair( u8empty, current ) );
    basename_ctest.insert( u8pair( current, current ) );
    basename_ctest.insert( u8pair( parent, parent ) );
    basename_ctest.insert( u8pair( root, root ) );
    basename_ctest.insert( u8pair( sep2, root ) );
    basename_ctest.insert( u8pair( cursep, current ) );
    basename_ctest.insert( u8pair( sep + current, current ) );
    basename_ctest.insert( u8pair( scursep, current ) );
    basename_ctest.insert( u8pair( parsep, parent ) );
    basename_ctest.insert( u8pair( sep + parent, parent ) );
    basename_ctest.insert( u8pair( sparsep, parent ) );
    basename_ctest.insert( u8pair( usr, usr ) );
    basename_ctest.insert( u8pair( usrsep, usr ) );
    basename_ctest.insert( u8pair( totopath, toto ) );
    basename_ctest.insert( u8pair( libpath, lib ) );
    basename_ctest.insert( u8pair( libpathex, lib ) );
    basename_ctest.insert( u8pair( lunapath, lunabase ) );

    dirname_ctest.insert( u8pair( u8empty, current ) );
    dirname_ctest.insert( u8pair( current, current ) );
    dirname_ctest.insert( u8pair( parent, current ) );
    dirname_ctest.insert( u8pair( root, root ) );
    dirname_ctest.insert( u8pair( sep2, root ) );
    dirname_ctest.insert( u8pair( cursep, current ) );
    dirname_ctest.insert( u8pair( root + current, root ) );
    dirname_ctest.insert( u8pair( scursep, current ) );
    dirname_ctest.insert( u8pair( parsep, current ) );
    dirname_ctest.insert( u8pair( root + parent, root ) );
    dirname_ctest.insert( u8pair( sparsep, current ) );
    dirname_ctest.insert( u8pair( usr, current ) );
    dirname_ctest.insert( u8pair( usrsep, current ) );
    dirname_ctest.insert( u8pair( totopath, sep + tmp ) );
    dirname_ctest.insert( u8pair( libpath, sep + usr ) );
    dirname_ctest.insert( u8pair( libpathex, sep + usr ) );
    dirname_ctest.insert( u8pair( lunapath, lunadir ) );


    lx::Log::log( " == TEST basename() == " );

    for ( auto it = basename_ctest.begin(); it != basename_ctest.end(); it++ )
    {
        lx::Log::logInfo( lx::Log::TEST, " → basename of %s",
                          ( it->first.utf8_empty() ? "<empty>" : it->first.utf8_str() ) );
        UTF8string u8got = lx::FileSystem::basename( it->first );
        if ( u8got != it->second )
        {
            lx::Log::logInfo( lx::Log::TEST, "FAILURE - expected: %s; got: %s",
                              it->second.utf8_str(), u8got.utf8_str() );
        }
        else
        {
            lx::Log::logInfo( lx::Log::TEST, "SUCCESS - expected: %s; got: %s",
                              it->second.utf8_str(), u8got.utf8_str() );
        }
    }

    lx::Log::log( " == END TEST == \n " );
    lx::Log::log( " == TEST dirname() == " );

    for ( auto it = dirname_ctest.begin(); it != dirname_ctest.end(); it++ )
    {
        lx::Log::logInfo( lx::Log::TEST, " → dirname of %s",
                          ( it->first.utf8_empty() ? "<empty>" : it->first.utf8_str() ) );
        UTF8string u8got = lx::FileSystem::dirname( it->first );
        if ( u8got != it->second )
        {
            lx::Log::logInfo( lx::Log::TEST, "FAILURE - expected: %s; got: %s",
                              it->second.utf8_str(), u8got.utf8_str() );
        }
        else
        {
            lx::Log::logInfo( lx::Log::TEST, "SUCCESS - expected: %s; got: %s",
                              it->second.utf8_str(), u8got.utf8_str() );
        }
    }

    lx::Log::log( " == END TEST == " );
    lx::Log::log( " = END TEST = " );
}


void test_getChunk( void )
{
    lx::Mixer::Chunk * lxmix = nullptr;
    const std::string fname( "data/explosion.wav" );

    lx::Log::log( " = TEST Chunk from buffer = " );
    lx::Log::log( "Open \"%s\" ...", fname.c_str() );
    FileBuffer f( fname );

    try
    {
        lx::Mixer::Chunk * dump = f.loadSample();
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - Chunk instanciation done." );
        delete dump;
    }
    catch ( IOException& ioe )
    {
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - Cannot instanciate Chunk with a file buffer as argument" );
    }

    lxmix = lx::Mixer::loadSample( f );

    if ( lxmix == nullptr )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - nullptr -> %s", lx::getError() );
    else
    {
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - loaded from %s", f.getFilename() );
        delete lxmix;
    }

    lx::Log::log( " = END TEST = " );
}
