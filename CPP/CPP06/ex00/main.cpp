//
// Created by Mano Segransan on 3/3/22.
//

#include "Number.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	Number n(av[1]);
	std::cout << n << std::endl;
}
