#include <iostream>
#include "templ.h"

extern void CallGrade();
int main()
{
	CallGrade();

	// 12.3.3 Full Member Specialization
	CallHolder<CallCtr> test;
	test.tt.callMe();
}