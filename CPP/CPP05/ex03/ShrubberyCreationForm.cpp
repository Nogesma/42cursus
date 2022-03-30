//
// Created by Mano Segransan on 3/30/22.
//

#include "ShrubberyCreationForm.h"
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm(const std::string t) : Form(
	"Shrubbery Creation Form", 145, 137), target(t)
{
}


ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &f)
	: Form(f)
{
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
}

void ShrubberyCreationForm::execute(const Bureaucrat &executor) const
{
	Form::execute(executor);
	std::ofstream file(this->target + "_shrubbery");

	std::cout << "no error" << std::endl;
	file << "               ,@@@@@@@,\n"
				 "       ,,,.   ,@@@@@@/@@,  .oo8888o.\n"
				 "    ,&%%&%&&%,@@@@@/@@@@@@,8888\\88/8o\n"
				 "   ,%&\\%&&%&&%,@@@\\@@@/@@@88\\88888/88'\n"
				 "   %&&%&%&/%&&%@@\\@@/ /@@@88888\\88888'\n"
				 "   %&&%/ %&%%&&@@\\ V /@@' `88\\8 `/88'\n"
				 "   `&%\\ ` /%&'    |.|        \\ '|8'\n"
				 "       |o|        | |         | |\n"
				 "       |.|        | |         | |\n"
				 "jgs \\\\/ ._\\//_/__/  ,\\_//__\\\\/.  \\_//__/_\n";
}
