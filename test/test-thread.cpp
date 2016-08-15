
#include <LunatiX/Lunatix_engine.hpp>
#include <stdexcept>

int foo0(LX_Multithreading::LX_Data data);
int foo1(LX_Multithreading::LX_Data data);
int foo2(LX_Multithreading::LX_Data data);
int foo3(LX_Multithreading::LX_Data data);


namespace
{
int val = 0;
LX_Multithreading::LX_Mutex mutex;
LX_Multithreading::LX_Mutex mutex2;
LX_Multithreading::LX_Cond cond;
LX_Multithreading::LX_ASyncChannel<int> c;

struct msg_t
{
    unsigned int tid;
    std::string s;
};

LX_Multithreading::LX_ASyncChannel<msg_t> sc;
LX_Multithreading::LX_ASyncChannel<msg_t> rc;

};

int countValue(LX_Multithreading::LX_Data data);
int countValueAgain(LX_Multithreading::LX_Data data);
int sigValue(LX_Multithreading::LX_Data data);

int sender(LX_Multithreading::LX_Data data);
int receiver(LX_Multithreading::LX_Data data);

int sender2(LX_Multithreading::LX_Data data);
int fwd(LX_Multithreading::LX_Data data);
int receiver2(LX_Multithreading::LX_Data data);

void test_thread();
void test_thread_fail();
void test_mutex();
void test_cond();
void test_channel();
void test_channel2();

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

    /*test_thread();
    test_thread_fail();
    test_mutex();
    test_cond();*/
    //test_channel();
    test_channel2();

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
    LX_Log::log("(#%x) Hello World! from foo1",SDL_GetThreadID(nullptr));
    return 0;
}

int foo2(LX_Multithreading::LX_Data data)
{
    LX_Log::log("(#%x) Hello World!",SDL_GetThreadID(nullptr));
    return 0;
}

int foo3(LX_Multithreading::LX_Data data)
{
    char * str = (char *) data;
    LX_Log::log("Thread <%s>#%x: Hello World!",str,SDL_GetThreadID(nullptr));
    return EX;
}

int countValue(LX_Multithreading::LX_Data data)
{
    LX_Log::log("countValue - New thread(#%x) is running",SDL_GetThreadID(nullptr));
    mutex.lock();
    for(int j = 0; j < 2; j++)
    {
        val++;
    }
    mutex.unlock();
    return 0;
}

int countValueAgain(LX_Multithreading::LX_Data data)
{
    LX_Log::log("countValueAgain - New thread(#%x) is running",SDL_GetThreadID(nullptr));
    mutex2.lock();
    for(int j = 0; j < 10; j++)
    {
        if(val == 4)
        {
            cond.wait(mutex2);
        }
        val++;
    }
    mutex2.unlock();
    return 0;
}

int sigValue(LX_Multithreading::LX_Data data)
{
    LX_Log::log("New signal thread(#%x) is running",SDL_GetThreadID(nullptr));
    for(int j = 0; j < 10; j++)
    {
        mutex2.lock();
        cond.broadcast();
        mutex2.unlock();
    }
    return 0;
}


void test_thread()
{
    LX_Log::log("   == TEST thread #1 ==   ");

    const unsigned long tid = SDL_GetThreadID(nullptr);

    LX_Log::log("(#%x): Basic thread #1 (create a joinable thread but do not start it)",
                tid);
    try
    {
        {
            LX_Multithreading::LX_Thread th1(foo0,"foo0",nullptr);
            LX_Log::log("(#%x): No mesage should be displayed",tid);
        }
        LX_Log::log("(#%x): SUCCESS - no crash",tid);
    }
    catch(...)
    {
        LX_Log::log("(#%x): FAILURE - CRITICAL → basic thread #1",tid);
    }

    LX_Log::log("(#%x): Basic thread #2 (create and start a joinable thread, but do not join it)",
                tid);
    try
    {
        {
            LX_Multithreading::LX_Thread th2(foo1,"foo1",nullptr);
            th2.start();
        }
        LX_Log::log("(#%x): Thread joined at destruction",tid);
        LX_Log::log("(#%x): SUCCESS - no crash",tid);
    }
    catch(...)
    {
        LX_Log::log("(#%x): FAILURE - CRITICAL → basic thread #2",
                    tid);
    }

    LX_Log::log("(#%x): Basic thread #3 (create, start and join the thread)",
                tid);
    try
    {
        {
            LX_Multithreading::LX_Thread th3(foo1,"foo2",nullptr);
            th3.start();
            th3.join();
        }
        LX_Log::log("(#%x): SUCCESS - no crash",tid);
    }
    catch(...)
    {
        LX_Log::log("(#%x): FAILURE - CRITICAL → basic thread #3",
                    tid);
    }


    LX_Log::log("(#%x): Basic thread #4 (create, start and detach the thread)",
                tid);
    try
    {
        {
            LX_Multithreading::LX_Thread th4(foo2,"foo2",nullptr);
            th4.startAndDetach();
            SDL_Delay(256);
        }
        LX_Log::log("(#%x): SUCCESS - no crash",tid);
    }
    catch(...)
    {
        LX_Log::log("(#%x): FAILURE - CRITICAL → basic thread #4",tid);
    }

    LX_Log::log("(#%x): Basic thread #5 (create, start, join the thread, and retrieve the result value from it)",
                tid);
    try
    {
        {
            char s[] = "foo3";
            LX_Multithreading::LX_Thread th5(foo3,s,s);
            th5.start();
            SDL_Delay(128);
            int ret;
            th5.join(&ret);

            if(ret == EX)
                LX_Log::log("(#%x): SUCCESS - good return value: %d",tid,EX);
            else
                LX_Log::log("(#%x): FAILURE - expected: %d; got: %d",tid,EX,ret);
        }
        LX_Log::log("(#%x): SUCCESS - no crash",tid);
    }
    catch(...)
    {
        LX_Log::log("(#%x): FAILURE - CRITICAL → basic thread #5",tid);
    }

    LX_Log::log("(#%x): Basic thread #6 (create, start the thread, stop and restart it)",
                tid);
    try
    {
        {
            LX_Multithreading::LX_Thread th6(foo2,"foo2",nullptr);
            th6.start();
            th6.join();
            LX_Log::log("(#%x): restart",tid);
            th6.start();
            th6.join();
            SDL_Delay(128);
        }
        LX_Log::log("(#%x): SUCCESS - no crash",tid);
    }
    catch(...)
    {
        LX_Log::log("(#%x): FAILURE - CRITICAL → basic thread #6",tid);
    }

    LX_Log::log("      == END TEST ==    ");
}


void test_thread_fail()
{
    LX_Log::log("   == TEST thread #2 ==   ");

    const unsigned long tid = SDL_GetThreadID(nullptr);

    LX_Log::log("(#%x): fail thread #1 (create a thread with a null function pointer)",
                tid);
    try
    {
        {
            LX_Multithreading::LX_Thread th1(nullptr,"nullptr",nullptr);
            th1.start();
            th1.join();
        }
        LX_Log::log("(#%x): FAILURE - should crash → #1",tid);
    }
    catch(std::invalid_argument& iv)
    {
        LX_Log::log("(#%x): %s",tid,iv.what());
        LX_Log::log("(#%x): SUCCESS - exception occurred",tid);
    }


    LX_Log::log("(#%x): fail thread #2 (create a thread with no function name → null)",
                tid);
    try
    {
        {
            LX_Multithreading::LX_Thread th2(foo3,nullptr,nullptr);
            th2.start();
            th2.join();
        }
        LX_Log::log("(#%x): FAILURE - should crash → #2",tid);
    }
    catch(...)
    {
        LX_Log::log("(#%x): SUCCESS - exception occurred",tid);
    }


    LX_Log::log("(#%x): fail thread #3 (join a thread that was not launched)",
                tid);
    try
    {
        {
            LX_Multithreading::LX_Thread th3(foo3,"foo3",nullptr);
            th3.join();
        }
        LX_Log::log("(#%x): FAILURE - should crash → #3",tid);
    }
    catch(std::invalid_argument& i)
    {
        LX_Log::log("(#%x): %s",tid,i.what());
        LX_Log::log("(#%x): SUCCESS - exception occurred",tid);
    }


    LX_Log::log("(#%x): fail thread #4 (join a thread that was already joined)",
                tid);
    try
    {
        {
            LX_Multithreading::LX_Thread th4(foo2,"foo2",nullptr);
            th4.start();
            th4.join();
            th4.join();
        }
        LX_Log::log("(#%x): FAILURE - should crash → #4",tid);
    }
    catch(std::invalid_argument& inv)
    {
        LX_Log::log("(#%x): %s",tid,inv.what());
        LX_Log::log("(#%x): SUCCESS - exception occurred",tid);
    }


    LX_Log::log("(#%x): fail thread #5 (join a detached thread)",tid);
    try
    {
        {
            LX_Multithreading::LX_Thread th5(foo2,"foo2",nullptr);
            th5.startAndDetach();
            th5.join();
        }
        LX_Log::log("(#%x): FAILURE - should crash → #5",tid);
    }
    catch(std::invalid_argument&)
    {
        LX_Log::log("(#%x): SUCCESS - exception occurred",tid);
    }

    LX_Log::log("      == END TEST ==    ");
}


void test_mutex()
{
    LX_Log::log("   == TEST mutex ==   ");

    const unsigned long tid = SDL_GetThreadID(nullptr);
    LX_Multithreading::LX_Thread th1(countValue,"countValue #1",nullptr);
    LX_Multithreading::LX_Thread th2(countValue,"countValue #2",nullptr);

    LX_Log::log("(#%x): Launching two thread that increment a global variable",tid);
    LX_Log::log("(#%x): from value = %d",tid,val);

    th1.start();
    th2.start();
    SDL_Delay(128);
    th1.join();
    th2.join();
    LX_Log::log("(#%x): result value = %d",tid,val);
    LX_Log::log("    == END TEST ==    ");
}


void test_cond()
{
    LX_Log::log("   == TEST condition ==   ");

    const unsigned long tid = SDL_GetThreadID(nullptr);
    val = 0;

    LX_Log::log("(#%x): Launching several threads that increment a global variable",tid);
    LX_Log::log("(#%x): Each thread will block at val = 4",tid);
    LX_Log::log("(#%x): until the signal thread awakes them",tid);

    LX_Multithreading::LX_Thread th1(countValueAgain,"countValueAgain #1",nullptr);
    LX_Multithreading::LX_Thread th2(countValueAgain,"countValueAgain #2",nullptr);
    LX_Multithreading::LX_Thread th3(countValueAgain,"countValueAgain #3",nullptr);
    LX_Multithreading::LX_Thread th4(countValueAgain,"countValueAgain #4",nullptr);
    LX_Multithreading::LX_Thread thsig(sigValue,"sigValue #2",nullptr);

    LX_Log::log("(#%x): Start the threads",tid);
    th1.start();
    th2.start();
    th3.start();
    th4.start();
    LX_Log::log("(#%x): Start the signal thread",tid);
    thsig.start();
    th1.join();
    th2.join();
    th3.join();
    th4.join();
    thsig.join();
    LX_Log::log("      == END TEST ==    ");
}


int sender(LX_Multithreading::LX_Data data)
{
    LX_Random::initRand();
    int n = LX_Random::xorshiftRand100();

    do
    {
        SDL_Delay(16);
        n = LX_Random::xorshiftRand100();
    }while(c.send(n));

    return 0;
}


int receiver(LX_Multithreading::LX_Data data)
{
    int n;

    SDL_Delay(1024);

    for(int i = 0; i < 8; i++)
   ; {
        c.recv(n);
        LX_Log::log("(#%x): received from the channel → %d",
                    SDL_GetThreadID(nullptr),n);
    }

    c.close();
    return 0;
}

/* forwarding */

int sender2(LX_Multithreading::LX_Data data)
{
    const int MAX_MSG = 10;
    LX_Random::initRand();
    int nb = 0;

    msg_t msg;
    msg.tid = LX_Random::xorshiftRand100();
    msg.s = "hello";

    while(nb < MAX_MSG)
    {
        msg.tid = LX_Random::xorshiftRand100();
        LX_Log::log("(#%x): SEND",SDL_GetThreadID(nullptr));
        if(!sc.send(msg))
        {
            sc.close();
            break;
        }
        nb++;
    }

    LX_Log::log("(#%x): OVER sender",SDL_GetThreadID(nullptr));
    return 0;
}


int fwd(LX_Multithreading::LX_Data data)
{
    int cpt = 0;
    const int N = 10;
    msg_t msg;

    while(sc.recv(msg))
    {
        LX_Log::log("(#%x): fwd → %d; %s",SDL_GetThreadID(nullptr),msg.tid,msg.s.c_str());
        rc.send(msg);

        cpt++;

        if(cpt == N)
        {
            LX_Log::log("(#%x): CLOSE ALL",SDL_GetThreadID(nullptr));
            sc.close();
            rc.close();
            break;
        }
    }
    LX_Log::log("(#%x): OVER fwd",SDL_GetThreadID(nullptr));
    return 0;
}


int receiver2(LX_Multithreading::LX_Data data)
{
    msg_t m;

    while(rc.recv(m))
    {
        LX_Log::log("(#%x): received from the channel → %d; %s",
                    SDL_GetThreadID(nullptr),m.tid,m.s.c_str());
    }

    LX_Log::log("(#%x): OVER recv",SDL_GetThreadID(nullptr));
    return 0;
}


void test_channel()
{
    LX_Log::log("   == TEST channel #1 ==   ");

    const unsigned long tid = SDL_GetThreadID(nullptr);
    LX_Multithreading::LX_Thread s1(sender,"sender #1",nullptr);
    LX_Multithreading::LX_Thread s2(sender,"sender #2",nullptr);
    LX_Multithreading::LX_Thread r(receiver,"receiver",nullptr);

    LX_Log::log("(#%x): Start the communication between the threads",tid);
    s1.start();
    s2.start();
    r.start();
    LX_Log::log("(#%x): ...",tid);
    s1.join();
    s2.join();
    r.join();
    LX_Log::log("(#%x): Done",tid);

    LX_Log::log("      == END TEST ==    ");
}


void test_channel2()
{
    LX_Log::log("   == TEST channel #2 ==   ");

    const unsigned long tid = SDL_GetThreadID(nullptr);
    LX_Multithreading::LX_Thread s1(sender2,"sender2 #1",nullptr);
    LX_Multithreading::LX_Thread s2(sender2,"sender2 #2",nullptr);
    LX_Multithreading::LX_Thread forwd(fwd,"fwd",nullptr);
    LX_Multithreading::LX_Thread r(receiver2,"receiver2 #1",nullptr);
    LX_Multithreading::LX_Thread r2(receiver2,"receiver2 #2",nullptr);

    LX_Log::log("(#%x): Start the communication between the threads",tid);
    s1.start();
    //s2.start();
    //SDL_Delay(16);
    forwd.start();
    r.start();
    //r2.start();

    LX_Log::log("(#%x): ...",tid);

    s1.join();
    //s2.join();
    forwd.join();
    r.join();
    //r2.join();

    LX_Log::log("(#%x): Done",tid);
    LX_Log::log("      == END TEST ==    ");
}
