//
// Created by Mano Segransan on 3/3/22.
//

#ifndef CPP04_ANIMAL_H
#define CPP04_ANIMAL_H

#include <iostream>

class Animal
{
public:
  virtual ~Animal();

  std::string getType() const;

  void setType(std::string type);

  virtual void makeSound() const;

protected:
  Animal();

  Animal(const Animal &a);

  Animal &operator=(const Animal &a);

  std::string type;
};


#endif //CPP04_ANIMAL_H
