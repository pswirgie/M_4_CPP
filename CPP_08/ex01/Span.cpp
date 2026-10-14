#include "Span.hpp"

Span::Span( void )
	: _size(0) {};

Span::Span( unsigned int N )
	: _size(N) {};

Span::Span( const Span& other )
	: _array(other._array), _size(other._size) {};

Span& Span::operator=( const Span& other )
{
	if (this != &other)
	{
		if (_array.size())
			_array.clear();
		_array = other._array;
		_size = other._size;
	}
	return (*this);
}

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

void	Span::addRange( void )
{
	 
}

