//
// Created by Mano Segransan on 3/2/22.
//

#include "ScavTrap.hpp"

ScavTrap::ScavTrap(std::string name) : ClapTrap(name)
{
	hp = 100;
	ep = 50;
	dmg = 20;
	std::cout << "ScavTrap " << this->name <<" : created" << std::endl;
}

ScavTrap::~ScavTrap()
{
	std::cout << "ScavTrap " << this->name <<" : destroyed" << std::endl;
}

void ScavTrap::attack(const std::string &target)
{
	if (ep <= 0 || hp <= 0)
		return ;
	this->ep--;
	std::cout
		<< "ScavTrap " << this->name << " attacks " << target << ", causing "
		<< this->dmg << " points of damage!"
		<< std::endl;
}
void ScavTrap::guardGate()
{
	std::cout << "ScavTrap " << name << " is now in gate keeper mode."
			  << std::endl;
}
