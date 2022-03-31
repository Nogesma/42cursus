//
// Created by segransm on 3/24/22.
//

#include "Cure.h"

Cure::Cure() : AMateria("cure") {}

Cure::Cure(const Cure &i) : AMateria(i.type) {}

AMateria *Cure::clone() const { return (new Cure(*this)); }

void Cure::use(ICharacter &target) {
  std::cout << "* heals " << target.getName() << "’s wounds *" << std::endl;
}
