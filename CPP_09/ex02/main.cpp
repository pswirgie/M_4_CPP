/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pswirgie <pswirgie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 16:44:47 by pswirgie          #+#    #+#             */
/*   Updated: 2026/10/13 09:36:27 by pswirgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void	testsParsing( void )
{
	std::cout << std::endl << BLUE << std::string(60, '-') << std::endl;
	std::cout << "1. TESTS - parsing\n" << RESET;
	
	PmergeMe all;

	std::cout << std::endl << "No arguments\n" << "{\"./Pmerge\", \"\", \"\"}" << std::endl;
	const char* args[] = {"./Pmerge", "", ""};
	all.algo(3, (char **)args);

	std::cout << std::endl << "One argument\n" << "{\"./Pmerge\", \"5\"}" << std::endl;
	const char* args4[] = {"./Pmerge", "5"};
	all.algo(2, (char **)args4);

	std::cout << std::endl << "Argument not a num or space\n" << "{\"./Pmerge\", \"!\"}" << std::endl;
	const char* args7[] = {"./Pmerge", "!"};
	all.algo(3, (char **)args7);

	std::cout << std::endl << "< Int min && negative\n" << "{\"./Pmerge\", \"-2147483649\", \"50\"}" << std::endl;
	const char *args2[] = {"./Pmerge", "-2147483649", "50"};
	all.algo(3, (char **)args2);

	std::cout << std::endl << "> Int max\n" << "{\"./Pmerge\", \"2147483648\", \"50\"}" << std::endl;
	const char *args3[] = {"./Pmerge", "2147483648", "50"};
	all.algo(3, (char **)args3);

	std::cout << std::endl << "Already sorted simple\n" << "{24, 75}" << std::endl;
	const char *args5[] = {"./Pmerge", "24", "75"};
	all.algo(3, (char **)args5);

	std::cout << std::endl << "Already sorted\n" << "{2, 3, 15, 130, 198, 201}" << std::endl;
	const char *args6[] = {"./Pmerge", "2", "3", "15", "130", "198", "201"};
	all.algo(7, (char **)args6);
}

void	testsDivers( void )
{
	std::cout << std::endl << BLUE << std::string(60, '-') << std::endl;
	std::cout << "2. TESTS - divers\n" << RESET << std::endl;
	
	PmergeMe all;
	
	std::cout << "10 8 7 9 6 3 4 5 2 1 11" << std::endl;
	const char *args1[] = {"./Pmerge", "10", "8", "7", "9", "6", "3", "4", "5", "2", "1", "11"};
	all.algo(12, (char **)args1);
	std::cout << std::endl;

	std::cout << "75 4 8741 130 198 25 7" << std::endl;
	const char *args2[] = {"./Pmerge", "75", "4", "8741", "130", "198", "25", "7"};
	all.algo(8, (char **)args2);
	std::cout << std::endl;

	std::cout << "5 4 6 1 2 3 5 8 9 10 11 42 50 60 80 90" << std::endl;
	const char *args3[] = {"./Pmerge", "5", "4", "6", "1", "2", "3", "5", "8", "9", "10", "11", "42", "50", "60", "80", "90"};
	all.algo(17, (char **)args3);
	std::cout << std::endl;

}

int main( int ac, char **av )
{

	std::cout << BLUE << "Welcome to this tester\n";
	std::cout << "1. Tests parsing\n" << "2. Tests divers\n" << "3. Test terminal\n";
	std::cout << "See if result is sorted: make sorted && ./PmergeMe [numbers]\n" << RESET;

	// 1. Tests Parsing --------
	testsParsing();

	// 2. Tests Divers --------
	testsDivers();

	(void)ac;
	(void)av;

	// 3. Tests Divers --------
	{
		std::cout << std::endl << BLUE << std::string(60, '-') << std::endl;
		std::cout << BLUE << "3. TESTS - terminal\n" << RESET;
		std::cout << std::endl;

		PmergeMe all;
		all.algo(ac, av);
	}
	std::cout << std::endl << BLUE << std::string(60, '-') << RESET << std::endl;
}
