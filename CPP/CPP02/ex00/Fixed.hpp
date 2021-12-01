// ************************************************************************** //
//                                                                            //
//                Account.hpp for GlobalBanksters United                //
//                Created on  : Thu Nov 20 19:43:15 1989                      //
//                Last update : Wed Jan 04 14:54:06 1992                      //
//                Made by : Brad "Buddy" McLane <bm@gbu.com>                  //
//                                                                            //
// ************************************************************************** //


#pragma once
#ifndef __FIXED_H__
#define __FIXED_H__

// ************************************************************************** //
//                               Account Class                                //
// ************************************************************************** //

class Fixed {


public:

	typedef Fixed	t;

	Fixed( void );
	~Fixed( void );

	Fixed( const Fixed &obj);

	int		getRawBits( void ) const;
	void	setRawBits( int const raw );

private:

	int				_val;
	static const	_precision = 8;

};

#endif /* __FIXED_H__ */
