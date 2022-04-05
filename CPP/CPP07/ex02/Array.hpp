//
// Created by Mano Segransan on 4/5/22.
//

#ifndef CPP07_ARRAY_HPP
#define CPP07_ARRAY_HPP

#include <iostream>

template <typename T> class Array {
public:
  Array();

  Array(unsigned int);

  Array(const Array<T> &);

  Array<T> &operator=(const Array<T> &);

  T &operator[](const size_t &i);

  size_t size() const;

private:
  T *getArray() const;

  T *t;
  size_t s;
};

template <typename T> Array<T>::Array() {
  this->t = new T[0];
  this->s = 0;
}

template <typename T> Array<T>::Array(unsigned int n) {
  this->t = new T[n];
  this->s = n;
}

template <typename T> Array<T>::Array(const Array<T> &a) {
  this->t = new T[a.getSize()];
  this->size = a.getSize();

  for (int i = 0; i < a.getSize(); ++i) {
    this->t[i] = a.getArray()[i];
  }
}

template <typename T> Array<T> &Array<T>::operator=(const Array<T> &a) {
  this->t = new T[a.size()];
  this->size = a.size();

  for (int i = 0; i < a.size(); ++i) {
    this->t[i] = a[i];
  }

  return (*this);
}

template <typename T>
T &Array<T>::operator[](const size_t &i) {
  if (i < 0 || i >= this->s)
    throw std::exception();

  return (this->t[i]);
}

template <typename T> size_t Array<T>::size() const { return (this->s); }

template <typename T> T *Array<T>::getArray() const { return (this->t); }

//#include "Array.tpp"

#endif // CPP07_ARRAY_HPP
