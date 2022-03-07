//
// Created by Mano Segransan on 3/2/22.
//

#include "DiamondTrap.h"

DiamondTrap::DiamondTrap(std::string name) : ClapTrap(name + "_clap_name"),
											 FragTrap(name),
											 ScavTrap(name),
											 name(name)
{
	hp = 100;
	ep = ScavTrap::ep;
	dmg = 30;
	std::cout << "DiamondTrap " << this->name << " : created" << std::endl;
}

DiamondTrap::~DiamondTrap()
{
	std::cout << "DiamondTrap " << this->name << " : destroyed" << std::endl;
}

void DiamondTrap::whoAmI()
{
	std::cout << "DiamondTrap is " << this->name << " | "
			  << this->ClapTrap::name
			  << std::endl;
}

DiamondTrap::DiamondTrap(const DiamondTrap &a) : ClapTrap(a),
												 FragTrap(a),
												 ScavTrap(a)
{
	*this = a;
}

DiamondTrap &DiamondTrap::operator=(const DiamondTrap &a)
{
	this->hp = a.hp;
	this->ep = a.ep;
	this->dmg = a.dmg;
	this->name = a.name;

	return (*this);
}
