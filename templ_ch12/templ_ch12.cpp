#include <iostream>
#include <list>
#include "templ.h"

// 12.4 Partial Class Template Specialization

template<typename T>
class List {
	void append(T const&);
	inline size_t length() const;
};

template<> class List <void*> {
	std::list<void*> alist;
public:
	size_t length() const {
		return alist.size();
	}
	void append(void * const obj) {
		alist.push_back(obj);
	}
};

template<typename T>
class List < T* > {
	List<void*> impl;
public:
	void append(T* p) {
		impl.append(p);
	}
	size_t length() const {
		return impl.length();
	}
};

template<typename T, int I = 3>
class S;

//template<typename T>
//class S < int, T > ; // parameter kind mismatch, arguments of partial specialization must match in kind (type, nontype, template)

//template<typename T = int> // no default arguments
//class S < T, 10 > ;

//template<int I>
//class S <int, I*2> ; // no non type expressions allowed, 

template<int I>
class S <std::string, I>;

extern void CallGrade();
int main()
{
	CallGrade();

	// 12.3.3 Full Member Specialization
	CallHolder<CallCtr> test;
	test.tt.callMe();

	List<void*> plist;
	plist.length();
}