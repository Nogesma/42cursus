//
// Created by Mano Segransan on 3/2/22.
//

#ifndef CPP03_DIAMONDTRAP_H
#define CPP03_DIAMONDTRAP_H

#include "FragTrap.h"
#include "ScavTrap.hpp"

class DiamondTrap : public FragTrap, public ScavTrap
{

public:
	DiamondTrap(std::string name);

  ~DiamondTrap();

  void whoAmI();

private:
  std::string name;
};

#endif //CPP03_DIAMONDTRAP_H
