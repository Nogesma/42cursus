//
// Created by Mano Segransan on 3/3/22.
//

#include "Data.hpp"

uintptr_t serialize(Data *ptr);

Data *deserialize(uintptr_t raw);

int main()
{
	Data *d = new Data("42");

	std::cout << d << std::endl;

	uintptr_t ptr = serialize(d);
	std::cout << ptr << std::endl;

	std::cout << deserialize(ptr) << std::endl;
}
