//
// Created by Mano Segransan on 3/2/22.
//

#include "DiamondTrap.h"

DiamondTrap::DiamondTrap(std::string name)
{
	ClapTrap(name);
	hp = this->FragTrap::hp;
	ep = this->ScavTrap::ep;
	dmg = this->FragTrap::dmg;
	std::cout << "DiamondTrap " << this->name << " : created" << std::endl;
}

DiamondTrap::~DiamondTrap()
{
	std::cout << "DiamondTrap " << this->name << " : destroyed" << std::endl;
}

void DiamondTrap::whoAmI()
{
	std::cout << "DiamondTrap " << this->name << "|" << this->ClapTrap::name << std::endl;
}
