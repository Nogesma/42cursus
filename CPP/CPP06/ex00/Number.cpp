//
// Created by Mano Segransan on 4/4/22.
//

#include "Number.hpp"
#include <sstream>
#include <iomanip>
#include <cmath>

Number::Number(std::string str)
{
	if (str.back() == 'f')
		str.pop_back();

	this->c = this->stoc(str);
	this->i = this->stoi(str);
	this->f = this->stof(str);
	this->d = this->stod(str);

	if (str == "nan")
	{
		this->f = NAN;
		this->isValid |= 4;
		this->d = NAN;
		this->isValid |= 8;
	}
	else if (str == "+inf" || str == "inf")
	{
		this->f = INFINITY;
		this->isValid |= 4;
		this->d = INFINITY;
		this->isValid |= 8;
	}	else if (str == "-inf")
	{
		this->f = INFINITY;
		this->isValid |= 4;
		this->d = INFINITY;
		this->isValid |= 8;

	}
}

Number::Number(const Number &a)
{
	this->c = a.getChar();
	this->i = a.getInt();
	this->f = a.getFloat();
	this->d = a.getDouble();
	this->isValid = a.getValid();
}

Number &Number::operator=(const Number &a)
{
	this->c = a.getChar();
	this->i = a.getInt();
	this->f = a.getFloat();
	this->d = a.getDouble();
	this->isValid = a.getValid();
	return (*this);
}

Number::~Number()
{
}

char Number::getChar() const
{
	return (this->c);
}

int Number::getInt() const
{
	return (this->i);
}

float Number::getFloat() const
{
	return (this->f);
}

double Number::getDouble() const
{
	return (this->d);
}

int Number::getValid() const
{
	return (this->isValid);
}

char Number::stoc(const std::string &s)
{
	int i;

	if (std::istringstream(s) >> i)
		this->isValid |= 1;
	if (i > CHAR_MAX || i < CHAR_MIN)
		this->isValid &= 14; // 0b1110
	return (i);

}

int Number::stoi(const std::string &s)
{
	int i;

	if (std::istringstream(s) >> i)
		this->isValid |= 2;
	return (i);
}

float Number::stof(const std::string &s)
{
	float i;

	if (std::istringstream(s) >> i)
		this->isValid |= 4;
	return (i);
}

double Number::stod(const std::string &s)
{
	double i;

	if (std::istringstream(s) >> i)
		this->isValid |= 8;
	return (i);
}


std::ostream &operator<<(std::ostream &os, const Number &n)
{
	os << "char: ";
	if (!(n.getValid() & 1))
		os << "impossible\n";
	else if (std::isprint(n.getChar()))
		os << '\'' << n.getChar() << '\'' << '\n';
	else
		os << "Non displayable\n";

	os << "int: ";
	if (!(n.getValid() & 2))
		os << "impossible\n";
	else
		os << n.getInt() << '\n';

	os << "float: ";
	if (!(n.getValid() & 4))
		os << "impossible\n";
	else
	{
		if (n.getInt() == n.getFloat())
			os << std::fixed << std::setprecision(1);
		os << n.getFloat() << 'f' << '\n';
	}

	os << "double: ";
	if (!(n.getValid() & 8))
		os << "impossible";
	else
	{
		if (n.getInt() == n.getDouble())
			os << std::fixed << std::setprecision(1);
		os << n.getDouble() << std::endl;
	}

	return (os);
}
