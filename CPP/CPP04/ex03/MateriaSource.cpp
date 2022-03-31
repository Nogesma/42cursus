//
// Created by Mano Segransan on 3/31/22.
//

#include "MateriaSource.h"

MateriaSource::MateriaSource(): IMateriaSource(), i(0) {

}


void MateriaSource::learnMateria(AMateria *AM) {
  if (this->i >= 4)
    return;

  this->m[i++] = AM;
}

AMateria *MateriaSource::createMateria(const std::string &type) {
  for (int i = 0; i < this->i; ++i) {
    if (this->m[i]->getType() == type)
      return (this->m[i]->clone());
  }
  return (NULL);
}
