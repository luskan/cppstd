#include <iostream>
#include <string>
#include <vector>
#include <ppl.h>
#include <concrtrm.h>
#include <windows.h>

bool isprime(int number) {

	if (number < 2) return false;
	if (number == 2) return true;
	if (number % 2 == 0) return false;
	for (int i = 3; (i*i) <= number; i += 2) {
		if (number % i == 0) return false;
	}
	return true;
}

int nthprime(int n) {
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