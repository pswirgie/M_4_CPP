#include <string>
#include <stack>
#define RED		"\033[31m"
#define RESET	"\033[0m"

enum OperatorType
{
	ADD,
	SUBSTRACT,
	DIVIDE,
	MULTIPLY
};

enum Level
{
	INFO,
	TRACE,
	ERROR,
	DEBUGS
};

class RPN
{
	public:
		RPN( void ){};
		RPN( const RPN& ){};
		RPN&	operator=( const RPN& ){ return (*this); };
		~RPN(){};

		void	start( const std::string& src );
		void	_parsing( const std::string& src );
		template <typename T>
		void	printMessage(Level level, const std::string &header, const T &message);
		
	private:
		double	_strTdo( const std::string& src, const std::string& context );
		bool	_isOperatorStr( const std::string& src );
		bool	_isOperatorChr( const char& src );
		void	_calcul( void );
		std::string	_getWordFromStr( const std::string& src, size_t* start,
			const size_t& end, const std::string& context );
		bool	_isDigitOnly( const std::string& src );

		std::stack<int>	_stack;
		int				_res;
		OperatorType	_operatorType;
};
