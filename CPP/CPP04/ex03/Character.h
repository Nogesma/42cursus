//
// Created by Mano Segransan on 3/31/22.
//

#ifndef CPP04_CHARACTER_H
#define CPP04_CHARACTER_H

#include "ICharacter.h"

class Character : public ICharacter {
public:
  Character(const std::string &);
  ~Character() {}
  std::string const &getName() const;
  void equip(AMateria *m);
  void unequip(int idx);
  void use(int idx, ICharacter &target);

private:
  const std::string name;
  AMateria *m[4];
  int i;
};

#endif // CPP04_CHARACTER_H
