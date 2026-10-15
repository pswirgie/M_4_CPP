#include "MutantStack.hpp"
#include <iostream>
#include <vector>

int main( void )
{
	MutantStack<int> mstack;

	mstack.push(5);
	mstack.push(17);
	std::cout << "push: 5, 17" << std::endl;
	std::cout << "size: " << mstack.size() << std::endl;
	std::cout << "top (last element): " << mstack.top() << std::endl;

	mstack.pop();
	std::cout << "pop (remove first element)" << std::endl;
	std::cout << "size: " << mstack.size() << std::endl;
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	//[...]
	mstack.push(0);
	std::cout << "push: 3, 5, 737, 0" << std::endl;
	std::cout << "top: " << mstack.top() << std::endl;
	MutantStack<int>::iterator it = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();
	++it;
	--it;
	while (it != ite)
	{
		std::cout << *it << std::endl;
		++it;
	}

	std::stack<int> s(mstack);
	MutantStack<int>::iterator it = s.begin();
	MutantStack<int>::iterator ite = s.end();
	for (; it != ite; ++it)
		std::cout << *it << std::endl;
	return 0;
}
