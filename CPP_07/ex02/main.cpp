#include "Array.hpp"
#include <iostream>

int main( void )
{
	Array<int> a(5);
	Array<int> b(6, 8);
	Array<int> c(6, 10);

	try
	{
		std::cout << "a (5 indexs, filled with 0)" << std::endl;
		std::cout << "value for a[4]: " << a[4] << std::endl;
		std::cout << "size a: " << a.size() << std::endl << std::endl;

		std::cout << "a = b (6 index, filled with 8)" << std::endl;
		a = b;
		std::cout << "value for a[5]: " << a[5] << std::endl;
		std::cout << "size a: " << a.size() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		return (1);
	}
	return (0);
}
