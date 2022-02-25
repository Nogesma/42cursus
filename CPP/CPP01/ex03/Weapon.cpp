#include "Weapon.hpp"

Weapon::Weapon( std::string name ): _name(name)
{
//	std::cout << "<create wp> " << this->_name << std::endl;
	return ;
}

Weapon::~Weapon( void )
{
//	std::cout << "<delete wp> " << this->_name << std::endl;
	return ;
}

const std::string&	Weapon::getType( void )
{
	return (this->_name);
}

void	Weapon::setType( std::string name )
{
	this->_name = name;
}
