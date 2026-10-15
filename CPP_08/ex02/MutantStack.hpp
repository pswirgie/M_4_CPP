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

		typedef typename std::stack<T>::container_type containerType;

		typedef typename containerType::iterator iterator;
		iterator	begin();
		iterator	end();

		typedef typename containerType::const_iterator const_iterator;
		const_iterator	begin() const;
		const_iterator	end() const;
};

#include "MutantStack.tpp"
