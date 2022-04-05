//
// Created by Mano Segransan on 4/4/22.
//

#ifndef CPP06_NUMBER_HPP
#define CPP06_NUMBER_HPP

#include <iostream>

class Number
{
public:
  Number(char *s);

  Number(const Number &n);

  ~Number();

  Number &operator=(const Number &n);

  double getValue() const;

  char getType() const;

  int getValid() const;

private:
  void stod(const std::string &s);

  int isValid;
  double val;
  char type;
};

std::ostream &operator<<(std::ostream &os, const Number &n);

#endif //CPP06_NUMBER_HPP
