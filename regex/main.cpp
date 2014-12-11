
#include <regex>
#include <iostream>
using namespace std;

void SoTest1() {
	std::string s("aaabbbccd123456eeffgg");
	std::smatch match;
	std::regex braced_regex("([a-zA-Z_]+)(\\d{2,})(\\w+)");
	std::regex plus_regex("(\\w+)(\\d+)(\\w+)");

	auto printer = [](decltype(*match.begin())& match) {
		std::ssub_match sub(match);
		std::string match_substring(sub.str());
		std::cout << match_substring << '\n';
	};

	std::regex_match(s, match, braced_regex);
	std::cout << "Number of braced matches: " << match.size() << '\n';
	std::for_each(match.begin(), match.end(), printer);

	std::regex_match(s, match, plus_regex);
	std::cout << "Number of plus matches: " << match.size() << '\n';
	std::for_each(match.begin(), match.end(), printer);
	return;
}

int main() {

	SoTest1();

	regex  reg("[0-9]+");
	if (regex_match("123000", reg)) {
		cout << "It's a match!" << endl;
	}
	return 0;
}
