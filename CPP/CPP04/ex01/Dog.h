//
// Created by Mano Segransan on 3/3/22.
//

#ifndef CPP04_DOG_H
#define CPP04_DOG_H

#include "Animal.h"
#include "Brain.h"

class Dog : public Animal {
public:
  Dog();

  ~Dog();

  void makeSound() const;

  Dog(const Dog &a);

  Dog &operator=(const Dog &a);

private:
  Brain *brain;
};

#endif // CPP04_DOG_H
