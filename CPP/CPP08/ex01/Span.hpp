//
// Created by segransm on 4/6/22.
//

#ifndef CPP08_SPAN_HPP
#define CPP08_SPAN_HPP

#include <vector>

class Span {
public:
  Span(unsigned int);

  Span(const Span &);

  ~Span();

  Span &operator=(const Span &);

  void addNumber(int);
  void fill(const std::vector<int>::iterator &,
            const std::vector<int>::iterator &);

  int shortestSpan();
  int longestSpan() const;

  void print();

private:
  int shortestSpanSorted(std::vector<int>::iterator,
                         std::vector<int>::iterator);

  std::vector<int> vect;
};

#endif // CPP08_SPAN_HPP
