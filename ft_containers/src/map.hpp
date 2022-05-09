//
// Created by segransm on 5/9/22.
//

#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP

#include <cstddef>
#include <functional>
#include <memory>

#include "RedBlackTree.hpp"
#include "utility.hpp"

namespace ft
{
	template<typename Key, typename T, typename Compare = std::less<Key>,
			 typename Alloc = std::allocator<pair<const Key, T>>>
	class map
	{
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef pair<const key_type, mapped_type> value_type;
		typedef Compare key_compare;
		//	typedef value_comp value_compare;

		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;

		typedef typename std::iterator<pointer, map> iterator;
		typedef typename std::iterator<const_pointer, map> const_iterator;
		typedef typename std::reverse_iterator<iterator> reverse_iterator;
		typedef typename std::reverse_iterator<const_iterator> const_reverse_iterator;

		typedef std::iterator_traits<iterator> difference_type;
		typedef std::size_t size_type;

	private:
		RedBlackTree<T, Compare, Alloc> _value;
	};
}// namespace ft
#endif// FT_CONTAINERS_MAP_HPP
