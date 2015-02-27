// ConsoleApplication2.cpp : Defines the entry point for the console application.
//
//#include <windows.h>
#include <iostream>
#include <typeinfo>

// 9.2.3 Injected class name
// Unqualified name of class refers to injected name which is actually 'class with its parameters as its arguments 
//  (or, for a partial specialization, its specialization arguments)'
// To force the name of the template to be found use the file scope qualifier ::.

template<template<typename T> class TT> class X {};
template<typename T> class C {
	//X<C> c; //error: C without a template argument list does not denote a template
	X<::C> c; // now its OK, 
};

class Y;
namespace ns1 {
	class X {
		int n;
	public:
		//friend class Y; // error: this Y refers to ns1::Y, which does not exists
		friend class ::Y;
	};
}
class Y {
public:
	Y(ns1::X* x) {
		x->n++;
	}
};

class Tiny {
	int n;
	void assign(int x) { n = x; }
public:
	Tiny(int k) { assign(k); }

	operator int() { return n; }
	Tiny& operator=(int i) { assign(i); return *this; }
};

template<int N>
class Outer {
public:
	template<int Y>
	class Inner {

	};
};

template<typename T>
class A {
public:
	void foo() {
		this->g<int>();
	}

	template<typename U>
	void g() {

	}
};

// 9.4 Derivation and class template

template<typename X>
class Base {
public:
	int basefield;
	typedef int T;
};

// non template, and using base as nondependent this way
class D1 : public Base < double > {
public:
	void foo() {
		basefield = 1;
		T test;
		test = 1;
	}
};

// template, but using base as nondependent
template <typename T>
class D2 : public Base < double > {
public:
	void foo() {
		basefield = 1;
		T test;
		test = 1;
		std::cout << "Type of T = " << typeid(T).name() << std::endl;
	}
};

// 9.4.2 - now we will have dependent base class, and will create its specialization without basefield

template<typename T>
class D3 : public Base < T > {
public:
	void foo() {
		
		// Below will cause error, 'basefield': undeclared identifier, this is because:
		// standard C++ says that nondependent names (here basefield is used as nondependent, there is no link to T in its use),
		// are not looked up in dependent base classes.
		
		//basefield2 = 1; // here is a nondependent use of basefield, which causes above error, but only under G++/clang, VS accepts that!!

		this->basefield2 = 1; // now its dependent, so basefield name lookup will be postponed until 
							 //  phase 2 where template instantiation is taking place

		
		std::cout << "Type of T = " << typeid(T).name() << std::endl;
	}
};

template<>
class Base < bool > {
public:
	int basefield2;
};

template <typename T,typename R = std::conditional<sizeof(T) == 4, char, short>::type>
R foo(T bar){ return R(0); }

int main()
{
	auto  foo_short  = foo('1');
	auto foo_char = foo(1);
	std::cout << "foo_char:" << typeid(foo_char).name() << std::endl;
	std::cout << "foo_short:" << typeid(foo_short).name() << std::endl;


	Outer<1>::Inner<2> ee;
	A<int> aa;
	aa.foo();

	//9.4
	D1 d1;
	d1.foo();

	D2<float> d2; 
	d2.foo(); // outputs: Type of T = int, yes - T is from base class.

	D3<bool> d3;
	d3.foo();


}
