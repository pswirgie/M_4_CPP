#include "Span.hpp"

Span::Span( unsigned int N )
	: _size(N) {};

void	Span::addNumber( int value )
{
	if (_array.size() < _size)
		_array.push_back(value);
	throw std::runtime_error("Forbidden add value");
}

size_t	Span::shortestSpan( void )
{
	if (_array.size() < 2)
		throw std::runtime_error("Not enough numbers to check");
	
}

size_t	Span::longestSpan( void )
{
	if (_array.size() < 2)
		throw std::runtime_error("Not enough numbers to check");
	
}
