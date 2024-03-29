//
// Created by segransm on 1/26/22.
//

#ifndef CPP00_CONTACT_HPP
#define CPP00_CONTACT_HPP

#include <string>

class Contact
{

public:
  std::string getFirstname(void);

  std::string getLastname(void);

  std::string getNickname(void);

  std::string getPhoneNumber(void);

  std::string getDarkestSecret(void);

  bool getContact(void);

  void updateContact(std::string _firstname,
					 std::string _lastname,
					 std::string _nickname,
					 std::string _phone_number,
					 std::string _darkest_secret,
					 bool _iscontact);

  Contact();
  ~Contact(void);

private:
  std::string _firstname;
  std::string _lastname;
  std::string _nickname;
  std::string _phone_number;
  std::string _darkest_secret;
  bool _iscontact;
};

#endif //CPP00_CONTACT_HPP
