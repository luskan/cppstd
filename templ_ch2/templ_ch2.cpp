// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <memory>
#include <array>
#include <functional>
#include <cstring>

// as a rule of thumb you should always have all overloaded versions of a function declared before the function is called.


//
// Example presents error (UB) when mixing templates accepting and returning parameters by reference and by pointer.

template<typename T>
inline T const& max(T const& a, T const& b) {
	return a < b ? b : a;
}

inline char const* max(char const* a, char const* b) {
	return std::strcmp(a, b) < 0 ? b : a;
}

template<typename T>
inline T const& max(T const& a, T const& b, T const& c) {
	// Here max(a, b) will return temporary value, which will be returned further by reference causing UB.
	return max(max(a, b), c);
}

void mixedTemplateArgs() {
	const char* s1 = "ds1";
	const char* s2 = "ds2";
	const char* s3 = "ds3";
	const char* smax = ::max(s1, s2, s3); // warning C4172: returning address of local variable or temporary
}

//
// Explicit template argument types specification

template<typename T, typename T2, typename T3>
void specFoo1(const T& arg1, const T2& arg2, const T3& arg3) {
	std::cout << "specFoo1:" << arg1 << ", " << arg2 << ", " << arg3 << std::endl;
}

//template<typename T, typename T2, typename T3>
//void specFoo1(const T& arg1, const T2& args, const T3& arg3) {
//	std::cout << "specFoo1" << std::endl;
//}

template <typename RET, typename T1, typename T2>
RET specFoo2(const T1& arg1, const T2& arg2) {
	std::cout << "specFoo2: " << arg1 << ", " << arg2 << std::endl;
	return arg1 > arg2 ? arg1 : arg2;
}

void partialFuncTempl() {
	int a1=1;
	char a2 = 2;
	float a3 = 3.1;

	// fully specialized
	specFoo1<int, int, int>(a1, a2, a3);

	// partially specialized
	specFoo1<int, int>(a1, a2, a3);

	// Partial explicit argument list specification.
}

int main()
{
	//mixedTemplateArgs();

	partialFuncTempl();

	return 0;
}


