//
// Created by Mano Segransan on 3/30/22.
//

#ifndef CPP05_PRESIDENTIALPARDONFORM_H
#define CPP05_PRESIDENTIALPARDONFORM_H

#include "Form.h"

class PresidentialPardonForm : public Form
{
public:
  PresidentialPardonForm(const std::string target);

  PresidentialPardonForm(const PresidentialPardonForm &f);

  ~PresidentialPardonForm();

  PresidentialPardonForm &operator=(const PresidentialPardonForm &f);

  void execute(const Bureaucrat &executor) const;

private:
  std::string target;
};


#endif //CPP05_PRESIDENTIALPARDONFORM_H
