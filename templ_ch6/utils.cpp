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

void callMe1() {
	foo("test1");
}

// Definition of class
template<typename T>
ShowTypeInfoClass<T>::ShowTypeInfoClass() {
	std::cout << typeid(T).name() << std::endl;
}

extern template ShowTypeInfoClass<int>::ShowTypeInfoClass(int);

// Explicit instantiation of whole cass for T=int
template ShowTypeInfoClass < int > ;

// Specialization of constructr for T=double
template<> ShowTypeInfoClass<double>::ShowTypeInfoClass() {
	std::cout << "speciaization for double type: " << typeid(double).name() << std::endl;
}

// Explicit instantiation of constructor for T=long
template ShowTypeInfoClass<long>::ShowTypeInfoClass();