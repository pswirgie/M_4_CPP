#include <iostream>
#include <stdexcept>
#include <bits/stdc++.h>

class Span
{
	public:
		Span( unsigned int N );
		void	addNumber( int value );
		size_t	shortestSpan( void );
		size_t	longestSpan( void );


	private:
		std::vector<int>	_array;
		unsigned int		_size;
};
