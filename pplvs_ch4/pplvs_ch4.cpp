#include <iostream>
#include <string>
#include <vector>
#include <ppl.h>
#include <concrtrm.h>
#include <windows.h>
#include <algorithm>
#include <numeric>
#include "../common/ppl_common.h"

#if _MSC_PLATFORM_TOOLSET <= 120
#include "../common/ppl_extras.h"
#endif

void example1() {
	std::vector<int> vec(1000);
	for (int n = 0; n < vec.size(); ++n)
		vec[n] = n;
	
	Concurrency::combinable<int> count([]() {return 0;});
	Concurrency::parallel_for_each(vec.cbegin(), vec.cend(), [&count, &vec](int i) {
		count.local() += isprime(vec[i]) ? 1 : 0;
	});

	std::cout << count.combine(std::plus<int>()) << std::endl;
}

void example2() {
	std::vector<int> vec(10000);
	for (int n = 0; n < vec.size(); ++n)
		vec[n] = n;

	int total = std::accumulate(vec.cbegin(), vec.cend(), 0, [](int total, int element) { return total + isprime(element)?1:0; });

	std::cout << total << std::endl;
}

struct CountPrimes
{
	int operator()(std::vector<int>::const_iterator beg, std::vector<int>::const_iterator end, int right) const {
		return right + std::accumulate(beg, end, 0, [](int total, int element) { return total + isprime(element) ? 1 : 0; });
	}
};

void example3() {
	std::vector<int> vec(10000);
	for (int n = 0; n < vec.size(); ++n)
		vec[n] = n;

	// Below code does not compile wit
	
#if _MSC_PLATFORM_TOOLSET <= 120
	using namespace ::Concurrency::samples;
#else
	using namespace ::Concurrency;
#endif
	int total = parallel_reduce(vec.cbegin(), vec.cend(), 0,
		
		//CountPrimes(), 
		[](std::vector<int>::const_iterator beg, std::vector<int>::const_iterator end, int right) -> int { 
			return right + std::accumulate(beg, end, 0, [](int total, int element) { return total + isprime(element) ? 1 : 0; });
		},
		
		std::plus<int>()
	);
	std::cout << total << std::endl;
}

int main() {
	TimedRun(example1, "example1() - Parallel Aggregation pattern");
	TimedRun(example2, "example2() - Sequential Aggregation - accumulate");
	TimedRun(example3, "example3() - Sequential Aggregation - accumulate in reduce");
	getchar();
}