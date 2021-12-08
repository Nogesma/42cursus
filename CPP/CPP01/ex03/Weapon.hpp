#pragma once
#ifndef __WEAPON_H__
#define __WEAPON_H__

#include <iostream>

class Weapon {


public:

  typedef Weapon	t;

  Weapon( std::string name );
  Weapon( void ) {};
  ~Weapon( void );

  const std::string getType ( void );
  void 	setType ( std::string );


private:

  std::string	_name;
};

#endif