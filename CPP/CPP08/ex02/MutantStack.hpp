//
// Created by segransm on 4/6/22.
//

#ifndef CPP08_MUTANTSTACK_HPP
#define CPP08_MUTANTSTACK_HPP

#include <stack>

template<class T, class Container = deque <T> >
class MutantStack : std::stack<T, Container>
{
  explicit MutantStack(const container_type &);

  MutantStack(const MutantStack &);

  ~MutantStack();

  MutantStack &operator=(const MutantStack &);
};

#endif // CPP08_MUTANTSTACK_HPP
