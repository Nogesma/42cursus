//
// Created by Mano Segransan on 4/4/22.
//

#ifndef CPP06_NUMBER_HPP
#define CPP06_NUMBER_HPP

#include <iostream>

class Number
{
public:
  Number(std::string str);

  Number(const Number &n);

  ~Number();

  Number &operator=(const Number &n);

  char getChar() const;

  int getInt() const;

  float getFloat() const;

  double getDouble() const;

  int getValid() const;

private:
  char stoc(const std::string &s);

  int stoi(const std::string &s);

  float stof(const std::string &s);

  double stod(const std::string &s);

  class InvalidConversionException : public std::exception
  {
  public:
	const char *what() const throw()
	{
		return "Could not convert number.";
	}
  };

  char c;
  int i;
  float f;
  double d;
  int isValid;
};

std::ostream &operator<<(std::ostream &os, const Number &n);

#endif //CPP06_NUMBER_HPP
