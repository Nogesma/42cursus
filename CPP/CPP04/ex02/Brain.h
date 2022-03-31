//
// Created by Mano Segransan on 3/3/22.
//

#ifndef CPP04_BRAIN_H
#define CPP04_BRAIN_H

#include <iostream>

class Brain {
public:
  Brain();

  ~Brain();

  Brain(const Brain &a);

  Brain &operator=(const Brain &a);

private:
  std::string ideas[100];
};

#endif // CPP04_BRAIN_H
