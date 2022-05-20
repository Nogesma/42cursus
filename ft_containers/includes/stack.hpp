//
// Created by segransm on 5/20/22.
//

#ifndef FT_CONTAINERS_STACK_HPP
#define FT_CONTAINERS_STACK_HPP

#include "vector.hpp"

namespace ft
{
	template< class T, class Container = ft::vector< T > >
	class stack
	{
	public:
		typedef T value_type;
		typedef Container container_type;

		typedef std::size_t size_type;

	protected:
		container_type c;

	public:
		explicit stack(const container_type &ctnr = container_type()) : c(ctnr) {}

		bool empty() const { return c.empty(); }

		size_type size() const { return c.size(); }

		value_type &top() { return c.back(); }

		const value_type &top() const { return c.back(); }

		void push(const value_type &val) { c.push_back(val); }

		void pop() { c.pop_back(); }
	};
}// namespace ft
#endif//FT_CONTAINERS_STACK_HPP
