//
// Created by Mano Segransan on 4/5/22.
//

#ifndef CPP07_WHATEVER_HPP
#define CPP07_WHATEVER_HPP

template <typename T> void swap(T &a, T &b) {
  T tmp;
  tmp = a;
  a = b;
  b = tmp;
}

template <typename T> T min(T &a, T &b) { return (a < b ? a : b); }

template <typename T> T max(T &a, T &b) { return (a > b ? a : b); }

#endif // CPP07_WHATEVER_HPP
