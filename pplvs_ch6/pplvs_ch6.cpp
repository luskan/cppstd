#include <iostream>
#include <string>
#include <vector>
#include <ppl.h>
#include <concrtrm.h>
#include <windows.h>
#include <algorithm>
#include <numeric>
#include <cassert>
#include "../common/ppl_common.h"

#if _MSC_PLATFORM_TOOLSET <= 120
#include "../common/ppl_extras.h"
#endif

template<typename T>
class TreeNode {
public:
  T data;
  std::shared_ptr<TreeNode> left; // use class name injection - TreeNode = TreeNode<T>
  std::shared_ptr<TreeNode> right;
};

template<typename T, typename F>
void FillBinTree(std::shared_ptr<T> root, int depth, F f) {
  if (depth != 0) {
    root->left = std::make_shared<T>();
    root->right = std::make_shared<T>();
    FillBinTree(root->left, depth - 1, f);
    FillBinTree(root->right, depth - 1, f);
  }
  f(root->data);
}

template<typename T, typename F>
void WalkTree(std::shared_ptr<TreeNode<T>> root, F f) {
  if (root == nullptr)
    return;

  f(root->data);
  WalkTree(root->left, f);
  WalkTree(root->right, f);
}

template<typename T, typename F>
void ParallelWalkTree(std::shared_ptr<TreeNode<T>> root, F f) {
  if (root == nullptr)
    return;

  Concurrency::parallel_invoke(
    [=]() { f(root->data); },
    [=]() { WalkTree(root->left, f); },
    [=]() { WalkTree(root->right, f); }
  );
}

auto BuildTree(int depth) {
  std::atomic<int> count(0);
  auto root = std::make_shared<TreeNode<int>>();
  FillBinTree(root, depth, [&](int& n) {n = count++;});
  return root;
}

void example1(std::shared_ptr<TreeNode<int>> root) {
  std::atomic<unsigned long long> sum(0);
  WalkTree(root, [&](int n) { sum += 1; });
  std::cout << "Walked depth: " << sum.load() << std::endl;
}

void example2(std::shared_ptr<TreeNode<int>> root) {
  std::atomic<unsigned long long> sum(0);
  ParallelWalkTree(root, [&](int n) { sum += 1; });
  std::cout << "Walked depth: " << sum.load() << std::endl;
}

void example3(std::shared_ptr<TreeNode<int>> root) {
  std::atomic<unsigned long long> sum(0);
  ParallelWalkTree(root, [&](int n) { sum += 1; });
  std::cout << "Walked depth: " << sum.load() << std::endl;
}

template<typename VectorIter>
void InsertionSort(VectorIter begin, VectorIter end) {
  if (begin == end)
    return;
  for (VectorIter bg1 = begin + 1; bg1 != end; ++bg1) {
    int cur = *bg1;
    VectorIter bg2;
    for (bg2 = bg1 - 1; bg2 >= begin ; --bg2) {
      if (cur > *bg2) {
        *(bg2 + 1) = cur;
        break;
      }
      *(bg2 + 1) = *bg2;
      if (bg2 == begin) {
        *bg2 = cur;
        break;
      }
    }
  }
}

/*
Concurrency::parallel_for(0, 1000, [](int k) {
std::vector<int> arr;
for (int p = 0; p < k; ++p)
arr.push_back(rand() % 100);

std::vector<int> arr1 = arr;
InsertionSort(arr1.begin(), arr1.end());

std::vector<int> arr2 = arr;
std::sort(arr2.begin(), arr2.end());

assert(arr2 == arr1);
});
*/

template<typename VectorIter>
static void SequentialQuickSort(VectorIter begin,
  VectorIter end,
  long threshold)
{
  if (distance(begin, end) <= threshold)
  {
    InsertionSort(begin, end);
  }
  else
  {
    VectorIter pivot = partition(begin + 1,
      end,
      bind2nd(std::less<int>(), *begin));
    iter_swap(begin, pivot - 1);
    SequentialQuickSort(begin, pivot - 1, threshold);
    SequentialQuickSort(pivot, end, threshold);
  }
}

template<typename VectorIter>
static void ParallelQuickSort(VectorIter begin, VectorIter end,
  long threshold, int depthRemaining)
{
  if (distance(begin, end) <= threshold)
  {
    InsertionSort(begin, end);
  }
  else
  {
    VectorIter pivot = partition(begin + 1,
      end,
      bind2nd(std::less<int>(), *begin));
    iter_swap(begin, pivot - 1);
    if (depthRemaining > 0)
    {
      Concurrency::parallel_invoke(
        [begin, end, pivot, depthRemaining, threshold] {
        ParallelQuickSort(begin, pivot - 1,
          depthRemaining - 1, threshold);
      },
        [&pivot, begin, end, depthRemaining, threshold] {
        ParallelQuickSort(pivot, end,
          depthRemaining - 1, threshold);
      }
      );
    }
    else
    {
      SequentialQuickSort(begin, pivot - 1, threshold);
      SequentialQuickSort(pivot, end, threshold);
    }
  }
}

static void ParallelQuickSort(std::vector<int>& a, long threshold)
{
  const int maxTasks =
    Concurrency::CurrentScheduler::Get()->GetNumberOfVirtualProcessors();

  ParallelQuickSort(a.begin(), a.end(),
    threshold, (int)std::log2f(float(maxTasks)) + 4);
}

void example4() {
  std::vector<int> av;
  srand(123333);
  for (int n = 0; n < 1000000; ++n) {
    av.push_back(rand() % 1000);
  }
  SequentialQuickSort(av.begin(), av.end(), 5);
}

void example5() {
  std::vector<int> av;
  srand(123333);
  for (int n = 0; n < 1000000; ++n) {
    av.push_back(rand() % 1000);
  }
  ParallelQuickSort(av, 5);
}

/*
#include <vector>
#include <iostream>

template < typename T > class TD; // type visualiser

template<class T>
class A
{
public:
   A(T arg) { _data = arg; }

  template<typename D>
  operator A<D>() {
    static_assert(std::is_same<D, float>::value || std::is_same<D, double>::value, "double/floats allowed only");
    //TD<D>();  // D is float here
    return A<D>(static_cast<D>(_data));
  }

  T _data;
};

typedef A<float> A_f;
typedef A<double> A_d;
typedef A<int> A_i;

int main() {
  A_f f(3.14151);
  A_d d(3.14152);

  std::cout << f._data << std::endl;
  std::cout << d._data << std::endl;

  f = (A_f)d;
  //f = (A_i)d; // static assertion here

  std::cout << f._data << std::endl;
  return 0;
}
*/

int main() {

  auto root = BuildTree(17);
  TimedRun([&]() {example1(root);}, "example1() - sequential tree walk");
  TimedRun([&]() {example2(root);}, "example2() - parallel tree walk");
  //TimedRun([&]() {example3(root);}, "example2() - parallel tree walk");
  TimedRun([&]() {example4();}, "example4() - sequential sort");
  TimedRun([&]() {example5();}, "example5() - parallel sort");
	getchar();
}
