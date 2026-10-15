#include <iostream>
#include <stdexcept>
#include <bits/stdc++.h>

class Span
{
	public:
		Span( void );
		Span( unsigned int N );
		Span( const Span& other );
		Span&	operator=( const Span& other );

		void	addNumber( int value );
		size_t	shortestSpan( void );
		size_t	longestSpan( void );
		void	addRange( const std::vector<int>& range );
		void	print( void );


	private:
		std::vector<int>	_array;
		unsigned int		_size;
};
