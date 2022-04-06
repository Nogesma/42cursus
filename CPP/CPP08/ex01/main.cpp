//
// Created by Mano Segransan on 3/3/22.
//

#include "Span.hpp"
#include <iostream>
#include <algorithm>

int main() {
  {
    Span sp = Span(5);

    sp.addNumber(6);
    sp.addNumber(3);
    sp.addNumber(17);
    sp.addNumber(9);
    sp.addNumber(11);

    sp.print();
    std::cout << sp.shortestSpan() << '\n';
    std::cout << sp.longestSpan() << '\n';
  }
  {
    std::vector<int> vect(1000000);
    Span sp = Span(1000000);

    std::generate(vect.begin(), vect.end(), std::rand);

    sp.fill(vect.begin(), vect.end());

    std::cout << sp.shortestSpan() << '\n';
    std::cout << sp.longestSpan() << '\n';
  }
}
