#include "Karen.hpp"

void Karen::complain(std::string level)
{
	std::string lv[4] = {
		"DEBUG",
		"INFO",
		"WARNING",
		"ERROR"
	};

	fn f[4] = {
		&Karen::debug,
		&Karen::info,
		&Karen::warning,
		&Karen::error,
	};
	(this->*(f[std::distance(lv, std::find(lv, lv + 5, level))]))();
}

void Karen::debug()
{
	std::cout << "[ DEBUG ]\n"
				 "I love having extra bacon for my 7XL-double-cheese-triple"
				 "-pickle-special-ketchup burger. I really do!" << std::endl;
}

void Karen::info()
{
	std::cout << "[ INFO ]\n"
				 "I cannot believe adding extra bacon costs more money. "
				 "You didn’t put enough bacon in my burger! If you did, "
				 "I wouldn’t be asking for more!" << std::endl;
}

void Karen::warning()
{
	std::cout << "[ WARNING ]\n"
				 " think I deserve to have some extra bacon for free. "
				 "I’ve been coming for years whereas you started working "
				 "here since last month." << std::endl;
}

void Karen::error()
{
	std::cout << "[ ERROR ]\n"
				 "This is unacceptable! "
				 "I want to speak to the manager now." << std::endl;
}
