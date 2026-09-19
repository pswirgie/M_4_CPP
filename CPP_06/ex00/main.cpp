/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pswirgie <pswirgie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/16 09:52:14 by pswirgie          #+#    #+#             */
/*   Updated: 2026/09/19 14:38:35 by pswirgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <iostream>
#include <string>
#include <sstream>

#define RED		"\033[31m"
#define BROWN	"\033[33m"
#define RESET	"\033[0m"

int main( int ac, char **av )
{
	std::cout << std::endl << std::string(60, '-') << std::endl;
	std::cout << BROWN << "TESTS - Pattern by types" << std::endl;
	std::cout << "1. Subject tests if given" << std::endl;
	std::cout << "2. Custom tests" << std::endl;
	std::cout << "With make re, we can show the input type " << RESET << std::endl;

// Custom -------------------------------------------------------------------------------
	std::cout << std::endl << std::string(30, '-') << std::endl;
	std::cout << BROWN << "TESTS - Argument test"<< RESET << std::endl;
	
	if (ac == 2 && av[1])
		ScalarConverter::convert(av[1]);
	else
		std::cerr << RED << "Required one argument" << RESET << std::endl;

// Char -------------------------------------------------------------------------------
	std::cout << std::endl << std::string(30, '-') << std::endl;
	std::cout << BROWN << "TESTS - Char"<< RESET << std::endl << std::endl;

	std::cout << BROWN << "b"<< RESET << std::endl;
	ScalarConverter::convert("b");

// Int -------------------------------------------------------------------------------
	std::cout << std::endl << std::string(30, '-') << std::endl;
	std::cout << BROWN << "TESTS - Int"<< RESET << std::endl << std::endl;

	std::cout << BROWN << "SUBJECT 0"<< RESET << std::endl;
	ScalarConverter::convert("0");
	std::cout << std::endl;

	std::cout << BROWN << "28"<< RESET << std::endl;
	ScalarConverter::convert("28");
	std::cout << std::endl;

	std::cout << BROWN << "2147483648 - overload"<< RESET << std::endl;
	ScalarConverter::convert("2147483648");
	std::cout << std::endl;

	std::cout << BROWN << "-2147483649 - overload"<< RESET << std::endl;
	ScalarConverter::convert("-2147483649");


// Float -------------------------------------------------------------------------------
	std::cout << std::endl << std::string(30, '-') << std::endl;
	std::cout << BROWN << "TESTS - Float"<< RESET << std::endl << std::endl;

	std::cout << BROWN << "SUBJECT 42.0f"<< RESET << std::endl;
	ScalarConverter::convert("42.0f");
	std::cout << std::endl;

	std::cout << BROWN << "0.42f"<< RESET << std::endl;
	ScalarConverter::convert("0.42f");
	std::cout << std::endl;

	std::cout << BROWN << "4521.9856f"<< RESET << std::endl;
	ScalarConverter::convert("4521.9856f");

// Double -------------------------------------------------------------------------------
	std::cout << std::endl << std::string(30, '-') << std::endl;
	std::cout << BROWN << "TESTS - Double"<< RESET << std::endl << std::endl;

	std::cout << BROWN << "0.4254151"<< RESET << std::endl;
	ScalarConverter::convert("0.4254151");
	std::cout << std::endl;

	std::cout << BROWN << "42121.0000"<< RESET << std::endl;
	ScalarConverter::convert("42121.0000");
	std::cout << std::endl;

	std::cout << BROWN << "87512.55264112"<< RESET << std::endl;
	ScalarConverter::convert("87512.55264112");
	

// Nan -------------------------------------------------------------------------------
	std::cout << std::endl << std::string(30, '-') << std::endl;
	std::cout << BROWN << "TESTS - SUBJECT - Nan test" << RESET << std::endl;
	ScalarConverter::convert("nan");

	std::cout << std::endl << std::string(60, '-') << std::endl;
}
