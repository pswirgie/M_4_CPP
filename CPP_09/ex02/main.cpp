/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pswirgie <pswirgie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 16:44:47 by pswirgie          #+#    #+#             */
/*   Updated: 2026/10/12 15:35:14 by pswirgie         ###   ########.fr       */
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
	all.algo(3, (char **)args);
	all.clearArrayA();

	std::cout << std::endl << "One argument" << std::endl;
	const char* args4[] = {"./Pmerge", "5"};
	all.algo(2, (char **)args4);
	all.clearArrayA();

	std::cout << std::endl << "Argument not a num or space" << std::endl;
	const char* args7[] = {"./Pmerge", "!"};
	all.algo(3, (char **)args7);
	all.clearArrayA();

	std::cout << std::endl << "< Int min && negative" << std::endl;
	const char *args2[] = {"./Pmerge", "-2147483649", "50"};
	all.algo(3, (char **)args2);
	all.clearArrayA();

	std::cout << std::endl << "> Int max" << std::endl;
	const char *args3[] = {"./Pmerge", "2147483648", "50"};
	all.algo(3, (char **)args3);
	all.clearArrayA();

	std::cout << std::endl << "Already sorted simple" << std::endl;
	std::cout << "{24, 75}" << std::endl;
	const char *args5[] = {"./Pmerge", "24", "75"};
	all.algo(3, (char **)args5);
	all.clearArrayA();

	std::cout << std::endl << "Already sorted" << std::endl;
	std::cout << "{2, 3, 15, 130, 198, 201}" << std::endl;
	const char *args6[] = {"./Pmerge", "2", "3", "15", "130", "198", "201"};
	all.algo(7, (char **)args6);
	all.clearArrayA();

	std::cout << std::endl << std::string(60, '-') << std::endl;
}

int main( int ac, char **av )
{
	testsParsing();

	{
		std::cout << "TESTS - terminal" << std::endl;
		std::cout << std::endl;

		PmergeMe all;
		all.algo(ac, av);
	}

	std::cout << std::endl << std::string(60, '-') << std::endl;
	std::cout << "TESTS - divers" << std::endl << std::endl;

	PmergeMe all;

	// tester nombre pair impair
	// mettre en place l autorisatin d avoir des doublons
	// + modifier le code pour accepeter les doublons
	// tester : ./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`
	
	// std::cout << "10 8 7 9 6 3 4 5 2 1 11" << std::endl;
	// const char *args6[] = {"./Pmerge", "10", "8", "7", "9", "6", "3", "4", "5", "2", "1", "11"};
	// all.argsToNumbers(13, (char **)args6);
	// all.algo();
	// all.clearArrayA();

	// std::cout << "75 4 8741 130 198 25 7" << std::endl;
	// const char *args6[] = {"./Pmerge", "75", "4", "8741", "130", "198", "25", "7"};
	// all.argsToNumbers(9, (char **)args6);
	// all.algo();
	// all.clearArrayA();

	// std::cout << "5 4 6 1 2 3 5 8 9 10 11 42 50 60 80 90" << std::endl;
	// const char *args7[] = {"./Pmerge", "5", "4", "6", "1", "2", "3", "5", "8", "9", "10", "11", "42", "50", "60", "80", "90"};
	// all.algo(18, (char **)args7);
	// all.clearArrayA();

	std::cout << std::endl << std::string(60, '-') << std::endl;
}
