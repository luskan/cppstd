// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <memory>
#include <array>
#include <functional>
#include "WidgetClass.h"

// Template class

template<typename T>
class Foo1 {
public:
	void testCall1(const T& arg1);
	void testCall2(const T& arg1);
};

template<typename T>
void Foo1<T>::testCall1(const T& arg1) {
	arg1.print1();
}

template<typename T>
void Foo1<T>::testCall2(const T& arg1) {
	arg1.print2();
}

// Template class specialization
template<> class Foo1 <int> {
public:
	void testCall1(const int& arg1);
	//void testCall2(const int& arg1);
};

void Foo1<int>::testCall1(const int& arg1) {
	std::cout << arg1 << std::endl;
}
/*
void Foo1<int>::testCall2(const int& arg1) {
	std::cout << arg1 << std::endl;
}
*/

class Bar1 {
public:
	void print1() const {
		std::cout << "Bar1::print1" << std::endl;
	}
};

int main()
{
	Bar1 bar1;
	Foo1<Bar1> foo1;
	foo1.testCall1(bar1);

	Foo1<int> foo1int;
	foo1int.testCall1(1);

	// Below will show error because print2 is not in Bar1. Without this line it will be ok
	// because template class functions are instantiated upon their use.
	// foo1.testCall2(bar1);

	WidgetClass<int, char> widgetDiffTypes;
	WidgetClass<int, int> widgetSameTypes;
	//WidgetClass<int*, int*> widgetPointerTypes;  // error because <T, T> is as good match as <T1*, T2*>, uncomment <T*,T*> specialization to disambiguate

	std::cout << "test " << typeid(const char*).name() << std::endl;
	std::cout << "test " << typeid(char).name() << std::endl;
	
	return 0;
}


