#include "Fixed.hpp"

Fixed::Fixed(void) : _val(0)
{
	std::cout << "Default constructor called" << std::endl;
}

Fixed::~Fixed(void)
{
	std::cout << "Destructor called" << std::endl;
}

Fixed::Fixed(const Fixed &obj)
{
	std::cout << "Copy constructor called" << std::endl;
	*this = obj;
}

Fixed::Fixed(const int i)
{
	std::cout << "Int constructor called" << std::endl;
	this->_val = i << this->_precision;
}

Fixed::Fixed(const float f)
{
	std::cout << "Float constructor called" << std::endl;
	this->_val = roundf(f * (1 << this->_precision));
}

Fixed &Fixed::operator=(const Fixed &obj)
{
	std::cout << "Copy assignment operator called" << std::endl;

	this->setRawBits(obj.getRawBits());

	return (*this);
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
