/******************************************************************
文件名：		Timer.h
创建人：		zhaoweiwang
加注日期：	2013-4-5
描述：		高精度计时器类的实现
******************************************************************/
#ifndef _TIMER_H_
#define _TIMER_H_

#ifdef _WIN32
typedef __int64 i64 ;
#else
typedef long long i64;
#endif

class CPerfCounter {

public:
    CPerfCounter();
    ~CPerfCounter();
    void Start(void);
    void Stop(void);
    void Reset(void);
    double GetElapsedTime(void);

private:

    i64 _freq;
    i64 _clocks;
    i64 _start;
};

#endif

