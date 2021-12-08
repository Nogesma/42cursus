#include "HumanB.hpp"

HumanB::HumanB( std::string name ): _name(name)
{
//	std::cout << "<create hb> " << this->_name << std::endl;
	return ;
}

HumanB::~HumanB( void )
{
//	std::cout << "<delete hb> " << this->_name << std::endl;
	return ;
}

void	HumanB::setWeapon( Weapon *wp )
{
	this->_weapon = wp;
}

void HumanB::attack(void)
{
	std::cout << this->_name << " attacks with his " << this->_weapon->getType() << std::endl;
}
