#if !defined(TEMPL_H)
#define TEMPL_H

// For 12.3.3
class CallCtr {
public:
	CallCtr(int n=0) {
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
#endif