#include <iostream>
#include <string>
#include <vector>
#include <ppl.h>
#include <concrtrm.h>
#include <windows.h>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <string>
#include <numeric>
#include "../common/ppl_common.h"
#include "PipelineGovernor.h"

#if _MSC_PLATFORM_TOOLSET <= 120
#include "../common/ppl_extras.h"
#endif

#define MAX_PRIMES 10000

class ParseToInt : public Concurrency::agent {
  Concurrency::unbounded_buffer<std::shared_ptr<std::string>>& indata;
  Concurrency::unbounded_buffer<int>& outdata;
public:

  ParseToInt(Concurrency::unbounded_buffer<std::shared_ptr<std::string>>& in, Concurrency::unbounded_buffer<int>& out) : indata(in), outdata(out) {}

  void run() {

    while (true) {
      auto str = Concurrency::receive(indata);  
      if (str->empty()) {
        Concurrency::asend(outdata, -1);
        break;
      }
      int num = std::stoi(*str);
      if (num == -1) {
        Concurrency::asend(outdata, -1);
        break;
      }
      Concurrency::asend(outdata, num);
    }
    done();
  }
};

class CheckIfPrime : public Concurrency::agent {
  Concurrency::unbounded_buffer<int>& indata;
  Concurrency::unbounded_buffer<std::shared_ptr<std::string>>& outdata;
public:

  CheckIfPrime(Concurrency::unbounded_buffer<int>& in, Concurrency::unbounded_buffer<std::shared_ptr<std::string>>& out) : indata(in), outdata(out) {}

  void run() {

    while (true) {
      auto num = Concurrency::receive(indata);
      if (num == -1) {
        Concurrency::asend(outdata, std::make_shared<std::string>(""));
        break;
      }
      bool isPrime = isprime(num);
      if (isPrime) {
        std::stringstream str;
        str << "Value: " << num << " isPrime";
        Concurrency::asend(outdata, std::make_shared<std::string>(str.str()));
      }
      else {
        Concurrency::asend(outdata, std::make_shared<std::string>("ignore"));
      }
    }
    done();
  }
};

class WriteToFile : public Concurrency::agent {
  Concurrency::unbounded_buffer<std::shared_ptr<std::string>>& indata;
  PipelineUtilities::PipelineGovernor& gov;
public:

  WriteToFile(Concurrency::unbounded_buffer<std::shared_ptr<std::string>>& in, PipelineUtilities::PipelineGovernor& g) : indata(in), gov(g) {}

  void run() {

    std::ofstream fout("primes.txt");
    while (true) {
      auto str = Concurrency::receive(indata);
      if (str->empty()) {
        break;
      }
      if (*str != "ignore") {
        fout << *str << "\r\n";
        fout.flush();
      }
      gov.FreePipelineSlot();
      
    }
    fout.close();
    done();
  }
};

void example2() {
  std::ofstream fout("primes.txt");
  for (int k = 0; k < MAX_PRIMES; ++k) {
    std::string str(std::to_string(k));
    int num = std::stoi(str);
    bool isPrime = isprime(num);
    if (isPrime) {
      std::stringstream str;
      str << "Value: " << num << " isPrime";
      fout << str.str() << "\r\n";
      fout.flush();
    }
  }
  fout.close();
}

void example1() {
  Concurrency::unbounded_buffer<std::shared_ptr<std::string>> buffer1;
  Concurrency::unbounded_buffer<int> buffer2;
  Concurrency::unbounded_buffer<std::shared_ptr<std::string>> buffer3;

  PipelineUtilities::PipelineGovernor gov(5);

  ParseToInt parseToIntAgent(buffer1, buffer2);
  CheckIfPrime checkIfPrimeAgent(buffer2, buffer3);
  WriteToFile writeToFileAgent(buffer3, gov);
  
  parseToIntAgent.start();
  checkIfPrimeAgent.start();
  writeToFileAgent.start();

  Concurrency::task_group tg;
  tg.run(
    [&]() {
    for (int k = 0; k <= MAX_PRIMES; ++k) {
      gov.WaitForAvailablePipelineSlot();
      Concurrency::asend(buffer1, std::make_shared<std::string>(std::to_string(k== MAX_PRIMES ?-1:k)));
    }
  });

  gov.WaitForEmptyPipeline();
  Concurrency::agent* agents[3] = {&parseToIntAgent, &checkIfPrimeAgent, &writeToFileAgent};
  Concurrency::agent::wait_for_all(3, agents);
}

int main() {
	TimedRun(example1, "example1() - pipeline");
  TimedRun(example2, "example2() - seq pipeline");
	getchar();
}