//
// Created by Mano Segransan on 3/3/22.
//

#include "Cat.h"

Cat::Cat() {
  setType("cat");
  std::cout << "Cat: created" << std::endl;
}

Cat::~Cat() { std::cout << "Cat: destroyed" << std::endl; }

Cat::Cat(const Cat &c) : Animal() { *this = c; }

Cat &Cat::operator=(const Cat &c) {
  this->type = c.type;

  return (*this);
}

void Cat::makeSound() const { std::cout << "Miaou!" << std::endl; }
