#include "iter.hpp"
#include <iostream>
#include <string>

template <typename T>
void	print( T& element )
{
	std::cout << element << std::endl;
}

int main( void )
{
	char		arrChr[] = {'a', 'b'};
	int			arrInt[2] = {1, 2};
	std::string	arrStr[] = {"coucou", "les"};

	std::cout << BROWN << "Char:" << RESET << std::endl;
	iter(arrChr, 2, &print<char>);

	std::cout << BROWN << "int:" << RESET << std::endl;
	iter(arrInt, 2, &print<int>);

	std::cout << BROWN << "const string:" << RESET << std::endl;
	iter(arrStr, 2, &print<std::string>);
	return 0;
}
