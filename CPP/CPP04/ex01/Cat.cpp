//
// Created by Mano Segransan on 3/3/22.
//

#include "Cat.h"

Cat::Cat() {
  setType("cat");
  brain = new Brain();
  std::cout << "Cat: created" << std::endl;
}

Cat::~Cat() {
  delete brain;
  std::cout << "Cat: destroyed" << std::endl;
}

void Cat::makeSound() const { std::cout << "Miaou!" << std::endl; }

Cat::Cat(const Cat &a) : Animal() { *this = a; }

Cat &Cat::operator=(const Cat &a) {
  this->type = a.type;
  this->brain = a.brain;

  return (*this);
}
