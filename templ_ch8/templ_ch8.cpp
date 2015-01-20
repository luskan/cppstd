// ConsoleApplication2.cpp : Defines the entry point for the console application.
//
//#include <windows.h>
#include <iostream>
#include <memory>
#include <array>
#include <vector>
#include <deque>
#include <functional>
#include <boost/timer.hpp>
#include <cmath>
#include <chrono>
#include <string>
#include <map>

// Below code should not compile, but it does under VS
int X2;
template<typename T>
class X2 {
	
};

// 8.2.1 Type Parameters
template<typename T>
class X1 {
public:
	friend T;
};

X1<std::string> ix1;

// 8.2.2 non type template parameters
template<typename T, int SIZE>
class MyArr {
public:
	//virtual ~MyArr() {}
	T arr[SIZE];
};

template<const char* STR>
class MyStr {
public:
	void print() {
		std::cout << STR << std::endl;
	}
};

template<float& F>
class MyFloat {
public:
	void print() {
		std::cout << F << std::endl;
	}
};

// 8.2.3 template template pamaters

template<typename T, template<typename, typename> class cls>
class Y {
public:
	cls<T, std::allocator<T>> data;
};

/*
int UTF16toUTF8(const WCHAR* utf16, CHAR* utf8) {
	int len = WideCharToMultiByte(CP_UTF8, 0, utf16, -1, NULL, 0, 0, 0);
	if (utf8 == NULL)
		return len;
	if (len>1) {
		return WideCharToMultiByte(CP_UTF8, 0, utf16, -1, utf8, len, 0, 0);
	}
	return 0;
}

int UTF8toUTF16(const CHAR* utf8, WCHAR* utf16) {
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	if (utf16 == NULL)
		return len;
	if (len>1) {
		return MultiByteToWideChar(CP_UTF8, 0, utf8, -1, utf16, len);
	}
	return 0;
}
*/
//extern "C" {   template<class T>  class X1 { };   }
extern const char my_string[]; const char my_string[] = "alfabet";

// 8.2.4 Default Parameters - default parameters cannot be repeated

void foo1(int a = 0, int b = 1);
//error: void foo1(int a = 0, int b = 1);
void foo1(int a, int b); // ok!

template<class T = int> class X3;
template<class T = int> class X3 {};

// SO test for 
// http://stackoverflow.com/questions/9787593/c-implicit-type-conversion-with-template

template<typename T>
class X {
public:
	int n;

	X(int rn) : n(rn) {}

	//template<class U>
	//friend X<U>& operator+(const X<U>& lhs, const X<U>& rhs);

	friend X& operator+(const X& lhs, const X& rhs)	{
		X ret(0);
		ret.n = lhs.n + rhs.n;
		return ret;;
	}
};

template<typename U>
X<U>& operator+(const X<U>& lhs, const X<U>& rhs)	{
	X<U> ret(0);
	ret.n = lhs.n + rhs.n;
	return ret;
}

// 8.3.1 SFINAE

typedef char Ret1;
typedef struct { char a[2]; } Ret2;

template<typename T>
Ret1 Test1(typename T::xtype const*) {}
template<typename T>
Ret2 Test1(...) {}

#define TYPE_CONTAINS_XVARIABLE(T) (sizeof(Test1<T>(0)) == 1)

struct ClassXVar {
	typedef int xtype;
};
struct ClassNoXVar {
	typedef int xtype_none;
};

// 8.3.2 Type Arguments
template<typename T>
struct Class1 {
};

// 8.3.3 Nontype Arguments
template<typename T, T nontype>
struct CType {
	void call() {
		*nontype = 101;
	}
};
extern int ag = 0;

typedef std::pair<double, double> MyKey;
class MyKey_compare {
public:
	MyKey_compare() {}
	size_t operator( )(const MyKey& Key) const {
		return static_cast<long>(Key.first*1000.0) ^ static_cast<long>(Key.second*1000.0);
	}
	bool operator( )(const MyKey& Key1, const MyKey& Key2) const {
		if (Key1.first < Key2.first)
			return true;
		else
			if (Key1.first > Key2.first)
				return false;
		return Key1.second < Key2.second;
	}
};

template <typename T, T nontype>
class CL {};

// integral type
CL<int, 123> cl1;
CL<bool, false> cl2;
CL<char, 'a'> cl3;
CL<unsigned long long int, 123> cl4;

// enumeration
enum Enum { Foo, Bar };
enum class Enum2 { Foo, Bar };
CL<Enum, Foo> cl5;
//CL<Enum, 0> cl5; // error
CL<Enum2, Enum2::Foo> cl6;

// pointer to object or to function
//void f();
void f(int);
CL<void(*)(int), &f> cl7;
//CL<decltype((f)), &f> cl8; // VS 2013 update 4, gives internal compiler error
CL<decltype(f)*, &f> cl8; // but this works

struct XL {
	int n;
	static bool b;
};
CL<bool&, XL::b> cl9;
CL<decltype((XL::b)), XL::b> cl10;

// 8.3.5 Equivalence

class CVBase {
public:
	virtual void foo() {
		std::cout << "CVBase::foo" << std::endl;
	}
};

template<typename T> 
class CVDerived : public CVBase {
public:
	//template members cannot be virtual.
	//template<typename T2>
	virtual void foo() {
		std::cout << "CVDerived::foo" << std::endl;
	}
};

// 8.4 Friends

namespace Forest {
	struct HeightType { HeightType(int) {} };
	class CTree {
	public:
		CTree(int) {}

		// This parameter less foo function is actually unaccessible
		friend void foo() {}

		// This one is accessibly only thought ADT
		friend void foo(const CTree&) {}
	};
}

std::deque<int> getValues() {
	std::deque<int> res;
	res.push_back(1);
	return res;
}


#include <iostream>
#include <string>

class CoolString
{
	std::string s;
public:
	CoolString(const char* p) {
		s = p;
	}

	char& operator[](size_t i) {
		std::cout << "char& operator[](size_t i)" << std::endl;
		return s.at(i);
	}
	//const char& operator[](size_t i) const {
	//	std::cout << "    const char& operator[](size_t i)" << std::endl;
	//	return s.at(i);
	//}
	
	operator const char*() const {
		std::cout << "operator const char*" << std::endl;
		return s.c_str();
	}
	
	operator char*() {
		std::cout << "operator char*()" << std::endl;
		return &s[0];
	}
	
};

class A {
	int i;
public:
	A() : i(0) {}
	A& operator++() { i++; return *this; }
	A operator++(int) {
		A temp = *this;
		++*this;
		return temp;
	}
};

void func(ptrdiff_t n){}
void func(size_t n) {}

class AB {
public:
 explicit operator bool() {
		return true;
	}
};

int main()  {

	/*
	func(1);

	AB ab;
	if (ab) {

	}
	bool bl = (bool)ab;

	int kk = 123;
	int && rkk = std::move(kk);
	
	CoolString ss("asd");
	ss[1] = '1';
	

	std::cout << "size_t = " << typeid(size_t).name() << std::endl;			// VS2013: unsigned int, g++: unsigned long
	std::cout << "ptrdiff_t = " << typeid(ptrdiff_t).name() << std::endl;	// VS2013: int, g++: long
	*/
	/*
	// SO sample code
	typedef std::map<MyKey, std::string, MyKey_compare> KeyDataMap;
	KeyDataMap mymap;
	mymap[std::make_pair(10.0, 10.0)] = "point 1";
	mymap[std::make_pair(11.0, 21.0)] = "point 3";
	mymap[std::make_pair(10.0, 20.0)] = "point 2";

	for (KeyDataMap::iterator itr = mymap.begin(); itr != mymap.end(); ++itr)
		std::cout << itr->first.first << ", " << itr->first.second << ", " << itr->second << std::endl;
	*/

	Y<int, std::vector> yy;

	///*
	X<int> a = 1;
	X<int> b = 2;
	X<int> c = a + b;
	c = c + 1;
	c = 1 + c;
	std::cout << "X : " << c.n << std::endl;
	//*/

	// 8.2.2
	MyArr<char, 10> arr;
	std::cout << sizeof(arr) << std::endl;

	MyStr<my_string> str1;
	str1.print();
	//static const float f = 10;
	//MyFloat<f> ff;
	//ff.print();

	// 8.3.1 SFINAE
	if (TYPE_CONTAINS_XVARIABLE(ClassXVar))
		std::cout << "ClassXVar - has xtype" << std::endl;
	else
		std::cout << "ClassXVar - has no xtype" << std::endl;

	if (TYPE_CONTAINS_XVARIABLE(ClassNoXVar))
		std::cout << "ClassNoXVar - has xtype" << std::endl;
	else
		std::cout << "ClassNoXVar - has no xtype" << std::endl;

	// 8.3.2 Type Arguments 
	// Below are not allowed in 2003 standard
	class Test1Inner {};
	Class1<Test1Inner> cls1;

	struct Test2Inner {};
	Class1<Test2Inner> cls2;

	enum Enum1Inner { A, B, C};
	Class1<Enum1Inner> cls3;

	// 8.3.3
	CType<int*, &ag> clsg;
	clsg.call();
	std::cout << "ag = " << ag << std::endl;

	// 8.3.5
	CVDerived<int> derived;
	//derived.foo<int>();

	// 8.4

	Forest::CTree tree(0);
	foo(tree); // ok - call by ADT
	//foo(); // error
	//foo(0); // error - foo is not considered as candidate using ADL due to required implicit conversion
	//Forest:foo(); // error
	//Forest::foo(tree); // error
	//Forest::foo(); // error

	std::map<int, std::string> foob;
	std::map<int, std::string>::value_type nn_var;
	decltype(foob)::value_type nn2_var;
	typedef decltype(foob)::value_type value_typeb;
	//nn2_var.first = 0;
	std::cout << "value_type: " << typeid(nn2_var.first).name() << typeid(nn2_var.second).name() << std::endl;

}

/*

// SO TEST
int main()
{
	int MyData = 0;
	const TCHAR* utf16str = L"\u0105\u0107abcde"; // "¹æabcde"
	INT requiredLen = UTF16toUTF8(utf16str, NULL);
	if (requiredLen > 0) {
		std::vector<CHAR> utf8str(requiredLen, '\0');
		INT isOk = UTF16toUTF8(utf16str, &utf8str.front());
		if (isOk <= 0)
			std::cout << "Error: " << ::GetLastError();
		else
			std::cout << &utf8str.front(); // C4 85 C4 87 61 62 63 64 65

requiredLen = UTF8toUTF16(utf8str.data(), nullptr);
if (requiredLen > 0) {
	std::vector<WCHAR> utf16str(requiredLen, '\0');
	UTF8toUTF16(utf8str.data(), &utf16str.front());
	int n = 0;
	n++;
}
		
	}
	else if (requiredLen < 0) {
		std::cout << "Error: " << ::GetLastError();
	}

	
}
*/
