//
// Created by segransm on 4/6/22.
//

#include "Span.hpp"
#include <iostream>
#include <climits>
#include <algorithm>

Span::Span(unsigned int N) {
  this->vect = std::vector<int>(N);
  this->vect.clear();
}

Span::Span(const Span &s) { this->vect = s.vect; }

Span::~Span() {}

Span &Span::operator=(const Span &s) {
  this->vect = s.vect;
  return (*this);
}

void Span::addNumber(int num) {
  if (this->vect.size() == this->vect.capacity())
    throw std::exception();
  this->vect.push_back(num);
}

void Span::print() const {
  for (std::vector<int>::const_iterator i = this->vect.begin(); i != this->vect.end();
       ++i)
    std::cout << *i << ' ';

  std::cout << '\n';
}

void Span::fill(const std::vector<int>::iterator &first,
                const std::vector<int>::iterator &last) {
  if (last < first || (unsigned long)(last - first) > this->vect.capacity() - this->vect.size())
    throw std::exception();
  this->vect.insert(this->vect.end(), first, last);
}

int Span::shortestSpanSorted(const std::vector<int>::const_iterator &first,
                             const std::vector<int>::const_iterator &last) const {
  int shortest = INT_MAX;
  int tmp;
  int i = 0;
  
  
  while (first + i + 1 != last) {
    tmp = std::abs(*(first + i) - *(first + i + 1));
    if (tmp < shortest)
      shortest = tmp;
	++i;
  }

  return (shortest);
}

int Span::shortestSpan() const {
  if (this->vect.size() < 2)
    throw std::exception();
  std::vector<int> tmp = this->vect;

  std::sort(tmp.begin(), tmp.end());

  return (this->shortestSpanSorted(tmp.begin(), tmp.end()));
}

int Span::longestSpan() const {
  if (this->vect.size() < 2)
    throw std::exception();
  return (*std::max_element(this->vect.begin(), this->vect.end()) -
          *std::min_element(this->vect.begin(), this->vect.end()));
}
