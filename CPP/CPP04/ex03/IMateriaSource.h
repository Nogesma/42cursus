#ifndef CPP04_IMATERIASOURCE_H
#define CPP04_IMATERIASOURCE_H

#include <iostream>

class IMateriaSource {
public:
  virtual ~IMateriaSource() {}
  virtual void learnMateria(AMateria *) = 0;
  virtual AMateria *createMateria(std::string const &type) = 0;
};

#endif
