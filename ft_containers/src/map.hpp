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
		//		typedef value_comp value_compare;

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
			: _value(alloc), _comparator(value_compare(comp)), _allocator(alloc)
		{}

		template< class InputIterator >
		map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type());

		map(const map &x);

		~map(){};

		bool empty() const { return (_value.empty()); }
		size_type size() const { return (_value.size()); }

		size_type max_size() const { return (std::min(_allocator.max_size(), _value.max_size())); }

		mapped_type &operator[](const key_type &k)
		{
			value_type obj = value_type(k, mapped_type());

			return (_value.insert_no_overwrite(_comparator, obj).second);
		}

		void print() { _value.print(); }
		void clear() { _value.clear(); }

		size_type erase(const key_type &k)
		{
			value_type obj = value_type(k, mapped_type());
			return (_value.find_and_delete(_comparator, obj));
		}

	private:
		class value_compare : std::binary_function< value_type, value_type, bool >
		{
			friend class map;

		protected:
			Compare comp;
			explicit value_compare(Compare c) : comp(c) {}

		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			bool operator()(const value_type &x, const value_type &y) const
			{
				return comp(x.first, y.first);
			}
		};

		RedBlackTree< value_type, allocator_type > _value;
		const value_compare _comparator;
		allocator_type _allocator;
	};
}// namespace ft
#endif// FT_CONTAINERS_MAP_HPP
