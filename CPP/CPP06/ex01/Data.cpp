//
// Created by Mano Segransan on 4/4/22.
//

#include "Data.hpp"
#include <sstream>
#include <iomanip>
#include <cmath>

Data::Data(const std::string &str): name(str)
{
}

Data::Data(const Data &d)
{
	this->name = d.getData();
}

Data &Data::operator=(const Data &d)
{
	this->name = d.getData();

	return (*this);
}

Data::~Data()
{
}

std::string Data::getData() const
{
	return (this->name);
}
