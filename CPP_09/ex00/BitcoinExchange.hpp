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
		// forme canonique a faire
		void	start( const std::string& inputFile );

	private:
		void	_getDatabase( const std::string& databaseFile );
		void	_parsingInput( const std::string& inputFile );
		void	_calculValues( void );
		void	_printMap( const std::map<std::string, double>& arr );
		void	_isValideDate( const std::string& date );
		double	_strTdo( const std::string& src );
		std::string	_getWordFromStr( const std::string& src, size_t* start,
				const size_t& end, const std::string& context);

		std::map<std::string, double>	_dataBase;
};
