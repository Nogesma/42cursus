#include "Zombie.hpp"
#include <iostream>
#include <iomanip>

Zombie::Zombie( std::string name ): _name(name)
{
	std::cout << "<create> " << this->_name << std::endl;
	return ;
}

Zombie::~Zombie( void )
{
	std::cout << "<delete> " << this->_name << std::endl;
	return ;
}

void	Zombie::announce( void )
{
	std::cout << "<name> " << this->_name << std::endl;
}
