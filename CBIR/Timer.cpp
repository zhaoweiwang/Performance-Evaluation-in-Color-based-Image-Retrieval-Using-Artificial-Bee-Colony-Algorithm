/******************************************************************
文件名：		Timer.cpp
创建人：		zhaoweiwang
加注日期：	2013-4-5
描述：		高精度计时器类的实现
******************************************************************/
#include "stdafx.h"

#include "Timer.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

CPerfCounter::CPerfCounter() : _clocks(0), _start(0)
{

#ifdef _WIN32
    QueryPerformanceFrequency((LARGE_INTEGER *)&_freq);
#else
    _freq = 1000;
#endif

}

CPerfCounter::~CPerfCounter()
{
    // EMPTY!
}

void CPerfCounter::Start(void)
{
#ifdef _WIN32
    QueryPerformanceCounter((LARGE_INTEGER *)&_start);
#else
    struct timeval s;
    gettimeofday(&s, 0);
    _start = (i64)s.tv_sec * 1000 + (i64)s.tv_usec / 1000;
#endif
}

void CPerfCounter::Stop(void)
{
    i64 n;

#ifdef _WIN32
    QueryPerformanceCounter((LARGE_INTEGER *)&n);
#else
    struct timeval s;
    gettimeofday(&s, 0);
    n = (i64)s.tv_sec * 1000 + (i64)s.tv_usec / 1000;
#endif

    n -= _start;
    _start = 0;
    _clocks += n;
}

void CPerfCounter::Reset(void)
{
    _clocks = 0;
}

double CPerfCounter::GetElapsedTime(void)
{
    return (double)_clocks / (double)_freq;

}

