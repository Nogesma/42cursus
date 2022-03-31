//
// Created by segransm on 3/24/22.
//

#include "Ice.h"

virtual Ice *Ice::clone() const = 0
{
  return (new Ice(this));
}

virtual void Ice::use(ICharacter &target) {
  std::cout << "* shoots an ice bolt at " << target.getName() << " *"
            << std::endl;
}
