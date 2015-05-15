// ConsoleApplication2.cpp : Defines the entry point for the console application.
//
//#include <windows.h>
#include <iostream>
#include <typeinfo>

#include "templ.h"


// For 12.3.3
class CallCtr {
public:
	CallCtr() {
		std::cout << "CallCtr::CallCtr()" << std::endl;
	}
private:
	CallCtr(CallCtr const&);
};

template<typename T>
class CallHolder {
public:
	static T tt;
};

template<>
CallCtr CallHolder<CallCtr>::tt;

extern void CallGrade();
int main()
{
	MyGrade<int> grade;
	int nn = grade.value;
	std::cout << "From templ_ch12.cpp:: " << nn << std::endl;
	CallGrade();

	// 12.3.3 Full Member Specialization
	CallHolder<CallCtr> test;
}
