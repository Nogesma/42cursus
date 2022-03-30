//
// Created by Mano Segransan on 3/3/22.
//

#include "Bureaucrat.h"
#include "Form.h"
#include "ShrubberyCreationForm.h"
#include "RobotomyRequestForm.h"
#include "PresidentialPardonForm.h"
int main()
{
	Bureaucrat a("42", 13);

	std::cout << a << std::endl;
	a.decGrade();
	std::cout << a << std::endl;
	a.incGrade();
	a.incGrade();
	std::cout << a << std::endl;
	try
	{
		Bureaucrat b("43", 0);
	} catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	try
	{
		Bureaucrat c("44", 153);
	} catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	ShrubberyCreationForm f("42");

	a.signForm(f);
	std::cout << f << std::endl;
	a.executeForm(f);

	RobotomyRequestForm rf("12");

	a.signForm(rf);
	std::cout << rf << std::endl;
	a.executeForm(rf);

	PresidentialPardonForm pf("24");

	a.signForm(pf);
	std::cout << pf << std::endl;
	a.executeForm(pf);

	Bureaucrat c("President", 2);
	c.executeForm(pf);

	return 0;

}
