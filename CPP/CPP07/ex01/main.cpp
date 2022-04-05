//
// Created by Mano Segransan on 3/3/22.
//

#include "iter.hpp"

template <typename T> void print(T t) { std::cout << t << '\n'; }

void printInt(int &i) { std::cout << i << '\n'; }

void printStr(std::string &i) { std::cout << i; }

int main() {
  int lst[5] = {0, 1, 2, 3, 4};
  std::string str[3] = {"Hello", " ", "42!"};

  iter(lst, 5, printInt);
  iter(str, 3, printStr);

  iter(lst, 5, print);
  iter(str, 3, print);
}
