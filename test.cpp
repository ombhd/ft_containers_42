
// C++ program for illustration
// of std::allocator() function
#include <iostream>
#include <memory>
using namespace std;
int main()
{

	// allocator for integer values
	allocator<int> myAllocator;

	// allocate space for five ints
	int *arr = myAllocator.allocate(5);

	// construct arr[0] and arr[3]
	for (size_t i = 0; i < 5; i++)
	{
		myAllocator.construct(&arr[i], arr[i]);
		cout << arr[i] << endl;
	}

	arr[3] = 10;

	// cout << arr[3] << endl;
	// cout << arr[0] << endl;

	// deallocate space for five ints
	myAllocator.deallocate(arr, 5);

	return 0;
}