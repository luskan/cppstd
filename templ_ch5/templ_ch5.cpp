// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <memory>
#include <array>
#include <vector>
#include <functional>


// 5.2

template<typename T>
class Base {
public:
	void exit1() {}
};

template<typename T>
class Derived : public Base < T > {

public:

	void callMe() {
		// as a rule of thumb, we recommend that you always qualify any symbol that is declared in a 
		// base that is somehow dependent on a template parameter with this-> or Base<T>::.
		//Base<T>::exit1();
		exit1();
		//exit1(); // com
	}

};


// Sample from:
// http://stackoverflow.com/questions/19816509/use-typedef-using-from-templated-base-class-in-derived-class
template <typename T>
class Base2 {
public:
	using mytype = T;
};

template <typename T>
class Derived2 : public Base2<T>{
public:
	// using the base's mytype here
	static typename Base2<T>::mytype func() { return 0; }
	//static typename mytype func() { return 0; }
};

// Example from [temp.dep]p3
// http://clang.llvm.org/compatibility.html#dep_lookup_bases
typedef double A;
template<class T> class B {
public:
	typedef int A;
};
template<class T> struct X : B<T> {
public:
	A a; // a has type double
};

// http://blog.llvm.org/2009/12/dreaded-two-phase-name-lookup.html

int main()
{
	//Derived<int> ad;
	//ad.callMe();

	//Derived2<int> ad2;
	//ad2.func();

	X<int> x;
	std::cout << "type of a: " << typeid(x.a).name() << std::endl;
}
