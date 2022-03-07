//
// Created by Mano Segransan on 3/3/22.
//

#ifndef CPP04_WRONGANIMAL_H
#define CPP04_WRONGANIMAL_H

#include <iostream>

class WrongAnimal
{
public:
  WrongAnimal();

  virtual ~WrongAnimal();

  WrongAnimal(const WrongAnimal &w);

  WrongAnimal &operator=(const WrongAnimal &w);

  std::string getType() const;

  void setType(std::string type);

  virtual void makeSound() const;

protected:
  std::string type;
};


#endif //CPP04_WRONGANIMAL_H
