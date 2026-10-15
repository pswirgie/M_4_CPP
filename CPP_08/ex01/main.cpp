#include "Span.hpp"
#include <iostream>
#include <vector>
#define RED		"\033[31m"
#define RESET	"\033[0m"

int main( void )
{
	{
		try
		{
			std::cout << "Too many addNumbers:" << std::endl;
			std::cout << "Span sp = Span(5);" << std::endl;
			std::cout << "addNumbers x 6" << std::endl;
			Span sp = Span(5);
			sp.addNumber(6);
			sp.addNumber(3);
			sp.addNumber(17);
			sp.addNumber(17);
			sp.addNumber(17);
			sp.addNumber(17);
		}
		catch(const std::exception& e)
		{
			std::cerr << RED << e.what() << RESET << '\n';
		}
	}
	std::cout << std::endl;
	{
		try
		{
			std::cout << "Spans:" << std::endl;
			std::cout << "Span sp = Span(5);" << std::endl;
			std::cout << "addNumbers: 10, 6, 2" << std::endl;
			Span sp2 = Span(5);
			sp2.addNumber(10);
			sp2.addNumber(6);
			sp2.addNumber(2);
			std::cout << "Shortest span is: " << sp2.shortestSpan() << std::endl;
			std::cout << "Longest span is: " << sp2.longestSpan() << std::endl;
			
			std::cout << std::endl;
			std::cout << "AddRange:" << std::endl;
			std::cout << "Before:" << std::endl;
			sp2.print();
			std::vector<int> range;
			range.push_back(3);
			range.push_back(4);
			sp2.addRange(range);
			std::cout << "After:" << std::endl;
			sp2.print();
		}
		catch(const std::exception& e)
		{
			std::cerr << RED << e.what() << RESET << '\n';
		}
	}
	return 0;
}
