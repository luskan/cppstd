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

// 5.2 Using this->

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
		this->exit1();
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


//
// 5.3 member templates

template<typename T>
class BulkDataCollection {
public:
	std::vector<T> data;

	BulkDataCollection(std::initializer_list<T> const& rop) : data(rop) {}

	void print() {
		for (int i : data) {
			std::cout << i << std::endl;
		}
	}

	template<typename T2>
	BulkDataCollection<T>& operator=(BulkDataCollection<T2> const& rop);
};

template<typename T>
template<typename T2>
BulkDataCollection<T>& BulkDataCollection<T>::operator = (BulkDataCollection<T2> const& rop) {
	if (this == (void*)&rop)
		return *this;

	data.clear();
	for (typename std::vector<T2>::const_iterator itr = rop.data.begin(); itr != rop.data.end(); ++itr) {
		data.push_back(*itr);
	}

	return *this;
}

// 5.4 template template parameters

template<class T> class myarray {};

// two type template parameters and one template template parameter:
template<class K, class V, template<typename, typename> class C = std::vector>
C<K, std::allocator<K>> foo() {
	C<K, std::allocator<K>> cont;
	cont.push_back(0);
};

template<typename T>
class BaseType {
public:
	void callMe(int n) {}
};

template<template<typename> class T>
void func(int nn) {
	T<int> foo;
	foo.callMe(nn);
}

//5.5 zero init

// if T is class, then it will be default initialized, but primitive types will not so below is hot to default init them.
template<typename T>
class FooClass {
	T x;
public:
	FooClass() : 
		 x() // init to 0/default, this will work even for built int types
	{
		T tt = T(); // init to 0/default
	}
};

//5.6 Using string literals

namespace std {

	// disambiguates case when std::max is used for literals of different lengths.
	template<typename T, int M, int N>
	T const* max(T const (&a)[M], T const (&b)[N]) {
		return a < b ? a : b;
	}

}

int main()
{
	/* ()
	_MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
// Example code for testing subnormal float efficency, not related to tempaltes:)
float f = 2.0f;
std::chrono::steady_clock::duration prevdiff;
for (int k = 0; k < 10000; ++k) {
	float sum = .0f;
		
	auto start = std::chrono::steady_clock::now();

	for (int n = 0; n < 1e7; ++n) {
		sum += f * 0.1f;
	}

	auto end = std::chrono::steady_clock::now();
	auto diff = end - start;
	std::cout << k << ", f=" << f << ", isnormal=" << std::isnormal(f)
		<< ", elapsed=" << std::chrono::duration_cast<std::chrono::milliseconds>(diff).count() << "ms" <<
		", ratio=" << (prevdiff.count() == 0 ? 0 : (diff.count() / prevdiff.count())) << std::endl;
	prevdiff = diff;

	if (f < std::numeric_limits<float>::min())
		break;

	f /= 2.0f;
}
*/

	//Derived<int> ad;
	//ad.callMe();

	//Derived2<int> ad2;
	//ad2.func();

	X<int> x;
	std::cout << "type of a: " << typeid(x.a).name() << std::endl;

	//
	BulkDataCollection<int> intBulkData = { 0, 1, 2 };
	BulkDataCollection<float> floatBulkData = { 0.2f, 1.3f, 0.4f };

	intBulkData = floatBulkData;
	intBulkData.print();

	//5.4
	func<BaseType>(1);

	//5.5
	FooClass<int> fc1;
	FooClass<std::vector<int>> fc2;

	//5.6
	auto pair = std::make_pair("alpha", "alpha1");
	std::max("al", "al1"); // error, different types. std::max is expecting bot arguments to be of same type, here they are
		                   // of type char const[2] and char const[3]. Since std::max use T const&, literals does not decay to char const*
}