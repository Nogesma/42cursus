#include "Zombie.hpp"

void randomChump( std::string name )
{
	Zombie *zomb;

	zomb = newZombie(name);
	if (zomb)
		zomb->announce();
	delete zomb;
}
