//
// Created by Mano Segransan on 3/30/22.
//

#include "Intern.h"
#include "RobotomyRequestForm.h"
#include "PresidentialPardonForm.h"
#include "ShrubberyCreationForm.h"

Intern::Intern()
{
}

Intern::Intern(const Intern &i)
{
	(void) i;
}

Intern &Intern::operator=(const Intern &i)
{
	(void) i;

	return (*this);
}

Intern::~Intern()
{
}

const ptr Intern::forms[3] = {
	&Intern::createShrubberyCreationForm,
	&Intern::createRobotomyRequestForm,
	&Intern::createPresidentialPardonForm,
};

Form *Intern::createShrubberyCreationForm(const std::string target) const
{
	return (new ShrubberyCreationForm(target));
}

Form *Intern::createRobotomyRequestForm(const std::string target) const
{
	return (new RobotomyRequestForm(target));
}

Form *Intern::createPresidentialPardonForm(const std::string target) const
{
	return (new PresidentialPardonForm(target));
}

Form *
Intern::makeForm(const std::string formName, const std::string formTarget) const
{
	std::string forms[3] = {
		"ShrubberyCreationForm",
		"RobotomyRequestForm",
		"PresidentialPardonForm",
	};

	int i = std::distance(forms, std::find(forms, forms + 4, formName));
	if (i > 2)
		throw Intern::NotFoundException();

	return ((this->*(Intern::forms[i]))(formTarget));
}
