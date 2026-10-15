#include <iostream>
#include "BitcoinExchange.hpp"

int	main( int ac, char **av )
{
	if (ac != 2 || !av[1])
	{
		std::cerr << "Required 1 argument" << std::endl;
		return (1);
	}
	// caution !!! annne bisextil, mois en 30 ou 31, fevrier en 28 ou 27
	BitcoinExchange algo;
	algo.start(av[1]);
	return (0);
}
