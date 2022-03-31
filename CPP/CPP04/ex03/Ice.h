//
// Created by segransm on 3/24/22.
//

#ifndef CPP04_ICE_H
#define CPP04_ICE_H

#include "AMateria.h"

class Ice : public AMateria {
  virtual Ice *clone() const = 0;
  virtual void use(ICharacter &target);
};

#endif // CPP04_ICE_H
