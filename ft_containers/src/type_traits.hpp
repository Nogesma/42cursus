//
// Created by segransm on 5/9/22.
//

#ifndef FT_CONTAINERS_TYPE_TRAITS_HPP
#define FT_CONTAINERS_TYPE_TRAITS_HPP

#include <cstddef>

namespace ft
{
	template< bool Cond, typename T = void >
	struct enable_if
	{};

	template< class T >
	struct enable_if< true, T >
	{
		typedef T type;
	};

	template< class T, T v >
	struct integral_constant
	{
		static const T value = v;
		typedef T value_type;
		typedef integral_constant< T, v > type;
		operator T() { return v; }
	};


	typedef integral_constant< bool, true > true_type;
	typedef integral_constant< bool, false > false_type;


	template< typename >
	struct is_integral_helper : public ft::false_type
	{};

	template<>
	struct is_integral_helper< bool > : public ft::true_type
	{};

	template<>
	struct is_integral_helper< char > : public ft::true_type
	{};

	template<>
	struct is_integral_helper< wchar_t > : public ft::true_type
	{};

	template<>
	struct is_integral_helper< signed char > : public ft::true_type
	{};

	template<>
	struct is_integral_helper< short int > : public ft::true_type
	{};

	template<>
	struct is_integral_helper< int > : public ft::true_type
	{};

	template<>
	struct is_integral_helper< long int > : public ft::true_type
	{};

	template<>
	struct is_integral_helper< unsigned char > : public ft::true_type
	{};

	template<>
	struct is_integral_helper< unsigned short int > : public ft::true_type
	{};

	template<>
	struct is_integral_helper< unsigned int > : public ft::true_type
	{};

	template<>
	struct is_integral_helper< unsigned long int > : public ft::true_type
	{};

	template< class T >
	struct is_integral : public ft::is_integral_helper< T >
	{};

	template< typename T, typename = void >
	struct is_iterator
	{
		static const bool value = false;
	};

	template< class From, class To >
	struct is_convertible : public ft::false_type
	{};

}// namespace ft

#endif//FT_CONTAINERS_TYPE_TRAITS_HPP
