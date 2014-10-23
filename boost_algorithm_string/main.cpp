#include <iostream>
#include <boost/algorithm/string.hpp>
using namespace std;
using namespace boost;
int main()
{
	string s1(" hello world! ");
	cout << "value      : '" << s1 << "'" << endl;

	to_upper(s1);
	cout << "to_upper() : '" << s1 << "'" << endl;

	trim(s1);
	cout << "trim()     : '" << s1 << "'" << endl;

	return 0;
}
