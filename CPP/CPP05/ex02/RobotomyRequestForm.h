//
// Created by Mano Segransan on 3/30/22.
//

#ifndef CPP05_ROBOTOMYREQUESTFORM_H
#define CPP05_ROBOTOMYREQUESTFORM_H

#include "Form.h"

class RobotomyRequestForm : public Form
{
public:
  RobotomyRequestForm(const std::string target);

  RobotomyRequestForm(const RobotomyRequestForm &f);

  ~RobotomyRequestForm();

  RobotomyRequestForm &operator=(const RobotomyRequestForm &f);

  void execute(Bureaucrat const & executor) const;
private:
  std::string target;
};


#endif //CPP05_ROBOTOMYREQUESTFORM_H
