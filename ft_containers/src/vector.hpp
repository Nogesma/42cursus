//
// Created by Mano Segransan on 5/5/22.
//

#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

#include "algorithm.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"
#include <cstddef>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>

namespace ft
{
	template< typename T, typename Alloc = std::allocator< T > >
	class vector
	{
	public:
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;

		typedef typename ft::random_access_iterator< pointer, vector > iterator;
		typedef typename ft::random_access_iterator< const_pointer, vector > const_iterator;
		typedef typename ft::reverse_iterator< iterator > reverse_iterator;
		typedef typename ft::reverse_iterator< const_iterator > const_reverse_iterator;

		typedef typename ft::iterator_traits< iterator >::difference_type difference_type;
		typedef std::size_t size_type;

		/* Constructors */
		explicit vector(const allocator_type &alloc = allocator_type())
			: _capacity(0), _size(0), _allocator(alloc)
		{
			_value = _allocator.allocate(0, 0);
		}

		explicit vector(size_type n, const value_type &val = value_type(),
						const allocator_type &alloc = allocator_type())
			: _capacity(n), _size(n), _allocator(alloc)
		{
			if (n > max_size())
				throw std::length_error("cannot create ft::vector larger than max_size()");

			_value = _allocator.allocate(_capacity, 0);
			for (size_type i = 0; i < _size; ++i) _allocator.construct(_value + i, val);
		}

		template< typename InputIterator >
		vector(InputIterator first, InputIterator last,
			   const allocator_type &alloc = allocator_type(),
			   typename ft::enable_if< !ft::is_integral< InputIterator >::value, int >::type = 0)
			: _allocator(alloc)
		{
			const size_type n = last - first;

			if (n > max_size())
				throw std::length_error("cannot create ft::vector larger than max_size()");
			_capacity = n;
			_size = n;
			_value = _allocator.allocate(_capacity, 0);

			for (size_type i = 0; i < _size; ++i) _allocator.construct(_value + i, *(first + i));
		}

		vector(const vector &x) : _capacity(x._capacity), _size(x._size), _allocator(x._allocator)
		{
			_value = _allocator.allocate(_capacity, 0);
			for (size_type i = 0; i < _size; ++i) _allocator.construct(_value + i, x[i]);
		}

		~vector()
		{
			clear();
			_allocator.deallocate(_value, _capacity);
		}

		vector &operator=(const vector &x)
		{
			if (this == &x) { return *this; }

			_value = _allocator.allocate(_capacity, 0);
			for (size_type i = 0; i < _size; ++i) _allocator.construct(_value + i, x[i]);

			return (*this);
		}


		/* Iterators */
		iterator begin() { return (iterator(&_value[0])); }

		const_iterator begin() const { return (const_iterator(&_value[0])); }

		iterator end() { return (iterator(&_value[_size])); }

		const_iterator end() const { return (const_iterator(&_value[_size])); }

		reverse_iterator rbegin() { return (reverse_iterator(&_value[_size - 1])); }

		const_reverse_iterator rbegin() const { return (reverse_iterator(&_value[_size - 1])); }

		reverse_iterator rend() { return (reverse_iterator(&_value[-1])); }

		const_reverse_iterator rend() const { return (reverse_iterator(&_value[-1])); }
		/* Capacity */
		size_type size() const { return _size; }

		size_type max_size() const { return _allocator.max_size(); }

		void resize(size_type n, value_type val = value_type())
		{
			if (n > max_size()) throw std::length_error("vector::resize");

			size_type old_size = _size;
			size_type old_capacity = _capacity;

			_capacity = n;
			_size = n;
			if (n < old_size)
			{

				for (size_type i = n; i < old_size; ++i) _allocator.destroy(_value + i);
				value_type *tmp = _value;
				_value = _allocator.allocate(n, _value);

				for (size_type i = 0; i < n; ++i)
				{
					_allocator.construct(_value + i, tmp[i]);
					_allocator.destroy(tmp + i);
				}

				_allocator.deallocate(tmp, old_capacity);
			}
			else if (n > old_capacity)
			{
				value_type *tmp = _value;

				_value = _allocator.allocate(n, _value);
				for (size_type i = 0; i < old_size; ++i)
				{
					_allocator.construct(_value + i, tmp[i]);
					_allocator.destroy(tmp + i);
				}
				for (size_type i = old_size; i < n; ++i) _allocator.construct(_value + i, val);

				_allocator.deallocate(tmp, old_capacity);
			}
			else if (n > old_size)
			{
				for (size_type i = old_size; i < n; ++i)
					_allocator.construct(_value + old_size, val);
			}
		}

		size_type capacity() const { return _capacity; }

		bool empty() const { return _size == 0; }

		void reserve(size_type n)
		{
			if (n > max_size()) throw std::length_error("vector::reserve");

			if (n > _capacity)
			{
				value_type *tmp = _value;

				_value = _allocator.allocate(n, _value);
				for (size_type i = 0; i < _size; ++i)
				{
					_allocator.construct(_value + i, tmp[i]);
					_allocator.destroy(tmp + i);
				}
				_allocator.deallocate(tmp, _capacity);
				_capacity = n;
			}
		}

		/* Element access */

		reference operator[](size_type n) { return (_value[n]); }

		const_reference operator[](size_type n) const { return (_value[n]); }

		reference at(size_type n)
		{
			if (n >= _size)
			{
				std::ostringstream s;

				s << "vector::at: n (which is " << n << ") >= this->size() (which is " << _size
				  << ')';

				throw std::out_of_range(s.str());
			}
			return (_value[n]);
		}

		const_reference at(size_type n) const
		{
			if (n >= _size)
			{
				std::ostringstream s;

				s << "vector::at: n (which is " << n << ") >= this->size() (which is " << _size
				  << ')';

				throw std::out_of_range(s.str());
			}

			return (_value[n]);
		}

		reference front() { return (_value[0]); }

		const_reference front() const { return (_value[0]); }

		reference back() { return (_value[_size - 1]); }

		const_reference back() const { return (_value[_size - 1]); }

		/* Modifiers */

		template< class InputIterator >
		void assign(InputIterator first, InputIterator last)
		{

			const size_type n = last - first;

			if (n > max_size()) throw std::length_error("vector::assign");

			if (n < _capacity)
			{
				if (n < _size)
				{
					for (size_type i = 0; i < n; ++i, ++first)
					{
						_allocator.destroy(_value + i);
						_allocator.construct(_value + i, *first);
						++first;
					}
					for (size_type i = n; i < _size; ++i) _allocator.destroy(_value + i);
				}
				else
				{
					for (size_type i = 0; i < _size; ++i, ++first)
					{
						_allocator.destroy(_value + i);
						_allocator.construct(_value + i, *first);
					}
					for (size_type i = _size; i < n; ++i, ++first)
						_allocator.construct(_value + i, *first);
				}
			}
			else
			{
				value_type *tmp = _value;

				_value = _allocator.allocate(n, _value);
				for (size_type i = 0; i < _size; ++i, ++first)
				{
					_allocator.construct(_value + i, *first);
					_allocator.destroy(tmp + i);
				}
				for (size_type i = _size; i < n; ++i, ++first)
					_allocator.construct(_value + i, *first);
				_allocator.deallocate(tmp, _capacity);
				_capacity = n;
			}
			_size = n;
		}

		void assign(size_type n, const value_type &val)
		{
			if (n > max_size()) throw std::length_error("vector::assign");

			if (n < _capacity)
			{
				if (n < _size)
				{
					for (size_type i = 0; i < n; ++i)
					{
						_allocator.destroy(_value + i);
						_allocator.construct(_value + i, val);
					}
					for (size_type i = n; i < _size; ++i) _allocator.destroy(_value + i);
				}
				else
				{
					for (size_type i = 0; i < _size; ++i)
					{
						_allocator.destroy(_value + i);
						_allocator.construct(_value + i, val);
					}
					for (size_type i = _size; i < n; ++i) _allocator.construct(_value + i, val);
				}
			}
			else
			{
				value_type *tmp = _value;

				_value = _allocator.allocate(n, _value);
				for (size_type i = 0; i < _size; ++i)
				{
					_allocator.construct(_value + i, val);
					_allocator.destroy(tmp + i);
				}
				for (size_type i = _size; i < n; ++i) _allocator.construct(_value + i, val);
				_allocator.deallocate(tmp, _capacity);
				_capacity = n;
			}
			_size = n;
		}

		void push_back(const value_type &val)
		{
			if (_size == _capacity)
			{
				if (_size == 0) reserve(1);
				else
					reserve(_size * 2);
			}
			_allocator.construct(_value + _size++, val);
		}

		void pop_back() { _allocator.destroy(_value + --_size); }

		iterator insert(iterator position, const value_type &val)
		{
			if (empty())
			{
				push_back(val);
				return (begin());
			}

			size_type idx = position - begin();
			value_type b = back();

			push_back(b);

			for (size_type i = _size - 2; i > idx; i--) _value[i] = _value[i - 1];

			_value[idx] = val;
			return (begin() + idx);
		}

		void insert(iterator position, size_type n, const value_type &val)
		{
			size_type idx = position - begin();

			if (_size + n > _capacity) reserve(_size + n);

			size_type i;
			for (i = 0; i < n; ++i, ++_size)
			{
				if (n <= _size && _size - n >= idx)
					_allocator.construct(_value + _size, _value[_size - n]);
				else
					_allocator.construct(_value + _size, val);
			}

			for (i = _size - n; i >= idx + n; i--) _value[i] = _value[i - n];
			for (i = 0; i < _size - n; i++) _value[idx + i] = val;
		}

		template< class InputIterator >
		void
		insert(iterator position, InputIterator first, InputIterator last,
			   typename ft::enable_if< !ft::is_integral< InputIterator >::value, int >::type = 0)
		{
			size_type idx = position - begin();
			size_type n = last - first;

			if (_size + n > _capacity) reserve(_size + n);

			size_type i;
			for (i = 0; i < n; ++i, ++_size)
			{
				if (n <= _size && _size - n >= idx)
					_allocator.construct(_value + _size, _value[_size - n]);
				else
					_allocator.construct(_value + _size, *(first + i));
			}

			for (i = _size - n; i >= idx + n; i--) _value[i] = _value[i - n];
			for (i = 0; i < _size - n; i++) _value[idx + i] = *(first + i);
		}

		iterator erase(iterator position)
		{
			size_type idx = position - begin();

			for (size_type i = idx; i < _size - 1; i++) _value[i] = _value[i + 1];

			pop_back();

			return (position);
		}
		iterator erase(iterator first, iterator last)
		{
			size_type idx = first - begin();
			size_type n = last - first;

			for (size_type i = idx; i < _size - n; i++) _value[i] = _value[i + n];

			for (size_type i = 0; i < n; ++i) pop_back();

			return (first);
		}

		void swap(vector &x)
		{
			size_type tmp_capacity;
			size_type tmp_size;
			value_type *tmp_value;

			tmp_capacity = _capacity;
			tmp_size = _size;
			tmp_value = _value;

			_capacity = x._capacity;
			_size = x._size;
			_value = x._value;

			x._capacity = tmp_capacity;
			x._size = tmp_size;
			x._value = tmp_value;
		}

		void clear()
		{
			for (; _size > 0; _size--) _allocator.destroy(_value + _size - 1);
		}

		/* Allocator */
		allocator_type get_allocator() const { return _allocator; }

	private:
		size_type _capacity;
		size_type _size;
		value_type *_value;
		allocator_type _allocator;
	};

	/* Relationnal operators */
	template< typename T, typename Alloc >
	bool operator==(const vector< T, Alloc > &lhs, const vector< T, Alloc > &rhs)
	{
		if (lhs.size() != rhs.size()) return (false);

		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template< typename T, typename Alloc >
	bool operator!=(const vector< T, Alloc > &lhs, const vector< T, Alloc > &rhs)
	{
		return (!(lhs == rhs));
	}

	template< typename T, typename Alloc >
	bool operator<(const vector< T, Alloc > &lhs, const vector< T, Alloc > &rhs)
	{
		typename vector< T, Alloc >::iterator lit = lhs.begin();
		typename vector< T, Alloc >::iterator rit = rhs.begin();

		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template< typename T, typename Alloc >
	bool operator<=(const vector< T, Alloc > &lhs, const vector< T, Alloc > &rhs)
	{
		return (!(rhs < lhs));
	}

	template< typename T, typename Alloc >
	bool operator>(const vector< T, Alloc > &lhs, const vector< T, Alloc > &rhs)
	{
		return (rhs < lhs);
	}

	template< typename T, typename Alloc >
	bool operator>=(const vector< T, Alloc > &lhs, const vector< T, Alloc > &rhs)
	{
		return (!(lhs < rhs));
	}

	template< class T, class Alloc >
	void swap(vector< T, Alloc > &x, vector< T, Alloc > &y)
	{
		x.swap(y);
	}
}// namespace ft


#endif//FT_CONTAINERS_VECTOR_HPP
