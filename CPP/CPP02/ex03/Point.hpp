#pragma once
#ifndef __POINT_H__
#define __POINT_H__

#include <iostream>
#include "Fixed.hpp"

class Point
{


public:

  typedef Point t;

  Point(void) : x(0), y(0)
  {};

  Point(float const x, float const y) : x(x), y(y)
  {};

  Point(Fixed const x, Fixed const y) : x(x), y(y)
  {};

  ~Point(void)
  {};

  Point(const Point &obj) : x(obj.x), y(obj.y)
  {};

  Point operator=(const Point &obj);

  Fixed const getX(void) const;

  Fixed const getY(void) const;

private:

  Fixed const x;
  Fixed const y;

};

#endif /* __POINT_H__ */
