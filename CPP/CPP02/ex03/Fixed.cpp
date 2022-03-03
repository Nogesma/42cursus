#include "Fixed.hpp"

Fixed::Fixed(void) : _val(0)
{}

Fixed::~Fixed(void)
{}

Fixed::Fixed(const Fixed &obj)
{
	*this = obj;
}

Fixed::Fixed(const int i)
{
	this->_val = i << this->_precision;
}

Fixed::Fixed(const float f)
{
	this->_val = roundf(f * (1 << this->_precision));
}

Fixed &Fixed::operator=(const Fixed &obj)
{
	this->setRawBits(obj.getRawBits());
	return (*this);
}

Fixed Fixed::operator+(const Fixed &obj) const
{
	Fixed tmp;

	tmp._val = this->_val + obj._val;

	return (tmp);
}

Fixed Fixed::operator-(const Fixed &obj) const
{
	Fixed tmp;

	tmp._val = this->_val - obj._val;

	return (tmp);
}

Fixed Fixed::operator*(const Fixed &obj) const
{
	Fixed tmp(this->toFloat() * obj.toFloat());

	return (tmp);
}

Fixed Fixed::operator/(const Fixed &obj) const
{
	Fixed tmp(this->toFloat() / obj.toFloat());

	return (tmp);
}

bool Fixed::operator>(const Fixed &obj) const
{
	return (this->_val > obj._val);
}

bool Fixed::operator>=(const Fixed &obj) const
{
	return (this->_val >= obj._val);
}

bool Fixed::operator<(const Fixed &obj) const
{
	return (this->_val < obj._val);
}

bool Fixed::operator<=(const Fixed &obj) const
{
	return (this->_val <= obj._val);
}

bool Fixed::operator==(const Fixed &obj) const
{
	return (this->_val == obj._val);
}

bool Fixed::operator!=(const Fixed &obj) const
{
	return (this->_val != obj._val);
}

Fixed Fixed::operator++()
{
	++this->_val;

	return (*this);
}

Fixed Fixed::operator++(int)
{
	const Fixed old(*this);

	++(*this);

	return (old);
}

int Fixed::getRawBits(void) const
{
	return (this->_val);
}

void Fixed::setRawBits(const int raw)
{
	this->_val = raw;
}

int Fixed::toInt() const
{
	return (this->_val >> 8);
}

float Fixed::toFloat() const
{
	return ((float) this->_val / (1 << this->_precision));
}

std::ostream &operator<<(std::ostream &os, const Fixed &obj)
{
	os << obj.toFloat();
	return (os);
}

Fixed &Fixed::min(Fixed &a, Fixed &b)
{
	return ((a < b) ? a : b);
}

const Fixed &Fixed::min(const Fixed &a, const Fixed &b)
{
	return ((a < b) ? a : b);
}

Fixed &Fixed::max(Fixed &a, Fixed &b)
{
	return ((a > b) ? a : b);
}

const Fixed &Fixed::max(const Fixed &a, const Fixed &b)
{
	return ((a > b) ? a : b);
}
