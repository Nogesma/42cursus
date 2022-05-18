//
// Created by Mano Segransan on 5/5/22.
//

#ifndef USE_STD_NAMESPACE
#define USE_STD_NAMESPACE 0
#endif

#if USE_STD_NAMESPACE

#include <map>
#include <stack>
#include <type_traits>
#include <vector>

namespace ft = std;


#else
#include <map.hpp>
//#include <stack.hpp>
#include <type_traits.hpp>
#include <vector.hpp>

#endif

#include <iostream>

#include <iterator>
#include <map>
#include <vector>

int main()
{
	// vector
	{
		std::cout << "Starting Vector tests: \n";

		ft::vector< int > a(1, 42);

		std::cout << "a.front (42) : " << a.front() << '\n';

		ft::vector< int > b(1, 10);

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
		for (int i = 0; i < 100; i += 5) a.push_back(i);

		for (ft::vector< int >::iterator i = a.begin(); i < a.end(); ++i) std::cout << *i << ' ';
		std::cout << '\n';

		ft::vector< int > fc(a.begin(), a.end());

		std::cout << "fc.size " << fc.size() << ' ' << fc.max_size() << '\n';
		fc.resize(3);
		for (int i = 0; i < 3; ++i) { std::cout << fc[i] << ' '; }
		std::cout << '\n';
	}
	// is_integral
	{
		std::cout << std::boolalpha;
		std::cout << "is_integral:\n";
		std::cout << "char: " << ft::is_integral< char >::value << '\n';
		std::cout << "int: " << ft::is_integral< int >::value << '\n';
		std::cout << "float: " << ft::is_integral< float >::value << '\n';
	}
	// map
	{
		ft::map< std::string, int > mp;

		std::cout << "map:\n";
		std::cout << "empty: " << mp.empty() << '\n';

		std::cout << mp["a"] << '\n';

		mp["a"] = 42;

		std::cout << mp["a"] << '\n';
		std::cout << (mp["b"] = 3) << '\n';
		mp.print();
		std::cout << (mp["c"] = 3) << '\n';
		std::cout << (mp["ef"] = 3) << '\n';
		std::cout << (mp["e"] = 3) << '\n';
		std::cout << (mp["f"] = 3) << '\n';
		std::cout << (mp["w"] = 3) << '\n';
		std::cout << (mp["y"] = 3) << '\n';

		mp.print();
		mp.erase("v");
		mp.erase("a");
		mp.erase("ef");
		mp.print();
	}


	{
		ft::vector< int > a;

		a.push_back(42);
		a.push_back(43);
		a.push_back(44);


		for (ft::vector< int >::iterator i = a.begin(); i < a.end(); ++i) std::cout << *i << ' ';
		std::cout << '\n';
		a.insert(a.end() - 1, 3, -1);
		for (ft::vector< int >::iterator i = a.begin(); i < a.end(); ++i) std::cout << *i << ' ';
		std::cout << '\n';
	}

	{
		int a[4] = {0, 1, 2, 3};
		int c[4] = {42, 43, 44, 45};
		ft::vector< int > b(a, a + 4);


		for (ft::vector< int >::iterator i = b.begin(); i < b.end(); ++i) std::cout << *i << ' ';
		std::cout << '\n';

		b.insert(b.end() - 1, c, c + 4);
		for (ft::vector< int >::iterator i = b.begin(); i < b.end(); ++i) std::cout << *i << ' ';
		std::cout << '\n';

		b.erase(b.begin());
		for (ft::vector< int >::iterator i = b.begin(); i < b.end(); ++i) std::cout << *i << ' ';
		std::cout << '\n';

		b.erase(b.begin() + 1, b.begin() + 3);
		for (ft::vector< int >::iterator i = b.begin(); i < b.end(); ++i) std::cout << *i << ' ';
		std::cout << '\n';
	}
}
