
#include <LunatiX/LX_Library.hpp>
#include <LunatiX/LX_Thread.hpp>
#include <LunatiX/LX_Timer.hpp>
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

const unsigned long NB_THREADS = 10;

struct msg_t
{
    unsigned int tid;
    std::string s;
};

}

void test_thread();
void test_thread_fail();
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
            LX_Timer::delay(128);
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
