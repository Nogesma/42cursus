//
// Created by segransm on 5/9/22.
//

#ifndef FT_CONTAINERS_REDBLACKTREE_HPP
#define FT_CONTAINERS_REDBLACKTREE_HPP

#include <cstddef>
#include <memory>

namespace ft
{

	template< typename T, typename Alloc >
	class RedBlackTree
	{
	public:
		typedef T value_type;

		typedef Alloc allocator_type;
		typedef std::size_t size_type;


		explicit RedBlackTree(allocator_type alloc) : _root(NULL), _allocator(alloc)
		{
			_node_allocator = std::allocator< node >();
		}

		~RedBlackTree()
		{
			//			for (auto i = begin(); i != end(); ++i)
			//			{
			//				_allocator.destroy(i.val);
			//				_allocator.deallocate(i.val, 1);
			//				_node_allocator.destroy(*i);
			//				_node_allocator.deallocate(*i, 1);
			//			}
		}

		void del(value_type &);

		template< typename T1 >
		value_type &insert_no_overwrite(T1 f, value_type &v)
		{
			node *elem = _root;

			if (elem == NULL)
			{
				_root = create_new_elem(v);
				_root->colour = BLACK;
				return (*_root->val);
			}

			while (true)
			{
				if (f(v, *elem->val))
				{
					if (elem->left == NULL) return (*insert_elem(elem, v, LEFT)->val);
					elem = elem->left;
				}
				else if (f(*elem->val, v))
				{
					if (elem->right == NULL) return (*insert_elem(elem, v, RIGHT)->val);
					elem = elem->right;
				}
				else
					return (*elem->val);
			}
		}

		bool empty() const { return (_size == 0); }

		size_type size() const { return (_size); }

		size_type max_size() const { return (_node_allocator.max_size()); }

	private:
		enum color_t
		{
			BLACK,
			RED
		};

		enum direction_t
		{
			LEFT,
			RIGHT
		};
		struct node
		{
			value_type *val;
			node *parent;
			node *left;
			node *right;
			bool colour;

			node(value_type *v, node *P)
			{
				val = v;
				left = NULL;
				right = NULL;
				parent = P;
				colour = RED;
			}
		};

		node *create_new_elem(value_type &v, node *P = NULL)
		{
			value_type *vptr = _allocator.allocate(1, 0);
			_allocator.construct(vptr, v);

			node *new_elem = _node_allocator.allocate(1, 0);
			_node_allocator.construct(new_elem, node(vptr, P));

			++_size;
			return (new_elem);
		}

		node *rotate_tree(node *tree, bool dir)
		{
			node *parent = tree->parent;

			// todo:
			if (parent == NULL) { return (tree); }

			if (dir == LEFT)
			{
				if (get_child_dir(tree) == LEFT) parent->left = tree->right;
				else
					parent->right = tree->right;

				node *r = tree->right;

				tree->right = r->left;
				r->left = tree;
			}
			else
			{
				if (get_child_dir(tree) == LEFT) parent->left = tree->left;
				else
					parent->right = tree->left;

				node *l = tree->left;

				tree->left = l->right;
				l->right = tree;
			}

			return tree;
		}

		direction_t get_child_dir(node *n) { return (n == n->parent->right ? LEFT : RIGHT); }

		node *insert_elem(node *P, value_type &v, bool dir)
		{
			node *new_elem = create_new_elem(v, P);

			node *N = new_elem;
			node *G;
			node *U;
			if (dir == LEFT) P->left = new_elem;
			else
				P->right = new_elem;

			do {
				if (P->colour == BLACK) return (new_elem);

				G = P->parent;

				if (G == NULL) goto case0;

				dir = get_child_dir(P);

				if (dir == LEFT) U = G->right;
				else
					U = G->left;
				if (U == NULL || U->colour == BLACK) goto case1;

				P->colour = BLACK;
				U->colour = BLACK;
				G->colour = RED;
				N = G;
			} while ((P = N->parent) != NULL);

			return (new_elem);

		case0:
			P->colour = BLACK;
			return (new_elem);

		case1:
			if ((dir == LEFT && N == P->left) || (dir == RIGHT && N == P->right))
			{
				rotate_tree(P, dir);
				N = P;
				if (dir == LEFT) P = G->left;
				else
					P = G->right;
			}

			// Case_I6 (P red && U black && N outer grandchild of G):
			rotate_tree(G, 1 - dir);// G may be the root
			P->colour = BLACK;
			G->colour = RED;
			return (new_elem);
		}
		node *_root;
		size_type _size;
		std::allocator< node > _node_allocator;
		allocator_type _allocator;
	};
}// namespace ft

#endif// FT_CONTAINERS_REDBLACKTREE_HPP
