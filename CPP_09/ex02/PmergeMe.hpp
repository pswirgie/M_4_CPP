/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pswirgie <pswirgie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 16:30:25 by pswirgie          #+#    #+#             */
/*   Updated: 2026/10/13 09:01:47 by pswirgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <vector>
#include <deque>
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
#define FILLIGN	50

enum LevelMessage
{
	INFO,
	TRACE,
	ERROR,
	DEBUGS
};

enum ContainerType
{
	VECTOR,
	DEQUE
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
		void	algo( int ac, char **av );
		
	private:
		void	_parsing( int ac, char **av );
		void	_invalidArguement( void );
		template <typename T>
		bool	_isSorted( const T& arr );
		template <typename T>
		void	_printArray( const T& arr );
		template <typename T>
		void	_printArrayWithIndexs( const std::string& context, const T& arr, bool sortByLoseWin,size_t sizeGrp );

		template <typename T>
		void	_sortAll( ContainerType type, T& arrA, size_t levelIteration, size_t sizeGrp );
		template <typename T>
		void	_startSort( T& arrA, ContainerType type );
		template <typename T>
		void	_printAfter( ContainerType type, const T& arr );
		
		size_t	_nbGrp( size_t sizeArr, size_t sizeGrp );
		size_t	_nbGrpStrict( size_t sizeArr, size_t sizeGrp );
		template <typename T>
		void	_orderGrp( T& arr, size_t sizeGrp );
		template <typename T>
		void	_moveRange( bool deleteFromSrc, size_t startGrp, size_t length, size_t newIndex, T& src, T& dst );
		template <typename T>
		void	_allLosersToArrayB( T& arrA, T& arrB, T& indexWinnerA, size_t sizeGrp, size_t nbGrp );
		template <typename T>
		void	_pushToArr( size_t start, size_t length, bool deleteFromSrc, T& src, T& dst );
		template <typename T>
		size_t	_binarySearch( T& arr, int nbTarget, size_t sizeGrp, size_t endSearch);
		template <typename T>
		void	_insertGrpBinarySearch( T& arrA, T&arrB, T& indexWinnerA, size_t sizeGrp, size_t indexNextGrpToInsert, size_t isInter );
		template <typename T>
		void	_initLeftOvers( T& arrA, T& leftOver, size_t sizeGrp, size_t nbGrp );
		template <typename T>
		void	_printArrBWithWinnerIndex( T& arrB, T& indexWinnerA, size_t sizeGrp );
		
		template <typename T>
		void	_initSuiteJacobsthal( T& arr );
		template <typename T>
		size_t	_getSuiteJacobsthal( T& suiteJaco );
		template <typename T>
		void	_printArrayJacobsthal( const T& arr  );

		std::vector<int>		_unsortedNumbers;
};
