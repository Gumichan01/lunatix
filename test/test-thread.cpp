
#include <LunatiX/Lunatix.hpp>
#include <stdexcept>
#include <sstream>

void foo0(LX_Multithreading::LX_Data data);
void foo1(LX_Multithreading::LX_Data data);
void foo2(LX_Multithreading::LX_Data data);
void foo3(LX_Multithreading::LX_Data data);


namespace
{
int val = 0;
unsigned int w = 0;
LX_Multithreading::LX_Mutex mutex;
LX_Multithreading::LX_Mutex mutex2;
LX_Multithreading::LX_Cond cond;
LX_Multithreading::LX_Channel<int> c;
LX_Multithreading::LX_Channel<int> c2;
LX_Multithreading::LX_Channel<std::string> result;

struct msg_t
{
    unsigned int tid;
    std::string s;
};

LX_Multithreading::LX_Channel<msg_t> sc;
LX_Multithreading::LX_Channel<msg_t> rc;
};

void countValue(LX_Multithreading::LX_Data data);
void countValueAgain(LX_Multithreading::LX_Data data);
void sigValue(LX_Multithreading::LX_Data data);

void sender(LX_Multithreading::LX_Data data);
void receiver(LX_Multithreading::LX_Data data);

void sender2(LX_Multithreading::LX_Data data);
void fwd(LX_Multithreading::LX_Data data);
void receiver2(LX_Multithreading::LX_Data data);

void vsender(LX_Multithreading::LX_Data data);
void vreceiver(LX_Multithreading::LX_Data data);

void test_thread();
void test_thread_fail();
void test_mutex();
void test_cond();
void test_channel();
void test_channel2();
void test_channel3();


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
    test_mutex();
    test_cond();
    test_channel();
    test_channel2();
    test_channel3();

    LX_Log::log(" ==== END TEST ==== ");
    LX_Quit();
    return 0;
}


void foo0(LX_Multithreading::LX_Data data)
{
    LX_Log::log("FAILURE - should not be called",LX_Multithreading::getID());
}

void foo1(LX_Multithreading::LX_Data data)
{
    LX_Log::log("(#%x) Hello World! from foo1",LX_Multithreading::getID());
}

void foo2(LX_Multithreading::LX_Data data)
{
    LX_Log::log("(#%x) Hello World!",LX_Multithreading::getID());
}

void foo3(LX_Multithreading::LX_Data data)
{
    char * str = (char *) data;
    LX_Log::log("Thread <%s>#%x: Hello World!",str,LX_Multithreading::getID());
}

void countValue(LX_Multithreading::LX_Data data)
{
    LX_Log::log("countValue - New thread(#%x) is running",LX_Multithreading::getID());
    mutex.lock();
    for(int j = 0; j < 128; j++)
    {
        val++;
    }
    mutex.unlock();
}

void countValueAgain(LX_Multithreading::LX_Data data)
{
    LX_Log::log("countValueAgain - New thread(#%x) is running",LX_Multithreading::getID());
    mutex2.lock();
    for(int j = 0; j < 10; j++)
    {
        if(val == 10)
        {
            w += 1;
            cond.wait(mutex2);
            w -= 1;
        }
        val++;
    }
    mutex2.unlock();
}

void sigValue(LX_Multithreading::LX_Data data)
{
    LX_Log::log("New signal thread(#%x) is running",LX_Multithreading::getID());

    while(w > 0)
    {
        mutex2.lock();
        cond.signal();
        mutex2.unlock();
    }
}


void test_thread()
{
    LX_Log::log("   == TEST thread #1 ==   ");

    const unsigned long tid = LX_Multithreading::getID();

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

    LX_Log::log("(#%x): Basic thread #5 (create, start, do something, and join the thread",
                tid);
    try
    {
        {
            char s[] = "foo3";
            LX_Multithreading::LX_Thread th5(foo3,s,s);
            th5.start();
            SDL_Delay(128);
            th5.join();
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

    const unsigned long tid = LX_Multithreading::getID();

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

    const unsigned long tid = LX_Multithreading::getID();
    LX_Multithreading::LX_Thread th1(countValue,"countValue #1",nullptr);
    LX_Multithreading::LX_Thread th2(countValue,"countValue #2",nullptr);

    LX_Log::log("(#%x): Launching two thread that increment a global variable",tid);
    LX_Log::log("(#%x): from value = %d",tid,val);

    th1.start();
    th2.start();
    th1.join();
    th2.join();
    SDL_Delay(128);
    LX_Log::log("(#%x): result value = %d",tid,val);
    LX_Log::log("    == END TEST ==    \n");
}


void test_cond()
{
    LX_Log::log("   == TEST condition ==   ");

    const unsigned long tid = LX_Multithreading::getID();
    mutex2.lock();
    val = 0;
    mutex2.unlock();

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
    SDL_Delay(256);

    LX_Log::log("(#%x): Start and detach the signal thread",tid);
    thsig.startAndDetach();
    th1.join();
    th2.join();
    th3.join();
    th4.join();
    LX_Log::log("(#%x): result value = %d",tid,val);
    LX_Log::log("      == END TEST ==    \n");
}


void sender(LX_Multithreading::LX_Data data)
{
    LX_Random::initRand();
    int n = LX_Random::xorshiftRand100();

    do
    {
        SDL_Delay(16);
        n = LX_Random::xorshiftRand100();
    }
    while(c.send(n));
}


void receiver(LX_Multithreading::LX_Data data)
{
    int n;

    for(int i = 0; i < 8; i++)
    {
        c.recv(n);
        LX_Log::log("(#%x): received from the channel → %d",
                    LX_Multithreading::getID(),n);
    }

    c.close();
}

/// forwarding

void sender2(LX_Multithreading::LX_Data data)
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

        if(!sc.send(msg))
        {
            sc.close();
            break;
        }
        nb++;
    }

    LX_Log::log("(#%x): END sender",LX_Multithreading::getID());
}


void fwd(LX_Multithreading::LX_Data data)
{
    int cpt = 0;
    const int N = 10;
    msg_t msg;

    while(sc.recv(msg))
    {
        LX_Log::log("(#%x): fwd → %d; %s",LX_Multithreading::getID(),msg.tid,msg.s.c_str());
        rc.send(msg);

        cpt++;

        if(cpt == N)
        {
            LX_Log::log("(#%x): CLOSE THE CHANNELS",LX_Multithreading::getID());
            sc.close();
            rc.close();
            break;
        }
    }
    LX_Log::log("(#%x): END fwd",LX_Multithreading::getID());
}


void receiver2(LX_Multithreading::LX_Data data)
{
    msg_t m;

    while(rc.recv(m))
    {
        LX_Log::log("(#%x): received from the channel → %d; %s",
                    LX_Multithreading::getID(),m.tid,m.s.c_str());
    }

    LX_Log::log("(#%x): END recv",LX_Multithreading::getID());
}


void test_channel()
{
    LX_Log::log("   == TEST channel #1 ==   ");

    const unsigned long tid = LX_Multithreading::getID();
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

    const unsigned long tid = LX_Multithreading::getID();
    LX_Multithreading::LX_Thread s1(sender2,"sender2 #1",nullptr);
    LX_Multithreading::LX_Thread s2(sender2,"sender2 #2",nullptr);
    LX_Multithreading::LX_Thread forwd(fwd,"fwd",nullptr);
    LX_Multithreading::LX_Thread r(receiver2,"receiver2 #1",nullptr);
    LX_Multithreading::LX_Thread r2(receiver2,"receiver2 #2",nullptr);

    LX_Log::log("(#%x): Start the communication between the threads",tid);
    s1.start();
    s2.start();
    forwd.start();
    r.start();
    r2.start();

    LX_Log::log("(#%x): ...",tid);

    s1.join();
    s2.join();
    forwd.join();
    r.join();
    r2.join();

    LX_Log::log("(#%x): Done",tid);
    LX_Log::log("      == END TEST ==    ");
}


void vsender(LX_Multithreading::LX_Data data)
{
    if(data == nullptr)
        return;

    LX_Log::log("(#%x): running",LX_Multithreading::getID());
    std::vector<int> v = *((std::vector<int> *) data);
    c2.vsend(v);
}

void vreceiver(LX_Multithreading::LX_Data data)
{
    const unsigned int SZ = 32;
    std::vector<int> v;
    std::ostringstream ss;

    LX_Log::log("(#%x): running",LX_Multithreading::getID());
    while(c2.vrecv(v,SZ));

    for(int n: v)
    {
        ss << n << " ";
    }
    const std::string tmp(ss.str());
    result.send(tmp);
    result.close();
}


void test_channel3()
{
    LX_Log::log("   == TEST channel #3 ==   ");

    const unsigned long tid = LX_Multithreading::getID();
    std::vector<int> v1 = {1,2,4,8,16,32};
    std::vector<int> v2 = {3,5,7,11,17,35};
    LX_Multithreading::LX_Thread s1(vsender,"vsender #1",&v1);
    LX_Multithreading::LX_Thread s2(vsender,"vsender #2",&v2);
    LX_Multithreading::LX_Thread r(vreceiver,"vreceiver",nullptr);

    LX_Log::log("(#%x): Start the communication between the threads",tid);
    s1.start();
    s2.start();
    r.start();

    // Join
    s1.join();
    s2.join();
    c2.close();
    r.join();

    std::string str;
    result.recv(str);
    LX_Log::log("(#%x): Received from the receiver thread",tid);
    LX_Log::log("(#%x): %s",tid,str.c_str());

    LX_Log::log("(#%x): Done",tid);
    LX_Log::log("      == END TEST ==    ");
}
