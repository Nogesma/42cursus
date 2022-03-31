//
// Created by segransm on 3/24/22.
//

#ifndef CPP04_ICE_H
#define CPP04_ICE_H

#include "AMateria.h"
#include "ICharacter.h"

class Ice : public AMateria {
public:
  Ice();
  Ice(const Ice &);

  AMateria *clone() const;
  void use(ICharacter &target);
};

#endif // CPP04_ICE_H
