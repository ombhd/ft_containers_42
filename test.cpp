
// C++ program for illustration
// of std::allocator() function
#include <iostream>
#include <memory>
#include <map>
using namespace std;
int main()
{

	std::map<int, int> m;


	std::map<int, int>::iterator it = m.end();
	std::cout << "last =|" << it->second << "|" << it->first<< "|" << std::endl;


	it = m.begin();
	std::cout << "first =|" << it->second << "|" << it->first<< "|" << std::endl;

	return 0;
}