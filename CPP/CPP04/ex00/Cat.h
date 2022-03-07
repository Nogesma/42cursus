//
// Created by Mano Segransan on 3/3/22.
//

#ifndef CPP04_CAT_H
#define CPP04_CAT_H

#include "Animal.h"

class Cat : public Animal
{
public:
  Cat();

  Cat(const Cat &c);

  Cat &operator=(const Cat &c);

  ~Cat();

  void makeSound() const;

};


#endif //CPP04_CAT_H
