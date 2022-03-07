//
// Created by Mano Segransan on 3/3/22.
//

#ifndef CPP04_WRONGCAT_H
#define CPP04_WRONGCAT_H

#include "WrongAnimal.h"

class WrongCat: public WrongAnimal
{
public:
  WrongCat();

  ~WrongCat();

  WrongCat(const WrongCat &w);

  WrongCat &operator=(const WrongCat &w);
};


#endif //CPP04_WRONGCAT_H
