#include "TimeCall.h"

long compute(long n)
{
	return n * n;
}

int main()
{
	__int64 cost = time_call([] () { compute(10); });
}

