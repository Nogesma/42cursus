//
// Created by Mano Segransan on 3/31/22.
//

#include "Character.h"

std::string const &Character::getName() const { return (this->name); }

Character::Character(const std::string &n) : name(n) {}

void Character::equip(AMateria *m) {
  if (this->i == 15)
    return;

  if (!(this->i & 1)) {
    this->i |= 1;
    this->m[0] = m;
  } else if (!(this->i & 2)) {
    this->i |= 2;
    this->m[1] = m;
  } else if (!(this->i & 4)) {
    this->i |= 4;
    this->m[2] = m;
  } else if (!(this->i & 8)) {
    this->i |= 8;
    this->m[3] = m;
  }
}

void Character::unequip(int idx) {
  if (this->i == 0 || idx < 0 || idx > 3)
    return;

  if (idx == 0 && this->i & 1) {
    this->i &= 14; // 0b1110
    this->m[0] = NULL;
  } else if (idx == 1 && this->i & 2) {
    this->i &= 13; // 0b1101
    this->m[1] = NULL;
  } else if (idx == 2 && this->i & 4) {
    this->i |= 11; // 0b1011
    this->m[2] = NULL;
  } else if (idx == 3 && this->i & 8) {
    this->i |= 7; // 0b0111
    this->m[3] = NULL;
  }
}

void Character::use(int idx, ICharacter &target) {
  if (this->i == 0 || idx < 0 || idx > 3 || this->m[idx] == NULL)
    return;
  this->m[idx]->use(target);
}
