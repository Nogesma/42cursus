// ************************************************************************** //
//                                                                            //
//                Account.hpp for GlobalBanksters United                //
//                Created on  : Thu Nov 20 19:43:15 1989                      //
//                Last update : Wed Jan 04 14:54:06 1992                      //
//                Made by : Brad "Buddy" McLane <bm@gbu.com>                  //
//                                                                            //
// ************************************************************************** //


#pragma once
#ifndef __ZOMBIE_H__
#define __ZOMBIE_H__

#include <iostream>

// ************************************************************************** //
//                               Zombie Class                                 //
// ************************************************************************** //

class Zombie {


public:

	typedef Zombie	t;

	Zombie( std::string name );
	~Zombie( void );

	void 	announce ( void );


private:

	std::string	_name;
};

Zombie* newZombie( std::string name );

void randomChump( std::string name );

#endif /* __ZOMBIE_H__ */
