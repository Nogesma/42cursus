//
// Created by Mano Segransan on 3/30/22.
//

#include "PresidentialPardonForm.h"

PresidentialPardonForm::PresidentialPardonForm(const std::string t) : Form(
	"Presidential Pardon Creation Form", 25, 5), target(t)
{
}


PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &f)
	: Form(f)
{
}

PresidentialPardonForm::~PresidentialPardonForm()
{
}

void PresidentialPardonForm::execute(const Bureaucrat &executor) const
{
	Form::execute(executor);

	std::cout << this->target << " has been pardoned by Zaphod Beeblebrox." << std::endl;
}
