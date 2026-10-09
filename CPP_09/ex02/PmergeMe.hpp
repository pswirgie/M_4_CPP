/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pswirgie <pswirgie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 16:30:25 by pswirgie          #+#    #+#             */
/*   Updated: 2026/10/09 15:38:30 by pswirgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <vector>
#include <iostream>
#include <sstream>
#include <climits>
#include <stdlib.h>
#include <errno.h>
#include <cmath>
#include <iomanip>

#define RED		"\033[31m"
#define CYAN	"\033[36m"
#define LYLA	"\033[35m"
#define BLUE	"\033[34m"
#define BROWN	"\033[33m"
#define RESET	"\033[0m"
#define GROUP	3
#define FILLIGN	50

enum LevelMessage
{
	INFO,
	TRACE,
	ERROR,
	DEBUGS
};

template <typename T>
void	printMessage(LevelMessage level, const std::string &header, const T &message)
{
	std::ostringstream stream;
	stream << message;

	std::ostream &out = (level == ERROR) ? std::cerr : std::cout;

	switch (level)
	{
		case (INFO):
		{
			out << BROWN << "[INFO]	- " << header << stream.str() << RESET << std::endl;
			return;
		}
		case (TRACE):
		{
			out << BLUE << "[TRACE]	- " << header << stream.str() << RESET << std::endl;
			return;
		}
		case (DEBUGS):
		{
			out << RESET << "[DEBUG]	- " << header << stream.str() << RESET << std::endl;
			return;
		}
		case (ERROR):
		{
			out << RED << "[ERROR]	- " << header << stream.str() << RESET << std::endl;
			return;
		}
		default:
		{
			out << RED << "[ERROR]	- " << header << stream.str() << RESET << std::endl;
		}
	}
}

/*
Arr = array
Grp = groupe
*/
class PmergeMe
{
	public:
		PmergeMe( void );
		void	insertNumber( void );
		int		argsToNumbers( int ac, char **av );
		void	invalidArguement( void );
		void	clearArrayA( void );
		void	printArray( char arr, bool sortByLoseWin );
		void	algo( void );
		
	private:
		void	_sortAll( size_t levelIteration, size_t sizeGrp );
	
		int		_sendToArray( std::string str );
		bool	_isSorted( std::vector<int>& arr );
		size_t	_nbGrp( size_t sizeArr, size_t sizeGrp );
		void	_orderGrp( size_t sizeGrp );
		void	_moveRange( size_t start, size_t length, size_t newIndex, std::vector<int>& src, std::vector<int>& dst );
		void	_allLosersToArrayB( size_t sizeGrp, size_t nbGrp );
		void	_pushToArr( size_t start, size_t length, std::vector<int>& src, std::vector<int>& dst );
		int		_binarySearch( std::vector<int>& arr, int nbTarget );
		void	_insertGrpBinarySearch( std::vector<int>& arr, int nbTarget, size_t startGrp, size_t sizeGrp );

		void	_initSuiteJacobsthal( void );
		size_t	_getSuiteJacobsthal( void );
		void	_printArrayJacobsthal( void );

		std::vector<int>			_arrayA;
		std::vector<int>			_arrayB;
		std::vector<size_t>			_suiteJacobsthal; // give the last group Index for comparsion inorder to insert losers
		std::vector<int>::iterator	it;
};