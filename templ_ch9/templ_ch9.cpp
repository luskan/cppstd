// ConsoleApplication2.cpp : Defines the entry point for the console application.
//
//#include <windows.h>
#include <iostream>

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

int main()
{

}
