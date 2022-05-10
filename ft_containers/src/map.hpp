//
// Created by segransm on 5/9/22.
//

#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP

#include "RedBlackTree.hpp"
#include "utility.hpp"
#include <cstddef>
#include <functional>
#include <memory>
#include <string>
namespace ft
{
	template< typename Key, typename T, typename Compare = std::less< Key >,
			  typename Alloc = std::allocator< ft::pair< const Key, T > > >
	class map
	{
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair< const key_type, mapped_type > value_type;
		typedef Compare key_compare;
		//	typedef value_comp value_compare;

		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;

		typedef typename std::iterator< pointer, map > iterator;
		typedef typename std::iterator< const_pointer, map > const_iterator;
		typedef typename std::reverse_iterator< iterator > reverse_iterator;
		typedef typename std::reverse_iterator< const_iterator > const_reverse_iterator;

		typedef std::iterator_traits< iterator > difference_type;
		typedef std::size_t size_type;

		explicit map(const key_compare &comp = key_compare(),
					 const allocator_type &alloc = allocator_type())
			: _value(comp), _allocator(alloc)
		{
			value_type *v = _allocator.allocate(1, 0);
			const key_type a = "Hello 42!";
			_allocator.construct(v, ft::make_pair(a, 2));
//			_value.insert(v);
		}


		//		template< class InputIterator >
		//		map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(),
		//			const allocator_type &alloc = allocator_type());


		//		map(const map &x);


	private:
		// Overload pair comparison operator to only compare first element
		//		template< class T1, class T2 >
		//		bool operator<(const pair< T1, T2 > &lhs, const pair< T1, T2 > &rhs)
		//		{
		//			return (lhs.first < rhs.first);
		//		}
		//		typedef bool comparator_type(value_type, value_type) const;
		//
		//		bool apply_comparator(value_type a, value_type b) const
		//		{
		//			return (_comparator(a.first, b.first));
		//		}

		RedBlackTree< T, key_compare > _value;
		allocator_type _allocator;
	};
}// namespace ft
#endif// FT_CONTAINERS_MAP_HPP
