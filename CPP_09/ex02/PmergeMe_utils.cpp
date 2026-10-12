/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe_utils.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pswirgie <pswirgie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 16:44:29 by pswirgie          #+#    #+#             */
/*   Updated: 2026/10/12 18:50:24 by pswirgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void PmergeMe::_sendToArray( std::string str )
{
	char *end;
	long nb = std::strtol(str.c_str(), &end, 10); // INT MIN, INT MAX
	// std::cout << BLUE << "[DEBUG] " << nb << RESET << std::endl;
	if (errno || nb < 0 || nb > INT_MAX)
		_invalidArguement();
	_arrayA.push_back((int)nb);
}

void	PmergeMe::_printArrBWithWinnerIndex( ContainerType type, size_t sizeGrp )
{
	printMessage(DEBUGS, "Print _array B with winner Index", std::string(FILLIGN - 20, '-'));
	std::cout << BLUE << "ArrB:";
	// for (size_t i = 0; i < _arrayB.size(); ++i)
	size_t i = 0;
	while ((type == VECTOR && i < _arrayB.size())
			|| (type == DEQUE && i < _DarrayB.size()))
	{
		std::cout << "	" << std::setfill('0') << std::setw(2) << (type == VECTOR ? _arrayB[i] : _DarrayB[i]);
		++i;
	}
	i = 0;
	std::cout << std::endl << LYLA << "Iwin:";
	while ((type == VECTOR && i < _indexWinnerA.size())
			|| (type == DEQUE && i < _DindexWinnerA.size()))
	{
		std::cout << std::string(sizeGrp, '	') << std::setfill('0') << std::setw(2) << (type == VECTOR ? _indexWinnerA[i] : _DindexWinnerA[i]);
		++i;
	}
	std::cout << RESET << std::endl;
	printMessage(DEBUGS, "", std::string(FILLIGN, '-'));
}

void	PmergeMe::clearArrayA( void )
{
	_arrayA.clear();
	_DarrayA.clear();
}

size_t	PmergeMe::_nbGrp( size_t sizeArr, size_t sizeGrp )
{
	size_t res = ceil(static_cast<double>(sizeArr) / sizeGrp);
	// std::cout << BROWN << "[DEBUG] _nbGrp -> res: " << res << RESET << std::endl;
	return (res);
}

size_t	PmergeMe::_nbGrpStrict( size_t sizeArr, size_t sizeGrp )
{
	size_t res = floor(sizeArr / sizeGrp);
	// printMessage(DEBUGS, "_nbGrpStrict() - res: ", res);
	return (res);
}
