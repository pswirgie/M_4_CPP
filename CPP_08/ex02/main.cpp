#include "MutantStack.hpp"
#include <iostream>
#include <vector>

int main( void )
{
	{
		std::cout << "TESTS - MutantStack" << std::endl;
		MutantStack<int> mstack;
	
		mstack.push(5);
		mstack.push(17);
		std::cout << "MutantStack<int> mstack" << std::endl;
		std::cout << "push: 5, 17" << std::endl;
		std::cout << "size: " << mstack.size() << std::endl;
		std::cout << "top (last element): " << mstack.top() << std::endl;
	
		mstack.pop();
		std::cout << "pop (remove last element)" << std::endl;
		std::cout << "size: " << mstack.size() << std::endl;
		mstack.push(3);
		mstack.push(5);
		mstack.push(737);
		//[...]
		mstack.push(16);
		std::cout << "push: 3, 5, 737, 16" << std::endl;
		std::cout << "top (last element): " << mstack.top() << std::endl;
		MutantStack<int>::iterator it = mstack.begin();
		MutantStack<int>::iterator ite = mstack.end();
		++it;
		--it;
		while (it != ite)
		{
			std::cout << *it << std::endl;
			++it;
		}
		std::cout << std::endl;
	
		std::cout << "Copy std::stack<int> s(mstack)" << std::endl;
		std::stack<int> s(mstack);
		std::cout << "top: " << s.top() << std::endl;

		std::cout << std::endl;

	}
	{
		std::cout << "SAME TESTS - std::list" << std::endl;
		std::list<int> mlist;
	
		mlist.push_back(5);
		mlist.push_back(17);
		std::cout << "std::list<int> mlist" << std::endl;
		std::cout << "push_back: 5, 17" << std::endl;
		std::cout << "size: " << mlist.size() << std::endl;
		std::cout << "back (last element): " << mlist.back() << std::endl;
	
		mlist.pop_back();
		std::cout << "pop_back (remove last element)" << std::endl;
		std::cout << "size: " << mlist.size() << std::endl;
		mlist.push_back(3);
		mlist.push_back(5);
		mlist.push_back(737);
		//[...]
		mlist.push_back(16);
		std::cout << "push_back: 3, 5, 737, 16" << std::endl;
		std::cout << "back (last element): " << mlist.back() << std::endl;
		std::list<int>::iterator it = mlist.begin();
		std::list<int>::iterator ite = mlist.end();
		++it;
		--it;
		while (it != ite)
		{
			std::cout << *it << std::endl;
			++it;
		}
		std::cout << std::endl;
	}
	{
		std::cout << "TESTS - Mutant = Mutant" << std::endl;
		std::cout << "MutantStack<int> a -> push(1)" << std::endl;
		std::cout << "MutantStack<int> b -> b = a" << std::endl;
		MutantStack<int> a;
		a.push(1);

		MutantStack<int> b;
		b = a;
		std::cout << "b -> top: " << b.top() << std::endl;
		std::cout << std::endl;
	}
	{
		std::cout << "TESTS - Const Iterator" << std::endl;
		std::cout << "MutantStack<int> c -> push: 1, 2" << std::endl;
		std::cout << "Create const_iterator begin and end" << std::endl;
		MutantStack<int> mstack;
		mstack.push(1);
		mstack.push(2);
		MutantStack<int>::const_iterator it = mstack.begin();
		MutantStack<int>::const_iterator ite = mstack.end();
		++it;
		--it;
		while (it != ite)
		{
			std::cout << *it << std::endl;
			// *it += 1;
			++it;
		}
		std::cout << "Here, we can't modify value pointed by iterator " << std::endl;
		
		std::cout << "Create iterator begin and end" << std::endl;
		std::cout << "*iterator += 1 before print" << std::endl;
		MutantStack<int>::iterator start = mstack.begin();
		MutantStack<int>::iterator end = mstack.end();
		++start;
		--start;
		while (start != end)
		{
			*start += 1;
			std::cout << *start << std::endl;
			++start;
		}
		std::cout << "Here, we can modify value " << std::endl;

		
		std::cout << std::endl;
	}
	return 0;
}
