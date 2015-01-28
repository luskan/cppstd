// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <memory>
#include <array>
#include <vector>
#include <deque>
#include <functional>
#include <boost/timer.hpp>
#include <cmath>
#include <chrono>

#include "utils.h"

extern int mm = 1;

void fun(int, int = 10);

int main()
{
	fun(1, 2);
	mm = 1;
	foo("test2");

		ShowTypeInfoClass<int> stic;
		ShowTypeInfoClass<double> stic2;
		ShowTypeInfoClass<long> stic3;
}

void fun(int, int) {

}
