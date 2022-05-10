//
// Created by segransm on 5/9/22.
//

#ifndef FT_CONTAINERS_REDBLACKTREE_HPP
#define FT_CONTAINERS_REDBLACKTREE_HPP

#include <cstddef>
#include <memory>

namespace ft
{

	template< typename T, typename Compare >
	class RedBlackTree
	{
	public:
		typedef Compare compare;
		typedef T value_type;

		explicit RedBlackTree(compare comp);

		void insert(T &);

		void del(T &);

		T &find(T &);

	private:
		struct node
		{
			T val;
			node *left;
			node *right;
			bool colour;

			explicit node(T &v)
			{
				val = v;
				left = NULL;
				right = NULL;
				colour = false;
			}
		};

		node *_root;
		compare _comparator;
		std::allocator< node > _allocator;
	};

	template< typename T, typename Compare >
	RedBlackTree< T, Compare >::RedBlackTree(compare comp) : _root(NULL), _comparator(comp)
	{
		_allocator = std::allocator< node >();
	}

	template< typename T, typename Compare >
	T &RedBlackTree< T, Compare >::find(T &v)
	{
		node *elem = _root;

		while (elem != NULL)
		{
			if (_comparator(v, elem->val)) elem = elem->left;
			else if (_comparator(elem->val, v))
				elem = elem->right;
			else
				return (elem->val);
		}
		return (NULL);
	}

	template< typename T, typename Compare >
	void RedBlackTree< T, Compare >::insert(T &v)
	{
		node *elem = _root;
		node *new_elem = _allocator.allocate(1, 0);
		_allocator.construct(new_elem, v);

		if (elem == NULL)
		{
			elem = new_elem;
			return;
		}
	}
}// namespace ft

#endif// FT_CONTAINERS_REDBLACKTREE_HPP
