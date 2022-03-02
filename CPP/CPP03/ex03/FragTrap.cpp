//
// Created by Mano Segransan on 3/2/22.
//

#include "FragTrap.h"

FragTrap::FragTrap(std::string name) : ClapTrap(name)
{
	hp = 100;
	ep = 100;
	dmg = 30;
	std::cout << "FragTrap " << this->name << " : created" << std::endl;
}

FragTrap::~FragTrap()
{
	std::cout << "FragTrap " << this->name << " : destroyed" << std::endl;
}

void FragTrap::highFivesGuys()
{
	std::string high_five;

	std::cout << "FragTrap " << name << " is waiting for a high five."
			  << std::endl;
	std::getline(std::cin, high_five);
}
