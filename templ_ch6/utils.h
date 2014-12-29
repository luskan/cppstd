#if !defined(UTILS_H)
#define UTILS_H
#include <typeinfo>

template<typename T>
void foo(T& str) {
	std::cout << str << ": " << typeid(T).name() << std::endl;
}

// Template does not cause redefinition, but regular function does.
// To fix it make below function either: static or inline
/*void foo(const char* str) {
	std::cout << str << std::endl;
}*/

template<typename T>
class ShowTypeInfoClass {
public:
	ShowTypeInfoClass();
    ShowTypeInfoClass(int);
};

#endif