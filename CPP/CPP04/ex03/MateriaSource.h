//
// Created by Mano Segransan on 3/31/22.
//

#ifndef CPP04_MATERIASOURCE_H
#define CPP04_MATERIASOURCE_H

#include "IMateriaSource.h"

class MateriaSource : public IMateriaSource {
public:
  MateriaSource();

  ~MateriaSource() {}
  void learnMateria(AMateria *);
  AMateria *createMateria(std::string const &type);

private:
  AMateria *m[4];
  int i;
};

#endif // CPP04_MATERIASOURCE_H
