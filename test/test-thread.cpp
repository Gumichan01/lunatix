
#include <LunatiX/Lunatix_engine.hpp>

int foo0(LX_Multithreading::LX_Data data);
int foo1(LX_Multithreading::LX_Data data);
int foo2(LX_Multithreading::LX_Data data);
int foo3(LX_Multithreading::LX_Data data);

void test_thread();
void test_thread_fail();

#define EX 64

int main(int argc, char **argv)
{
    bool err = LX_Init();

    if(err)
        LX_Log::log("SUCCESS - Initialization OK");
    else
        LX_Log::log("SUCCESS - Initialization KO");

    LX_Log::log(" ==== TEST Multithread ==== ");
    LX_Log::setDebugMode();

    test_thread();
    //test_thread_fail();

    LX_Log::log(" ==== END TEST ==== ");
    LX_Quit();
    return 0;
}


int foo0(LX_Multithreading::LX_Data data)
{
    LX_Log::log("FAILURE - should not be called",SDL_GetThreadID(nullptr));
    return -1;
}

int foo1(LX_Multithreading::LX_Data data)
{
    LX_Log::log("(#%ld) Hello World! from foo1",SDL_GetThreadID(nullptr));
    return 0;
}

int foo2(LX_Multithreading::LX_Data data)
{
    LX_Log::log("(#%ld) Hello World!",SDL_GetThreadID(nullptr));
    return 0;
}

int foo3(LX_Multithreading::LX_Data data)
{
    char * str = (char *) data;
    LX_Log::log("Thread <%s>#%ld: Hello World!",str,SDL_GetThreadID(nullptr));
    return EX;
}

void test_thread()
{
    LX_Log::log("   == TEST thread #1 ==   ");

    const unsigned long tid = SDL_GetThreadID(nullptr);

    LX_Log::log("(#%ld): Basic thread #1 (create a joinable thread but do not start it)",
                tid);
    try
    {
        {
            LX_Multithreading::LX_Thread th1(foo0,"foo0",nullptr);
        }
        LX_Log::log("(#%ld): Thread destroyed, normally no failure message has been printed",
                    tid);
    }
    catch(...)
    {
        LX_Log::log("(#%ld): FAILURE - CRITICAL → basic thread #1",tid);
    }

    LX_Log::log("(#%ld): Basic thread #2 (create and start a joinable thread, but do not join it)",
                tid);
    try
    {
        {
            LX_Multithreading::LX_Thread th2(foo1,"foo1",nullptr);
            th2.start();
        }
        LX_Log::log("(#%ld): Thread destroyed, normally it has been joined at destruction",
                    tid);
    }
    catch(...)
    {
        LX_Log::log("(#%ld): FAILURE - CRITICAL → basic thread #2",
                    tid);
    }

    LX_Log::log("(#%ld): Basic thread #3 (create, start and join the thread)",
                tid);
    try
    {
        {
            LX_Multithreading::LX_Thread th3(foo1,"foo2",nullptr);
            th3.start();
            th3.join();
        }
        LX_Log::log("(#%ld): Thread destroyed",tid);
    }
    catch(...)
    {
        LX_Log::log("(#%ld): FAILURE - CRITICAL → basic thread #3",
                    tid);
    }


    LX_Log::log("(#%ld): Basic thread #4 (create, start and detach the thread)",
                tid);
    try
    {
        {
            LX_Multithreading::LX_Thread th3(foo2,"foo2",nullptr);
            th3.start();
            th3.detach();
            SDL_Delay(512);
        }
        LX_Log::log("(#%ld): Thread destroyed",tid);
    }
    catch(...)
    {
        LX_Log::log("(#%ld): FAILURE - CRITICAL → basic thread #4",tid);
    }

    LX_Log::log("(#%ld): Basic thread #5 (create, start, join the thread, and retrieve the result value from it)",
                tid);
    try
    {
        {
            char * s = "foo3";
            LX_Multithreading::LX_Thread th3(foo3,"foo3",s);
            th3.start();
            SDL_Delay(1000);
            int ret;
            th3.join(&ret);

            if(ret == EX)
                LX_Log::log("SUCCESS - good return value: %d",EX);
            else
                LX_Log::log("FAILURE - expected: %d; got: %d",EX,ret);
        }
        LX_Log::log("Thread destroyed");
    }
    catch(...)
    {
        LX_Log::log("(#%ld): FAILURE - CRITICAL → basic thread #5",tid);
    }

    LX_Log::log("      == END TEST ==    ");
}

















