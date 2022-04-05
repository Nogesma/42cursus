//
// Created by Mano Segransan on 4/4/22.
//

#include "Number.hpp"
#include <sstream>
#include <iomanip>
#include <cmath>

Number::Number(char *s)
{
	std::string str(s);

	if (str.length() == 1 && std::isprint(str[0]) && !std::isdigit(str[0]))
	{
		this->type = 'c';
		this->val = str[0];
		this->isValid = 1;
	} else if ((str.back() == 'f' && str.find("inf") == std::string::npos) ||
			   str.find("inff") != std::string::npos)
	{
		str.pop_back();
		this->type = 'f';
	} else if (str.find('.') != std::string::npos ||
			   str == "nan" ||
			   str.find("inf") != std::string::npos)
		this->type = 'd';
	else
		this->type = 'i';

	if (this->type != 'c')
	{
		this->stod(str);
		if (str == "nan")
		{
			this->val = NAN;
			this->isValid = 1;
		} else if (str == "+inf" || str == "inf")
		{
			this->val = INFINITY;
			this->isValid = 1;
		} else if (str == "-inf")
		{
			this->val = -INFINITY;
			this->isValid = 1;
		}
	}
}

Number::Number(const Number &a)
{
	this->type = a.type;
	this->val = a.val;
}

Number &Number::operator=(const Number &a)
{
	this->type = a.type;
	this->val = a.val;
	return (*this);
}

Number::~Number()
{
}

double Number::getValue() const
{
	return (this->val);
}

char Number::getType() const
{
	return (this->type);
}

int Number::getValid() const
{
	return (this->isValid);
}

void Number::stod(const std::string &s)
{
	double i;

	if (std::istringstream(s) >> i)
	{
		this->val = i;
		this->isValid = 1;
	}
}

std::ostream &operator<<(std::ostream &os, const Number &n)
{
	os << "char: ";
	if (!n.getValid() ||
		static_cast<char>(n.getValue()) != std::round(n.getValue()))
		os << "impossible\n";
	else if (std::isprint(static_cast<char>(n.getValue())))
		os << '\'' << static_cast<char>(n.getValue()) << '\'' << '\n';
	else
		os << "Non displayable\n";

	os << "int: ";
	if (!n.getValid() ||
		static_cast<int>(n.getValue()) != std::round(n.getValue()))
		os << "impossible\n";
	else
		os << static_cast<int>(n.getValue()) << '\n';

	os << "float: ";
	if (!n.getValid() || (std::round(static_cast<float>(n.getValue())) !=
						  std::round(n.getValue()) &&
						  n.getValue() == n.getValue()))
		os << "impossible\n";
	else
	{
		if (static_cast<int>(n.getValue()) ==
			static_cast<double>(n.getValue())) // todo: fix precision
			os << std::fixed << std::setprecision(1);
		os << static_cast<double>(n.getValue()) << 'f' << '\n';
	}

	os << "double: ";
	if (!n.getValid())
		os << "impossible\n";
	else
	{
		if (static_cast<int>(n.getValue()) ==
			static_cast<double>(n.getValue())) // todo: fix precision
			os << std::fixed << std::setprecision(1);
		os << n.getValue() << '\n';
	}

	return (os);
}
