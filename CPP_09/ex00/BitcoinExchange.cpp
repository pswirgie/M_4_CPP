#include "BitcoinExchange.hpp"
#include <fstream>
#define RED		"\033[31m"
#define RESET	"\033[0m"

void	BitcoinExchange::start( const std::string& valuesFile )
{
	try
	{
		_readDatabase();
		(void) valuesFile;
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << e.what() << RESET << '\n';
	}
	
}

void	BitcoinExchange::_readDatabase( void )
{
	std::fstream	file("data.csv");
	std::string		buffer;

	if (!file.is_open())
		throw std::runtime_error("Permissions denied or missing database file");
	while (getline(file, buffer))
		_rawDatabase.push_back(buffer);
	file.close();
	for (size_t i = 0; i < _rawDatabase.size(); ++i)
		printMessage(_rawDatabase[i]);
}

