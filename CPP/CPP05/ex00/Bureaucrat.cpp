//
// Created by Mano Segransan on 3/3/22.
//

#include "Bureaucrat.h"

Bureaucrat::Bureaucrat(const std::string n, int g) : name(n), grade(g)
{
	this->checkGrade();
	std::cout << "Bureaucrat: " << name << " created" <<
			  std::endl;
}

Bureaucrat::Bureaucrat(const Bureaucrat &a) : name(a.name)
{
	this->grade = a.grade;
}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &a)
{
	this->grade = a.grade;

	return (*this);
}

Bureaucrat::~Bureaucrat()
{
	std::cout << "Bureaucrat: " << name << " destroyed" <<
			  std::endl;}

std::string Bureaucrat::getName() const
{
	return (this->name);
}

int Bureaucrat::getGrade() const
{
	return (this->grade);
}

void Bureaucrat::incGrade()
{
	this->grade--;
	this->checkGrade();
}

void Bureaucrat::decGrade()
{
	this->grade++;
	this->checkGrade();
}

void Bureaucrat::checkGrade() const
{
	if (this->grade < 1)
		throw Bureaucrat::GradeTooHighException();
	if (this->grade > 150)
		throw Bureaucrat::GradeTooLowException();
}

std::ostream& operator<<(std::ostream& os, const Bureaucrat &b)
{
	os << b.getName() << ", bureaucrat grade " << b.getGrade() << ".";

	return (os);
}
