#include <iostream>
#include <vector>
#include <list>
#include <deque>


#include "test.h"

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
}