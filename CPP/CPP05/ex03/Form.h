//
// Created by Mano Segransan on 3/30/22.
//

#ifndef CPP05_FORM_H
#define CPP05_FORM_H

#include <iostream>
#include "Bureaucrat.h"

class Bureaucrat;

class Form
{
public:
  Form(const std::string name, const int gradeSign, const int gradeExec);

  Form(const Form &f);

  ~Form();

  Form &operator=(const Form &f);

  std::string getName() const;

  int getGradeSign() const;

  int getGradeExec() const;

  bool getIsSigned() const;

  void beSigned(const Bureaucrat &b);

  virtual void execute(Bureaucrat const & executor) const;
private:
  const std::string name;
  const int gradeSign;
  const int gradeExec;
  bool isSigned;

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

  class NotSignedException : public std::exception
  {
  public:
	const char *what() const throw()
	{
		return "Form is not signed";
	}
  };
};

std::ostream &operator<<(std::ostream &os, const Form &b);


#endif //CPP05_FORM_H
