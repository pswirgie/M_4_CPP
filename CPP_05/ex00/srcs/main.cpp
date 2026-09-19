/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pswirgie <pswirgie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 10:18:33 by pswirgie          #+#    #+#             */
/*   Updated: 2026/09/19 14:06:32 by pswirgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Bureaucrat.hpp"
#include <exception>
#include <iostream>
#define RED		"\033[31m"
#define RESET	"\033[0m"

int main( void )
{
	std::cout << std::endl << std::string(60, '-') << std::endl << std::endl;
	try 
	{
		Bureaucrat ();
		Bureaucrat jean("Jean");
		Bureaucrat mish("Mich", 15);
		Bureaucrat jeanTwin(jean);

		std::cout << "TESTS - getter et setter" << std::endl << std::endl;
		
		
		std::cout << jean.getName() << " have the garde " << jean.getGrade() << std::endl;
		std::cout << "Jean is incredible, he has score 72 at final exam." << std::endl;
		std::cout << "(Jean upgrade 78 times)" << std::endl;
		for (int i = 0; i < 78; ++i)
			jean.incrementGrade();
		std::cout << "So Jean have the garde " << jean.getGrade() << std::endl;
		for (int i = 0; i < 135; ++i)
			mish.decrementGrade();
		std::cout << "(Mish downgrade 135 times)" << std::endl;
		std::cout << "But imaginary Mish has cheated so he have the grade " << mish.getGrade();
		std::cout << std::endl << std::endl;

		std::cout << "Overload << :" << std::endl;
		std::cout << jean;
	
	}
	catch (std::exception & e)
	{	std::cout << RED << e.what() << RESET << std::endl;	}





	std::cout << std::endl << std::string(60, '-') << std::endl << std::endl;
	std::cout << "TESTS - limits" << std::endl << std::endl;
	
	try
	{
		Bureaucrat mish("Mich", 15);
		std::cout << "Recreate a Mish(15) and try to downgrade 150 times." << std::endl;
		for (int i = 0; i < 150; ++i)
			mish.decrementGrade();
	}
	catch (std::exception & e)
	{	std::cout << RED << e.what() << RESET << std::endl;	}
	
	try
	{
		std::cout << "Create Mickeal(152)" << std::endl;
		Bureaucrat ("Mickeal", 152);
	}
	catch (std::exception & e)
	{	std::cout << RED << e.what() << RESET << std::endl;	}

	try
	{	
		std::cout << "Create Jim(-1)" << std::endl;
		Bureaucrat ("Jim", -1);
	}
	catch (std::exception & e)
	{	std::cout << RED << e.what() << RESET << std::endl;	}

	std::cout << std::endl << std::string(60, '-') << std::endl << std::endl;
}