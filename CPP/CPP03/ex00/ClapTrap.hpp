//
// Created by Mano Segransan on 3/2/22.
//

#ifndef CPP03_CLAPTRAP_H
#define CPP03_CLAPTRAP_H

#include <iostream>

class ClapTrap
{
  typedef ClapTrap t;

public:

  ClapTrap(std::string name);

  ~ClapTrap();

  ClapTrap(const ClapTrap &c);

  ClapTrap &operator=(const ClapTrap &a);

  void attack(const std::string &target);

  void takeDamage(unsigned int amount);

  void beRepaired(unsigned int amount);

private:
  std::string name;
  int hp;
  int ep;
  int dmg;

};


#endif //CPP03_CLAPTRAP_H
