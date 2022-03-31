//
// Created by segransm on 3/24/22.
//

#ifndef CPP04_CURE_H
#define CPP04_CURE_H

#include "AMateria.h"
#include "ICharacter.h"

class Cure: public AMateria {
public:
  Cure();
  Cure(const Cure &);

  ~Cure();

  AMateria *clone() const;
  void use(ICharacter &target);
};

#endif // CPP04_CURE_H
