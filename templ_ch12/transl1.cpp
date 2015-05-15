#include <iostream>
#include "templ.h"

// under vs2013 default ctor gets caed
// under gcc5.1.0 no ctor gets called, its nondefining
template<>
CallCtr CallHolder<CallCtr>::tt;

void CallGrade()
{
	// 12.3.3 Full Member Specialization
	CallHolder<CallCtr> test;
	test.tt.callMe();
}