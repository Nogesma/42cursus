//
// Created by segransm on 5/9/22.
//

#ifndef FT_CONTAINERS_UTILITY_HPP
#define FT_CONTAINERS_UTILITY_HPP

namespace ft
{
	/* pair */
	template< typename T1, typename T2 >
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		T1 first;
		T2 second;

		pair() : first(), second() {}

		pair(const first_type &a, const second_type &b) : first(a), second(b) {}

		template< typename U1, typename U2 >
		explicit pair(const pair< U1, U2 > &p) : first(p.first), second(p.second)
		{}

		//		pair &operator=(const pair &pr)
		//		{
		//			first = pr.first;
		//			second = pr.second;
		//
		//			return (*this);
		//		}
	};

	template< class T1, class T2 >
	bool operator==(const pair< T1, T2 > &lhs, const pair< T1, T2 > &rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template< class T1, class T2 >
	bool operator!=(const pair< T1, T2 > &lhs, const pair< T1, T2 > &rhs)
	{
		return (!(lhs == rhs));
	}

	template< class T1, class T2 >
	bool operator<(const pair< T1, T2 > &lhs, const pair< T1, T2 > &rhs)
	{
		return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
	}

	template< class T1, class T2 >
	bool operator<=(const pair< T1, T2 > &lhs, const pair< T1, T2 > &rhs)
	{
		return (!(rhs < lhs));
	}

	template< class T1, class T2 >
	bool operator>(const pair< T1, T2 > &lhs, const pair< T1, T2 > &rhs)
	{
		return (rhs < lhs);
	}

	template< class T1, class T2 >
	bool operator>=(const pair< T1, T2 > &lhs, const pair< T1, T2 > &rhs)
	{
		return (!(lhs < rhs));
	}

	/* make-pair */
	template< class T1, class T2 >
	pair< T1, T2 > make_pair(T1 x, T2 y)
	{
		return (pair< T1, T2 >(x, y));
	}
}// namespace ft

#endif// FT_CONTAINERS_UTILITY_HPP
