//
// Created by Mano Segransan on 3/3/22.
//

#include "Array.hpp"


int main() {
  Array<int> a(20);

  std::cout << a[19] << '\n';
  a[19] = 12;
  std::cout << a[19];
}
