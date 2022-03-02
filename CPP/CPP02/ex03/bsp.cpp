#include "Fixed.hpp"
#include "Point.hpp"

bool	orientation(Point const a, Point const b, Point const c)
{
	Point AB(b.getX() - a.getX(), b.getY() - a.getY());
	Point AC(c.getX() - a.getX(), c.getY() - a.getY());

	return (((AB.getX() * AC.getY()) - (AB.getY() * AC.getX())) > 0);
}

bool	bsp(Point const a, Point const b, Point const c, Point const point)
{
	return (orientation(a, b, point) + orientation(b, c, point) +
				orientation(c, a, point) == 3);
}
