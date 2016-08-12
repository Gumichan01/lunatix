
#include <LunatiX/Lunatix_engine.hpp>
#include <stdexcept>

int foo0(LX_Multithreading::LX_Data data);
int foo1(LX_Multithreading::LX_Data data);
int foo2(LX_Multithreading::LX_Data data);
int foo3(LX_Multithreading::LX_Data data);
char foo4(int data);

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
    test_thread_fail();

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

char foo4(int data)
{
    LX_Log::log("WHAT! → %d",data);
    return '\x00';
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
            LX_Log::log("(#%ld): No mesage should be displayed",tid);
        }
        LX_Log::log("(#%ld): SUCCESS - no crash",tid);
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
        LX_Log::log("(#%ld): Thread joined at destruction",tid);
        LX_Log::log("(#%ld): SUCCESS - no crash",tid);
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
        LX_Log::log("(#%ld): SUCCESS - no crash",tid);
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
            LX_Multithreading::LX_Thread th4(foo2,"foo2",nullptr);
            th4.start();
            th4.detach();
            SDL_Delay(512);
        }
        LX_Log::log("(#%ld): SUCCESS - no crash",tid);
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
            char s[] = "foo3";
            LX_Multithreading::LX_Thread th5(foo3,s,s);
            th5.start();
            SDL_Delay(1000);
            int ret;
            th5.join(&ret);

            if(ret == EX)
                LX_Log::log("(#%ld): SUCCESS - good return value: %d",tid,EX);
            else
                LX_Log::log("(#%ld): FAILURE - expected: %d; got: %d",tid,EX,ret);
        }
        LX_Log::log("(#%ld): SUCCESS - no crash",tid);
    }
    catch(...)
    {
        LX_Log::log("(#%ld): FAILURE - CRITICAL → basic thread #5",tid);
    }

    LX_Log::log("(#%ld): Basic thread #6 (create, start and detach the thread)",
                tid);
    try
    {
        {
            LX_Multithreading::LX_Thread th6(foo2,"foo2",nullptr);
            th6.start();
            th6.join();
            LX_Log::log("(#%ld): restart",tid);
            th6.start();
            th6.join();
            SDL_Delay(512);
        }
        LX_Log::log("(#%ld): SUCCESS - no crash",tid);
    }
    catch(...)
    {
        LX_Log::log("(#%ld): FAILURE - CRITICAL → basic thread #6",tid);
    }

    LX_Log::log("      == END TEST ==    ");
}


void test_thread_fail()
{
    LX_Log::log("   == TEST thread #2 ==   ");

    const unsigned long tid = SDL_GetThreadID(nullptr);

    LX_Log::log("(#%ld): fail thread #1 (create a thread with a null function pointer)",
                tid);
    try
    {
        {
            LX_Multithreading::LX_Thread th1(nullptr,"nullptr",nullptr);
            th1.start();
            th1.join();
        }
        LX_Log::log("(#%ld): FAILURE - should crash → #1",tid);
    }
    catch(std::invalid_argument& iv)
    {
        LX_Log::log("(#%ld): %s",tid,iv.what());
        LX_Log::log("(#%ld): SUCCESS - exception occurred",tid);
    }


    LX_Log::log("(#%ld): fail thread #2 (create a thread with no function name → null)",
                tid);
    try
    {
        {
            LX_Multithreading::LX_Thread th2(foo3,nullptr,nullptr);
            th2.start();
            th2.join();
        }
        LX_Log::log("(#%ld): FAILURE - should crash → #2",tid);
    }
    catch(...)
    {
        LX_Log::log("(#%ld): SUCCESS - exception occurred",tid);
    }


    LX_Log::log("(#%ld): fail thread #3 (join a thread that was not launched)",
                tid);
    try
    {
        {
            LX_Multithreading::LX_Thread th3(foo3,"foo3",nullptr);
            th3.join();
        }
        LX_Log::log("(#%ld): FAILURE - should crash → #3",tid);
    }
    catch(std::invalid_argument& i)
    {
        LX_Log::log("(#%ld): %s",tid,i.what());
        LX_Log::log("(#%ld): SUCCESS - exception occurred",tid);
    }


    LX_Log::log("(#%ld): fail thread #4 (join a thread that was already joined)",
                tid);
    try
    {
        {
            LX_Multithreading::LX_Thread th4(foo2,"foo2",nullptr);
            th4.start();
            th4.join();
            th4.join();
        }
        LX_Log::log("(#%ld): FAILURE - should crash → #4",tid);
    }
    catch(std::invalid_argument& inv)
    {
        LX_Log::log("(#%ld): %s",tid,inv.what());
        LX_Log::log("(#%ld): SUCCESS - exception occurred",tid);
    }


    LX_Log::log("(#%ld): fail thread #5 (detach a thread that was joined)",
                tid);
    try
    {
        {
            LX_Multithreading::LX_Thread th5(foo2,"foo2",nullptr);
            th5.start();
            th5.join();
            th5.detach();
        }
        LX_Log::log("(#%ld): FAILURE - should crash → #5",tid);
    }
    catch(std::invalid_argument&)
    {
        LX_Log::log("(#%ld): SUCCESS - exception occurred",tid);
    }


    LX_Log::log("(#%ld): fail thread #6 (join a detached thread)",tid);
    try
    {
        {
            LX_Multithreading::LX_Thread th6(foo2,"foo2",nullptr);
            th6.start();
            th6.detach();
            th6.join();
        }
        LX_Log::log("(#%ld): FAILURE - should crash → #6",tid);
    }
    catch(std::invalid_argument&)
    {
        LX_Log::log("(#%ld): SUCCESS - exception occurred",tid);
    }


    LX_Log::log("(#%ld): fail thread #7 (detach a detached thread)",tid);
    try
    {
        {
            LX_Multithreading::LX_Thread th7(foo2,"foo2",nullptr);
            th7.start();
            th7.detach();
            th7.detach();
        }
        LX_Log::log("(#%ld): FAILURE - should crash → #7",tid);
    }
    catch(std::invalid_argument&)
    {
        LX_Log::log("(#%ld): SUCCESS - exception occurred",tid);
    }

    LX_Log::log("(#%ld): fail thread #8 (detach a thread that has not been launched)",tid);
    try
    {
        {
            LX_Multithreading::LX_Thread th8(foo2,"foo2",nullptr);
            th8.detach();
        }
        LX_Log::log("(#%ld): FAILURE - should crash → #8",tid);
    }
    catch(std::invalid_argument&)
    {
        LX_Log::log("(#%ld): SUCCESS - exception occurred",tid);
    }


    LX_Log::log("(#%ld): fail thread #9 (detach and launch a thread)",tid);
    try
    {
        {
            LX_Multithreading::LX_Thread th9(foo2,"foo2",nullptr);
            th9.detach();
            th9.start();
        }
        LX_Log::log("(#%ld): FAILURE - should crash → #9",tid);
    }
    catch(std::invalid_argument&)
    {
        LX_Log::log("(#%ld): SUCCESS - exception occurred",tid);
    }

    LX_Log::log("      == END TEST ==    ");
}