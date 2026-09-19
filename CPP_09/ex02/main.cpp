/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pswirgie <pswirgie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 16:44:47 by pswirgie          #+#    #+#             */
/*   Updated: 2026/08/22 11:15:12 by pswirgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"


void	testsParsing( void )
{
	std::cout << std::endl << std::string(60, '-') << std::endl;
	std::cout << "TESTS - parsing" << std::endl;
	
	PmergeMe all;

	std::cout << std::endl << "No arguments" << std::endl;
	const char* args[] = {"", "", ""};
	all.argsToNumbers(3, (char **)args);
	all.clearArrayA();

	std::cout << std::endl << "One argument" << std::endl;
	const char* args4[] = {"5"};
	all.argsToNumbers(2, (char **)args4);
	all.clearArrayA();

	std::cout << std::endl << "Argument not a num or space" << std::endl;
	const char* args7[] = {"!"};
	all.argsToNumbers(3, (char **)args7);
	all.clearArrayA();

	std::cout << std::endl << "< Int min && negative" << std::endl;
	const char *args2[] = {"-2147483649", "50"};
	all.argsToNumbers(3, (char **)args2);
	all.clearArrayA();

	std::cout << std::endl << "> Int max" << std::endl;
	const char *args3[] = {"2147483648", "50"};
	all.argsToNumbers(3, (char **)args3);
	all.clearArrayA();

	std::cout << std::endl << "Already sorted" << std::endl;
	std::cout << "{24, 75}" << std::endl;
	const char *args5[] = {"24", "75"};
	all.argsToNumbers(3, (char **)args5);
	all.clearArrayA();

	std::cout << "{2, 3, 15, 130, 198, 201}" << std::endl;
	const char *args6[] = {"2", "3", "15", "130", "198", "201"};
	all.argsToNumbers(7, (char **)args6);
	all.clearArrayA();

	std::cout << std::endl << std::string(60, '-') << std::endl;
}

int main( int ac, char **av )
{
	{
		std::cout << std::endl << std::string(60, '-') << std::endl;
		std::cout << "TESTS - terminal" << std::endl;
		std::cout << std::endl;

		PmergeMe all;
		if (ac <= 2 || !av[1])
		{
			all.invalidArguement();
			// return (1);
		}
		else
			all.argsToNumbers(ac, av);
	}
	// testsParsing();

	std::cout << std::endl << std::string(60, '-') << std::endl;
	std::cout << "TESTS" << std::endl << std::endl;

	PmergeMe all;

	// std::cout << "75 4 8741 130 198 25 7" << std::endl;
	// const char *args6[] = {"75", "4", "8741", "130", "198", "25", "7"};
	// all.argsToNumbers(8, (char **)args6);
	// all.algo();
	// all.clearArrayA();

	// std::cout << "5 4 6 1 2 3" << std::endl;
	// const char *args7[] = {"5", "4", "6", "1", "2", "3", "5", "8", "9", "10", "11", "42", "50", "60", "80", "90"};
	// all.argsToNumbers(17, (char **)args7);
	all.algo();
	// all.clearArrayA();

	std::cout << std::endl << std::string(60, '-') << std::endl;
}
