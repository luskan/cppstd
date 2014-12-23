// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <memory>
#include <array>
#include <vector>
#include <functional>
#include <algorithm>

// VAL - can be a pointer but it must be a pointer to object with external linkage.
//       ie. string literals are objects with internal linkage (two string literals
//       with the same value but in different modules are different objects).

template <typename T, int VAL>
T addValue(T const& x) {
	return x + VAL;
}

template<const char* VAL>
void foo() { std::cout << VAL << std::endl; }

extern char const s[] = "test";

int main()
{
	std::vector<double> as = { 0, 1, 2, 3 };
	std::vector<double> out(as.size());
	std::transform(
		as.begin(), 
		as.end(), 
		out.begin(), 
		addValue<double, 5> //< a function template instance
		);

	// Function template instances are considered to name a set of overloaded functions
	// (even if the set has only one member).
	
	// in 2003 standard set of overloaded functions could not be used for template
	// parameter deduction. So you had to cast it to exact type of function template 
	// argument: (int(*)(int const&))addValue<int,5>
	//
	// It looks like since vs2005 it was fixed. Look in core issue 115.

	// Thats fine, s has external linkage
	foo<s>();
	foo<s>();

	const char* const literalName1 = "alabama";
	const char* const literalName2 = "alabama";
	std::cout << std::hex << (intptr_t)"alabama" << std::endl;
	std::cout << std::hex << (intptr_t)"alabama" << std::endl;
	std::cout << std::hex << (intptr_t)literalName1 << std::endl;
	std::cout << std::hex << (intptr_t)literalName2 << std::endl;
}
