#if !defined(TEMPL_H)
#define TEMPL_H

template<typename T>
struct MyGrade {
	const int value = 10;
};

// For 12.3.3
class CallCtr {
public:
	CallCtr() {
		std::cout << "CallCtr::CallCtr()" << std::endl;
	}
	void callMe() {
		std::cout << "CallCtr::callMe" << std::endl;
	}

private:
	CallCtr(CallCtr const&);
};

template<typename T>
class CallHolder {
public:
	static T tt;
};

template<>
CallCtr CallHolder<CallCtr>::tt;

#endif