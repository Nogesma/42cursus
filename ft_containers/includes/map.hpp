//
// Created by segransm on 5/9/22.
//

#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP

#include <RedBlackTree.hpp>
#include <algorithm.hpp>
#include <iterator.hpp>
#include <utility.hpp>

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
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;


	private:
		typedef RedBlackTree< value_type, allocator_type > rbtree_type;

	public:
		typedef typename rbtree_type::iterator iterator;
		typedef typename rbtree_type::const_iterator const_iterator;

		typedef typename rbtree_type::reverse_iterator reverse_iterator;
		typedef typename rbtree_type::const_reverse_iterator const_reverse_iterator;

		typedef typename rbtree_type::difference_type difference_type;
		typedef typename rbtree_type::size_type size_type;


		/* Constructors */
		explicit map(const key_compare &comp = key_compare(),
					 const allocator_type &alloc = allocator_type())
			: _value(alloc), _comparator(value_compare(comp)), _allocator(alloc)
		{}

		template< class InputIterator >
		map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type())
			: _value(alloc), _comparator(value_compare(comp)), _allocator(alloc)
		{
			insert(first, last);
		}

		map(const map &x)
			: _value(x._allocator), _comparator(x._comparator), _allocator(x._allocator)
		{
			insert(x.begin(), x.end());
		}

		~map(){};

		map &operator=(const map &x)
		{
			_value = x._value;
			_comparator = x._comparator;
			_allocator = x._allocator;
			return (*this);
		}
		/* Iterators */
		iterator begin() { return _value.begin(); }

		const_iterator begin() const { return _value.begin(); }

		iterator end() { return _value.end(); }

		const_iterator end() const { return _value.end(); }

		reverse_iterator rbegin() { return (_value.rbegin()); }

		const_reverse_iterator rbegin() const { return (_value.rbegin()); }

		reverse_iterator rend() { return _value.rend(); }

		const_reverse_iterator rend() const { return (_value.rend()); }

		/* Capacity */
		bool empty() const { return (_value.empty()); }

		size_type size() const { return (_value.size()); }

		size_type max_size() const { return (std::min(_allocator.max_size(), _value.max_size())); }

		/* Element access */
		mapped_type &operator[](const key_type &k)
		{
			value_type obj = value_type(k, mapped_type());

			return (*(_value.insert(_comparator, obj).first)).second;
		}

		/* Modifiers */

		ft::pair< iterator, bool > insert(const value_type &val)
		{
			return (_value.insert(_comparator, val));
		}


		iterator insert(iterator position, const value_type &val)
		{
			return (_value.insert(_comparator, val, position).first);// todo: maybe fix hint
		}


		template< class InputIterator >
		void
		insert(InputIterator first, InputIterator last,
			   typename ft::enable_if< !ft::is_integral< InputIterator >::value, int >::type = 0)
		{
			for (; first != last; ++first) _value.insert(_comparator, *first);
		}

		void erase(iterator position) { _value.del_elem(*position); }

		size_type erase(const key_type &k)
		{
			value_type obj = value_type(k, mapped_type());
			return (_value.find_and_delete(_comparator, obj));
		}

		void erase(iterator first, iterator last)
		{
			for (; first != last; ++first) _value.del_elem(*first);
		}

		void swap(map &x)
		{
			std::swap(_comparator, x._comparator);
			std::swap(_allocator, x._allocator);
			ft::swap(_value, x._value);
		}

		void clear() { _value.clear(); }

		/* Observers */
		key_compare key_comp() const { return _comparator.comp; }

		value_compare value_comp() const { return (_comparator); }

		/* Operations */
		iterator find(const key_type &k)
		{
			value_type obj = value_type(k, mapped_type());
			ft::pair< iterator, int > f = _value.find(_comparator, obj);
			if (f.second != 0) return (end());
			return (f.first);
		}


		const_iterator find(const key_type &k) const
		{
			value_type obj = value_type(k, mapped_type());
			ft::pair< const_iterator, int > f = _value.find(_comparator, obj);
			if (f.second != 0) return (end());
			return (f.first);
		}

		size_type count(const key_type &k) const
		{
			value_type obj = value_type(k, mapped_type());
			ft::pair< iterator, int > f = _value.find(_comparator, obj);
			if (f.second != 0) return (0);
			return (1);
		}

		//todo: lower/upper bound, equal range
		iterator lower_bound(const key_type &k)
		{
			value_type obj = value_type(k, mapped_type());
			_value.lower_bound(_comparator, obj);
		}
		const_iterator lower_bound(const key_type &k) const
		{
			value_type obj = value_type(k, mapped_type());
			_value.lower_bound(_comparator, obj);
		}

		/* Allocator */
		allocator_type get_allocator() const { return _allocator; }


	private:
		rbtree_type _value;
		value_compare _comparator;
		allocator_type _allocator;
	};


	template< class Key, class T, class Compare, class Alloc >
	bool operator==(const map< Key, T, Compare, Alloc > &lhs,
					const map< Key, T, Compare, Alloc > &rhs)
	{
		if (lhs.size() != rhs.size()) return (false);

		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}


	template< class Key, class T, class Compare, class Alloc >
	bool operator!=(const map< Key, T, Compare, Alloc > &lhs,
					const map< Key, T, Compare, Alloc > &rhs)
	{
		return (!(lhs == rhs));
	}


	template< class Key, class T, class Compare, class Alloc >
	bool operator<(const map< Key, T, Compare, Alloc > &lhs,
				   const map< Key, T, Compare, Alloc > &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}


	template< class Key, class T, class Compare, class Alloc >
	bool operator<=(const map< Key, T, Compare, Alloc > &lhs,
					const map< Key, T, Compare, Alloc > &rhs)
	{
		return (!(rhs < lhs));
	}


	template< class Key, class T, class Compare, class Alloc >
	bool operator>(const map< Key, T, Compare, Alloc > &lhs,
				   const map< Key, T, Compare, Alloc > &rhs)
	{
		return (rhs < lhs);
	}


	template< class Key, class T, class Compare, class Alloc >
	bool operator>=(const map< Key, T, Compare, Alloc > &lhs,
					const map< Key, T, Compare, Alloc > &rhs)
	{
		return (!(lhs < rhs));
	}

	template< class Key, class T, class Compare, class Alloc >
	void swap(map< Key, T, Compare, Alloc > &x, map< Key, T, Compare, Alloc > &y)
	{
		x.swap(y);
	}

}// namespace ft
#endif// FT_CONTAINERS_MAP_HPP
