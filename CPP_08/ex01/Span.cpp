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
	{
		_array.push_back(value);
		return;
	}
	throw std::runtime_error("Forbidden add value");
}

// The shortest span:
// the value between the smallest number and the second smallest number
size_t	Span::shortestSpan( void )
{
	if (_array.size() < 2)
		throw std::runtime_error("Not enough numbers to check");
	std::vector<int>	tmp;
	tmp = _array;
	int	distance = INT_MAX;
	std::sort(tmp.begin(), tmp.end());
	for (size_t i = 0; i < tmp.size(); ++i)
	{
		for (size_t j = i + 1; j < tmp.size(); ++j)
		{
			if (tmp[i + 1] - tmp[i] < distance)
				distance = tmp[i + 1] - tmp[i];
		}
	}
	return (distance);
}

// The longest span:
// the value between the biggest number and the smallest number
size_t	Span::longestSpan( void )
{
	if (_array.size() < 2)
		throw std::runtime_error("Not enough numbers to check");
	std::vector<int>::iterator min = std::min_element(_array.begin(), _array.end());
	std::vector<int>::iterator max = std::max_element(_array.begin(), _array.end());
	return (*max - *min);
}

void	Span::addRange( const std::vector<int>& range )
{
	if ((range.size() + _array.size()) <= _size)
		_array.insert(_array.begin(), range.begin(), range.end());
	else
		throw std::runtime_error("Array is already full");
}

void	Span::print( void )
{
	std::cout << "values:";
	for (size_t i = 0; i < _array.size(); ++i)
		std::cout << "	" << _array[i];
	std::cout << std::endl;
}
