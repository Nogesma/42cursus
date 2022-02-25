#include "Zombie.hpp"

int		main( void )
{
	Zombie *ptr;

	ptr = zombieHorde(5, "bar");

	for (int i = 0; i < 5; i++)
		(ptr + i)->announce();
	delete[] ptr;
}
