#include <iostream>
#include <list>

template<typename T1, typename T2>
int countr(T1 a, T2 b) {
	return a + b + 1;
}

class MyData {
public:
	MyData(){}
	MyData(const MyData& rop) {
		int n = 0;
		n++;
		std::cout << "1: " << __FUNCTION__ << std::endl;
	}
	MyData(MyData&& rop) {
		int n = 0;
		n++;
		std::cout << "2: " << __FUNCTION__ << std::endl;
	}
	MyData& operator=(const MyData& rop) {
		int n = 0;
		n++;
		std::cout << "3: " << __FUNCTION__ << std::endl;
		return *this;
	}
	MyData& operator=(const MyData&& rop) {
		int n = 0;
		n++;
		std::cout << "4: " << __FUNCTION__ << std::endl;
		return *this;
	}
};

MyData callMe(){
	MyData md;
	return static_cast<MyData&>(md);
	//return md;
}

int main()
{
	std::cout << countr(1, 2) << std::endl;
	MyData md = callMe();
}