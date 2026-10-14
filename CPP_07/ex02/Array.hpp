#pragma once
#include <iostream>

template <typename T>
class Array
{
	public:
		Array<T>( void );
		Array<T>( unsigned int n );
		Array<T>( unsigned int n, unsigned int value );
		Array<T>( const Array<T>& other );
		Array<T>&	operator=( const Array<T>& other);
		~Array<T>( void );
		T&	operator[]( const unsigned int& index );
		size_t	size( void );

	private:
		T* _array;
		size_t _size;
};

#include "Array.tpp"
