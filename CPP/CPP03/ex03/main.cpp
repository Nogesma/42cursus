#include "DiamondTrap.h"

int main()
{
	DiamondTrap dt("foo");

	dt.attack("bar");
	dt.attack("baz");
	dt.takeDamage(4);
	dt.takeDamage(4);
	dt.takeDamage(4);
	dt.takeDamage(4);
	dt.beRepaired(5000);
	dt.guardGate();
	dt.whoAmI();
	dt.highFivesGuys();


}
