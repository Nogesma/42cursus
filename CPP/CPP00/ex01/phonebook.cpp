#include <iostream>
#include <string>

class Contact
{

public:
  Contact(std::string firstname,
		  std::string lastname,
		  std::string nickname,
		  std::string phone_number,
		  std::string darkest_secret,
		  bool iscontact
  );

private:
  std::string firstname;
  std::string lastname;
  std::string nickname;
  std::string phone_number;
  std::string darkest_secret;
  bool iscontact;
};

class PhoneBook
{

public:
  static void addContact(int i);

private:
  Contact contact[8];

};

Contact::Contact( std::string firstname,
				  std::string lastname,
				  std::string nickname,
				  std::string phone_number,
				  std::string darkest_secret,
				  bool iscontact ):
				  	firstname(firstname),
					lastname(lastname),
					nickname(nickname),
					phone_number(phone_number),
					darkest_secret(darkest_secret),
					iscontact(iscontact)
{
	return ;
}

void PhoneBook::addContact(int i)
{
	std::string fn;
	std::string ln;
	std::string nn;
	std::string pn;
	std::string ds;

	std::cout << "First name:";
	std::getline(std::cin, fn);
	if (!std::cin) std::exit(0);
	std::cout << "Last name:";
	std::getline(std::cin, ln);
	if (!std::cin) std::exit(0);
	std::cout << "Nickname:";
	std::getline(std::cin, nn);
	if (!std::cin) std::exit(0);
	std::cout << "Phone number:";
	std::getline(std::cin, pn);
	if (!std::cin) std::exit(0);
	std::cout << "Darkest secret:";
	std::getline(std::cin, ds);
	if (!std::cin) std::exit(0);
	this->contact[i] = Contact::Contact(fn, ln, nn, pn, 1);
}

//void print_w10(std::string s)
//{
//	if (s.length() > 10)
//	{
//		for (int i = 0; i < 9; i++)
//			std::cout << s[i];
//		std::cout << '.';
//	} else
//	{
//		for (int i = 0; i + s.length() < 10; i++)
//			std::cout << ' ';
//		std::cout << s;
//	}
//}

//void print_contact(PhoneBook *pb, int i)
//{
//	if (i < 0 || i > 7 || !pb->contact[i].iscontact)
//	{
//		std::cerr << i << " is not a valid index." << std::endl;
//		return;
//	}
//	std::cout << std::endl << "First name:";
//	std::cout << pb->contact[i].firstname << std::endl;
//	std::cout << "Last name: ";
//	std::cout << pb->contact[i].lastname << std::endl;
//	std::cout << "Nickname: ";
//	std::cout << pb->contact[i].nickname << std::endl;
//	std::cout << "Phone number: ";
//	std::cout << pb->contact[i].phone_number << std::endl;
//	std::cout << "Darkest secret: ";
//	std::cout << pb->contact[i].darkest_secret << std::endl << std::endl;
//}

//void print_index(PhoneBook *pb)
//{
//	std::cout << std::endl << "|     index|first name| last name|  nickname|"
//			  << std::endl;
//	std::cout << "|----------|----------|----------|----------|" << std::endl;
//	for (int i = 0; i < 8; i++)
//	{
//		if (!pb->contact[i].iscontact)
//			break;
//		std::cout << "|";
//		print_w10(std::to_string(i));
//		std::cout << "|";
//		print_w10(pb->contact[i].firstname);
//		std::cout << "|";
//		print_w10(pb->contact[i].lastname);
//		std::cout << "|";
//		print_w10(pb->contact[i].nickname);
//		std::cout << "|" << std::endl;
//	}
//	std::cout << std::endl;
//}

//void search(PhoneBook *pb)
//{
//	std::string line;
//
//	print_index(pb);
//	std::cout << "Enter contact index to get more info: ";
//	std::getline(std::cin, line);
//	try
//	{
//		print_contact(pb, std::stoi(line));
//	}
//	catch (...)
//	{
//		std::cerr << line << " is not a valid index." << std::endl;
//	}
//}

int main(void)
{
	std::string line;
	PhoneBook pb;
	int i = 0;

	for (int j = 0; j < 8; j++)
		pb.contact[j].iscontact = 0;
	std::cout << "> ";
	std::getline(std::cin, line);
	while (std::cin)
	{
		if (line == "ADD")
		{
			add_contact(&pb, i);
			i++;
			if (i == 8)
				i = 0;
		}
//		else if (line == "SEARCH")
//			search(&pb);
//		else if (line == "EXIT")
//			std::exit(0);
		std::cout << "> ";
		std::getline(std::cin, line);
	}
}
