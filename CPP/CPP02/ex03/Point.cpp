#include "Point.hpp"

Point Point::operator=(const Point &obj)
{
	Point tmp(obj);

	return (tmp);
}

Fixed const Point::getX(void) const
{
	return (this->x);
}

Fixed const Point::getY(void) const
{
	return (this->y);
}
