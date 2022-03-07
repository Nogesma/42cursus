//
// Created by Mano Segransan on 3/3/22.
//

#include "Dog.h"

Dog::Dog()
{
	setType("dog");
	std::cout << "Dog: created" << std::endl;
}

Dog::~Dog()
{
	std::cout << "Dog: destroyed" << std::endl;
}

Dog::Dog(const Dog &d)
{
	*this = d;
}

Dog &Dog::operator=(const Dog &d)
{
	this->type = d.type;

	return (*this);
}

void Dog::makeSound() const
{
	std::cout << "Woof!" << std::endl;
}
