#pragma once
#ifndef __FIXED_H__
#define __FIXED_H__

class Fixed
{


public:

  typedef Fixed t;

  Fixed(void);

  ~Fixed(void);

  Fixed(const Fixed &obj);

  Fixed &operator=(const Fixed &obj);

  int getRawBits(void) const;

  void setRawBits(int const raw);

private:

  int _val;
  static const int _precision = 8;

};

#endif /* __FIXED_H__ */
