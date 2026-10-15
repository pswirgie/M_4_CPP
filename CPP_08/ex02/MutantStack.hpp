#pragma once

#include <iostream>
#include <stdexcept>
#include <bits/stdc++.h>
#include <stack>

template <typename T>
class MutantStack: public std::stack<T>
{
	public:
		MutantStack( void ){};
		MutantStack( const MutantStack& other );
		MutantStack&	operator=( const MutantStack& other );
		~MutantStack( void ){};

		typedef typename std::stack<T>::container_type::iterator iterator;
		iterator begin();
		iterator end();
};

#include "MutantStack.tpp"
