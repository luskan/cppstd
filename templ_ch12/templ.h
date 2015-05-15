#if !defined(TEMPL_H)
#define TEMPL_H

template<typename T>
struct MyGrade {
	const int value = 10;
};

// For 12.3.3
class CallCtr {
public:
	CallCtr(int n) {
		std::cout << "CallCtr::CallCtr()" << std::endl;
		value = 17;
	}
	void callMe() {
		std::cout << "CallCtr::callMe: " << value << std::endl;
	}

private:
	CallCtr(CallCtr const&);
	int value;
};

template<typename T>
class CallHolder {
public:
	static T tt;
};

//template<>
//CallCtr CallHolder<CallCtr>::tt;

#endif