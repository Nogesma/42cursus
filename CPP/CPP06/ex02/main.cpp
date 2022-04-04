//
// Created by Mano Segransan on 3/3/22.
//

#include "Base.hpp"
#include <iostream>

Base *generate(void);

void identify(Base *p);

void identify(Base &p);

int main()
{
	for (int i = 0; i < 10; ++i)
	{
		Base *b = generate();

		identify(b);
		identify(*b);
		std::cout << '\n';
	}
}
