//
// Created by Mano Segransan on 3/3/22.
//

#ifndef CPP04_CAT_H
#define CPP04_CAT_H

#include "Animal.h"
#include "Brain.h"

class Cat : public Animal
{
public:
  Cat();

  ~Cat();

  void makeSound() const;

  Cat(const Cat &a);

  Cat &operator=(const Cat &a);

private:
  Brain *brain;
};


#endif //CPP04_CAT_H
