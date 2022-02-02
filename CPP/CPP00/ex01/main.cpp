//
// Created by segransm on 1/26/22.
//
#include "Phonebook.hpp"
#include "Contact.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>

void search(PhoneBook *pb)
{
	std::string line;
	std::stringstream ss;
	int i;

	pb->printIndex();
	std::cout << "Enter contact index to get more info: ";
	std::getline(std::cin, line);
	i = line[0] - '0';
	if (line[1] == 0 && i >= 0 && i <= 7)
		pb->printContact(i);
	else
		std::cerr << line << " is not a valid index." << std::endl;
}

int main(void)
{
	std::string line;
	PhoneBook pb;
	int i = 0;

	std::cout << "> ";
	std::getline(std::cin, line);
	while (std::cin)
	{
		if (line == "ADD")
		{
			pb.addContact(i);
			i++;
			if (i == 8)
				i = 0;
		} else if (line == "SEARCH")
			search(&pb);
		else if (line == "EXIT")
			std::exit(0);
		std::cout << "> ";
		std::getline(std::cin, line);
	}
}