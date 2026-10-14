#include "Array.hpp"

template <typename T>
Array<T>::Array( void )
	: _array(NULL), _size(0){};

template <typename T>
Array<T>::Array( unsigned int n ) : _size(n)
{
	_array = new T[n];
	if (!_array)
		throw std::runtime_error("Bad allocation");
	for (size_t i = 0; i < _size; ++i)
		_array[i] = 0;
}

template <typename T>
Array<T>::Array( unsigned int n, unsigned int value ) : _size(n)
{
	_array = new T[n];
	if (!_array)
		throw std::runtime_error("Bad allocation");
	for (size_t i = 0; i < _size; ++i)
		_array[i] = value;
}

template <typename T>
Array<T>::Array( const Array<T>& other ) : _size(other._size)
{
	_array = new T[_size];
	if (!_array)
		throw std::runtime_error("Bad allocation");
	for (size_t i = 0; i < _size; ++i)
		_array[i] = other._array[i];
}

template <typename T>
Array<T>&	Array<T>::operator=( const Array<T>& other)
{
	_size = other._size;
	delete [] _array;
	_array = new T[_size];
	if (!_array)
		throw std::runtime_error("Bad allocation");
	for (size_t i = 0; i < _size; ++i)
		_array[i] = other._array[i];
	return (*this);
}

template <typename T>
Array<T>::~Array<T>( void )
{
	delete [] _array;
}

template <typename T>
T&	Array<T>::operator[]( const unsigned int& index )
{
	if (index < _size)
		return (_array[index]);
	throw std::runtime_error("Index out of range");
}

template <typename T>
size_t	Array<T>::size( void )
{
	return (_size);
}
