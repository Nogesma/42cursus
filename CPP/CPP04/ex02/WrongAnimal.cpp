//
// Created by Mano Segransan on 3/3/22.
//

#include "WrongAnimal.h"


WrongAnimal::WrongAnimal()
{
	std::cout << "WrongAnimal: created" << std::endl;
}

WrongAnimal::~WrongAnimal()
{
	std::cout << "WrongAnimal: destroyed" << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal &w)
{
	*this = w;
}

WrongAnimal &WrongAnimal::operator=(const WrongAnimal &w)
{
	this->type = w.type;

	return (*this);
}

std::string WrongAnimal::getType() const
{
	return (type);
}

void WrongAnimal::setType(std::string type)
{
	this->type = type;
}

void WrongAnimal::makeSound() const
{
	std::cout << "Wrong sound!" << std::endl;
}
