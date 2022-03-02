//
// Created by Mano Segransan on 3/2/22.
//

#include "ClapTrap.hpp"
#include <iostream>

ClapTrap::ClapTrap(std::string name):name(name), hp(10), ep(10), dmg(0)
{
	std::cout << "ClapTrap " << this->name <<" : created" << std::endl;
}

ClapTrap::~ClapTrap()
{
	std::cout << "ClapTrap " << this->name <<" : destroyed" << std::endl;
}

void ClapTrap::attack(const std::string &target)
{
	if (ep <= 0 || hp <= 0)
		return ;
	this->ep--;
	std::cout
		<< "ClapTrap " << this->name << " attacks " << target << ", causing "
		<< this->dmg << " points of damage!"
		<< std::endl;
}


void ClapTrap::takeDamage(unsigned int amount)
{
	this->hp -= amount;
	std::cout
		<< "ClapTrap " << this->name << " takes " << amount << " damage. "
		<< this->hp << " HP left!"
		<< std::endl;
}

void ClapTrap::beRepaired(unsigned int amount)
{
	if (ep <= 0 || hp <= 0)
		return ;
	this->ep--;
	this->hp += amount;
	std::cout
		<< "ClapTrap " << this->name << " repaired " << amount << ". "
		<< this->hp << " HP left!"
		<< std::endl;
}
