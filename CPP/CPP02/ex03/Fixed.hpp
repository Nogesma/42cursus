#pragma once
#ifndef __FIXED_H__
#define __FIXED_H__

#include <iostream>

class Fixed
{


public:

  typedef Fixed t;

  Fixed(void);

  ~Fixed(void);

  Fixed(const Fixed &obj);

  Fixed(const int i);

  Fixed(const float f);

  Fixed &operator=(const Fixed &obj);


  Fixed operator+(const Fixed &obj) const;

  Fixed operator-(const Fixed &obj) const;

  Fixed operator*(const Fixed &obj) const;

  Fixed operator/(const Fixed &obj) const;


  bool operator>(const Fixed &obj) const;

  bool operator>=(const Fixed &obj) const;

  bool operator<(const Fixed &obj) const;

  bool operator<=(const Fixed &obj) const;

  bool operator==(const Fixed &obj) const;

  bool operator!=(const Fixed &obj) const;


  Fixed operator++();

  Fixed operator++(int);


  static Fixed &min(Fixed &a, Fixed &b);

  static const Fixed &min(const Fixed &a, const Fixed &b);

  static Fixed &max(Fixed &a, Fixed &b);

  static const Fixed &max(const Fixed &a, const Fixed &b);


  int getRawBits(void) const;

  void setRawBits(int const raw);

  float toFloat(void) const;

  int toInt(void) const;

private:

  int _val;
  static const int _precision = 8;

};

std::ostream &operator<<(std::ostream &os, const Fixed &obj);


#endif /* __FIXED_H__ */
