// ConsoleApplication2.cpp : Defines the entry point for the console application.
//
//#include <windows.h>
#include <iostream>
#include <typeinfo>

#include "templ.h"

int main()
{
	MyGrade<int> grade;
	int nn = grade.value;
	std::cout << "From templ_ch12.cpp:: " << nn << std::endl;

	extern void CallGrade();
	CallGrade();
}
