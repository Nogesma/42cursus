//
// Created by Mano Segransan on 3/3/22.
//

#include "Dog.h"

Dog::Dog() {
  setType("dog");
  brain = new Brain();
  std::cout << "Dog: created" << std::endl;
}

Dog::~Dog() {
  delete brain;
  std::cout << "Dog: destroyed" << std::endl;
}

void Dog::makeSound() const { std::cout << "Woof!" << std::endl; }

Dog::Dog(const Dog &a) : Animal() { *this = a; }

Dog &Dog::operator=(const Dog &a) {
  this->type = a.type;
  this->brain = a.brain;

  return (*this);
}
