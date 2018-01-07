
#include <LunatiX/LX_Library.hpp>
#include <LunatiX/LX_Thread.hpp>
#include <LunatiX/LX_Sync.hpp>
#include <LunatiX/LX_Timer.hpp>
#include <LunatiX/LX_Channel.hpp>
#include <LunatiX/LX_Random.hpp>
#include <LunatiX/LX_Log.hpp>
#include <system_error>
#include <functional>
#include <sstream>
#include <vector>

void foo0();
void foo1();
void foo2();
void foo3(char * data);


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

}

void countValue();
void countValueAgain();
void sigValue();

void sender();
void receiver();

void sender2();
void fwd();
void receiver2();

void vsender(const std::vector<int>& v);
void vreceiver();

void test_thread();
void test_thread_fail();
void test_mutex();
void test_cond();
void test_channel();
void test_channel2();
void test_channel3();
void test_async();

unsigned long fact_(unsigned long n, unsigned long acc) noexcept;
unsigned long fact(long n);

unsigned long fact_(unsigned long n, unsigned long acc) noexcept
{
    if(n == 0 || n == 1)
        return acc;

    return fact_(n - 1, acc * n);
}

unsigned long fact(long n)
{
    if(n < 0)
        throw std::invalid_argument("n is negative");

    return fact_(static_cast<unsigned long>(n), 1);
}

int main(int argc, char **argv)
{
    LX_Log::log(" ==== TEST Multithread ==== ");
    LX_Log::setDebugMode();

    test_thread();
    test_thread_fail();
    test_mutex();
    test_cond();
    test_channel();
    test_channel2();
    test_channel3();
    test_async();

    LX_Log::log(" ==== END TEST ==== ");
    LX_Quit();
    return 0;
}


void foo0()
{
    LX_Log::log("(#%x) Hello World! from foo0", LX_Multithreading::getCurrentThreadID());
}

void foo1()
{
    LX_Log::log("(#%x) Hello World! from foo1", LX_Multithreading::getCurrentThreadID());
}

void foo2()
{
    LX_Log::log("(#%x) Hello World!", LX_Multithreading::getCurrentThreadID());
}

void foo3(char * data)
{
    LX_Log::log("Thread <%s>#%x: Hello World!", data, LX_Multithreading::getCurrentThreadID());
}

void countValue()
{
    LX_Log::log("countValue - New thread(#%x) is running",LX_Multithreading::getCurrentThreadID());
    mutex.lock();
    for(int j = 0; j < 128; j++)
    {
        val++;
    }
    mutex.unlock();
}

void countValueAgain()
{
    LX_Log::log("countValueAgain - New thread(#%x) is running",LX_Multithreading::getCurrentThreadID());
    mutex2.lock();
    w += 1;
    cond.wait(mutex2);
    w -= 1;
    mutex2.unlock();
}

void sigValue()
{
    LX_Log::log("New signal thread(#%x) is running",LX_Multithreading::getCurrentThreadID());

    while(w > 0)
    {
        cond.signal();
        LX_Timer::delay(100);
    }
}


void test_thread()
{
    LX_Log::log("   == TEST thread #1 ==   ");

    const size_t tid = LX_Multithreading::getCurrentThreadID();

    LX_Log::log("(#%x): Basic thread #1 (create a joinable thread)",
                tid);
    try
    {
        {
            LX_Multithreading::LX_Thread(false, foo0).join();
            LX_Multithreading::LX_Thread(false, foo1).join();
        }
        LX_Log::log("(#%x): SUCCESS - no crash",tid);
    }
    catch(...)
    {
        LX_Log::log("(#%x): FAILURE - CRITICAL → basic thread #1", tid);
    }

    LX_Log::log("(#%x): Basic thread #3 (create, and detach the thread)",
                tid);
    try
    {
        {
            LX_Multithreading::LX_Thread th4(true, foo2);
            LX_Timer::delay(256);
        }
        LX_Log::log("(#%x): SUCCESS - no crash",tid);
    }
    catch(...)
    {
        LX_Log::log("(#%x): FAILURE - CRITICAL → basic thread #4",tid);
    }

    LX_Log::log("(#%x): Basic thread #4 (create the thread, do something, and join the thread",
                tid);
    try
    {
        {
            char s[] = "foo3";
            LX_Multithreading::LX_Thread th5(false, foo3, s);
            LX_Timer::delay(128);
            th5.join();
        }
        LX_Log::log("(#%x): SUCCESS - no crash",tid);
    }
    catch(...)
    {
        LX_Log::log("(#%x): FAILURE - CRITICAL → basic thread #5",tid);
    }

    LX_Log::log("      == END TEST ==    ");
}


void test_thread_fail()
{
    LX_Log::log("   == TEST thread #2 ==   ");

    const size_t tid = LX_Multithreading::getCurrentThreadID();

    LX_Log::log("(#%x): fail thread #1 (join a thread that was already joined)",
                tid);
    try
    {
        {
            LX_Multithreading::LX_Thread th4(false, foo2);
            th4.join();
            th4.join();
        }
        LX_Log::log("(#%x): FAILURE - should crash → #4", tid);
    }
    catch(std::system_error& inv)
    {
        LX_Log::log("(#%x): %s", tid, inv.what());
        LX_Log::log("(#%x): SUCCESS - exception occurred", tid);
    }
    catch(...)
    {
        LX_Log::log("(#%x): ERROR - unknown exception", tid);
    }


    LX_Log::log("(#%x): fail thread #2 (join a detached thread)",tid);
    try
    {
        {
            LX_Multithreading::LX_Thread th5(true,foo2);
            th5.join();
        }
        LX_Log::log("(#%x): FAILURE - should crash → #5",tid);
    }
    catch(std::system_error& inv)
    {
        LX_Log::log("(#%x): %s", tid, inv.what());
        LX_Log::log("(#%x): SUCCESS - exception occurred", tid);
    }
    catch(...)
    {
        LX_Log::log("(#%x): ERROR - unknown exception", tid);
    }

    LX_Log::log("      == END TEST ==    ");
}


void test_mutex()
{
    LX_Log::log("   == TEST mutex ==   ");

    const size_t tid = LX_Multithreading::getCurrentThreadID();

    LX_Log::log("(#%x): Launching two thread that increment a global variable",tid);
    LX_Log::log("(#%x): from value = %d", tid, val);

    LX_Multithreading::LX_Thread th1(false, countValue);
    LX_Multithreading::LX_Thread th2(false, countValue);

    LX_Timer::delay(128);
    th1.join();
    th2.join();

    LX_Log::log("(#%x): result value = %d", tid, val);
    LX_Log::log("    == END TEST ==    \n");
}


void test_cond()
{
    LX_Log::log("   == TEST condition ==   ");

    const size_t tid = LX_Multithreading::getCurrentThreadID();
    mutex2.lock();
    val = 0;
    mutex2.unlock();

    LX_Log::log("(#%x): Launching several threads that increment a global variable",tid);
    LX_Log::log("(#%x): Each thread will block at val = 4",tid);
    LX_Log::log("(#%x): until the signal thread awakes them",tid);

    LX_Log::log("(#%x): Start the threads", tid);
    LX_Multithreading::LX_Thread th1(false, countValueAgain);
    LX_Multithreading::LX_Thread th2(false, countValueAgain);
    LX_Multithreading::LX_Thread th3(false, countValueAgain);
    LX_Multithreading::LX_Thread th4(false, countValueAgain);

    LX_Timer::delay(100);

    LX_Log::log("(#%x): Start and detach the signal thread",tid);
    LX_Multithreading::LX_Thread(false, sigValue).join();

    th1.join();
    th2.join();
    th3.join();
    th4.join();

    LX_Log::log("(#%x): result value = %d",tid,val);
    LX_Log::log("      == END TEST ==    \n");
}


void sender()
{
    LX_Random::initRand();
    int n = 0;

    do
    {
        LX_Timer::delay(50);
    }
    while(c.send(++n));
}


void receiver()
{
    int n;
    std::vector<int> vint;
    const size_t tid = LX_Multithreading::getCurrentThreadID();

    for(int i = 0; i < 20; i++)
    {
        c.recv(n);
        LX_Log::log("(#%x): received from the channel → %d", tid, n);
        vint.push_back(n);
    }

    c.close();
    for(size_t i = 0; i < vint.size(); i++)
    {
        if(vint[i] != static_cast<int>(i) + 1)
        {
            LX_Log::log("(#%x): FAILURE - cannot get the good values", tid);
            return;
        }
    }

    LX_Log::log("(#%x): SUCCES - good values", tid);
}

/// forwarding

void sender2()
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

    LX_Log::log("(#%x): END sender",LX_Multithreading::getCurrentThreadID());
}


void fwd()
{
    int cpt = 0;
    const int N = 10;
    msg_t msg;

    while(sc.recv(msg))
    {
        LX_Log::log("(#%x): fwd → %d; %s",LX_Multithreading::getCurrentThreadID(),
                    msg.tid, msg.s.c_str());

        rc.send(msg);
        cpt++;

        if(cpt == N)
        {
            LX_Log::log("(#%x): CLOSE THE CHANNELS", LX_Multithreading::getCurrentThreadID());
            sc.close();
            rc.close();
            break;
        }
    }
    LX_Log::log("(#%x): END fwd",LX_Multithreading::getCurrentThreadID());
}


void receiver2()
{
    msg_t m;

    while(rc.recv(m))
    {
        LX_Log::log("(#%x): received from the channel → %d; %s",
                    LX_Multithreading::getCurrentThreadID(), m.tid, m.s.c_str());
    }

    LX_Log::log("(#%x): END recv", LX_Multithreading::getCurrentThreadID());
}


void test_channel()
{
    LX_Log::log("   == TEST channel #1 ==   ");

    const size_t tid = LX_Multithreading::getCurrentThreadID();
    LX_Log::log("(#%x): Start the communication between the threads — int", tid);
    LX_Log::log("(#%x): ...",tid);

    LX_Multithreading::LX_Thread s(false, sender);
    LX_Multithreading::LX_Thread r(false, receiver);

    s.join();
    r.join();
    LX_Log::log("(#%x): Done",tid);

    LX_Log::log("      == END TEST ==    ");
}


void test_channel2()
{
    LX_Log::log("   == TEST channel #2 ==   ");

    const size_t tid = LX_Multithreading::getCurrentThreadID();

    LX_Log::log("(#%x): Start the communication between the threads — messages", tid);
    LX_Log::log("(#%x): ...",tid);
    LX_Multithreading::LX_Thread s(false, sender2);
    LX_Multithreading::LX_Thread forwd(false, fwd);
    LX_Multithreading::LX_Thread r(false, receiver2);

    LX_Timer::delay(1000);
    r.join();
    forwd.join();
    s.join();

    LX_Log::log("(#%x): Done", tid);
    LX_Log::log("      == END TEST ==    ");
}


void vsender(const std::vector<int>& v)
{
    LX_Log::log("(#%x): running",LX_Multithreading::getCurrentThreadID());
    c2.vsend(v.begin(), v.end());
}

void vreceiver()
{
    const unsigned int SZ = 32;
    std::vector<int> v;
    std::ostringstream ss;

    LX_Log::log("(#%x): running",LX_Multithreading::getCurrentThreadID());
    while(c2.vrecv(v, SZ));

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

    const size_t tid = LX_Multithreading::getCurrentThreadID();
    std::vector<int> v1 = {1,2,4,8,16,32};
    std::vector<int> v2 = {3,5,7,11,17,35};

    LX_Log::log("(#%x): Start the communication between the threads", tid);
    LX_Log::log("(#%x): ...", tid);
    LX_Multithreading::LX_Thread s1(true, vsender, v1);
    LX_Multithreading::LX_Thread s2(true, vsender, v2);
    LX_Multithreading::LX_Thread r(false, vreceiver);

    LX_Timer::delay(1000);
    c2.close();
    r.join();

    std::string str;
    result.recv(str);
    LX_Log::log("(#%x): Received from the receiver thread", tid);
    LX_Log::log("(#%x): %s", tid, str.c_str());

    LX_Log::log("(#%x): Done",tid);
    LX_Log::log("      == END TEST ==    ");
}

void test_async()
{
    LX_Log::log("   == TEST async task ==   ");

    const size_t tid = LX_Multithreading::getCurrentThreadID();
    LX_Log::log("(#%x): AsyncTask - normal case", tid);
    LX_Random::initRand();

    long param1 = static_cast<long>(LX_Random::crand() % 10);
    long param2 = static_cast<long>(LX_Random::crand() % 10);
    unsigned long expected1 = fact(param1);
    unsigned long expected2 = fact(param2);

    LX_Multithreading::LX_ASyncTask<unsigned long> async(fact, param1);

    LX_Log::log("(#%x): AsyncTask - simulate synchonous", tid);
    unsigned long r = LX_Multithreading::LX_ASyncTask<unsigned long>(fact, param2).getResult();
    LX_Log::log("(#%x): AsyncTask - simulate synchonous DONE", tid);

    LX_Log::log("(#%x): sync -  %u | %u", tid, r, expected2);

    if(r == expected2)
        LX_Log::log("(#%x): SUCCESS - sync OK", tid);
    else
        LX_Log::log("(#%x): FAILURE - sync KO", tid);

    LX_Log::log("(#%x): AsyncTask - normal case - get result", tid);

    r = async.getResult();
    LX_Log::log("(#%x): async - %u | %u", tid, r, expected1);

    if(r == expected1)
        LX_Log::log("(#%x): SUCCESS - normal case -  OK", tid);
    else
        LX_Log::log("(#%x): FAILURE - normal case - KO", tid);


    try
    {
        LX_Multithreading::LX_ASyncTask<unsigned long>(fact, -1L).getResult();
        LX_Log::log("(#%x): FAILURE - an exception should occur", tid);
    }
    catch(const std::invalid_argument& inv)
    {
        LX_Log::log("(#%x): SUCCESS - %s - OK", tid, inv.what());
    }

    LX_Log::log("      == END TEST ==    ");
}
