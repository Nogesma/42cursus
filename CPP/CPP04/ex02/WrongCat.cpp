//
// Created by Mano Segransan on 3/7/22.
//

#include "WrongCat.h"

WrongCat::WrongCat()
{}

WrongCat::~WrongCat()
{}

WrongCat::WrongCat(const WrongCat &w)
{
	*this = w;
}

WrongCat &WrongCat::operator=(const WrongCat &w)
{
	this->type = w.type;

	return (*this);
}
