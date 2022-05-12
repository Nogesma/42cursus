//
// Created by segransm on 5/9/22.
//

#ifndef FT_CONTAINERS_REDBLACKTREE_HPP
#define FT_CONTAINERS_REDBLACKTREE_HPP

#include <cassert>
#include <cstddef>
#include <iostream>
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

		struct tree
		{
			node *root;
		};

	public:
		explicit RedBlackTree(allocator_type alloc) : _allocator(alloc)
		{
			_node_allocator = std::allocator< node >();
			std::allocator< tree > _tree_allocator = std::allocator< tree >();

			_root = _tree_allocator.allocate(1, 0);
			_tree_allocator.construct(_root, tree());
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
			node *elem = _root->root;

			if (elem == NULL)
			{
				_root->root = create_new_elem(v);
				_root->root->colour = BLACK;
				return (*_root->root->val);
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

		void print() { std::cout << traversePreOrder() << std::endl; }

		void clear() { clear_rec(_root->root); }

		void clear_rec(node *N)
		{
			if (N == NULL) return;

			clear_rec(N->left);
			clear_rec(N->right);

			_allocator.destroy(N->val);
			_allocator.deallocate(N->val, 1);
			_node_allocator.destroy(N);
			_node_allocator.deallocate(N, 1);
		}


	private:
		std::string traversePreOrder()
		{

			if (_root->root == NULL) { return ""; }

			std::string sb;
			sb.append(_root->root->val->first);

			std::string pointerRight = "└──";
			std::string pointerLeft = (_root->root->right != NULL) ? "├──" : "└──";

			traverseNodes(sb, "", pointerLeft, _root->root->left, _root->root->right != NULL);
			traverseNodes(sb, "", pointerRight, _root->root->right, false);

			return sb;
		}

		void traverseNodes(std::string &sb, const std::string &padding, const std::string &pointer,
						   node *N, bool hasRightSibling)
		{

#define RESET "\033[0m"
#define R "\033[31m"
			if (N != NULL)
			{
				sb.append("\n");
				sb.append(padding);
				sb.append(pointer);
				if (N->colour == RED)
				{
					sb.append(R);
					sb.append(N->val->first);
					sb.append(RESET);
				}
				else
					sb.append(N->val->first);

				std::string paddingBuilder = std::string(padding);
				if (hasRightSibling) { paddingBuilder.append("│  "); }
				else
				{
					paddingBuilder.append("   ");
				}

				std::string paddingForBoth = paddingBuilder;
				std::string pointerRight = "└──";
				std::string pointerLeft = (N->right != NULL) ? "├──" : "└──";

				traverseNodes(sb, paddingForBoth, pointerLeft, N->left, N->right != NULL);
				traverseNodes(sb, paddingForBoth, pointerRight, N->right, false);
			}
		}

		node *create_new_elem(value_type &v, node *P = NULL)
		{
			value_type *vptr = _allocator.allocate(1, 0);
			_allocator.construct(vptr, v);

			node *new_elem = _node_allocator.allocate(1, 0);
			_node_allocator.construct(new_elem, node(vptr, P));

			++_size;
			return (new_elem);
		}

		node *rotate_tree(node *P, bool dir)
		{
			node *G = P->parent;
			node *S;

			if (dir == LEFT) S = P->right;
			else
				S = P->left;
			node *C;

			assert(S != NULL);// pointer to true node required
			if (dir == LEFT)
			{
				C = S->left;
				P->right = C;
			}
			else
			{
				C = S->right;
				P->left = C;
			}

			if (C != NULL) C->parent = P;
			if (dir == LEFT) { S->left = P; }
			else
			{
				S->right = P;
			}
			P->parent = S;
			S->parent = G;

			if (G != NULL)
			{
				dir = P == G->right ? RIGHT : LEFT;
				if (dir == LEFT) { G->left = S; }
				else
				{
					G->right = S;
				}
			}
			else
				_root->root = S;
			return S;// new root of subtree

			/*
			// todo:
			if (parent == NULL) { parent = _root; }


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

			return tree; */
		}

		direction_t get_child_dir(node *n) { return (n == n->parent->left ? LEFT : RIGHT); }

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
			if (get_child_dir(N) != dir)
			{
				rotate_tree(P, dir);
				N = P;
				if (dir == LEFT) P = G->left;
				else
					P = G->right;
			}

			rotate_tree(G, 1 - dir);
			P->colour = BLACK;
			G->colour = RED;
			return (new_elem);
		}

		tree *_root;
		size_type _size;
		std::allocator< node > _node_allocator;
		allocator_type _allocator;
	};
}// namespace ft

#endif// FT_CONTAINERS_REDBLACKTREE_HPP
