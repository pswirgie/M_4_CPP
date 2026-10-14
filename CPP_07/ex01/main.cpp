#include "iter.hpp"
#include <iostream>
#include <string>

void	print( char& element )
{
	std::cout << element << std::endl;
}

void	print( std::string const& element )
{
	std::cout << element << std::endl;
}

void	print( int& element )
{
	std::cout << element << std::endl;
}

int main( void )
{

	char		arrChr[] = {'a', 'b'};
	int			arrInt[2] = {1, 2};
	std::string	arrStr[] = {"coucou", "les"};

	std::cout << BROWN << "Char:" << RESET << std::endl;
	iter(arrChr, 2, &print);

	std::cout << BROWN << "size_t:" << RESET << std::endl;
	iter(arrInt, 2, &print);

	std::cout << BROWN << "const string:" << RESET << std::endl;
	iter(arrStr, 2, &print);
	return 0;
}