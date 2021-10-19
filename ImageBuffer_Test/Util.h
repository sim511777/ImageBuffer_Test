#pragma once

#include <windows.h>

double GetTime() {
    static LARGE_INTEGER freq;
    static BOOL callOnce = QueryPerformanceFrequency(&freq);
    
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return (double)count.QuadPart / freq.QuadPart;
}

double GetTimeMs() {
    return GetTime() * 1000.0;
}
