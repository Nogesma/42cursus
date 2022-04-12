//
// Created by Mano Segransan on 3/3/22.
//

#include "MutantStack.hpp"
#include <iostream>
#include <algorithm>
#include <list>

int main() {
	{
		MutantStack<int> mstack;
		mstack.push(5);
		mstack.push(17);
		std::cout << mstack.top() << std::endl;
		mstack.pop();
		std::cout << mstack.size() << std::endl;
		mstack.push(3);
		mstack.push(5);
		mstack.push(737);
//[...]
		mstack.push(0);
		MutantStack<int>::iterator it = mstack.begin();
		MutantStack<int>::iterator ite = mstack.end();
		++it;
		--it;
		while (it != ite)
		{
			std::cout << *it << std::endl;
			++it;
		}

		std::cout << "\n";

		MutantStack<int> clone = mstack;
		clone.pop();
		clone.push(-42);
		it = mstack.begin();
		ite = mstack.end();
		MutantStack<int>::iterator cit = clone.begin();
		MutantStack<int>::iterator cite = clone.end();
		++it;
		--it;
		while (it != ite && cit != cite)
		{
			std::cout << *it << " " << *cit << std::endl;
			++it;
			++cit;
		}

		std::stack<int> s(mstack);
	}
	std::cout << "\n\n";
	{
		std::list<int> mstack;
		mstack.push_back(5);
		mstack.push_back(17);
		std::cout << mstack.back() << std::endl;
		mstack.pop_back();
		std::cout << mstack.size() << std::endl;
		mstack.push_back(3);
		mstack.push_back(5);
		mstack.push_back(737);
//[...]
		mstack.push_back(0);
		std::list<int>::iterator it = mstack.begin();
		std::list<int>::iterator ite = mstack.end();
		++it;
		--it;
		while (it != ite)
		{
			std::cout << *it << std::endl;
			++it;
		}
	}
}
