//
// Created by Mano Segransan on 5/10/22.
//

#ifndef FT_CONTAINERS_ITERATOR_HPP
#define FT_CONTAINERS_ITERATOR_HPP

#include <iterator>

namespace ft
{
	template< class Iterator >
	class iterator_traits
	{};

	template< class T >
	class iterator_traits< T * >
	{};
	template< class T >
	class iterator_traits< const T * >
	{};

	template< class Category, class T, class Distance = ptrdiff_t,
			  class Pointer = T *, class Reference = T & >
	struct iterator
	{
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
		typedef Category iterator_category;
	};

	template< class Iterator >
	class reverse_iterator
	{};
}// namespace ft
#endif//FT_CONTAINERS_ITERATOR_HPP
