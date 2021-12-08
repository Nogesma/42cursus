#pragma once
#ifndef __HUMANA_H__
#define __HUMANA_H__

#include "Weapon.hpp"
#include <iostream>

class HumanA {


public:

  typedef HumanA	t;

  HumanA( std::string , Weapon& );
  ~HumanA( void );

  void 	attack ( void );


private:

  std::string	_name;
  Weapon		&_weapon;
};

#endif