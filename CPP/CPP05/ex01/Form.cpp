//
// Created by Mano Segransan on 3/30/22.
//

#include "Form.h"

Form::Form(const std::string n, const int gs, const int ge)
	: name(n), gradeSign(gs), gradeExec(ge), isSigned(false)
{
	this->checkGrade();
	std::cout << "Form: " << name << " created" <<
			  std::endl;
}

Form::Form(const Form &f) : name(f.name), gradeSign(f.gradeSign),
							gradeExec(f.gradeExec)
{
	this->isSigned = f.isSigned;
}

Form &Form::operator=(const Form &f)
{
	this->isSigned = f.isSigned;

	return (*this);
}

Form::~Form()
{
	std::cout << "Form: " << name << " destroyed" <<
			  std::endl;
}

std::string Form::getName() const
{
	return (this->name);
}

int Form::getGradeExec() const
{
	return (this->gradeExec);
}

int Form::getGradeSign() const
{
	return (this->gradeSign);
}

bool Form::getIsSigned() const
{
	return (this->isSigned);
}

void Form::beSigned(const Bureaucrat &b)
{
	if (b.getGrade() <= this->gradeSign)
		this->isSigned = true;
	else
		throw Form::GradeTooLowException();
}


void Form::checkGrade() const
{
	if (this->gradeExec < 1 || this->gradeSign < 1)
		throw Form::GradeTooHighException();
	if (this->gradeExec > 150 || this->gradeSign > 150)
		throw Form::GradeTooLowException();
}


std::ostream &operator<<(std::ostream &os, const Form &f)
{
	os << f.getName() << ", form grade sign " << f.getGradeSign()
	   << ", form grade exec " << f.getGradeExec() << ", is signed? "
	   << f.getIsSigned() << ".";

	return (os);
}
