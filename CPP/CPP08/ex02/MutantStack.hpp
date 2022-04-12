//
// Created by segransm on 4/6/22.
//

#ifndef CPP08_MUTANTSTACK_HPP
#define CPP08_MUTANTSTACK_HPP

#include <stack>
#include <iterator>

template<typename T>
class MutantStack : public std::stack<T>
{
public:
  typedef typename std::stack<T>::container_type::iterator iterator;

  explicit MutantStack();

  MutantStack(const MutantStack &);

  ~MutantStack();

  MutantStack &operator=(const MutantStack &);

  iterator begin();

  iterator end();
};

template<typename T>
MutantStack<T>::MutantStack(): std::stack<T>()
{

}

template<typename T>
MutantStack<T>::MutantStack(const MutantStack<T> &ms)
	: std::stack<T>(ms)
{

}

template<typename T>
MutantStack<T>::~MutantStack()
{

}

template<typename T>
MutantStack<T> &
MutantStack<T>::operator=(const MutantStack<T> &ms)
{
	this->c = ms.c;
	return (*this);
}

template<typename T>
typename MutantStack<T>::iterator MutantStack<T>::begin()
{
	return (std::stack<T>::c.begin());
}

template<typename T>
typename MutantStack<T>::iterator MutantStack<T>::end()
{
	return (std::stack<T>::c.end());
}

#endif // CPP08_MUTANTSTACK_HPP
