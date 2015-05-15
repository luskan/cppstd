#include <iostream>
#include <typeinfo>

#include "templ.h"

template<>
struct MyGrade<int> {
	const int value = 11;
};

void CallGrade()
{
	MyGrade<int> grade;
	int nn = grade.value;
	std::cout << "From trans1.cpp:: " << nn << std::endl;

	// 12.3.3 Full Member Specialization
	CallHolder<CallCtr> test;
	test.tt.callMe();
}