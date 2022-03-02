#include "ClapTrap.hpp"

int	main()
{
	ClapTrap ct("foo");

	ct.attack("bar");
	ct.attack("baz");
	ct.takeDamage(4);
	ct.takeDamage(4);
	ct.takeDamage(4);
	ct.takeDamage(4);
	ct.beRepaired(5000);


}
