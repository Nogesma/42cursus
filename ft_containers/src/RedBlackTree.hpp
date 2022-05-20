//
// Created by segransm on 5/9/22.
//

#ifndef FT_CONTAINERS_REDBLACKTREE_HPP
#define FT_CONTAINERS_REDBLACKTREE_HPP

#include "iterator.hpp"
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

		typedef std::size_t size_type;

		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;

		typedef typename ft::random_access_iterator< pointer, RedBlackTree > iterator;
		typedef typename ft::random_access_iterator< const_pointer, RedBlackTree > const_iterator;
		typedef typename ft::reverse_iterator< iterator > reverse_iterator;
		typedef typename ft::reverse_iterator< const_iterator > const_reverse_iterator;

		typedef ft::iterator_traits< iterator > difference_type;

	private:
		enum color_t
		{
			RED,
			BLACK
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
			char colour;

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

		tree *_root;
		size_type _size;
		std::allocator< node > _node_allocator;
		allocator_type _allocator;
		value_type *_begin;
		value_type *_end;

	public:
		/* Constructors */
		explicit RedBlackTree(allocator_type alloc)
			: _size(0), _allocator(alloc), _begin(NULL), _end(NULL)
		{
			_node_allocator = std::allocator< node >();
			std::allocator< tree > _tree_allocator = std::allocator< tree >();

			_root = _tree_allocator.allocate(1, 0);
			_tree_allocator.construct(_root, tree());
		}

		~RedBlackTree()
		{
			std::allocator< tree > _tree_allocator = std::allocator< tree >();

			clear();

			_tree_allocator.destroy(_root);
			_tree_allocator.deallocate(_root, 1);
		}
		/* Iterators */
		iterator begin() { return (iterator(_begin)); }

		const_iterator begin() const { return (const_iterator(_begin)); }

		iterator end() { return (iterator(NULL)); }

		const_iterator end() const { return (const_iterator(NULL)); }

		reverse_iterator rbegin() { return (reverse_iterator(_end)); }

		const_reverse_iterator rbegin() const { return (reverse_iterator(_end)); }

		reverse_iterator rend() { return (reverse_iterator(NULL)); }

		const_reverse_iterator rend() const { return (reverse_iterator(NULL)); }

		template< typename T1 >
		size_type find_and_delete(T1 f, value_type &v)
		{
			node *elem = _root->root;

			if (elem == NULL) return (0);

			while (true)
			{
				if (f(v, *elem->val))
				{
					if (elem->left == NULL) return (0);
					elem = elem->left;
				}
				else if (f(*elem->val, v))
				{
					if (elem->right == NULL) return (0);
					elem = elem->right;
				}
				else
				{
					del_elem(elem);
					return (1);
				}
			}
		}

		void del_elem(node *N)
		{
			// N is root and only elem in tree
			if (N->parent == NULL && N->left == NULL && N->right == NULL)
			{
				_root->root = NULL;
				_begin = NULL;
				_end = NULL;
				return (delete_node(N));
			}
			// neither child are leafs
			if (N->left != NULL && N->right != NULL)
			{
				node *elem;
				elem = N->left;
				while (elem->right != NULL) elem = elem->right;

				value_type *tmp;

				tmp = N->val;
				N->val = elem->val;
				elem->val = tmp;

				N = elem;
			}
			// two childs are leaf
			if (N->left == NULL && N->right == NULL)
			{
				if (N->colour == RED)
				{
					if (get_child_dir(N) == LEFT) N->parent->left = NULL;
					else
						N->parent->right = NULL;
					return (delete_node(N));
				}
				delete_complex(N);
				return (delete_node(N));
			}

			// one child is a leaf
			node *C;
			if (N->left == NULL) C = N->left;
			else if (N->right == NULL)
				C = N->right;
			else
				assert(1 == 0);// should never happen

			// one child is a leaf
			assert(C->colour == RED);
			C->colour = BLACK;
			if (get_child_dir(N) == LEFT) N->parent->left = C;
			else
				N->parent->right = C;
			return (delete_node(N));
		}


		template< typename T1 >
		value_type &insert_no_overwrite(T1 f, value_type &v)
		{
			node *elem = _root->root;

			if (elem == NULL)
			{
				_root->root = create_new_elem(v);
				_root->root->colour = BLACK;
				_begin = _root->root->val;
				_end = _root->root->val;
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

	private:
		void delete_complex(node *N)
		{
			struct node *P = N->parent;
			bool dir;
			struct node *S;
			struct node *C;
			struct node *D;

			assert(P != NULL);

			dir = get_child_dir(N);
			if (dir == LEFT) N->parent->left = NULL;
			else
				N->parent->right = NULL;

			goto Start_D;

			do {
				dir = get_child_dir(N);// side of parent P on which node N is located
			Start_D:
				S = get_sibling(N, dir);// sibling of N (has black height >= 1)
				D = get_child(S, !dir);
				C = get_child(S, dir);
				if (S->colour == RED) goto Case_D3;// S red ===> P+C+D black
				// S is black:
				if (D != NULL && D->colour == RED)// not considered black
					goto Case_D6;                 // D red && S black
				if (C != NULL && C->colour == RED)// not considered black
					goto Case_D5;                 // C red && S+D black
				// Here both nephews are == NIL (first iteration) or black (later).
				if (P->colour == RED) goto Case_D4;
				// Case_D1 (P+C+S+D black):
				S->colour = RED;
				N = P;// new current node (maybe the root)
					// iterate 1 black level
					//   (= 1 tree level) higher
			} while ((P = N->parent) != NULL);
			// end of the (do while)-loop

			// Case_D2 (P == NULL):
			return;             // deletion complete
		Case_D3:                // S red && P+C+D black:
			rotate_tree(P, dir);// P may be the root
			P->colour = RED;
			S->colour = BLACK;
			S = C;// != NIL
			// now: P red && S black
			D = get_child(S, !dir);
			if (D != NULL && D->colour == RED) goto Case_D6;// D red && S black
			C = get_child(S, dir);
			if (C != NULL && C->colour == RED) goto Case_D5;// C red && S+D black
		// Otherwise C+D considered black.
		// fall through to Case_D4
		Case_D4:// P red && S+C+D black:
			S->colour = RED;
			P->colour = BLACK;
			return;// deletion complete

		Case_D5:                 // C red && S+D black:
			rotate_tree(S, !dir);// S is never the root
			S->colour = RED;
			C->colour = BLACK;
			D = S;
			S = C;
			// now: D red && S black
			// fall through to Case_D6

		Case_D6:                // D red && S black:
			rotate_tree(P, dir);// P may be the root
			S->colour = P->colour;
			P->colour = BLACK;
			D->colour = BLACK;
		}

		inline node *get_sibling(node *N, bool dir)
		{
			if (dir == LEFT) return (N->parent->right);
			return (N->parent->left);
		}


		inline node *get_child(node *N, bool dir)
		{
			if (dir == LEFT) return (N->left);
			return (N->right);
		}

		void clear_rec(node *N)
		{
			if (N == NULL) return;

			clear_rec(N->left);
			clear_rec(N->right);

			delete_node(N);
		}

		void delete_node(node *N)
		{
			if (N->val == _begin) _begin = N->parent->val;
			if (N->val == _end) _end = N->parent->val;
			_allocator.destroy(N->val);
			_allocator.deallocate(N->val, 1);
			_node_allocator.destroy(N);
			_node_allocator.deallocate(N, 1);
		}

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

		void traverseNodes(std::string &sb, const std::string &padding, const std::string &ptr,
						   node *N, bool hasRightSibling)
		{

#define RESET "\033[0m"
#define R "\033[31m"
			if (N != NULL)
			{
				sb.append("\n");
				sb.append(padding);
				sb.append(ptr);
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
				else { paddingBuilder.append("   "); }

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
			else { S->right = P; }
			P->parent = S;
			S->parent = G;

			if (G != NULL)
			{
				dir = P == G->right ? RIGHT : LEFT;
				if (dir == LEFT) { G->left = S; }
				else { G->right = S; }
			}
			else
				_root->root = S;
			return S;
		}

		direction_t get_child_dir(node *n) { return (n == n->parent->left ? LEFT : RIGHT); }

		node *insert_elem(node *P, value_type &v, bool dir)
		{
			node *new_elem = create_new_elem(v, P);

			node *N = new_elem;
			node *G;
			node *U;

			if (dir == LEFT)
			{
				if (P->val == _begin) _begin = new_elem->val;
				P->left = new_elem;
			}
			else
			{
				if (P->val == _end) _end = new_elem->val;
				P->right = new_elem;
			}

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
	};
}// namespace ft

#endif// FT_CONTAINERS_REDBLACKTREE_HPP
