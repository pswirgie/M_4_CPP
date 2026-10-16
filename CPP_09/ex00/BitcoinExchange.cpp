#include "BitcoinExchange.hpp"
#include <fstream>
#include <cstdlib>


void	BitcoinExchange::start( const std::string& inputFile )
{
	try
	{
		_getDatabase("data.csv");
		// _printMap(_dataBase);
		_parsingInput(inputFile);
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << "Error: " << e.what() << RESET << '\n';
	}
	
}

void	BitcoinExchange::_getDatabase( const std::string& databaseFile )
{
	std::fstream	file(databaseFile.c_str());
	std::string		buffer;
	std::string		context("database - ");

	if (!file.is_open())
		throw std::runtime_error(context + "permissions denied or missing file");
	
	std::getline(file, buffer);
	while (std::getline(file, buffer))
	{
		size_t delimiter = buffer.find(",");
		if (delimiter == std::string::npos)
			throw std::runtime_error(context + "invalid format for: " + buffer);
		std::string date(buffer.substr(0, delimiter));
		std::string valueStr(buffer.substr(delimiter + 1));
		if (date.empty() || valueStr.empty())
			throw std::runtime_error(context + "invalid format for: " + buffer);
		long	value;
		char	*pEnd;
		value = std::strtod(valueStr.c_str(), &pEnd);
		if ( *pEnd != '\0' || errno == ERANGE || value < 0 )
			throw std::runtime_error(context + "invalid value");
		if (_dataBase[date])
			throw std::runtime_error(context + "date already have a value");
		_dataBase[date] = value;
	}
	file.close();
}

void	BitcoinExchange::_parsingInput( const std::string& inputFile )
{
	std::fstream	file(inputFile.c_str());
	std::string		buffer;
	std::string		context("input - ");
	if (!file.is_open())
		throw std::runtime_error(context + "permissions denied or missing");

	std::getline(file, buffer);
	if (buffer != "date | value")
		throw std::runtime_error(context + "invalid format for: " + buffer + ", required: \"date | value\"");

	while (std::getline(file, buffer))
	{
		size_t delimiter = buffer.find("|");
		if (delimiter == std::string::npos)
			throw std::runtime_error(context + "invalid format for: " + buffer);
		std::string date(buffer.substr(0, delimiter));
		std::string valueStr(buffer.substr(delimiter + 1));
		// 1. "[date][space]|[space][value]"
		if (date.empty() || valueStr.empty()
			|| date[date.size() - 1] != ' '
			|| valueStr[0] != ' ')
			throw std::runtime_error(context + "invalid format for: " + buffer);
		
		// 2. date: Year-Month-Day
		_isValideDate(date);

		// 3. value: a float or a positive integer, between 0 and 1000
	}
	file.close();
}

void	BitcoinExchange::_isValideDate( const std::string& date )
{
	std::string		context("input - ");
	// Date: [Year]-[Month]-[Day]
	// Year >= creation bitcoin
	// Month: [1 - 12]
	// Day: [01 - 31] -> ! 30 or 31 ! -> Leap year

	size_t delimiter = date.find('-');
	if (delimiter == std::string::npos)
		throw std::runtime_error(context + "invalid format for: " + date);
	std::string year(date.substr(0, delimiter));
	std::string month(date.substr(delimiter + 1));
	delimiter = date.find('-', delimiter + 1);
	if (delimiter == std::string::npos)
		throw std::runtime_error(context + "invalid format for: " + date);
	std::string day(date.substr(0, delimiter + 1));


}

void	BitcoinExchange::_calculValues( void )
{
	/*
	Your program should display on the standard output the result of the value multiplied
by the exchange rate according to the date indicated in your database.
	If the date used in the input does not exist in your DB then you
must use the closest date contained in your DB. Be careful to use the
lower date and not the upper one.

	1. trouver la date correspondante a celle demander par l input file 
		si pas trouver, prendre la premiere date en dessous
	2. multpilier la valeur du inputFile par la valeur de la database
	3. 
	*/


}

void	BitcoinExchange::_printMap( const std::map<std::string, double>& arr )
{
	std::map<std::string, double>::const_iterator it;
	for (it = arr.begin(); it != arr.end(); ++it)
		std::cout << it->first << " -> " << it->second << std::endl;
}
