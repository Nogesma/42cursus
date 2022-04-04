//
// Created by Mano Segransan on 4/4/22.
//

#ifndef CPP06_NUMBER_HPP
#define CPP06_NUMBER_HPP

#include <iostream>

class Data
{
public:
  Data(const std::string &str);

  Data(const Data &d);

  ~Data();

  Data &operator=(const Data &n);

  std::string getData() const;
private:
  std::string name;
};

#endif //CPP06_NUMBER_HPP
