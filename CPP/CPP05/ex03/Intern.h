//
// Created by Mano Segransan on 3/30/22.
//

#ifndef CPP05_INTERN_H
#define CPP05_INTERN_H

#include <iostream>
#include "Form.h"

class Intern;

typedef Form *(Intern::*ptr)(std::string) const;

class Intern
{
public:
  Intern();

  Intern(const Intern &i);

  ~Intern();

  Intern &operator=(const Intern &i);

  Form *
  makeForm(const std::string formName, const std::string formTarget) const;

private:
  class NotFoundException : public std::exception
  {
  public:
	const char *what() const throw()
	{
		return "Could not find form";
	}
  };

  Form *createShrubberyCreationForm(const std::string target) const;
  Form *createRobotomyRequestForm(const std::string target) const;
  Form *createPresidentialPardonForm(const std::string target) const;

  static const ptr forms[3];
};


#endif //CPP05_INTERN_H
