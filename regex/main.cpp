
#include <regex>
#include <iostream>
using namespace std;

int main() {
	regex  reg("[0-9]+");
	if (regex_match("123000", reg)) {
		cout << "It's a match!" << endl;
	}
	return 0;
}
