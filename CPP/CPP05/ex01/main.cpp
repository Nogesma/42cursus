//
// Created by Mano Segransan on 3/3/22.
//

#include "Bureaucrat.h"
#include "Form.h"

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

	Form f("IMPORTANT", 11, 15);

	a.signForm(f);
	std::cout << f << std::endl;
	return 0;

}
