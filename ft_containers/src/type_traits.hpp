//
// Created by segransm on 5/9/22.
//

#ifndef FT_CONTAINERS_TYPE_TRAITS_HPP
#define FT_CONTAINERS_TYPE_TRAITS_HPP

namespace ft
{
	template<bool Cond, typename T = void>
	struct enable_if
	{
	};

	template<class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};
}// namespace ft
#endif//FT_CONTAINERS_TYPE_TRAITS_HPP
