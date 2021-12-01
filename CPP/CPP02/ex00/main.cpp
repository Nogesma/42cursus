#include <iostream>

int main(void)
{
//	Fixed a;
//	Fixed b(a);
//	Fixed c;
//
//	c = b;
//	std::cout << a.getRawBits() << std::endl;
//	std::cout << b.getRawBits() << std::endl;
//	std::cout << c.getRawBits() << std::endl;

	int j;

	int n = 42;

	for (j = 0; j < 16; j++)
		printf ("%s", (n & (0x01 << j)) ? "1" : "0");
	return 0;
}
