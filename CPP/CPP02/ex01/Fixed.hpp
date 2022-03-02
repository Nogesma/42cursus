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
