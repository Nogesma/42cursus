//
// Created by Mano Segransan on 4/5/22.
//

#ifndef CPP07_ITER_HPP
#define CPP07_ITER_HPP

#include <iostream>

template <typename T> void iter(T *t, size_t s, void (*f)(T &)) {
  for (size_t i = 0; i < s; ++i)
    f(t[i]);
}

#endif // CPP07_ITER_HPP
