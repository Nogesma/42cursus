//
// Created by Mano Segransan on 3/3/22.
//

#include "Brain.h"

Brain::Brain() { std::cout << "Brain: created" << std::endl; }

Brain::~Brain() { std::cout << "Brain: destroyed" << std::endl; }

Brain::Brain(const Brain &a) { *this = a; }

Brain &Brain::operator=(const Brain &a) {
  for (int i = 0; i < 100; ++i)
    this->ideas[i] = a.ideas[i];

  return (*this);
}
