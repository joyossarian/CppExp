#include "TimeCall.h"

#include <boost/thread.hpp>
#include <boost/random.hpp>
#include <iostream>
#include <limits>

int* GenerateMatrix(size_t n)
{
	boost::mt19937 rng(time(0));
	unsigned long matSize = (unsigned long)(n * n);
	boost::uniform_int<> ui(-100000, 100000);
	
	int* m = new int[matSize];
	for (unsigned long i = 0; i < matSize; ++i)
	{
		m[i] = ui(rng);
	}
	return m;
}

void FillMatrixMul(int m1[], int m2[], int mr[], size_t low, size_t high, size_t n)
{
	for (size_t i = low; i < high; ++i)
		for (size_t j = 0; j < n; ++j)
		{
			for (size_t k = 0; k < n; ++k)
			{
				mr[i * n + j] = m1[i * n + k] * m2 [k * n + j];
			}
		}		
}

int* MatrixMultiply(int m1[], int m2[], size_t n)
{
	int* mr = new int[n * n];
	memset((void*)mr, 0, sizeof(int) * n * n);
	

	boost::thread t1([=] {FillMatrixMul(m1, m2, mr, 0, n / 4, n);});
	boost::thread t2([=] {FillMatrixMul(m1, m2, mr, n / 4 + 1, n / 2, n);});
	boost::thread t3([=] {FillMatrixMul(m1, m2, mr, n / 2 + 1, 3 * n / 4, n);});
	boost::thread t4([=] {FillMatrixMul(m1, m2, mr, 3 * n / 4 + 1, n, n);});

	//for (size_t i = 0; i < n; ++i)
	//	for (size_t j = 0; j < n; ++j)
	//	{
	//		for (size_t k = 0; k < n; ++k)
	//		{
	//			mr[i * n + j] = m1[i * n + k] * m2 [k * n + j];
	//		}
	//	}		
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	return mr;
}




void execute(int m1[], int m2[], size_t mn)
{
	int* m3 = MatrixMultiply(m1, m2, mn);
	delete[] m1;
	delete[] m2;
	delete[] m3;
}

int main()
{
	size_t mn = 1000;
	int* m1 = GenerateMatrix(mn);
	int* m2 = GenerateMatrix(mn);
	std::cout << time_call([=] {execute(m1, m2, mn);}) << std::endl;
}
