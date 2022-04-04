//
// Created by Mano Segransan on 4/4/22.
//

#include "Data.hpp"

uintptr_t serialize(Data *ptr)
{
	return (reinterpret_cast<uintptr_t>(ptr));
}


Data *deserialize(uintptr_t raw)
{
	return (reinterpret_cast<Data *>(raw));
}
