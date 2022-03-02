#include "FragTrap.h"

int main()
{
	FragTrap ft("foo");

	ft.attack("bar");
	ft.attack("baz");
	ft.takeDamage(4);
	ft.takeDamage(4);
	ft.takeDamage(4);
	ft.takeDamage(4);
	ft.beRepaired(5000);
	ft.highFivesGuys();
	ft.highFivesGuys();


}
