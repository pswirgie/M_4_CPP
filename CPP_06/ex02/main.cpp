/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pswirgie <pswirgie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 10:16:50 by pswirgie          #+#    #+#             */
/*   Updated: 2026/09/19 14:36:29 by pswirgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include <iostream>
#include <typeinfo>
#include <cstdlib>

#define RED		"\033[31m"
#define BROWN	"\033[33m"
#define RESET	"\033[0m"

Base	*generate( void )
{
	srand(time(0));
	int randomNum = rand() % 3;
	std::cout << "randomNum = " << randomNum << std::endl;
	switch (randomNum)
	{
		case 0:
			return ( new A );
		case 1:
			return ( new B );
		default:
			return ( new C );
	}
}

void	identify( Base *p )
{
	if (dynamic_cast<A*>(p))
		std::cout << "A identified" << std::endl;
	else if (dynamic_cast<B*>(p))
		std::cout << "B identified" << std::endl;
	else if (dynamic_cast<C*>(p))
		std::cout << "C identified" << std::endl;
	else
		std::cout << RED << "Type unknown" << RESET << std::endl;
}

void	identify( Base &p )
{
	try{
		(void)dynamic_cast<A&>(p);
		std::cout << "A identified" << std::endl;
	}
	catch (std::bad_cast&)
	{
		try{
			(void)dynamic_cast<B&>(p);
			std::cout << "B identified" << std::endl;
		}
		catch (std::bad_cast&)
		{
			try{
				(void)dynamic_cast<C&>(p);
				std::cout << "C identified" << std::endl;
			}
			catch (std::bad_cast&)
			{
				std::cout << RED << "Type unknown" << RESET << std::endl;
			}
		}
	}
}

int main( int , char ** )
{
	std::cout << std::endl << std::string(60, '-') << std::endl;
	std::cout << BROWN << "TESTS" << RESET << std::endl;
	std::cout << std::endl;

	std::cout << BROWN << "Generate a class" << RESET << std::endl;
	Base *basePtr = generate();

	std::cout << std::endl;

	std::cout << BROWN << "Identify this class" << RESET << std::endl;
	std::cout << BROWN << "Base *basePtr" << RESET << std::endl;
	identify(basePtr);
	std::cout << BROWN << "Base &baseRef = B" << RESET << std::endl;
	B b;
	Base &baseRef = b;
	identify(baseRef);
	std::cout << std::endl;

	std::cout << BROWN << "Try to identify invalid class D" << RESET << std::endl;
	std::cout << BROWN << "Base *basePtr2" << RESET << std::endl;
	Base *basePtr2 = new D;
	identify(basePtr2);
	std::cout << BROWN << "Base &baseRef2" << RESET << std::endl;
	D d;
	Base &baseRef2 = d;
	identify(baseRef2);

	delete basePtr;
	delete basePtr2;

	std::cout << std::endl << std::string(60, '-') << std::endl;
}
