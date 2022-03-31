//
// Created by segransm on 3/24/22.
//

#include "Ice.h"

Ice::Ice() : AMateria("ice") {}

Ice::Ice(const Ice &i): AMateria(i.type) {}

AMateria *Ice::clone() const { return (new Ice(*this)); }

void Ice::use(ICharacter &target) {
  std::cout << "* shoots an ice bolt at " << target.getName() << " *"
            << std::endl;
}
