//
// Created by Mano Segransan on 5/10/22.
//

#ifndef FT_CONTAINERS_ITERATOR_HPP
#define FT_CONTAINERS_ITERATOR_HPP

#include "type_traits.hpp"

namespace ft
{
	struct input_iterator_tag
	{};
	struct output_iterator_tag
	{};
	struct forward_iterator_tag : public input_iterator_tag
	{};
	struct bidirectional_iterator_tag : public forward_iterator_tag
	{};
	struct random_access_iterator_tag : public bidirectional_iterator_tag
	{};


	template< class Category, class T, class Distance = ptrdiff_t, class Pointer = T *,
			  class Reference = T & >
	struct iterator
	{
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
		typedef Category iterator_category;
	};

	template< typename Iterator >
	struct iterator_traits
	{
		typedef typename Iterator::iterator_category iterator_category;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
	};

	template< typename Tp >
	struct iterator_traits< Tp * >
	{
		typedef random_access_iterator_tag iterator_category;
		typedef Tp value_type;
		typedef ptrdiff_t difference_type;
		typedef Tp *pointer;
		typedef Tp &reference;
	};

	template< typename Tp >
	struct iterator_traits< const Tp * >
	{
		typedef random_access_iterator_tag iterator_category;
		typedef Tp value_type;
		typedef ptrdiff_t difference_type;
		typedef const Tp *pointer;
		typedef const Tp &reference;
	};

	template< class Iterator >
	class reverse_iterator
		: public iterator< typename iterator_traits< Iterator >::iterator_category,
						   typename iterator_traits< Iterator >::value_type,
						   typename iterator_traits< Iterator >::difference_type,
						   typename iterator_traits< Iterator >::pointer,
						   typename iterator_traits< Iterator >::reference >
	{
	private:
		typedef iterator_traits< Iterator > traits_type;

	public:
		typedef Iterator iterator_type;
		typedef typename traits_type::pointer pointer;
		typedef typename traits_type::difference_type difference_type;
		typedef typename traits_type::reference reference;

	private:
		Iterator _base;

	public:
		reverse_iterator() : _base() {}

		explicit reverse_iterator(iterator_type it) : _base(it){};

		template< class Iter >
		reverse_iterator(const reverse_iterator< Iter > &rev_it);


		iterator_type base() const { return (_base); }

		reference operator*() const
		{
			Iterator tmp = _base;
			return (*tmp);
		}

		reverse_iterator operator+(difference_type n) const
		{
			return (reverse_iterator(_base - n));
		}

		reverse_iterator &operator++()
		{
			--_base;
			return (*this);
		}

		reverse_iterator operator++(int)
		{
			reverse_iterator tmp = *this;
			--_base;
			return tmp;
		}

		reverse_iterator &operator+=(difference_type n)
		{
			_base -= n;
			return (*this);
		}

		reverse_iterator operator-(difference_type n) const
		{
			return (reverse_iterator(_base + n));
		}

		reverse_iterator &operator--()
		{
			++_base;
			return (*this);
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator tmp = *this;
			++_base;
			return (tmp);
		}

		reverse_iterator &operator-=(difference_type n)
		{
			_base += n;
			return (*this);
		}

		pointer operator->() const { return &(operator*()); }

		reference operator[](difference_type n) const { return (*this + n); }
	};

	template< class Iterator >
	bool operator==(const reverse_iterator< Iterator > &lhs,
					const reverse_iterator< Iterator > &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template< class Iterator >
	bool operator!=(const reverse_iterator< Iterator > &lhs,
					const reverse_iterator< Iterator > &rhs)
	{
		return (!(lhs == rhs));
	}

	template< class Iterator >
	bool operator<(const reverse_iterator< Iterator > &lhs, const reverse_iterator< Iterator > &rhs)
	{
		return (rhs.base() < lhs.base());
	}

	template< class Iterator >
	bool operator<=(const reverse_iterator< Iterator > &lhs,
					const reverse_iterator< Iterator > &rhs)
	{
		return !(rhs < lhs);
	}

	template< class Iterator >
	bool operator>(const reverse_iterator< Iterator > &lhs, const reverse_iterator< Iterator > &rhs)
	{
		return (rhs < lhs);
	}

	template< class Iterator >
	bool operator>=(const reverse_iterator< Iterator > &lhs,
					const reverse_iterator< Iterator > &rhs)
	{
		return (!(lhs < rhs));
	}


	template< typename Iterator, typename Container >
	class random_access_iterator
	{
	private:
		typedef iterator_traits< Iterator > traits_type;

	public:
		typedef Iterator iterator_type;
		typedef typename traits_type::pointer pointer;
		typedef typename traits_type::difference_type difference_type;
		typedef typename traits_type::reference reference;
		typedef typename traits_type::iterator_category iterator_category;
		typedef typename traits_type::value_type value_type;

	private:
		Iterator _base;

	public:
		random_access_iterator() : _base() {}

		explicit random_access_iterator(iterator_type it) : _base(it){};

		template< typename Iter, typename Cont >
		random_access_iterator(const random_access_iterator< Iter, Cont > &rev_it)
			: _base(rev_it._base)
		{}

		iterator_type base() const { return (_base); }

		reference operator*() const { return (*_base); }

		random_access_iterator operator+(difference_type n) const
		{
			return (random_access_iterator(_base + n));
		}

		random_access_iterator &operator++()
		{
			++_base;
			return (*this);
		}

		random_access_iterator operator++(int) { return random_access_iterator(_base++); }

		// Random access ite
		random_access_iterator &operator+=(difference_type n)
		{
			_base += n;
			return (*this);
		}

		random_access_iterator operator-(difference_type n) const
		{
			return (random_access_iterator(_base - n));
		}

		difference_type operator-(random_access_iterator n) const { return (_base - n.base()); }

		random_access_iterator &operator--()
		{
			--_base;
			return (*this);
		}

		random_access_iterator operator--(int) { return random_access_iterator(_base--); }

		random_access_iterator &operator-=(difference_type n)
		{
			_base -= n;
			return (*this);
		}

		pointer operator->() const { return _base; }

		reference operator[](difference_type n) const { return (_base[n]); }
	};


	template< typename Iterator, typename Container >
	bool operator==(const random_access_iterator< Iterator, Container > &lhs,
					const random_access_iterator< Iterator, Container > &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template< typename Iterator, typename Container >
	bool operator!=(const random_access_iterator< Iterator, Container > &lhs,
					const random_access_iterator< Iterator, Container > &rhs)
	{
		return (!(lhs == rhs));
	}

	template< typename Iterator, typename Container >
	bool operator<(const random_access_iterator< Iterator, Container > &lhs,
				   const random_access_iterator< Iterator, Container > &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template< typename Iterator, typename Container >
	bool operator<=(const random_access_iterator< Iterator, Container > &lhs,
					const random_access_iterator< Iterator, Container > &rhs)
	{
		return (!(rhs < lhs));
	}

	template< typename Iterator, typename Container >
	bool operator>(const random_access_iterator< Iterator, Container > &lhs,
				   const random_access_iterator< Iterator, Container > &rhs)
	{
		return (rhs < lhs);
	}

	template< typename Iterator, typename Container >
	bool operator>=(const random_access_iterator< Iterator, Container > &lhs,
					const random_access_iterator< Iterator, Container > &rhs)
	{
		return (!(lhs < rhs));
	}
}// namespace ft
#endif//FT_CONTAINERS_ITERATOR_HPP
