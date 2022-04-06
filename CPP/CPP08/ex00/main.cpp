//
// Created by Mano Segransan on 3/3/22.
//

#include "easyfind.hpp"

#include <list>
#include <vector>

int main() {
  {
    std::vector<int> vect;

    for (int i = 0; i < 5; ++i) {
      vect.push_back(i);
    }

    std::list<int> list(vect.begin(), vect.end());

    std::vector<int>::iterator vectIt;
    std::list<int>::iterator listIt;

    if ((vectIt = easyfind(vect, 3)) != vect.end())
      std::cout << *vectIt << " ";
    else
      std::cout << "Not in containter ";
    if ((listIt = easyfind(list, 3)) != list.end())
      std::cout << *listIt << " ";
    else
      std::cout << "Not in containter ";
    std::cout << '\n';

    if ((vectIt = easyfind(vect, 0)) != vect.end())
      std::cout << *vectIt << " ";
    else
      std::cout << "Not in containter ";
    if ((listIt = easyfind(list, 0)) != list.end())
      std::cout << *listIt << " ";
    else
      std::cout << "Not in containter ";
    std::cout << '\n';

    if ((vectIt = easyfind(vect, -1)) != vect.end())
      std::cout << *vectIt << " ";
    else
      std::cout << "Not in containter ";
    if ((listIt = easyfind(list, -1)) != list.end())
      std::cout << *listIt << " ";
    else
      std::cout << "Not in containter ";
    std::cout << '\n';

    if ((vectIt = easyfind(vect, 9)) != vect.end())
      std::cout << *vectIt << " ";
    else
      std::cout << "Not in containter ";
    if ((listIt = easyfind(list, 9)) != list.end())
      std::cout << *listIt << " ";
    else
      std::cout << "Not in containter ";
    std::cout << '\n';
  }
}
