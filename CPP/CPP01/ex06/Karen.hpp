#pragma once
#ifndef __KAREN_H__
#define __KAREN_H__

#include <iostream>

// ************************************************************************** //
//                               Zombie Class                                 //
// ************************************************************************** //

class Karen {


public:

	typedef Karen	t;

  	Karen( void ) {};
	~Karen( void ) {};

	void 	complain ( std::string level );


private:

	void	debug ( void );
	void	info ( void );
	void	warning ( void );
	void	error ( void );

	typedef void (Karen::*fn)( void );
};

#endif /* __KAREN_H__ */
