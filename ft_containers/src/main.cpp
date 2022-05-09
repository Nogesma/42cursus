//
// Created by Mano Segransan on 5/5/22.
//

#ifndef USE_STD_NAMESPACE
#define USE_STD_NAMESPACE 0
#endif

#if USE_STD_NAMESPACE

#include <map>
#include <stack>
#include <vector>

namespace ft = std;

#else

#include <map.hpp>
//#include <stack.hpp>
#include <vector.hpp>

#endif

#include <iostream>

int main()
{
	// vector
	{
		std::cout << "Starting Vector tests: \n";

		ft::vector<int> a(1, 42);

		std::cout << "a.front (42) : " << a.front() << '\n';

		ft::vector<int> b(1, 10);

		std::cout << "b.front (10) : " << b.front() << '\n';

		std::cout << "Swaping vectors\n";
		b.swap(a);

		std::cout << "a.front (10) : " << a.front() << '\n';
		std::cout << "b.front (42) : " << b.front() << '\n';


		std::cout << "Clearing vectors\n";
		a.clear();
		b.clear();

		std::cout << "a should be equal to b: " << (a == b) << '\n';

		std::cout << "and should be empty (0, 1): (" << a.size() << ", " << a.capacity() << ")\n";
		//		for (int i = 0; i < 100; ++i)
		//		{
		//			a.push_back(i);
		//			std::cout << a.size() << ' ' << a.capacity() << '\n';
		//		}

		//		for (ft::vector<int>::iterator i = a.begin(); i < a.end(); ++i)
		//		{
		//			std::cout << *i << '\n';
		//		}
	}
}
