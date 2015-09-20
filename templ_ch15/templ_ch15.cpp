#include <iostream>
#include <vector>
#include <list>
#include <deque>

#include "test.h"

template<typename T>
struct TD;

template<typename T>
struct ElementType;

template<typename T>
struct ElementType<std::vector<T>> { // partial specialization
  typedef T type;
};

template<typename T>
struct ElementType<std::list<T>> {
  typedef T type;
};

template<typename T>
struct ElementType<std::deque<T>> {
  typedef T type;
};

// SFINAE

template<typename T>
class IsClass {
public:
  typedef char One;
  typedef struct { char arr[2];  } Two;
  template<typename C>static One test(int C::*);
  template<typename C>static Two test(...);
  enum { YES = sizeof(/*IsClass<T>::template */test<T>(0)) == 1 };
  enum { NO = !YES };
};

class TestClass {};

template<bool T, typename T1, typename T2>
struct IfThenElse {
  typedef void value;
};

template<typename T1, typename T2>
struct IfThenElse<true, T1, T2> {
  typedef T1 value;
};

template<typename T1, typename T2>
struct IfThenElse<false, T1, T2> {
  typedef T2 value;
};

int main()
{
  Str1 d;
  func1(&d);
  func2(0);

  typedef std::vector<int> avec_type;
  typedef std::list<float> lvec_type;
  typedef std::deque<float> dvec_type;

  ElementType<avec_type>::type aa;
  avec_type::value_type aa2;

  ElementType<lvec_type>::type bb;
  ElementType<dvec_type>::type cc;

  if (IsClass<TestClass>::YES) {
    std::cout << "Its a class" << std::endl;
  }
  else {
    std::cout << "Its NOT a class" << std::endl;
  }

  char arr[1];
  IfThenElse<(sizeof(arr)>1), int, long>::value vv;
  //TD<decltype(vv)>();
}