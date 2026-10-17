#include "BitcoinExchange.hpp"
#include <fstream>
#include <cstdlib>
#include <climits>
#include<bits/stdc++.h>

static const std::string months[] = {"January", "Februray", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

void	BitcoinExchange::start( const std::string& inputFile )
{
	try
	{	_getDatabase("data.csv");
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
		double value;
		if (_strTdo(value, valueStr, "_getDatabase()"))
		{
			throw std::runtime_error("");
			break;
		}
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
		{
			_printError("invalid format for \"" + buffer + "\", required: \"[date] | [value]\"");
			continue;
		}
		size_t len = delimiter;
		if (!std::isdigit(buffer[delimiter]))
			--len;
		std::string dateStr(buffer.substr(0, len));
		std::string tmpValueStr(buffer.substr(delimiter + 1));
	
		// 1. "[date][space]|[space][value]"
		if (dateStr.empty() || tmpValueStr.empty()
			|| buffer[delimiter - 1] != ' '
			|| tmpValueStr[0] != ' ')
		{
			_printError("_parsingInput() - invalid format for: " + buffer);
			continue;
		}

		std::string valueStr(tmpValueStr.substr(1, tmpValueStr.size() - 1));
		
		// 2. date: Year-Month-Day
		if (_isValideDate(dateStr))
			continue;

		// 3. value: a float or a positive integer, between 0 and 1000
		double valueD;
		if (_strTdo(valueD, valueStr, "_parsingInput()"))
			continue;
		if (valueD < 0 || valueD > 1000)
		{
			_printError("value \"" + valueStr + "\" is invalid,"
				" format required: a float or a positive integer, between 0 and 1000");
			continue;
		}

		// Send date and value to calcul
		_calculExchange(dateStr, valueD);
	}
	file.close();
}

int	BitcoinExchange::_isValideDate( const std::string& date )
{
	// Date: [Year]-[Month]-[Day]
	// Year >= creation bitcoin
	// Month: [1 - 12]
	// Day: [01 - 31] -> ! 30 or 31 ! -> Leap year

	// Is format: [Year]-[Month]-[Day]
	size_t delimiterYear = date.find('-');
	if (delimiterYear == std::string::npos)
	{
		_printError("_isValideDate() - invalid format for: " + date);
		return (1);
	}
	size_t delimiterMonth = date.find('-', delimiterYear + 1);
	if (delimiterMonth == std::string::npos)
	{
		_printError("_isValideDate() - invalid format for: " + date);
		return (1);
	}

	size_t len = delimiterYear;
	std::string yearStr(date.substr(0, len));
	len = delimiterMonth - delimiterYear;
	--len;
	std::string monthStr(date.substr(delimiterYear + 1, len));
	len = (date.size() - delimiterMonth) + 1;
	std::string dayStr(date.substr(delimiterMonth + 1, len + 2));

	// convert to double
	double yearD;
	if (_strTdo(yearD, yearStr, "_isValideDate() - year"))
		return (1);
	double monthD; 
	if (_strTdo(monthD, monthStr, "_isValideDate() - month"))
		return (1);
	double dayD;
	if (_strTdo(dayD, dayStr, "_isValideDate() - day"))

	if (yearD < 2009 || (yearD < 2009 && dayD < 3))
	{
		_printError(date + " is before Bitcoin creation");
		return (1);
	}
	if (yearD >= INT_MAX)
	{
		_printError(date + " are you sure you will be alive ? or Earth will be ?");
		return (1);
	}
	if (monthD < 1 || monthD > 12)
	{
		_printError(date + " month " + monthStr + " unexist");
		return (1);
	}
	if (dayD < 1 || dayD > 31)
	{
		if (dayD == 0)
		{
			_printError(date + " day can't unexist");
			return (1);
		}
		_printError(date + " day " + dayStr + " unexist");
		return (1);
	}
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
			{
				_printError(date + " leap year " + yearStr + ", day " + dayStr + " unexist");
				return (1);
			}
			if (!leap && day > 28)
			{
				_printError(date + " February day " + dayStr + " unexist");
				return (1);
			}
		}
		if (month == 4 || month == 6 || month == 9 || month == 11)
		{
			if (day > 30)
			{
				_printError(date + " month " + months[month] + " has only 30 days, not " + dayStr);
				return (1);
			}
		}
	}
	return (0);
}

void	BitcoinExchange::_printMap( const std::map<std::string, double>& arr )
{
	std::map<std::string, double>::const_iterator it;
	for (it = arr.begin(); it != arr.end(); ++it)
		std::cout << it->first << " -> " << it->second << std::endl;
}

int	BitcoinExchange::_strTdo( double& target, const std::string& src, const std::string& context )
{
	double	value;
	char	*pEnd;
	value = std::strtod(src.c_str(), &pEnd);
	if ( *pEnd != '\0' || errno == ERANGE || value < 0 )
	{
		_printError(context + " invalid value for: " + src);
		return (1);
	}
	target = value;
	return (0);
}

void	BitcoinExchange::_calculExchange( const std::string& date, const double& value )
{
	std::map<std::string, double>::const_iterator matchDate;
	matchDate = _dataBase.begin();
	while (matchDate != _dataBase.end())
	{
		if (matchDate->first > date || matchDate->first == date)
			break;
		++matchDate;
	}
	if (matchDate->first != date)
		--matchDate;
	#ifdef DEBUG
	std::cout << "Database: " << matchDate->first << " -> " << matchDate->second << std::endl;
	std::cout << "Value: " << value << std::endl;
	#endif
	double res = value * matchDate->second;
	std::stringstream	ss;
	ss << matchDate->second << " = " << res;
	std::cout << date << " => " << ss.str() << std::endl;
}

void	BitcoinExchange::_printError( const std::string& message )
{
	std::cerr << RED << "Error: " << message << RESET << std::endl;
}
