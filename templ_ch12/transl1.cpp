#include <iostream>
#include "templ.h"

template<>
CallCtr CallHolder<CallCtr>::tt; // under gcc its nondefining

void CallGrade()
{
	// 12.3.3 Full Member Specialization
	CallHolder<CallCtr> test;
	test.tt.callMe();
}