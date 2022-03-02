#include "ScavTrap.hpp"

int	main()
{
	ScavTrap st("foo");

	st.attack("bar");
	st.attack("baz");
	st.takeDamage(4);
	st.takeDamage(4);
	st.takeDamage(4);
	st.takeDamage(4);
	st.beRepaired(5000);
	st.guardGate();


}
