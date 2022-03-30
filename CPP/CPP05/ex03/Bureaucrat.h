//
// Created by Mano Segransan on 3/3/22.
//

#ifndef CPP05_BUREAUCRAT_H
#define CPP05_BUREAUCRAT_H

#include <iostream>
#include "Form.h"

class Form;

class Bureaucrat
{
public:
  Bureaucrat(const std::string name, int grade);

  Bureaucrat(const Bureaucrat &a);

  ~Bureaucrat();

  Bureaucrat &operator=(const Bureaucrat &a);

  std::string getName() const;

  int getGrade() const;

  void incGrade();

  void decGrade();

  void signForm(Form &f);

  void executeForm(Form const &form);

private:
  const std::string name;
  int grade;

  void checkGrade() const;

  class GradeTooHighException : public std::exception
  {
  public:
	const char *what() const throw()
	{
		return "Grade too high";
	}
  };

  class GradeTooLowException : public std::exception
  {
  public:
	const char *what() const throw()
	{
		return "Grade too low";
	}
  };

};

std::ostream &operator<<(std::ostream &os, const Bureaucrat &b);

#endif //CPP05_BUREAUCRAT_H
