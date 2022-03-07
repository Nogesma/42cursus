//
// Created by Mano Segransan on 3/2/22.
//

#include "ClapTrap.hpp"

ClapTrap::ClapTrap(std::string name) : name(name), hp(10), ep(10), dmg(0)
{
	std::cout << this->name <<" : created" << std::endl;
}

ClapTrap::~ClapTrap()
{
	std::cout << name <<" : destroyed" << std::endl;
}

void ClapTrap::attack(const std::string &target)
{
	if (ep <= 0 || hp <= 0)
		return ;
	ep--;
	std::cout
		<< "ClapTrap " << name << " attacks " << target << ", causing "
		<< dmg << " points of damage!"
		<< std::endl;
}


void ClapTrap::takeDamage(unsigned int amount)
{
	hp -= amount;
	std::cout
		<< "ClapTrap " << name << " takes " << amount << " damage. "
		<< hp << " HP left!"
		<< std::endl;
}

void ClapTrap::beRepaired(unsigned int amount)
{
	if (ep <= 0 || hp <= 0)
		return ;
	ep--;
	hp += amount;
	std::cout
		<< "ClapTrap " << name << " repaired " << amount << ". "
		<< hp << " HP left!"
		<< std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &a)
{
	*this = a;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &a)
{
	this->hp = a.hp;
	this->ep = a.ep;
	this->dmg = a.dmg;
	this->name = a.name;

	return (*this);
}
