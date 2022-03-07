//
// Created by Mano Segransan on 3/2/22.
//

#ifndef CPP03_FRAGTRAP_H
#define CPP03_FRAGTRAP_H

#include "ClapTrap.hpp"

class FragTrap : public ClapTrap
{

public:
  FragTrap(std::string name);

  ~FragTrap();

  void highFivesGuys(void);

  FragTrap(const FragTrap &c);

  FragTrap &operator=(const FragTrap &a);

};



#endif //CPP03_FRAGTRAP_H
