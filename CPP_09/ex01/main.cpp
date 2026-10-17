#include <iostream>
#include "RPN.hpp"

int	main( int ac, char **av )
{
	if (ac != 2 || !av[1])
	{
		std::cerr << RED << "Error: 1 argument required" << RESET << std::endl;
		return (1);
	}
	RPN	calcul;
	calcul.start(av[1]);
	return (0);
}
