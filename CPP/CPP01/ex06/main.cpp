#include "Karen.hpp"

int main(int ac, char **av)
{
	Karen kr;

	if (ac == 2)
		kr.complain(av[1]);
	return (0);
}
