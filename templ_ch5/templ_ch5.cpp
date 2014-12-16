// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <memory>
#include <array>
#include <vector>
#include <functional>

template<typename T>
class Base {
public:
	void exit1() {}
};

template<typename T>
class Derived : public Base < T > {

public:

	void callMe() {
		exit1();
	}

};

int main()
{
}
