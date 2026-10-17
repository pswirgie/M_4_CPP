#include "RPN.hpp"
#include <iostream>
#include <stdexcept>
#include <cerrno>
#include <bits/stdc++.h>

static const std::string	operatorStr[4] = {"+", "-", "/", "*"};
static const OperatorType	operatorTypes[4] = {ADD, SUBSTRACT, DIVIDE, MULTIPLY};
#define OPERATORS 4

void	RPN::start( const std::string& src )
{
	try
	{
		_parsing(src);

	}
	catch(const std::exception& e)
	{
		std::cerr << RED << "Error: " << e.what() << '\n';
	}
}

void	RPN::_parsing( const std::string& src )
{
	// 1. is sign at end ?
	bool	isSign = false;
	for (size_t i = src.size() - 1; i > 0; --i)
	{
		if (_isOperatorChr(src[i]))
			isSign = true;
		if (std::isdigit(src[i]))
		{
			if(!isSign)
				throw std::runtime_error("sign required at end");
			break;
		}
	}

	//2. is sign at begin ?
	bool	isNb = false;
	// printMessage(DEBUGS, "parsing; ", src);
	for (size_t i = 0; i > src.size(); ++i)
	{
		if (_isOperatorChr(src[i]))
		{
			if(!isNb)
				throw std::runtime_error("sign can't be at begin");
			break;
		}
		if (std::isdigit(src[i]))
			isNb = true;
	}

	// 2. add to stack + check if [0;9]
	std::string word;
	size_t i = 0;
	size_t end = src.size();
	word = _getWordFromStr(src, &i, end, "_parsing() - ");
	if (word.empty())
		throw std::runtime_error("numbers required");
	// bool	isNumbers = false;
	// printMessage(DEBUGS, "parsing; ", word);
	while (!word.empty())
	{
		// add stack
		if (_isDigitOnly(word))
		{
			double nbD = _strTdo(word, "_parsing() - ");
			_stack.push((int)nbD);
		}
		// char	nbChr = word[0];
		if (_isOperatorStr(word))
		{
			// _calcul();
			// _stack.clear();
			// isNumbers = true;
		}
		word = _getWordFromStr(src, &i, end, "_parsing() - ");
	}
}

double	RPN::_strTdo( const std::string& src, const std::string& context )
{
	double	value;
	char	*pEnd;
	value = std::strtod(src.c_str(), &pEnd);
	if ( *pEnd != '\0' || errno == ERANGE || value < 0 || value > 9 )
		throw std::runtime_error(context + "invalid number, format: [0:9]");
	return (value);
}

bool	RPN::_isOperatorStr( const std::string& src )
{
	// printMessage(DEBUGS, "_isOperator", "");
	for (size_t i = 0; i < OPERATORS; ++i)
	{
		// printMessage(DEBUGS, "_isOperator: ", operatorStr[i]);
		// printMessage(DEBUGS, "src: ", src);
		if (src == operatorStr[i])
		{
			_operatorType = operatorTypes[i];
			return (true);
		}
	}
	return (false);
}

bool	RPN::_isOperatorChr( const char& src )
{
	for (size_t i = 0; i < OPERATORS; ++i)
	{
		// printMessage(DEBUGS, "_isOperator: ", operatorStr[i][0]);
		// printMessage(DEBUGS, "src: ", src);
		if (src == operatorStr[i][0])
		{
			_operatorType = operatorTypes[i];
			return (true);
		}
	}
	return (false);
}

void	RPN::_calcul( void )
{
	int	nb = -1;
	if (!_stack.empty())
		nb = _res;
	(void) nb;
	std::stack<int> temp(_stack);
	while (!temp.empty())
	{
		std::cout << temp.top() << " ";
		temp.pop();
	}
}

std::string	RPN::_getWordFromStr( const std::string& src, size_t* start,
	const size_t& end, const std::string& context )
{
	size_t	i = *start;
	size_t	wordEnd = 0;

	if (src.empty())
		return (std::string());
	// printMessage(DEBUGS, "getWordFromStr - src: ", src);
	while (i < end)
	{
		if (!std::isspace(src[i]) && !_isOperatorChr(src[i])
			&& src[i] != '(' && src[i] != ')')
		{
			wordEnd = i;
			while (wordEnd < end && !std::isspace(src[wordEnd])
					&& !_isOperatorChr(src[wordEnd])
					&& src[wordEnd] != '(' && src[wordEnd] != ')')
			{
				// printMessage(DEBUGS, "getWordFromStr - src[i]: ", src[wordEnd]);
				wordEnd++;
			}
			if (wordEnd > i)
			{
				std::string res = src.substr(i, wordEnd - i);
				*start = wordEnd;
				// printMessage(DEBUGS, "getWordFromStr - res: ", res);
				return (res);
			}
			break;
		}
		++i;
	}
	if (i >= end)
	{
		*start = i;
		return (std::string());
	}
	throw std::runtime_error(context + " getWord() wrong format");
}

bool	RPN::_isDigitOnly( const std::string& src )
{
	for (size_t i = 0; i < src.size(); ++i)
	{
		if (!std::isdigit(src[i]))
			return (false);
	}
	return (true);
}

template <typename T>
void	RPN::printMessage(Level level, const std::string &header, const T &message)
{
	std::ostringstream stream;
	stream << message;

	std::ostream &out = (level == ERROR) ? std::cerr : std::cout;
	out << RED;
	switch (level)
	{
		case (INFO):
		{
			out << "[INFO]	- ";
			break;
		}
		case (TRACE):
		{
			out << "[TRACE]	- ";
			break;
		}
		case (DEBUGS):
		{
			out << "[DEBUG]	- ";
			break;
		}
		case (ERROR):
		{
			out << "[ERROR]	- ";
			break;
		}
		default:
		{
			out << "[ERROR]	- ";
		}
	}
	out << header << stream.str() << RESET << std::endl;
}
