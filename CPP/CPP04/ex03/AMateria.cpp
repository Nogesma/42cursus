#include "AMateria.h"

AMateria::AMateria(std::string const &t) : type(t) {}

std::string const &AMateria::getType() const { return this->type; }
