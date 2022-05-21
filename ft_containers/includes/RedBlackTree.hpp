//
// Created by segransm on 5/9/22.
//

#ifndef FT_CONTAINERS_REDBLACKTREE_HPP
#define FT_CONTAINERS_REDBLACKTREE_HPP

#include <iterator.hpp>
#include <utility.hpp>

#include <cassert>
#include <cstddef>
#include <iostream>
#include <memory>
#include <sstream>

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


	private:
		enum color_t
		{
			RED,
			BLACK
		};

		enum direction_t
		{
			NULL_DIR = -1,
			LEFT,
			RIGHT
		};

		struct node
		{
			value_type *val;
			node *parent;
			node *left;
			node *right;
			int colour;

			node(value_type *v, node *P)
			{
				val = v;
				left = NULL;
				right = NULL;
				parent = P;
				colour = RED;
			}
		};

		struct rbtree_iterator
		{
			typedef T value_type;
			typedef T &reference;
			typedef T *pointer;

			typedef ft::bidirectional_iterator_tag iterator_category;
			typedef ptrdiff_t difference_type;

			typedef typename std::allocator< node >::pointer _node_ptr;

			rbtree_iterator() : _node_it() {}

			explicit rbtree_iterator(_node_ptr x) : _node_it(x) {}

			_node_ptr base() const { return (_node_it); }

			_node_ptr increment_rbtree(_node_ptr n)
			{

				if (n->right != NULL)
				{
					node *elem = n->right;
					while (elem->left) { elem = elem->left; }
					return elem;
				}
				while (get_child_dir(n) == RIGHT)
				{
					n = n->parent;
					if (n->parent == NULL) return NULL;
				}
				return (n->parent);
			}

			_node_ptr decrement_rbtree(_node_ptr n)
			{
				if (n->left != NULL)
				{
					node *elem = n->left;
					while (elem->right) { elem = elem->right; }
					return elem;
				}
				while (get_child_dir(n) == LEFT)
				{
					n = n->parent;
					if (n->parent == NULL) return NULL;
				}
				return (n->parent);
			}

			reference operator*() const { return *(_node_it)->val; }

			pointer operator->() const { return (_node_it)->val; }

			rbtree_iterator &operator++()
			{
				_node_it = increment_rbtree(_node_it);
				return *this;
			}

			rbtree_iterator operator++(int)
			{
				rbtree_iterator tmp = *this;
				_node_it = increment_rbtree(_node_it);
				return tmp;
			}

			rbtree_iterator &operator--()
			{
				_node_it = decrement_rbtree(_node_it);
				return *this;
			}

			rbtree_iterator operator--(int)
			{
				rbtree_iterator tmp = *this;
				_node_it = decrement_rbtree(_node_it);
				return tmp;
			}

			friend bool operator==(const rbtree_iterator &lhs, const rbtree_iterator &rhs)
			{
				return lhs._node_it == rhs._node_it;
			}


			friend bool operator!=(const rbtree_iterator &lhs, const rbtree_iterator &rhs)
			{
				return lhs._node_it != rhs._node_it;
			}

			_node_ptr _node_it;
		};

		struct rbtree_const_iterator
		{
			typedef T value_type;
			typedef const T &reference;
			typedef const T *pointer;

			typedef rbtree_iterator iterator;

			typedef bidirectional_iterator_tag iterator_category;
			typedef ptrdiff_t difference_type;


			rbtree_const_iterator() : _node_it() {}

			explicit rbtree_const_iterator(node *x) : _node_it(x) {}

			rbtree_const_iterator(const iterator x) : _node_it(x._node_it) {}

			node *base() const { return (_node_it); }

			const node *increment_rbtree(const node *n)
			{

				if (n->right != NULL)
				{
					node *elem = n->right;
					while (elem->left) { elem = elem->left; }
					return elem;
				}
				while (get_child_dir(n) == RIGHT)
				{
					n = n->parent;
					if (n->parent == NULL) return NULL;
				}
				return (n->parent);
			}

			const node *decrement_rbtree(const node *n)
			{
				if (n->left != NULL)
				{
					node *elem = n->left;
					while (elem->right) { elem = elem->right; }
					return elem;
				}
				while (get_child_dir(n) == LEFT)
				{
					n = n->parent;
					if (n->parent == NULL) return NULL;
				}
				return (n->parent);
			}

			reference operator*() const { return *static_cast< const node * >(_node_it)->val; }

			pointer operator->() const { return static_cast< const node * >(_node_it)->val; }

			rbtree_const_iterator &operator++()
			{
				_node_it = increment_rbtree(_node_it);
				return *this;
			}

			rbtree_const_iterator operator++(int)
			{
				rbtree_const_iterator tmp = *this;
				_node_it = increment_rbtree(_node_it);
				return tmp;
			}

			rbtree_const_iterator &operator--()
			{
				_node_it = decrement_rbtree(_node_it);
				return *this;
			}

			rbtree_const_iterator operator--(int)
			{
				rbtree_const_iterator tmp = *this;
				_node_it = decrement_rbtree(_node_it);
				return tmp;
			}

			friend bool operator==(const rbtree_const_iterator &lhs,
								   const rbtree_const_iterator &rhs)
			{
				return lhs._node_it == rhs._node_it;
			}

			friend bool operator!=(const rbtree_const_iterator &lhs,
								   const rbtree_const_iterator &rhs)
			{
				return lhs._node_it != rhs._node_it;
			}

			const node *_node_it;
		};

		node **_root;
		size_type _size;
		std::allocator< node > _node_allocator;
		allocator_type _allocator;
		node *_begin;
		node *_end;

	public:
		typedef rbtree_iterator iterator;
		typedef const rbtree_const_iterator const_iterator;
		typedef typename ft::reverse_iterator< iterator > reverse_iterator;
		typedef typename ft::reverse_iterator< const_iterator > const_reverse_iterator;

		typedef ft::iterator_traits< iterator > difference_type;

		/* Constructors */
		explicit RedBlackTree(allocator_type alloc)
			: _size(0), _allocator(alloc), _begin(NULL), _end(NULL)
		{
			_node_allocator = std::allocator< node >();
			std::allocator< node * > _tree_allocator = std::allocator< node * >();

			_root = _tree_allocator.allocate(1, 0);
			_tree_allocator.construct(_root, NULL);
		}

		RedBlackTree(const RedBlackTree &x)
			: _root(x._root), _size(x._size), _node_allocator(x._node_allocator),
			  _allocator(x._allocator), _begin(x._begin), _end(x._end)
		{}

		RedBlackTree &operator=(const RedBlackTree &x)
		{
			if (this == &x) { return *this; }

			_root = x._root;
			_size = x._size;
			_node_allocator = x._node_allocator;
			_allocator = x._allocator;
			_begin = x._begin;
			_end = x._end;

			return (*this);
		}

		~RedBlackTree()
		{
			std::allocator< node * > _tree_allocator = std::allocator< node * >();

			clear();

			_tree_allocator.destroy(_root);
			_tree_allocator.deallocate(_root, 1);
		}


		/* Iterators */
		iterator begin() { return (iterator(_begin)); }

		const_iterator begin() const { return (const_iterator(_begin)); }

		iterator end() { return (iterator(NULL)); }

		const_iterator end() const { return (const_iterator(NULL)); }


		reverse_iterator rbegin() { return (reverse_iterator(end())); }

		const_reverse_iterator rbegin() const { return (const_reverse_iterator(end())); }

		reverse_iterator rend() { return (reverse_iterator(begin())); }

		const_reverse_iterator rend() const { return (const_reverse_iterator(begin())); }

		void swap(RedBlackTree &x)
		{
			std::swap(_root, x._root);
			std::swap(_size, x._size);
			std::swap(_node_allocator, x._node_allocator);
			std::swap(_allocator, x._allocator);
			std::swap(_begin, x._begin);
			std::swap(_end, x._end);
		}

		template< typename T1 >
		size_type find_and_delete(T1 f, value_type &v)
		{
			node *elem = *_root;

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
				*_root = NULL;
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
		ft::pair< iterator, direction_t > find(T1 f, const value_type &v)
		{
			node *elem = *_root;

			if (elem == NULL) return (make_pair(iterator(NULL), NULL_DIR));

			while (true)
			{
				if (f(v, *elem->val))
				{
					if (elem->left == NULL) return (make_pair(iterator(elem), LEFT));
					elem = elem->left;
				}
				else if (f(*elem->val, v))
				{
					if (elem->right == NULL) return (make_pair(iterator(elem), RIGHT));
					elem = elem->right;
				}
				else
					return (make_pair(iterator(elem), NULL_DIR));
			}
		}

		template< typename T1 >
		ft::pair< const_iterator, direction_t > find(T1 f, const value_type &v) const
		{
			node *elem = *_root;

			if (elem == NULL) return (make_pair(const_iterator(NULL), NULL_DIR));

			while (true)
			{
				if (f(v, *elem->val))
				{
					if (elem->left == NULL) return (make_pair(const_iterator(elem), LEFT));
					elem = elem->left;
				}
				else if (f(*elem->val, v))
				{
					if (elem->right == NULL) return (make_pair(const_iterator(elem), RIGHT));
					elem = elem->right;
				}
				else
					return (make_pair(const_iterator(elem), NULL_DIR));
			}
		}

		template< typename T1 >
		ft::pair< iterator, bool > insert(T1 f, const value_type &v)
		{
			ft::pair< iterator, direction_t > elem = find(f, v);

			if (elem.first == iterator(NULL))
			{
				*_root = create_new_elem(v);
				(*_root)->colour = BLACK;
				_begin = *_root;
				_end = *_root;
				return (make_pair(iterator(*_root), true));
			}

			if (elem.second == NULL_DIR) return (make_pair(elem.first, false));
			return (make_pair(iterator(insert_elem(elem.first._node_it, v, elem.second)), true));
		}

		template< typename T1 >
		ft::pair< iterator, bool > insert(T1 f, const value_type &v, iterator hint)
		{
			node *elem = *hint;

			if (elem != NULL)
				if (f(*elem->val, v) && elem->right == NULL)
					return (make_pair(iterator(insert_elem(elem, v, RIGHT)), true));

			insert(f, v);
		}


		bool empty() const { return (_size == 0); }

		size_type size() const { return (_size); }

		size_type max_size() const { return (_node_allocator.max_size()); }

		void clear() { clear_rec(*_root); }

		template< typename T1 >
		iterator lower_bound(T1 f, const value_type &v)
		{
			node *elem = *_root;

			if (elem == NULL) return (end());

			while (true)
			{
				if (f(*elem->val, v))
				{
					if (elem->right == NULL) return (end());
					elem = elem->right;
				}
				else
				{
					if (elem->left == NULL) return (iterator(elem));
					elem = elem->left;
				}
			}
		}

	private:
		void delete_complex(node *N)
		{
			struct node *P = N->parent;
			int dir;
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

		inline node *get_sibling(node *N, int dir)
		{
			if (dir == LEFT) return (N->parent->right);
			return (N->parent->left);
		}


		inline node *get_child(node *N, int dir)
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
			if (N->parent != NULL)
			{
				if (N->parent->left == N) N->parent->left = NULL;
				if (N->parent->right == N) N->parent->right = NULL;
				if (N == _begin) _begin = N->parent;
				if (N == _end) _end = N->parent;
			}

			_allocator.destroy(N->val);
			_allocator.deallocate(N->val, 1);
			_node_allocator.destroy(N);
			_node_allocator.deallocate(N, 1);
		}

		node *create_new_elem(const value_type &v, node *P = NULL)
		{
			value_type *vptr = _allocator.allocate(1, 0);
			_allocator.construct(vptr, v);

			node *new_elem = _node_allocator.allocate(1, 0);
			_node_allocator.construct(new_elem, node(vptr, P));

			++_size;
			return (new_elem);
		}

		node *rotate_tree(node *P, int dir)
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
				dir = (P == G->right) ? RIGHT : LEFT;
				if (dir == LEFT) { G->left = S; }
				else { G->right = S; }
			}
			else
				*_root = S;
			return S;
		}

		static direction_t get_child_dir(const node *n)
		{
			return (n == n->parent->left ? LEFT : RIGHT);
		}

		node *insert_elem(node *P, const value_type &v, int dir)
		{
			node *new_elem = create_new_elem(v, P);

			node *N = new_elem;
			node *G;
			node *U;

			if (dir == LEFT)
			{
				if (P == _begin) _begin = new_elem;
				P->left = new_elem;
			}
			else
			{
				if (P == _end) _end = new_elem;
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


	template< class T, class Alloc >
	void swap(RedBlackTree< T, Alloc > &x, RedBlackTree< T, Alloc > &y)
	{
		x.swap(y);
	}

}// namespace ft

#endif// FT_CONTAINERS_REDBLACKTREE_HPP
