//
// Created by segransm on 4/6/22.
//

#ifndef CPP08_EASYFIND_HPP
#define CPP08_EASYFIND_HPP

#include <algorithm>
#include <iostream>

template <typename T> typename T::iterator easyfind(T &a, int n) {
  return (std::find(a.begin(), a.end(), n));
}

#endif // CPP08_EASYFIND_HPP
