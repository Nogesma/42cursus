//
// Created by Mano Segransan on 3/2/22.
//

#ifndef CPP03_SCAVTRAP_H
#define CPP03_SCAVTRAP_H

#include "ClapTrap.hpp"

class ScavTrap : public virtual ClapTrap
{

public:
  ScavTrap(std::string name);

  ~ScavTrap();

  void attack(const std::string &target);

  void guardGate();

};


#endif //CPP03_SCAVTRAP_H
