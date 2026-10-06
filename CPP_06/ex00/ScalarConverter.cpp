/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pswirgie <pswirgie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/16 10:11:09 by pswirgie          #+#    #+#             */
/*   Updated: 2026/09/21 15:01:57 by pswirgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

#define RED		"\033[31m"
#define BLUE	"\033[34m"
#define RESET	"\033[0m"

// = MEMBER FUNCTIONS =================================================

void		ScalarConverter::convert( const std::string& src )
{
	if (src.empty())
	{
		std::cerr << RED << "Invalid arguement" << RESET << std::endl;
		return ;
	}

	std::string input = src;
	double value = 0;
	char *end;
	if (input == "nan")
		value = std::numeric_limits<double>::quiet_NaN();
	else
		value = std::strtod(input.c_str(), &end);

	if (std::isnan(value) || std::isinf(value))
	{
		std::cout << "char:	impossible" << std::endl;
		std::cout << "int:	impossible" << std::endl;
		std::cout << "float:	impossible" << std::endl;
		std::cout << "double:	impossible" << std::endl;
		return ;
	}

	bool	(*findType[4])( const std::string& ) ={
		&ScalarConverter::isChar,
		&ScalarConverter::isInt,
		&ScalarConverter::isFloat,
		&ScalarConverter::isDouble
	};

	void	(*printType[4])( const std::string& ) ={
		&ScalarConverter::fromChar,
		&ScalarConverter::fromInt,
		&ScalarConverter::fromFloat,
		&ScalarConverter::fromDouble
	};

	for(int i = 0; i < 4; ++i)
	{
		if (findType[i](src))
		{
			printType[i](src);
			return ;
		}
	}
	std::cerr << RED << "Invalid arguement" << RESET << std::endl;
}

bool	ScalarConverter::isChar( const std::string& src)
{
	if (src.length() == 1
		&& !std::isdigit(src[0]))
	{
		#if DEBUG
		std::cout << BLUE << "[DEBUG] its a char" << RESET << std::endl;
		#endif
		return (true);
	}
	return (false);
}

bool	ScalarConverter::isInt( const std::string& src )
{
	char	*end;
	int		nb = std::strtol(src.c_str(), &end, 10);
	if (!errno && *end == '\0' && (nb >= INT_MIN && nb <= INT_MAX))
	{
		#if DEBUG
		std::cout << BLUE << "[DEBUG] its a int" << RESET << std::endl;
		#endif
		return (true);
	}
	return (false);
}

bool	ScalarConverter::isFloat( const std::string& src )
{
	char	*end;
	std::strtof(src.c_str(), &end);
	if (!errno && *end == 'f')
	{
		#if DEBUG
		std::cout << BLUE << "[DEBUG] its a float" << RESET << std::endl;
		#endif
		return (true);
	}
	return (false);
}

bool	ScalarConverter::isDouble( const std::string& src )
{
	char	*end;
	std::strtod(src.c_str(), &end);
	if (!errno && *end == '\0')
	{
		#if DEBUG
		std::cout << BLUE << "[DEBUG] its a double"<< RESET << std::endl;
		#endif
		return (true);
	}
	return (false);
}

void	ScalarConverter::fromChar( const std::string& src )
{
	char	value = *src.begin();
	std::cout << "char:	" << value << std::endl;
	std::cout << "int:	" << static_cast<int>(value)<< std::endl;
	printFloat(static_cast<float>(value), 1);
	printDouble(static_cast<float>(value), 1);
}

void	ScalarConverter::fromInt( const std::string& src )
{
	char	*end;
	long	valueLong = std::strtol(src.c_str(), &end, 10);
	int		value = std::atoi(src.c_str());
	printChar<int>(value);
	printInt(static_cast<long>(valueLong));
	printFloat(static_cast<float>(value), 1);
	printDouble(static_cast<float>(value), 1);
}

void	ScalarConverter::fromFloat( const std::string& src )
{
	char	*end;
	float	value = std::strtof(src.c_str(), &end);
	printChar<float>(value);
	printInt(static_cast<long>(value));
	if (size_t precis = setPrecision(src))
	{
		printFloat(static_cast<float>(value), precis - 1);
		printDouble(static_cast<double>(value), precis - 1);
	}
	else
	{
		printFloat(static_cast<float>(value), 0);
		printDouble(static_cast<double>(value), 0);
	}
}

void	ScalarConverter::fromDouble( const std::string& src )
{
	char	*end;
	double	value = std::strtod(src.c_str(), &end);
	printChar<double>(value);
	printInt(static_cast<long>(value));
	if (size_t precis = setPrecision(src))
	{
		printFloat(static_cast<float>(value), precis);
		printDouble(static_cast<double>(value), precis);
	}
	else
	{
		printFloat(static_cast<float>(value), 0);
		printDouble(static_cast<double>(value), 0);
	}
}

void	ScalarConverter::printInt( long value )
{
	std::cout << "long:	" << value << std::endl;
	if (value >= INT_MIN && value <= INT_MAX)
		std::cout << "int:	" << static_cast<int>(value) << std::endl;
	else
		std::cout << "int:	impossible" << std::endl;
}


void	ScalarConverter::printFloat( float value, size_t addPrecision )
{
	std::cout << std::fixed << "float:	" << std::setprecision(addPrecision) << value << "f" << std::endl;
}

void	ScalarConverter::printDouble( double value, size_t addPrecision )
{
	std::cout << std::fixed << "double:	" << std::setprecision(addPrecision) << value << std::endl;
}

size_t	ScalarConverter::setPrecision( const std::string& src )
{
	size_t	len = src.length();
	size_t	point = src.find(".");
	bool	null = true;
	size_t	i = point + 1;
	while (i < len - 1)
	{
		// std::cout << "i = " << i << "src[i] = " << src[i] << std::endl;
		if (src[i] != '0' && src[i] != 'f')
			null = false;
		++i;
	}
	return (i - point);
}
