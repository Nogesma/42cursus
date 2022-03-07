//
// Created by Mano Segransan on 3/2/22.
//

#ifndef CPP03_SCAVTRAP_H
#define CPP03_SCAVTRAP_H

#include "ClapTrap.hpp"

class ScavTrap : public ClapTrap
{

public:
  ScavTrap(std::string name);

  ~ScavTrap();

  ScavTrap(const ScavTrap &c);

  ScavTrap &operator=(const ScavTrap &a);

  void attack(const std::string &target);

  void guardGate();

};


#endif //CPP03_SCAVTRAP_H
