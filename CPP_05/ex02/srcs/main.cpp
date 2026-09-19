/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pswirgie <pswirgie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 10:18:33 by pswirgie          #+#    #+#             */
/*   Updated: 2026/09/19 14:47:59 by pswirgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Bureaucrat.hpp"
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
	std::cout << "Tests pattern : " << std::endl;
	std::cout << "- 1 new form by category." << std::endl;
	std::cout << "- bureaucrat Quentin with a high level 3 can sign and excute all." << std::endl;
	std::cout << "- bureaucrat Martin with a low level 150 can't sign and excute any." << std::endl;
	std::cout << "- bureaucrat X with level enough for sign but not excute." << std::endl;


// Abtract Class --------------------------------------------------------------------------------------------------------
	std::cout << std::endl << std::string(60, '-') << std::endl;
	std::cout << "TESTS - Abstract Class" << std::endl << "Please uncomment in the main the line to see the error." << std::endl;

	// AForm formulaire;


// Shrubbery --------------------------------------------------------------------------------------------------------
	std::cout << std::endl << std::string(60, '-') << std::endl;
	std::cout << "TESTS - Shrubbery : gardeSign 145 - gradeExec 137" << std::endl;
	std::cout << std::endl;

	std::cout << BROWN << "TESTS - Quentin, grade 3 sign a permis and execute it" << RESET << std::endl;
	Bureaucrat quentin("Quentin", 3);
	AForm *permis = new ShrubberyCreationForm("permis");
	quentin.signForm(*permis);
	quentin.executeForm(*permis);
	std::cout << std::endl;

	std::cout << BROWN << "TESTS - Martin doesn't sign certificate and try to execute it" << RESET << std::endl;
	Bureaucrat martin("Martin", 150);
	AForm *certificate = new ShrubberyCreationForm("certificate");
	martin.executeForm(*certificate);
	std::cout << std::endl;

	std::cout << BROWN << "TESTS - Martin, grade 150, try to sign certificate" << RESET << std::endl;
	martin.signForm(*certificate);
	std::cout << std::endl;

	std::cout << BROWN << "TESTS - Lupin, grade 138, try to sign and execute certificate" << RESET << std::endl;
	Bureaucrat lupin("Lupin", 138);
	lupin.signForm(*certificate);
	lupin.executeForm(*certificate);

	delete permis;
	delete certificate;

// Robotomy --------------------------------------------------------------------------------------------------------

	std::cout << std::endl << std::string(60, '-') << std::endl;
	std::cout << "TESTS - Robotomy : gardeSign 72 - gradeExec 45" << std::endl << std::endl;
	
	std::cout << BROWN << "TESTS - Quentin, grade 3, try to sign degree" << RESET << std::endl;
	AForm *degree = new RobotomyRequestForm("degree");
	quentin.signForm(*degree);
	quentin.executeForm(*degree);
	quentin.executeForm(*degree);
	std::cout << BROWN << "In order to relaunch the random (successfully 50% of the time), make re and run the program again." << RESET << std::endl;
	std::cout << std::endl;

	std::cout << BROWN << "TESTS - Martin, grade 150, try to sign degree" << RESET << std::endl;
	martin.executeForm(*degree);
	std::cout << std::endl;

	std::cout << BROWN << "TESTS - Alexandrin, grade 46, try to sign and excute degree" << RESET << std::endl;
	Bureaucrat alexandrin("Alexandrin", 46);
	alexandrin.signForm(*degree);
	alexandrin.executeForm(*degree);
	std::cout << std::endl;

	delete degree;

// Presidential --------------------------------------------------------------------------------------------------------

	std::cout << std::endl << std::string(60, '-') << std::endl;
	std::cout << "TESTS - Presidential : gardeSign 25 - gradeExec 5" << std::endl << std::endl;

	std::cout << BROWN << "TESTS - Quentin, grade 3, try to sign degree" << RESET << std::endl;
	AForm *punishement = new PresidentialPardonForm("punishement");
	quentin.signForm(*punishement);
	quentin.executeForm(*punishement);
	std::cout << std::endl;

	std::cout << BROWN << "TESTS - Martin, grade 150, try to sign degree" << RESET << std::endl;
	martin.signForm(*punishement);
	martin.executeForm(*punishement);
	std::cout << std::endl;

	std::cout << BROWN << "TESTS - Albin, grade 6, try to sign degree" << RESET << std::endl;
	Bureaucrat albin("Alexandrin", 6);
	albin.signForm(*punishement);
	albin.executeForm(*punishement);

	delete punishement;

	std::cout << std::endl << std::string(60, '-') << std::endl << std::endl;
}