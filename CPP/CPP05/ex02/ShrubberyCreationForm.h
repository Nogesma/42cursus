//
// Created by Mano Segransan on 3/30/22.
//

#ifndef CPP05_SHRUBBERYCREATIONFORM_H
#define CPP05_SHRUBBERYCREATIONFORM_H

#include "Form.h"

class ShrubberyCreationForm : public Form
{
public:
  ShrubberyCreationForm(const std::string target);

  ShrubberyCreationForm(const ShrubberyCreationForm &f);

  ~ShrubberyCreationForm();

  ShrubberyCreationForm &operator=(const ShrubberyCreationForm &f);

  void execute(Bureaucrat const & executor) const;

private:
  std::string target;
};


#endif //CPP05_SHRUBBERYCREATIONFORM_H
