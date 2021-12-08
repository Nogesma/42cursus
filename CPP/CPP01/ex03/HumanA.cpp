#include "HumanA.hpp"

HumanA::HumanA( std::string name, Weapon &wp ): _name(name), _weapon(wp)
{
//	std::cout << "<create ha> " << this->_name << this->_weapon.getType() << std::endl;
	return ;
}

HumanA::~HumanA( void )
{
//	std::cout << "<delete ha> " << this->_name << this->_weapon.getType() << std::endl;
	return ;
}

void HumanA::attack(void)
{
	std::cout << this->_name << " attacks with his " << this->_weapon.getType() << std::endl;
}
