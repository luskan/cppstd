#include <iostream>

class empty {
  typedef int nn;
};

class empty2 : public empty {

};

class nonempty : public empty, public empty2 {

};

int main()
{
  std::cout << sizeof(empty) << std::endl;
  std::cout << sizeof(empty2) << std::endl;
  std::cout << sizeof(nonempty) << std::endl; // VS gives 1 bytes, g++/clang++ gives 2 bytes
}