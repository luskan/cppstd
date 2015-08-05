#if !defined(PPL_COMMON_H)
#define PPL_COMMON_H

template<typename Func>
void TimedRun(Func test, std::string label)
{
	LARGE_INTEGER begin, end, freq;
	QueryPerformanceCounter(&begin);

	// invoke the function
	test();

	// print timings
	QueryPerformanceCounter(&end);

	QueryPerformanceFrequency(&freq);

	double result = (end.QuadPart - begin.QuadPart) / (double)freq.QuadPart;
	printf("%s : %4.2f ms\n", label.c_str(), result * 1000);
}

bool isprime(int number);
int nthprime(int n);

#endif