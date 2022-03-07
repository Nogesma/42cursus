//
// Created by Mano Segransan on 3/3/22.
//

#include "Dog.h"
#include "Cat.h"
#include "WrongCat.h"

int main()
{
	{
		const Animal* j = new Dog();
		const Animal* i = new Cat();
		delete j;//should not create a leak
		delete i;
	}
	std::cout << std::endl << std::endl << std::endl;
	{
		Animal *a[10];

		for (int i = 0; i < 10; ++i)
		{
			if (i < 5)
				a[i] = new Cat();
			else
				a[i] = new Dog();
		}

		for (int i = 0; i < 10; ++i)
			delete a[i];
	}
}
