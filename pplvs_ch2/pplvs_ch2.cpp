#include <iostream>
#include <string>
#include <vector>
#include <ppl.h>
#include <concrtrm.h>
#include <windows.h>
#include <crtdbg.h>

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

inline int nthprime(int n) {
	int np = 1;
	int np_test = 2;
	auto cancelTimer = GetTickCount();
	while (true) {
		bool isp = true;
		for (int i = 2; i < np_test; ++i) {
			if ((np_test % i) == 0) {
				isp = false;
				break;
			}
		}
		if ((GetTickCount() - cancelTimer) > 1000) {
			cancelTimer = GetTickCount();
			if (Concurrency::Context::IsCurrentTaskCollectionCanceling())
				return 0;
		}
		if (np == n && isp)
			break;
		if (isp)
			np++;
		np_test++;
	}
	return np_test;
}

void example1() {
	std::vector<int> primes(1000);
	for (int n = 0; n < primes.size(); n++)
		primes[n] = nthprime(n+1);
}

void example1_parallel_for() {
	std::vector<int> primes(1000);
	Concurrency::parallel_for(0u, primes.size(), [&](size_t n) {
		primes[n] = nthprime(n + 1);
	});
}

void example1_parallel_for_fixed() {
	std::vector<int> primes(1000);
	size_t stepSize = primes.size() / (Concurrency::GetProcessorCount());
	Concurrency::parallel_for(0u, primes.size(), stepSize, [&](size_t n) {
		primes[n] = nthprime(n + 1);
	});
}

void example2_parallel_for_with_exception() {
	std::vector<int> primes(1000);
	size_t stepSize = primes.size() / (Concurrency::GetProcessorCount());
	try {
		Concurrency::parallel_for(0u, primes.size(), stepSize, [&](size_t n) {
			primes[n] = nthprime(n + 1);
			if (n > 10) {
				std::cout << "example2_parallel_for_with_exception: Throwing !" << std::endl;
				throw "excp";
			}
		});
	}
	catch (...) {}
}

void example3_parallel_for_with_cancel() {
	std::vector<int> primes(1000000);
	size_t stepSize = primes.size() / (Concurrency::GetProcessorCount());
	Concurrency::task_group tg;
	tg.run([&]() {
		try {
			Concurrency::parallel_for(0u, primes.size(), stepSize, [&](size_t n) {
				primes[n] = nthprime(n + 1);
				if (tg.is_canceling()) {
					std::cout << "example3_parallel_for_with_cancel: cancelling !" << std::endl;
				}
			});
		}
		catch (...) {}
	});
	Concurrency::wait(3000);
	tg.cancel();
	tg.wait();
}

void example4_parallel_invoke() {
	std::vector<int> primes(1000000);
	size_t stepSize = primes.size() / (Concurrency::GetProcessorCount());
	Concurrency::task_group tg;
	tg.run([&]() {
		Concurrency::critical_section cs;
		Concurrency::parallel_invoke(
			[&] {auto n = nthprime(100); Concurrency::critical_section::scoped_lock lock(cs); std::cout << "100 : " << n << std::endl;},
			[&] {auto n = nthprime(101); Concurrency::critical_section::scoped_lock lock(cs); std::cout << "101 : " << n << std::endl;},
			[&] {auto n = nthprime(102); Concurrency::critical_section::scoped_lock lock(cs); std::cout << "102 : " << n << std::endl;},
			[&] {auto n = nthprime(103); Concurrency::critical_section::scoped_lock lock(cs); std::cout << "103 : " << n << std::endl;},
			[&] {auto n = nthprime(104); Concurrency::critical_section::scoped_lock lock(cs); std::cout << "104 : " << n << std::endl;}
			);
	});
	tg.wait();
}

int main() {
	TimedRun(example1, "example1() - non parallel");
	TimedRun(example1_parallel_for, "example1_parallel_for() - parallel");
	TimedRun(example1_parallel_for_fixed, "example1_parallel_for_fixed() - parallel fixed step");
	TimedRun(example2_parallel_for_with_exception, "example2_parallel_for_with_exception");
	TimedRun(example3_parallel_for_with_cancel, "example3_parallel_for_with_cancel");
	TimedRun(example4_parallel_invoke, "example4_parallel_invoke");
	getchar();
}