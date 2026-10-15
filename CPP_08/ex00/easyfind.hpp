#pragma once
#include <iostream>
#include <stdexcept>
#include <bits/stdc++.h>

template <typename T>
size_t	easyfind( T& arr, int value )
{
	typename T::const_iterator find;

	find = std::find(arr.begin(), arr.end(), value);
	if (find == arr.end())
		throw std::runtime_error("No occurrence found");
	return (find - arr.begin());
}
