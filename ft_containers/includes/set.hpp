//
// Created by segransm on 5/20/22.
//

#ifndef FT_CONTAINERS_SET_HPP
#define FT_CONTAINERS_SET_HPP

#include <RedBlackTree.hpp>
#include <algorithm.hpp>

#include <functional>
#include <memory>

namespace ft
{
	template< class T, class Compare = std::less< T >, class Alloc = std::allocator< T > >
	class set
	{

	public:
		typedef T key_type;
		typedef T value_type;
		typedef Compare key_compare;
		typedef Compare value_compare;

		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;


	private:
		typedef RedBlackTree< value_type, allocator_type > rbtree_type;

	public:
		typedef typename rbtree_type::const_iterator iterator;
		typedef typename rbtree_type::const_iterator const_iterator;

		typedef typename rbtree_type::const_reverse_iterator reverse_iterator;
		typedef typename rbtree_type::const_reverse_iterator const_reverse_iterator;

		typedef typename rbtree_type::difference_type difference_type;
		typedef typename rbtree_type::size_type size_type;

	private:
		rbtree_type _value;
		value_compare _comparator;
		allocator_type _allocator;

	public:
		/* Constructors */
		explicit set(const key_compare &comp = key_compare(),
					 const allocator_type &alloc = allocator_type())
			: _value(alloc), _comparator(comp), _allocator(alloc)
		{}

		template< class InputIterator >
		set(InputIterator first, InputIterator last, const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type())
			: _value(alloc), _comparator(comp), _allocator(alloc)
		{
			insert(first, last);
		}

		set(const set &x)
			: _value(x._allocator), _comparator(x._comparator), _allocator(x._allocator)
		{
			insert(x.begin(), x.end());
		}

		~set(){};

		set &operator=(const set &x)
		{
			clear();
			_comparator = x._comparator;
			insert(x.begin(), x.end());
			return (*this);
		}

		/* Iterators */
		const_iterator begin() const { return _value.begin(); }

		const_iterator end() const { return _value.end(); }

		const_reverse_iterator rbegin() const { return (_value.rbegin()); }

		const_reverse_iterator rend() const { return (_value.rend()); }

		/* Capacity */
		bool empty() const { return (_value.empty()); }

		size_type size() const { return (_value.size()); }

		size_type max_size() const { return (std::min(_allocator.max_size(), _value.max_size())); }

		/* Modifiers */
		ft::pair< iterator, bool > insert(const value_type &val)
		{
			ft::pair< typename rbtree_type::iterator, bool > p = _value.insert(_comparator, val);
			return pair< iterator, bool >(p.first, p.second);
		}

		iterator insert(iterator position, const value_type &val)
		{
			ft::pair< typename rbtree_type::iterator, bool > p =
				_value.insert(_comparator, position, val);

			return p.first;
		}

		template< class InputIterator >
		void
		insert(InputIterator first, InputIterator last,
			   typename ft::enable_if< !ft::is_integral< InputIterator >::value, int >::type = 0)
		{
			for (; first != last; ++first) _value.insert(_comparator, *first);
		}

		void erase(iterator position) { _value.del_elem(position.it_const_cast().base()); }

		size_type erase(const value_type &val)
		{
			return (_value.find_and_delete(_comparator, val));
		}

		void erase(iterator first, iterator last)
		{
			iterator tmp;
			while (first != last)
			{
				tmp = first;
				++first;
				_value.del_elem(tmp.it_const_cast().base());
			}
		}

		void swap(set &x)
		{
			std::swap(_comparator, x._comparator);
			std::swap(_allocator, x._allocator);
			ft::swap(_value, x._value);
		}

		void clear() { _value.clear(); }

		/* Observers */
		key_compare key_comp() const { return _comparator; }

		value_compare value_comp() const { return (_comparator); }

		/* Operations */
		iterator find(const value_type &val) const
		{
			ft::pair< const_iterator, int > f = _value.find(_comparator, val);
			if (f.second != -1) return (end());
			return (f.first);
		}

		size_type count(const value_type &val) const
		{
			ft::pair< const_iterator, int > f = _value.find(_comparator, val);
			if (f.second != -1) return (0);
			return (1);
		}

		iterator upper_bound(const value_type &val) const
		{
			return _value.upper_bound(_comparator, val);
		}

		iterator lower_bound(const value_type &val) const
		{
			return _value.lower_bound(_comparator, val);
		}

		pair< iterator, iterator > equal_range(const value_type &val) const
		{
			return _value.equal_range(_comparator, val);
		}


		/* Allocator */
		allocator_type get_allocator() const { return _allocator; }
	};


	template< class T, class Compare, class Alloc >
	bool operator==(const set< T, Compare, Alloc > &lhs, const set< T, Compare, Alloc > &rhs)
	{
		if (lhs.size() != rhs.size()) return (false);

		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}


	template< class T, class Compare, class Alloc >
	bool operator!=(const set< T, Compare, Alloc > &lhs, const set< T, Compare, Alloc > &rhs)
	{
		return (!(lhs == rhs));
	}


	template< class T, class Compare, class Alloc >
	bool operator<(const set< T, Compare, Alloc > &lhs, const set< T, Compare, Alloc > &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}


	template< class T, class Compare, class Alloc >
	bool operator<=(const set< T, Compare, Alloc > &lhs, const set< T, Compare, Alloc > &rhs)
	{
		return (!(rhs < lhs));
	}


	template< class T, class Compare, class Alloc >
	bool operator>(const set< T, Compare, Alloc > &lhs, const set< T, Compare, Alloc > &rhs)
	{
		return (rhs < lhs);
	}


	template< class T, class Compare, class Alloc >
	bool operator>=(const set< T, Compare, Alloc > &lhs, const set< T, Compare, Alloc > &rhs)
	{
		return (!(lhs < rhs));
	}

	template< class T, class Compare, class Alloc >
	void swap(set< T, Compare, Alloc > &x, set< T, Compare, Alloc > &y)
	{
		x.swap(y);
	}
}// namespace ft
#endif//FT_CONTAINERS_SET_HPP
