//
// Created by Mano Segransan on 5/5/22.
//
#include "vector.hpp"
#include <vector>
#include <iostream>

int main()
{
	{
		ft::vector<int> a(1, 42);

		std::cout << a.front() << '\n';

		ft::vector<int> b(1, 10);

		std::cout << b.front() << '\n';

		b.swap(a);

		std::cout << a.front() << '\n';
		std::cout << b.front() << '\n';
	}

	{

		std::vector<int> a;
		std::vector<int> b;

		for (int i = 0; i < 100; ++i)
		{
			a.push_back(i);
			std::cout << a.size() << ' ' << a.capacity() << '\n';
		}
	}

	std::cout << "\n\n\n";
	{

		ft::vector<int> a;
		ft::vector<int> b;

		std::cout << (a == b) << '\n';
		std::cout << a.size() << ' ' << a.capacity() << std::endl;
		for (int i = 0; i < 100; ++i)
		{
			a.push_back(i);
			std::cout << a.size() << ' ' << a.capacity() << '\n';
		}
	}

}
