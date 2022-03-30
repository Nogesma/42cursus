//
// Created by Mano Segransan on 3/30/22.
//

#include "RobotomyRequestForm.h"
#include <random>

RobotomyRequestForm::RobotomyRequestForm(const std::string t) : Form(
	"Robotomy Creation Form", 72, 45), target(t)
{
}


RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &f)
	: Form(f)
{
}

RobotomyRequestForm::~RobotomyRequestForm()
{
}

void RobotomyRequestForm::execute(const Bureaucrat &executor) const
{
	Form::execute(executor);

	std::random_device rd;
	if (rd() % 2)
		std::cout << this->target << " has been robotomized." << std::endl;
	else
		std::cout << this->target << " robotomy failed." << std::endl;
}
