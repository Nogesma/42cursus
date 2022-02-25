#include "Zombie.hpp"
#include <iostream>
#include <iomanip>

Zombie::Zombie( std::string name ): _name(name)
{
}

Zombie::~Zombie( void )
{
	std::cout << this->_name << ": destroyed" << std::endl;
	return ;
}

void	Zombie::announce( void )
{
	std::cout << this->_name << " : BraiiiiiiinnnzzzZ..." <<  std::endl;
}
