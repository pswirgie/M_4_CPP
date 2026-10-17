#include <string>
#include <map>
#include <iostream>
#define RED		"\033[31m"
#define RESET	"\033[0m"

template <typename T>
void	printMessage( T& message )
{
	std::cout << message << std::endl;
}

class BitcoinExchange
{
	public:
		BitcoinExchange( void ){};
		BitcoinExchange( const BitcoinExchange& ){};
		BitcoinExchange&	operator=( const BitcoinExchange& ){ return (*this); };
		~BitcoinExchange(){};
	
		void	start( const std::string& inputFile );

	private:
		void	_printError( const std::string& message );
		void	_getDatabase( const std::string& databaseFile );
		void	_parsingInput( const std::string& inputFile );
		void	_calculExchange( const std::string& date, const double& value );
		void	_printMap( const std::map<std::string, double>& arr );
		int		_isValideDate( const std::string& date );
		int		_strTdo( double& target, const std::string& src, const std::string& context );

		std::map<std::string, double>	_dataBase;
};
