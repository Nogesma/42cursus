//
// Created by Mano Segransan on 4/4/22.
//

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

#include <iostream>
#include <random>

Base *generate(void)
{
	std::random_device rd;

	unsigned int r = rd();

	switch (r % 3)
	{
		case 0:
			std::cout << "Creating A: ";
			return (new A());
		case 1:
			std::cout << "Creating B: ";
			return (new B());
		case 2:
			std::cout << "Creating C: ";
			return (new C());
		default:
			std::cout << "This should never happen";
			return (new A());
	}
}

void identify(Base *p)
{
	A *a = dynamic_cast<A *>(p);
	if (a)
	{
		std::cout << 'A';
		return;
	}

	B *b = dynamic_cast<B *>(p);
	if (b)
	{
		std::cout << 'B';
		return;
	}

	C *c = dynamic_cast<C *>(p);
	if (c)
	{
		std::cout << 'C';
		return;
	}

	std::cerr << "Could not identify Base" << std::endl;
}

void identify(Base &p)
{
	try
	{
		A &a = dynamic_cast<A &>(p);
		(void)a;
		std::cout << 'A';
		return ;
	}
	catch (std::exception &e)
	{}

	try
	{
		B &b = dynamic_cast<B &>(p);
		(void)b;
		std::cout << 'B';
		return ;
	}
	catch (std::exception &e)
	{}

	try
	{
		C &c = dynamic_cast<C &>(p);
		(void)c;
		std::cout << 'C';
		return ;
	}
	catch (std::exception &e)
	{}

	std::cerr << "Could not identify Base" << std::endl;
}
