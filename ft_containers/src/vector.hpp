//
// Created by Mano Segransan on 5/5/22.
//

#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

#include "iterator.hpp"
#include "type_traits.hpp"
#include <cstddef>
#include <memory>
#include <stdexcept>

#include <iostream>
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
			std::cout << "it: " << n << '\n';
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
			// todo: test
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
			// todo: test
			if (n > max_size()) throw std::length_error("vector::reserve");

			size_type old_capacity = _capacity;
			_capacity = n;

			if (n > old_capacity)
			{
				value_type *tmp = _value;

				_value = _allocator.allocate(n, _value);
				for (size_type i = 0; i < _size; ++i)
				{
					_allocator.construct(_value + i, tmp[i]);
					_allocator.destroy(tmp + i);
				}
				_allocator.deallocate(tmp, _capacity);
			}
		}

		/* Element access */

		reference operator[](size_type n) { return (_value[n]); }

		const_reference operator[](size_type n) const { return (_value[n]); }

		reference at(size_type n)
		{
			if (n < 0 || n >= _size) throw std::out_of_range("out of range");// todo: add real error
			return (_value[n]);
		}

		const_reference at(size_type n) const
		{
			if (n < 0 || n >= _size) throw std::out_of_range("out of range");// todo: add real error
			return (_value[n]);
		}

		reference front() { return (_value[0]); }

		const_reference front() const { return (_value[0]); }

		reference back() { return (_value[_size - 1]); }

		const_reference back() const { return (_value[_size - 1]); }

		// todo: constructor, destructors, operator =, modifiers, allocator, non-member function overload
		/* Modifiers */
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

		// todo: assign

		void pop_back() { _allocator.destroy(_value + --_size); }

		// todo: erase
		// todo: insert

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

		for (typename vector< T, Alloc >::size_type i = 0; i < lhs.size(); ++i)
			if (lhs[i] != rhs[i]) return (false);
		return (true);
	}

	template< typename T, typename Alloc >
	bool operator!=(const vector< T, Alloc > &lhs, const vector< T, Alloc > &rhs)
	{
		return (!(lhs == rhs));
	}

	template< typename T, typename Alloc >
	bool operator<(const vector< T, Alloc > &lhs, const vector< T, Alloc > &rhs)
	{
		// todo with iterators
		return (true);
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
}// namespace ft


#endif//FT_CONTAINERS_VECTOR_HPP
