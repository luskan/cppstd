// ConsoleApplication2.cpp : Defines the entry point for the console application.
//
#include <windows.h>
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

// Below code should not compile, but it does under VS
int X;
template<typename T>
class X {
	
};

// 8.2.1 Type Parameters
template<typename T>
class X1 {
public:
	friend T;
};

X1<std::string> ix1;

// 8.2.3 template template pamaters

template<typename T, template<typename, typename> class cls>
class Y {
public:
	cls<T, std::allocator<T>> data;
};


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

//extern "C" {   template<class T>  class X1 { };   }

int main() {
	Y<int, std::vector> yy;

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