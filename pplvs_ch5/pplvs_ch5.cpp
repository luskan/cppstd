#include <iostream>
#include <string>
#include <vector>
#include <ppl.h>
#include <concrtrm.h>
#include <agents.h>
#include <windows.h>
#include <algorithm>
#include <numeric>
#include "../common/ppl_common.h"

#if _MSC_PLATFORM_TOOLSET <= 120
//#include "../common/ppl_extras.h"
#endif

template<typename T>
class Future {
  Concurrency::single_assignment<T> res;
  Concurrency::task_group tg;
public:

  template<typename Func>
  Future(Func f) {
    tg.run([f, this]() {
      Concurrency::send(res, f());
    });
  }

  T Result() {
    tg.wait();
    return Concurrency::receive(res);
  }
};

void example2() {
  Future<int> fut1([]() { return 101; });
  Concurrency::wait(1000);
  std::cout << fut1.Result() << std::endl;
}

int main() {
  TimedRun(example2, "example2()");
	getchar();
}