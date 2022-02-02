//
// Created by segransm on 1/26/22.
//

#ifndef CPP00_PHONEBOOK_HPP
#define CPP00_PHONEBOOK_HPP

#include "Contact.hpp"


class PhoneBook
{

public:
  void addContact(int);

  void printContact(int i);
  void printIndex(void);

  PhoneBook(void);

  ~PhoneBook(void);

private:
  Contact contact[8];
};

#endif //CPP00_PHONEBOOK_HPP
