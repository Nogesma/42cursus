//
// Created by Mano Segransan on 3/3/22.
//

#include "Dog.h"
#include "Cat.h"
#include "WrongCat.h"

int main()
{
	{
		const Animal *meta = new Animal();
		const Animal *j = new Dog();
		const Animal *i = new Cat();
		std::cout << j->getType() << " " << std::endl;
		std::cout << i->getType() << " " << std::endl;
		i->makeSound(); //will output the cat sound!
		j->makeSound();
		meta->makeSound();

		delete meta;
		delete j;
		delete i;
	}
	std::cout << std::endl << std::endl << std::endl;
	{
		const WrongAnimal *meta = new WrongAnimal();
		const Animal *j = new Dog();
		const WrongAnimal *i = new WrongCat();
		std::cout << j->getType() << " " << std::endl;
		std::cout << i->getType() << " " << std::endl;
		i->makeSound(); //will output the cat sound!
		j->makeSound();
		meta->makeSound();

		delete meta;
		delete j;
		delete i;
	}
	return 0;

}
