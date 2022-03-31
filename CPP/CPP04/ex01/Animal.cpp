//
// Created by Mano Segransan on 3/3/22.
//

#include "Animal.h"

Animal::Animal() { std::cout << "Animal: created" << std::endl; }

Animal::Animal(const Animal &a) { *this = a; }

Animal &Animal::operator=(const Animal &a) {
  this->type = a.type;

  return (*this);
}

Animal::~Animal() { std::cout << "Animal: destroyed" << std::endl; }

std::string Animal::getType() const { return (type); }

void Animal::setType(std::string type) { this->type = type; }

void Animal::makeSound() const {}
