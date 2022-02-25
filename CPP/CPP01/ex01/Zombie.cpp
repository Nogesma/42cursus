#include "Zombie.hpp"

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

void 	Zombie::set_name ( std::string name )
{
	this->_name = name;
}
