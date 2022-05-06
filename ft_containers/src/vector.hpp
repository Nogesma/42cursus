//
// Created by Mano Segransan on 5/5/22.
//

#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

#include <memory>
#include <cstdlib>
#include <stdexcept>

namespace ft
{
  template<typename T, typename Alloc = std::allocator <T> >
  class vector
  {
  public:
	typedef T value_type;
	typedef Alloc allocator_type;
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;

	// todo: iterator typedef
//	typedef typename iterator_traits<iterator>::difference_type difference_type;
	typedef std::size_t size_type;


  public:
	/* Constructors */
	explicit vector(const allocator_type &alloc = allocator_type());

	explicit vector(size_type n, const value_type &val = value_type(),
					const allocator_type &alloc = allocator_type());

//	template<class InputIterator>
//	vector(InputIterator first, InputIterator last,
//		   const allocator_type &alloc = allocator_type());

	vector(const vector &x);

	~vector();

	vector &operator=(const vector &x);


	/* Capacity */
	size_type size() const;

	size_type max_size() const;

	void resize(size_type n, value_type val = value_type());

	size_type capacity() const;

	bool empty() const;

	void reserve(size_type n);

	/* Element access */

	reference operator[](size_type n);

	const_reference operator[](size_type n) const;

	reference at(size_type n);

	const_reference at(size_type n) const;

	reference front();

	const_reference front() const;

	reference back();

	const_reference back() const;

	/* Modifiers */
	void push_back(const value_type &val);

	// todo: assign

	void pop_back();

	// todo: erase
	// todo: insert

	void swap(vector &x);

	void clear();

	/* Allocator */
	allocator_type get_allocator() const;

	/* Relational operators
	bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);

	bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);

	bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);

	bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);

	bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);

	bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);
*/
  private:
	size_type _capacity;
	size_type _size;
	value_type *_value;
	allocator_type _allocator;
  };


  /* Constructors */
  template<typename T, typename Alloc>
  vector<T, Alloc>::vector(const allocator_type &alloc): _capacity(0), _size(0),
														 _allocator(alloc)
  {
	  _value = _allocator.allocate(0, 0);
  }

  template<typename T, typename Alloc>
  vector<T, Alloc>::vector(size_type n, const value_type &val,
						   const allocator_type &alloc): _capacity(n), _size(n),
														 _allocator(alloc)
  {
	  if (n > max_size())
		  throw std::length_error(
			  "cannot create ft::vector larger than max_size()");

	  _value = _allocator.allocate(_capacity, 0);
	  for (size_type i = 0; i < _size; ++i)
		  _allocator.construct(_value + i, val);
  }

//  template<typename T, typename Alloc>
//  template<class InputIterator>
//  vector<T, Alloc>::vector(InputIterator first, InputIterator last,
//						   const allocator_type &alloc)
//  {}

  template<typename T, typename Alloc>
  vector<T, Alloc>::vector(const vector &x): _capacity(x._capacity),
											 _size(x._size),
											 _allocator(x._allocator)
  {
	  _value = _allocator.allocate(_capacity, 0);
	  for (size_type i = 0; i < _size; ++i)
		  _allocator.construct(_value + i, x[i]);
  }

  template<typename T, typename Alloc>
  vector<T, Alloc>::~vector()
  {
	  clear();
	  _allocator.deallocate(_value, _capacity);
  }

  template<typename T, typename Alloc>
  vector<T, Alloc> &vector<T, Alloc>::operator=(const vector &x)
  {
	  _value = _allocator.allocate(_capacity, 0);
	  for (size_type i = 0; i < _size; ++i)
		  _allocator.construct(_value + i, x[i]);

	  return (*this);
  }


  /* Capacity */
  template<typename T, typename Alloc>
  typename vector<T, Alloc>::size_type vector<T, Alloc>::size() const
  {
	  return (_size);
  }

  template<typename T, typename Alloc>
  typename vector<T, Alloc>::size_type vector<T, Alloc>::max_size() const
  {
	  return (_allocator.max_size());
  }

  template<typename T, typename Alloc>
  void vector<T, Alloc>::resize(size_type n,
								value_type val) // todo: optimise allocate
  {
	  if (n < _size)
	  {
		  value_type *tmp = _value;

		  _value = _allocator.allocate(n, 0);
		  for (size_type i = 0; i < n; ++i)
		  {
			  _allocator.construct(_value + i, tmp[i]);
			  _allocator.destroy(tmp + i);
		  }
		  for (size_type i = n; i < _size; ++i)
			  _allocator.destroy(tmp + i);

		  _allocator.deallocate(tmp, _capacity);

		  _capacity = n;
		  _size = n;
	  } else if (n > _capacity)
	  {
		  value_type *tmp = _value;

		  _value = _allocator.allocate(n, 0);
		  for (size_type i = 0; i < _size; ++i)
		  {
			  _allocator.construct(_value + i, tmp[i]);
			  _allocator.destroy(tmp + i);
		  }
		  for (size_type i = _size; i < n; ++i)
			  _allocator.construct(_value + i, val);

		  _allocator.deallocate(tmp, _capacity);

		  _capacity = n;
		  _size = n;
	  } else if (n > _size)
	  {
		  for (; _size < n; _size++)
			  _allocator.construct(_value + _size, val);
	  }
  }

  template<typename T, typename Alloc>
  typename vector<T, Alloc>::size_type vector<T, Alloc>::capacity() const
  {
	  return (_capacity);
  }

  template<typename T, typename Alloc>
  bool vector<T, Alloc>::empty() const
  {
	  return (_size == 0);
  }

  template<typename T, typename Alloc>
  void vector<T, Alloc>::reserve(size_type n)
  {
	  if (n > max_size())
		  throw std::length_error(
			  "vector::reserve");

	  if (n > _capacity)
	  {
		  value_type *tmp = _value;

		  _value = _allocator.allocate(n, 0);
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
  template<typename T, typename Alloc>
  typename vector<T, Alloc>::reference vector<T, Alloc>::operator[](size_type n)
  {
	  return (_value[n]);
  }

  template<typename T, typename Alloc>
  typename vector<T, Alloc>::const_reference
  vector<T, Alloc>::operator[](size_type n) const
  {
	  return (_value[n]);
  }

  template<typename T, typename Alloc>
  typename vector<T, Alloc>::reference vector<T, Alloc>::at(size_type n)
  {
	  if (n < 0 || n > _size)
		  throw std::out_of_range();
	  return (_value[n]);
  }

  template<typename T, typename Alloc>
  typename vector<T, Alloc>::const_reference
  vector<T, Alloc>::at(size_type n) const
  {
	  if (n < 0 || n > _size)
		  throw std::out_of_range();
	  return (_value[n]);
  }

  template<typename T, typename Alloc>
  typename vector<T, Alloc>::reference vector<T, Alloc>::front()
  {
	  return (_value[0]);
  }

  template<typename T, typename Alloc>
  typename vector<T, Alloc>::const_reference
  vector<T, Alloc>::front() const
  {
	  return (_value[0]);
  }

  template<typename T, typename Alloc>
  typename vector<T, Alloc>::reference vector<T, Alloc>::back()
  {
	  return (_value[_size - 1]);
  }

  template<typename T, typename Alloc>
  typename vector<T, Alloc>::const_reference
  vector<T, Alloc>::back() const
  {
	  return (_value[_size - 1]);
  }


  /* Modifiers */
  template<typename T, typename Alloc>
  void vector<T, Alloc>::push_back(const value_type &val)
  {
	  if (_size == _capacity)
	  {
		  if (_size == 0)
			  reserve(1);
		  else
			  reserve(_size * 2);
	  }
	  _allocator.construct(_value + _size++, val);
  }


  template<typename T, typename Alloc>
  void vector<T, Alloc>::pop_back()
  {
	  _allocator.destroy(_value + --_size);
  }

  template<typename T, typename Alloc>
  void vector<T, Alloc>::swap(vector &x)
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

  template<typename T, typename Alloc>
  void vector<T, Alloc>::clear()
  {
	  for (; _size > 0; _size--)
		  _allocator.destroy(_value + _size - 1);
  }

  /* Allocators */
  template<typename T, typename Alloc>
  typename vector<T, Alloc>::allocator_type
  vector<T, Alloc>::get_allocator() const
  {
	  return (_allocator);
  }

  /* Relationnal operators */
  template<class T, class Alloc>
  bool operator==(const vector<T, Alloc> &lhs,
				  const vector<T, Alloc> &rhs)
  {
	  if (lhs.size() != rhs.size())
		  return (false);

	  for (typename vector<T, Alloc>::size_type i = 0; i < lhs.size(); ++i)
		  if (lhs[i] != rhs[i]) return (false);
	  return (true);
  }

  template<class T, class Alloc>
  bool operator!=(const vector<T, Alloc> &lhs,
				  const vector<T, Alloc> &rhs)
  {
	  return (!(lhs == rhs));
  }

  template<class T, class Alloc>
  bool operator<(const vector<T, Alloc> &lhs,
				 const vector<T, Alloc> &rhs)
  {

  }

  template<class T, class Alloc>
  bool operator<=(const vector<T, Alloc> &lhs,
				  const vector<T, Alloc> &rhs);

  template<class T, class Alloc>
  bool operator>(const vector<T, Alloc> &lhs,
				 const vector<T, Alloc> &rhs);


  template<class T, class Alloc>
  bool operator>=(const vector<T, Alloc> &lhs,
				  const vector<T, Alloc> &rhs);

}


#endif //FT_CONTAINERS_VECTOR_HPP
