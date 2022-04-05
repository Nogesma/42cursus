//
// Created by Mano Segransan on 3/3/22.
//

#include "whatever.hpp"
#include <iostream>

int main() {
  {
    int a = 4;
    int b = 2;

    std::cout << a << " " << b << '\n';
    std::cout << "min: " << min(a, b) << '\n';
    std::cout << "max: " << max(a, b) << '\n';
    swap(a, b);
    std::cout << a << " " << b << '\n';
  }
  std::cout << '\n';
  {
    float a = 42.42f;
    float b = 13.37f;

    std::cout << a << " " << b << '\n';
    std::cout << "min: " << min(a, b) << '\n';
    std::cout << "max: " << max(a, b) << '\n';
    swap(a, b);
    std::cout << a << " " << b << '\n';
  }
  std::cout << "\n\n";
  {
    int a = 2;
    int b = 3;
    ::swap(a, b);
    std::cout << "a = " << a << ", b = " << b << std::endl;
    std::cout << "min( a, b ) = " << ::min(a, b) << std::endl;
    std::cout << "max( a, b ) = " << ::max(a, b) << std::endl;
    std::string c = "chaine1";
    std::string d = "chaine2";
    ::swap(c, d);
    std::cout << "c = " << c << ", d = " << d << std::endl;
    std::cout << "min( c, d ) = " << ::min(c, d) << std::endl;
    std::cout << "max( c, d ) = " << ::max(c, d) << std::endl;
    return 0;
  }
}
