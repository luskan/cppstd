
#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>

template<int num>
struct pow3 {
  enum { value = pow3<num - 1>::value * 3 };
};

template<>
struct pow3<0> {
  enum { value = 1 };
};

struct StaticsTest {
  static const int value = 10;
  enum { value2 = 10 };
};

template<unsigned long long N, unsigned long long LO = 1, unsigned long long HI = N>
struct Sqrt {
  enum { MID = (LO + HI + 1) / 2 };
  enum { RESULT = (N < ((LO + HI + 1) / 2)*((LO + HI + 1) / 2)) ? Sqrt<N, LO, MID - 1>::RESULT : Sqrt<N, MID,HI>::RESULT };
};

template<unsigned long long N, unsigned long long M>
struct Sqrt<N,M,M> {
  enum { RESULT = M };
};

//
template<bool B, typename T1, typename T2>
struct IfThenElse;

template<typename T1, typename T2>
struct IfThenElse<true,T1,T2> {
  typedef T1 result_type;
};

template<typename T1, typename T2>
struct IfThenElse<false,T1,T2> {
  typedef T2 result_type;
};


template <unsigned long long N, unsigned long long LO = 1, unsigned long long HI = N>
struct SqrtV2 {
  enum { mid = (LO+HI+1)/2 };
  typedef typename IfThenElse < (N<((LO + HI + 1) / 2)*((LO + HI + 1) / 2)), SqrtV2<N, LO, mid - 1>, SqrtV2<N, mid, HI>>::result_type resB;
  enum { result = resB::result };
};

template<unsigned long long N, unsigned long long M>
struct SqrtV2<N,M,M> {
  enum { result = M };
};

template<int I>
struct Value {
  enum { result = I };
};

template<int N, int I=1>
struct SqrtV3 {
  typedef typename IfThenElse<(I*I<N),SqrtV3<N,I+1>,Value<I> >::result_type resB;
  enum { result = resB::result };
};

// unroll loops

template<int DIM, typename T>
struct DotProduct {
  static T result(T* a, T* b) {
    return *a * *b + DotProduct<DIM - 1, T>::result(a+1, b+1);
  }
};

template<typename T>
struct DotProduct<0,T> {
  static T result(T* a, T* b) {
    return *a * *b;
  }
};

template<int DIM, typename T>
static T dot_product(T* a, T* b) {
  return DotProduct<DIM, T>::result(a, b);
}

class TestC {
public:
  TestC(int n) {
    int n2 = 0;
    n2++;
  }
};

int main()
{
  std::cout << "pow3" << pow3<15>::value << std::endl;

//  TestC* arr2 = new TestC[10](0);

  //std::cout << "sqrt " << Sqrt<99000>::RESULT << std::endl; // takes a long time to compile
  //std::cout << "sqrtv2 " << SqrtV2<99000>::result << std::endl;

  std::cout << "sqrtv3 " << SqrtV3<16>::result << std::endl;

  //foo(1);

  std::cout << StaticsTest::value << std::endl;
  const int& val1 = StaticsTest::value;
  const int* val2 = &StaticsTest::value;
  const int& val3 = StaticsTest::value2;
  //int& val4 = StaticsTest::value2;

  // Small digression: value-initialize array elements during allocation:
  // http://stackoverflow.com/questions/2204176/how-to-initialise-memory-with-new-operator-in-c/2204380#2204380
  int* arr = new int[15]();
  for (int n = 0;n < 15;++n)
    std::cout << arr[n] << std::endl;

  // Unroll loops
  double vec1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
  double vec2[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
  std::cout << "dot_product = " << dot_product<10>(vec1, vec2) << std::endl;
}
