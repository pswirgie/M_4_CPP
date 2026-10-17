#include <iostream>
#include "RPN.hpp"

int	main( int ac, char **av )
{
	if (ac != 2 || !av[1])
	{
		std::cerr << RED << "Error: could not open file" << RESET << std::endl;
		return (1);
	}
	BitcoinExchange algo;
	algo.start(av[1]);
	return (0);
}
