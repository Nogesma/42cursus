//
// Created by segransm on 5/9/22.
//

#ifndef FT_CONTAINERS_REDBLACKTREE_HPP
#define FT_CONTAINERS_REDBLACKTREE_HPP

#include <memory>

namespace ft
{

	template<typename T, typename Compare, typename Alloc>
	class RedBlackTree
	{

		typedef Compare compare;
		typedef Alloc allocator_type;

		RedBlackTree(const compare &comp, const allocator_type &alloc);

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

			node(T &v, allocator_type &alloc)
			{
				val = alloc.allocate(1, 0);
				alloc.construct(val, v);
				left = NULL;
				right = NULL;
				colour = false;
			}
		};

		node *_root;
		compare _comparator;
		allocator_type _allocator;
	};

	template<typename T, typename Compare, typename Alloc>
	RedBlackTree<T, Compare, Alloc>::RedBlackTree(const compare &comp,
												  const allocator_type &alloc)
		: _root(NULL), _comparator(comp), _allocator(alloc)
	{}

	template<typename T, typename Compare, typename Alloc>
	T &RedBlackTree<T, Compare, Alloc>::find(T &v)
	{
		node *elem = _root;
		int r;

		while (elem != NULL)
		{
			if (_comparator(v, elem->val))
				elem = elem->left;
			else if (_comparator(elem->val, v))
				elem = elem->right;
			else
				return (elem->val);
		}
		return (NULL);
	}

	template<typename T, typename Compare, typename Alloc>
	void RedBlackTree<T, Compare, Alloc>::insert(T &v)
	{
		node *elem = _root;
		node *new_elem = node(v, _allocator);

		if (elem == NULL)
		{
			elem = new_elem;
			return;
		}
	}
}// namespace ft

#endif// FT_CONTAINERS_REDBLACKTREE_HPP
