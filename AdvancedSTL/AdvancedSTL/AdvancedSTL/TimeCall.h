#ifndef __TIME_CALL_H_
#define __TIME_CALL_H_

#include <Windows.h>

template <class Function>
__int64 time_call(Function&& f)
{
   __int64 begin = GetTickCount();
   f();
   return GetTickCount() - begin;
}


#endif