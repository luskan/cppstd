// ConsoleApplication2.cpp : Defines the entry point for the console application.
//


class Outer {
	int b;

	class Inner {
	public:
		int a;

		Inner(Outer* p) {
			p->b = 12;
		}

	};

	void call(Inner* p) {
		p->a = 1;
	}

};

int main(int argc, char** argv)
{
	return 0;
}

