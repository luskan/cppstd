#pragma once

template<typename T1, typename T2>
class WidgetClass
{
public:
	WidgetClass();
	~WidgetClass();
};

template<typename T1, typename T2>
WidgetClass<T1,T2>::WidgetClass()
{
	const std::type_info& r1 = typeid(T1);
	std::cout << "Call from <T1, T2>" << ", T1=" << r1.name() << ", T2=" << typeid(T2).name() << std::endl;
}

template<typename T1, typename T2>
WidgetClass<T1, T2>::~WidgetClass()
{
}

//
// Partial specialization for same type template parameters

template<typename T>
class WidgetClass<T, T> {
public:
	WidgetClass();
	~WidgetClass();
};

template<typename T>
WidgetClass<T, T>::WidgetClass()
{
	std::cout << "Call from <T, T> partial specialization, T = " << typeid(T).name() << std::endl;
}

template<typename T>
WidgetClass<T, T>::~WidgetClass()
{
}


//
// Partial specialization for pointer template parameters

template<typename T1, typename T2>
class WidgetClass<T1*, T2*> {
public:
	WidgetClass();
	~WidgetClass();
};

template<typename T1, typename T2>
WidgetClass<T1*, T2*>::WidgetClass()
{
	std::cout << "Call from <T1*, T2*> partial specialization, T1 = " << typeid(T1).name() << ", T2 = " << typeid(T2).name() << std::endl;
}

template<typename T1, typename T2>
WidgetClass<T1*, T2*>::~WidgetClass()
{
}

//
// Partial specialization for same type pointer template parameters

template<typename T>
class WidgetClass<T*, T*> {
public:
	WidgetClass();
	~WidgetClass();
};

template<typename T>
WidgetClass<T*, T*>::WidgetClass()
{
	std::cout << "Call from <T*, T*> partial specialization, T = " << typeid(T).name() << std::endl;
}

template<typename T>
WidgetClass<T*, T*>::~WidgetClass()
{
}