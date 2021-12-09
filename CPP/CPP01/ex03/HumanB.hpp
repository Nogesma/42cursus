#pragma once
#ifndef __HUMANB_H__
#define __HUMANB_H__

#include "Weapon.hpp"
#include <iostream>

class HumanB {


public:

  typedef HumanB	t;

  HumanB( std::string );
  ~HumanB( void );

  void 	attack ( void );
  void 	setWeapon ( Weapon& );


private:

  std::string	_name;
  Weapon		*_weapon;
};

#endif /* __HUMANB_H__ */
