//
// Created by Mano Segransan on 3/3/22.
//

#ifndef CPP04_DOG_H
#define CPP04_DOG_H

#include "Animal.h"

class Dog : public Animal {
public:
  Dog();

  Dog(const Dog &d);

  Dog &operator=(const Dog &d);

  ~Dog();

  void makeSound() const;
};

#endif // CPP04_DOG_H
