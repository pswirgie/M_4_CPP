/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pswirgie <pswirgie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 10:16:50 by pswirgie          #+#    #+#             */
/*   Updated: 2026/09/21 15:09:52 by pswirgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"
#include <iostream>

#define RED		"\033[31m"
#define BROWN	"\033[33m"
#define RESET	"\033[0m"

int main( int , char ** )
{
	std::cout << std::endl << std::string(60, '-') << std::endl;
	std::cout << BROWN << "TESTS" << RESET << std::endl;
	std::cout << std::endl;

	Data	myData;
	std::cout << BROWN << "Create Data mydata"<< RESET << std::endl;
	myData.data = "myContent";
	std::cout << "myData content : " << myData.data << std::endl;
	std::cout << std::endl;

	std::cout << BROWN << "Serialize &myData -> uintptr_t intptr" << std::endl;
	std::cout << "Deserialize intptr ->  Data *ptr " << RESET << std::endl;
	uintptr_t intptr = Serializer::serialize(&myData);
	Data *ptr = Serializer::deserialize(intptr);
	std::cout << std::endl;

	std::cout << "ptr Adress :	" << ptr << std::endl;
	std::cout << "myData adress :	" << &myData << std::endl;
	std::cout << "myData adress :	" << myData.data << std::endl;

	std::cout << std::endl << std::string(60, '-') << std::endl;
}
