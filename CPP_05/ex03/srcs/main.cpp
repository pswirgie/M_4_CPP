/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pswirgie <pswirgie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 10:18:33 by pswirgie          #+#    #+#             */
/*   Updated: 2026/09/19 14:49:31 by pswirgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Bureaucrat.hpp"
#include "../includes/Intern.hpp"
#include "../includes/PresidentialPardonForm.hpp"
#include "../includes/RobotomyRequestForm.hpp"
#include "../includes/ShrubberyCreationForm.hpp"
#include <exception>
#include <iostream>
#define RED		"\033[31m"
#define BROWN	"\033[33m"
#define RESET	"\033[0m"


int main( void )
{
	std::cout << std::endl << std::string(60, '-') << std::endl;

// Intern --------------------------------------------------------------------------------------------------------
	std::cout << BROWN << "TESTS - Intern : create each form + try create with form wrong name" << RESET << std::endl;
	std::cout << std::endl;

	Intern slave;

	std::cout << "shrubbery creation : ";
	AForm *shrubbery = slave.makeForm("shrubbery creation", "certificate");
	std::cout << "robotomy request : ";
	AForm *robotomy = slave.makeForm("robotomy request", "degree");
	std::cout << "presidential pardon : ";
	AForm *presidential = slave.makeForm("presidential pardon", "sentence");
	std::cout << std::endl;

	AForm *shrubbery2 = slave.makeForm("wrong name", "certificate");

// Use forms --------------------------------------------------------------------------------------------------------
	std::cout << std::endl << std::string(60, '-') << std::endl;
	std::cout << BROWN << "TESTS - A bureaucrat Martin, garde 1, will use the forms" << RESET << std::endl;
	std::cout << std::endl;

	Bureaucrat martin("Martin", 1);

	std::cout << BROWN << "TESTS - sign all" << RESET << std::endl;
	martin.signForm(*shrubbery);
	if (shrubbery2)
		martin.signForm(*shrubbery2);
	else
		std::cout << RED << "Martin try to sign form wrong name given to intern unsuccessfully." << RESET << std::endl;
	martin.signForm(*robotomy);
	martin.signForm(*presidential);
	std::cout << std::endl;

	std::cout << BROWN << "TESTS - excute all" << RESET << std::endl;
	martin.executeForm(*shrubbery);
	martin.executeForm(*robotomy);
	martin.executeForm(*presidential);

	delete shrubbery;
	delete shrubbery2;
	delete robotomy;
	delete presidential;

	std::cout << std::endl << std::string(60, '-') << std::endl << std::endl;
}