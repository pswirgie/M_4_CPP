#include <iostream>

#define BROWN "\033[33m"
#define RESET "\033[0m"

template <typename T>
void	iter( T* arr, const size_t& len, void (*func) (T &) )
{
	for (size_t i = 0; i < len; ++i)
		func(arr[i]);
}

template <typename T>
void	iter( T* arr, const size_t& len, void (*func) (T const &) )
{
	for (size_t i = 0; i < len; ++i)
		func(arr[i]);
}
