
// C++ program for illustration
// of std::allocator() function
#include <iostream>
#include <memory>
#include <map>
using namespace std;
int main()
{

	std::map<std::string, int> m;
	m["hello"] = 1;
	m["world"] = 2;
	m["hallo"] = 3;
	m["sekai"] = 4;

	for(std::map<std::string, int>::iterator it = m.begin(); it != m.end(); ++it)
	{
		cout << it->first << " " << it->second << endl;
	}

	return 0;
}