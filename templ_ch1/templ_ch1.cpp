// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <memory>
#include <array>
#include <functional>

template<typename T>
inline T const& max(T const& a, T const& b) {
	return a < b ? b : a;
}

inline char const* max(char const* a, char const* b) {
	return std::strcmp(a, b) < 0 ? b : a;
}

template<typename T>
inline T const& max(T const& a, T const& b, T const& c) {
	return max(max(a, b), c);
}

int main()
{
	const char* s1 = "ds1";
	const char* s2 = "ds2";
	const char* s3 = "ds3";
	const char* smax = ::max(s1, s2, s3); // warning C4172: returning address of local variable or temporary

	return 0;
}


