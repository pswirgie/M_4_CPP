#include "BitcoinExchange.hpp"
#include <fstream>
#include <cstdlib>
#include <climits>
#include<bits/stdc++.h>

static const std::string months[] = {"January", "Februray", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

void	BitcoinExchange::start( const std::string& inputFile )
{
	try
	{
		_getDatabase("data.csv");
		// _printMap(_dataBase);
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << "Error: database - " << e.what() << RESET << '\n';
		return ;
	}
	try
	{	_parsingInput(inputFile);	}
	catch(const std::exception& e)
	{
		std::cerr << RED << "Error: input file - " << e.what() << RESET << '\n';
	}
}

void	BitcoinExchange::_getDatabase( const std::string& databaseFile )
{
	std::fstream	file(databaseFile.c_str());
	std::string		buffer;

	if (!file.is_open())
		throw std::runtime_error("permissions denied or missing file");
	
	std::getline(file, buffer);
	while (std::getline(file, buffer))
	{
		size_t delimiter = buffer.find(",");
		if (delimiter == std::string::npos)
			throw std::runtime_error("invalid format for: " + buffer);
		std::string date(buffer.substr(0, delimiter));
		std::string valueStr(buffer.substr(delimiter + 1));
		if (date.empty() || valueStr.empty())
			throw std::runtime_error("invalid format for: " + buffer);
		double value = _strTdo(valueStr);
		if (_dataBase[date])
			throw std::runtime_error("date already have a value for: " + buffer);
		_dataBase[date] = value;
	}
	file.close();
}

void	BitcoinExchange::_parsingInput( const std::string& inputFile )
{
	std::fstream	file(inputFile.c_str());
	std::string		buffer;

	if (!file.is_open())
		throw std::runtime_error("permissions denied or missing");

	std::getline(file, buffer);
	if (buffer != "date | value")
		throw std::runtime_error("invalid format for: " + buffer + ", required: \"date | value\"");

	while (std::getline(file, buffer))
	{
		size_t delimiter = buffer.find("|");
		if (delimiter == std::string::npos)
			throw std::runtime_error("invalid format for \"" + buffer + "\", required: \"[date] | [value]\"");
		std::string dateStr(buffer.substr(0, delimiter));
		std::string tmpValueStr(buffer.substr(delimiter + 1));
		// 1. "[date][space]|[space][value]"
		if (dateStr.empty() || tmpValueStr.empty()
			|| dateStr[dateStr.size() - 1] != ' '
			|| tmpValueStr[0] != ' ')
			throw std::runtime_error("invalid format for: " + buffer);

		std::string valueStr(tmpValueStr.substr(1, tmpValueStr.size() - 1));
		
		// 2. date: Year-Month-Day
		_isValideDate(dateStr);

		// 3. value: a float or a positive integer, between 0 and 1000
		double valueD = _strTdo(valueStr);
		if (valueD < 0 || valueD > 1000)
			throw std::runtime_error("Value \"" + valueStr + "\" is invalid,"
				"format required: a float or a positive integer, between 0 and 1000");

				

	}
	file.close();
}

void	BitcoinExchange::_isValideDate( const std::string& date )
{
	// Date: [Year]-[Month]-[Day]
	// Year >= creation bitcoin
	// Month: [1 - 12]
	// Day: [01 - 31] -> ! 30 or 31 ! -> Leap year

	// Is format: [Year]-[Month]-[Day]
	size_t delimiter = date.find('-');
	if (delimiter == std::string::npos)
		throw std::runtime_error("invalid format for: " + date);
	std::string yearStr(date.substr(0, delimiter));
	std::string monthStr(date.substr(delimiter + 1, 2));
	delimiter = date.find('-', delimiter + 1);
	if (delimiter == std::string::npos)
		throw std::runtime_error("invalid format for: " + date);
	std::string dayStr(date.substr(delimiter + 1, 2));

	// convert to double
	double yearD = _strTdo(yearStr);
	double monthD = _strTdo(monthStr);
	double dayD = _strTdo(dayStr);
	// std::cout << year << std::endl;
	// std::cout << yearStr << std::endl;
	// std::cout << month << std::endl;
	// std::cout << monthStr << std::endl;
	// std::cout << day << std::endl;
	// std::cout << dayStr << std::endl;

	if (yearD < 2009 || (yearD < 2009 && dayD < 3))
		throw std::runtime_error("Date " + date + " is before Bitcoin creation");
	if (yearD >= INT_MAX)
		throw std::runtime_error("Are you sure you will be alive ? or Earth will be ?");
	if (monthD < 1 || monthD > 12)
		throw std::runtime_error("month " + monthStr + " unexist");
	if (dayD < 1 || dayD > 31)
		throw std::runtime_error("day " + dayStr + " unexist");
	else
	{ // Leap year -> search on wikipedia
		// (year % 4) == 0 -> leap
		// (year % 1000) == 0 -> no leap, but if (year % 400) == 0 -> leap
		int		year = (int)yearD;
		int		month = (int)monthD;
		int		day = (int)dayD;
		if (month == 2)
		{
			bool	leap = false;
			if ((year % 4) == 0)
			{
				if ((year % 100) == 0)
				{
					leap = false;
					if ((year % 400) == 0)
						leap = true;
				}
				else
					leap = true;
			}
			if (leap && day > 29)
				throw std::runtime_error("Leap year " + yearStr + ", day " + dayStr + " unexist for " + date);
			if (!leap && day > 28)
				throw std::runtime_error("February day " + dayStr + " unexist for " + date);
		}
		if (month == 4 || month == 6 || month == 9 || month == 11)
		{
			if (day > 30)
				throw std::runtime_error("Month " + months[month] + " has only 30 days, not " + dayStr);
		}
	}
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

std::string	BitcoinExchange::_getWordFromStr( const std::string& src, size_t* start, const size_t& end, const std::string& context)
{
	size_t	i = *start;
	size_t	wordEnd = 0;

	if (src.empty())
		return (std::string());
	while (i < end)
	{
		if (!std::isspace(src[i]))
		{
			wordEnd = i;
			while (wordEnd < end && !std::isspace(src[wordEnd]))
				wordEnd++;
			if (wordEnd > i)
			{
				std::string res = src.substr(i, wordEnd - i);
				*start = wordEnd;
				return (res);
			}
			break;
		}
		++i;
	}
	if (i >= end)
	{
		*start = i;
		return (std::string());
	}
	throw std::runtime_error(context + " getWord() wrong format");
}

double	BitcoinExchange::_strTdo( const std::string& src )
{
	double	value;
	char	*pEnd;
	value = std::strtod(src.c_str(), &pEnd);
	if ( *pEnd != '\0' || errno == ERANGE || value < 0 )
		throw std::runtime_error("invalid value for: " + src);
	return (value);
}

// std::stringstream	ss;
// ss << valueD;
// std::string res(ss.str());
// std::cout << res << std::endl;
