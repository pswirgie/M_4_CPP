#include <string>
#include <vector>
#include <iostream>

template <typename T>
void	printMessage( T& message )
{
	std::cout << message << std::endl;
}

class BitcoinExchange
{
	public:
		// forme canonique a faire
		void	start( const std::string& databaseName );

	private:
		void	_readDatabase( void );

		std::vector<std::string>	_rawDatabase;
};
