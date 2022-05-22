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
			BLACK,
			SENTINEL
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

			node(value_type *v, node *P, node *s)
			{
				val = v;
				left = s;
				right = s;
				parent = P;
				colour = RED;
			}


			node()
			{
				val = NULL;
				left = NULL;
				right = NULL;
				parent = NULL;
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

			rbtree_iterator() : _node_it() {}

			explicit rbtree_iterator(node *x) : _node_it(x) {}

			node *base() const { return (_node_it); }

			node *increment_rbtree(node *n)
			{
				if (n->colour == SENTINEL) return n->left;
				if (n->right->colour != SENTINEL)
				{
					node *elem = n->right;
					while (elem->left->colour != SENTINEL) { elem = elem->left; }
					return elem;
				}
				while (get_child_dir(n) == RIGHT)
				{
					n = n->parent;
					if (n->colour == SENTINEL) return n;
				}
				return (n->parent);
			}

			node *decrement_rbtree(node *n)
			{
				if (n->colour == SENTINEL) return n->right;
				if (n->left->colour != SENTINEL)
				{
					node *elem = n->left;
					while (elem->right->colour != SENTINEL) { elem = elem->right; }
					return elem;
				}
				while (get_child_dir(n) == LEFT)
				{
					n = n->parent;
					if (n->colour == SENTINEL) return n;
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

			node *_node_it;
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

			rbtree_const_iterator(const iterator &x) : _node_it(x._node_it) {}

			node *base() const { return _node_it; }
			iterator it_const_cast() { return iterator(const_cast< node * >(_node_it)); }

			const node *increment_rbtree(const node *n)
			{
				if (n->colour == SENTINEL) return (n->left);
				if (n->right->colour != SENTINEL)
				{
					node *elem = n->right;
					while (elem->left->colour != SENTINEL) { elem = elem->left; }
					return elem;
				}
				while (get_child_dir(n) == RIGHT)
				{
					n = n->parent;
					if (n->colour == SENTINEL) return n;
				}
				return (n->parent);
			}

			const node *decrement_rbtree(const node *n)
			{
				if (n->colour == SENTINEL) return n->right;
				if (n->left->colour != SENTINEL)
				{
					node *elem = n->left;
					while (elem->right->colour != SENTINEL) { elem = elem->right; }
					return elem;
				}
				while (get_child_dir(n) == LEFT)
				{
					n = n->parent;
					if (n->colour == SENTINEL) return n;
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
		node *_sentinel_node;

	public:
		typedef rbtree_iterator iterator;
		typedef rbtree_const_iterator const_iterator;
		typedef typename ft::reverse_iterator< iterator > reverse_iterator;
		typedef typename ft::reverse_iterator< const_iterator > const_reverse_iterator;

		typedef ft::iterator_traits< iterator > difference_type;

		/* Constructors */
		explicit RedBlackTree(allocator_type alloc) : _size(0), _allocator(alloc)
		{
			_node_allocator = std::allocator< node >();
			std::allocator< node * > _tree_allocator = std::allocator< node * >();

			_sentinel_node = _node_allocator.allocate(1, 0);
			_node_allocator.construct(_sentinel_node, node());
			_sentinel_node->colour = SENTINEL;
			_begin = _sentinel_node;
			_end = _sentinel_node;
			_sentinel_node->left = _begin;
			_sentinel_node->right = _end;
			_root = _tree_allocator.allocate(1, 0);
			_tree_allocator.construct(_root, _sentinel_node);
		}

		RedBlackTree(const RedBlackTree &x)
			: _root(x._root), _size(x._size), _node_allocator(x._node_allocator),
			  _allocator(x._allocator), _begin(x._begin), _end(x._end),
			  _sentinel_node(x._sentinel_node)
		{}

		RedBlackTree &operator=(const RedBlackTree &x)
		{
			if (this == &x) { return *this; }

			_root = x._root;
			_size = x._size;
			_begin = x._begin;
			_end = x._end;
			_sentinel_node = x._sentinel_node;

			return (*this);
		}

		~RedBlackTree()
		{
			std::allocator< node * > _tree_allocator = std::allocator< node * >();

			clear();

			_node_allocator.destroy(_sentinel_node);
			_node_allocator.deallocate(_sentinel_node, 1);
			_tree_allocator.destroy(_root);
			_tree_allocator.deallocate(_root, 1);
		}


		/* Iterators */
		iterator begin() { return (iterator(_begin)); }

		const_iterator begin() const { return (const_iterator(_begin)); }

		iterator end() { return (iterator(_sentinel_node)); }

		const_iterator end() const { return (const_iterator(_sentinel_node)); }

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
			std::swap(_sentinel_node, x._sentinel_node);
		}

		template< typename T1 >
		size_type find_and_delete(T1 f, const value_type &v)
		{
			node *elem = *_root;

			if (elem == _sentinel_node) return (0);

			while (true)
			{
				if (f(v, *elem->val))
				{
					if (elem->left == _sentinel_node) return (0);
					elem = elem->left;
				}
				else if (f(*elem->val, v))
				{
					if (elem->right == _sentinel_node) return (0);
					elem = elem->right;
				}
				else
				{
					del_elem(elem);
					return (1);
				}
			}
		}

		void del_const_elem(const node *N) { (void) (const_cast< node * >(N)); }

		void del_elem(node *N)
		{
			// avoid deleting sentinel node if  user passes end() to erase
			if (N == _sentinel_node) return;


			// N is root and only elem in tree
			if (N->parent == _sentinel_node && N->left == _sentinel_node &&
				N->right == _sentinel_node)
			{
				*_root = _sentinel_node;
				_begin = _sentinel_node;
				_sentinel_node->left = _begin;
				_end = _sentinel_node;
				_sentinel_node->right = _end;
				return (delete_node(N));
			}
			// neither child are leafs
			if (N->left != _sentinel_node && N->right != _sentinel_node)
			{
				node *elem;
				elem = N->left;
				while (elem->right != _sentinel_node) elem = elem->right;

				std::swap(N->val, elem->val);

				N = elem;
			}


			if (N == _begin)
			{
				node *elem;
				elem = N->right;
				if (elem != _sentinel_node)
				{
					while (elem->left != _sentinel_node) elem = elem->left;
					_begin = elem;
				}
				else
					_begin = N->parent;
				_sentinel_node->left = _begin;
			}
			if (N == _end)
			{
				node *elem;
				elem = N->left;
				if (elem != _sentinel_node)
				{
					while (elem->right != _sentinel_node) elem = elem->right;
					_end = elem;
				}
				else
					_end = N->parent;
				_sentinel_node->right = _end;
			}


			// two childs are leaf
			if (N->left == _sentinel_node && N->right == _sentinel_node)
			{
				if (N->colour == RED)
				{
					if (get_child_dir(N) == LEFT) N->parent->left = _sentinel_node;
					else
						N->parent->right = _sentinel_node;
					return (delete_node(N));
				}
				delete_complex(N);
				return (delete_node(N));
			}

			// one child is a leaf
			node *C;
			if (N->left == _sentinel_node) C = N->right;
			else if (N->right == _sentinel_node)
				C = N->left;
			else
				assert(1 == 0);// should never happen

			// one child is a leaf
			assert(C->colour == RED);
			C->colour = BLACK;
			if (get_child_dir(N) == LEFT) N->parent->left = C;
			else
				N->parent->right = C;
			C->parent = N->parent;
			return (delete_node(N));
		}

		template< typename T1 >
		ft::pair< iterator, int > find(T1 f, const value_type &v)
		{
			node *elem = *_root;

			if (elem == _sentinel_node)
				return (ft::make_pair(iterator(_sentinel_node), (int) NULL_DIR));

			while (true)
			{
				assert(elem != _sentinel_node && elem != NULL);
				if (f(v, *elem->val))
				{
					if (elem->left == _sentinel_node)
						return (ft::make_pair(iterator(elem), (int) LEFT));
					elem = elem->left;
				}
				else if (f(*elem->val, v))
				{
					if (elem->right == _sentinel_node)
						return (ft::make_pair(iterator(elem), (int) RIGHT));
					elem = elem->right;
				}
				else
					return (ft::make_pair(iterator(elem), (int) NULL_DIR));
			}
		}

		template< typename T1 >
		ft::pair< const_iterator, int > find(T1 f, const value_type &v) const
		{
			node *elem = *_root;

			if (elem == _sentinel_node)
				return (ft::make_pair(const_iterator(_sentinel_node), (int) NULL_DIR));

			while (true)
			{
				if (f(v, *elem->val))
				{
					if (elem->left == _sentinel_node)
						return (ft::make_pair(const_iterator(elem), (int) LEFT));
					elem = elem->left;
				}
				else if (f(*elem->val, v))
				{
					if (elem->right == _sentinel_node)
						return (ft::make_pair(const_iterator(elem), (int) RIGHT));
					elem = elem->right;
				}
				else
					return (ft::make_pair(const_iterator(elem), (int) NULL_DIR));
			}
		}

		template< typename T1 >
		ft::pair< iterator, bool > insert(T1 f, const value_type &v)
		{
			ft::pair< iterator, int > elem = find(f, v);

			if (elem.first == iterator(_sentinel_node))
			{
				*_root = create_new_elem(v);
				(*_root)->colour = BLACK;
				_begin = *_root;
				_sentinel_node->left = _begin;
				_end = *_root;
				_sentinel_node->right = _end;
				return (ft::make_pair(iterator(*_root), true));
			}

			if (elem.second == (int) NULL_DIR) return (ft::make_pair(elem.first, false));
			return (
				ft::make_pair(iterator(insert_elem(elem.first._node_it, v, elem.second)), true));
		}

		//		template< typename T1 >
		//		ft::pair< const_iterator, bool > insert(T1 f, const value_type &v)
		//		{
		//			ft::pair< const_iterator, int > elem = find(f, v);
		//
		//			if (elem.first == const_iterator(_sentinel_node))
		//			{
		//				*_root = create_new_elem(v);
		//				(*_root)->colour = BLACK;
		//				_begin = *_root;
		//				_sentinel_node->left = _begin;
		//				_end = *_root;
		//				_sentinel_node->right = _end;
		//				return (ft::make_pair(const_iterator(*_root), true));
		//			}
		//
		//			if (elem.second == (int) NULL_DIR) return (ft::make_pair(elem.first, false));
		//			return (ft::make_pair(const_iterator(insert_elem(elem.first._node_it, v, elem.second)),
		//								  true));
		//		}

		template< typename T1 >
		ft::pair< iterator, bool > insert(T1 f, iterator hint, const value_type &v)
		{
			(void) hint;// todo: fix
			//			node *elem = *hint;
			//
			//			if (elem != _sentinel_node)
			//				if (f(*elem->val, v) && elem->right == _sentinel_node)
			//					return (make_pair(iterator(insert_elem(elem, v, RIGHT)), true));

			return insert(f, v);
		}


		template< typename T1 >
		ft::pair< iterator, bool > insert(T1 f, const_iterator hint, const value_type &v)
		{
			(void) hint;// todo: fix
			//			node *elem = *hint;
			//
			//			if (elem != _sentinel_node)
			//				if (f(*elem->val, v) && elem->right == _sentinel_node)
			//					return (make_pair(iterator(insert_elem(elem, v, RIGHT)), true));

			return insert(f, v);
		}

		bool empty() const { return (_size == 0); }

		size_type size() const { return (_size); }

		size_type max_size() const { return (_node_allocator.max_size()); }

		void clear()
		{
			_begin = _sentinel_node;
			_end = _sentinel_node;
			_sentinel_node->left = _begin;
			_sentinel_node->right = _end;
			clear_rec(*_root);
			*_root = _sentinel_node;
		}

		template< typename T1 >
		iterator upper_bound(T1 f, const value_type &v)
		{
			iterator it = begin();

			while (it != end())
				if (f(v, *it)) return (it);
				else
					it++;
			return it;
		}

		template< typename T1 >
		const_iterator upper_bound(T1 f, const value_type &v) const
		{

			const_iterator it = begin();

			while (it != end())
				if (f(v, *it)) return (it);
				else
					it++;
			return it;
		}

		template< typename T1 >
		iterator lower_bound(T1 f, const value_type &v)
		{
			iterator it = begin();

			while (it != end())
				if (f(*it, v)) it++;
				else
					return (it);
			return it;
		}

		template< typename T1 >
		const_iterator lower_bound(T1 f, const value_type &v) const
		{
			const_iterator it = begin();

			while (it != end())
				if (f(*it, v)) it++;
				else
					return (it);
			return it;
		}

		template< typename T1 >
		pair< iterator, iterator > equal_range(T1 f, const value_type &v)
		{
			return (make_pair(lower_bound(f, v), upper_bound(f, v)));
		}

		template< typename T1 >
		pair< const_iterator, const_iterator > equal_range(T1 f, const value_type &v) const
		{
			return (make_pair(lower_bound(f, v), upper_bound(f, v)));
		}

	private:
		void delete_complex(node *N)
		{
			struct node *P = N->parent;
			int dir;
			struct node *S;
			struct node *C;
			struct node *D;

			assert(P != _sentinel_node);
			dir = get_child_dir(N);
			if (dir == LEFT) N->parent->left = _sentinel_node;
			else
				N->parent->right = _sentinel_node;

			goto Start_D;

			do {
				dir = get_child_dir(N);// side of parent P on which node N is located
			Start_D:
				S = get_sibling(N, dir);// sibling of N (has black height >= 1)
				D = get_child(S, !dir);
				C = get_child(S, dir);
				if (S->colour == RED) goto Case_D3;// S red ===> P+C+D black
				// S is black:
				if (D != _sentinel_node && D->colour == RED)// not considered black
					goto Case_D6;                           // D red && S black
				if (C != _sentinel_node && C->colour == RED)// not considered black
					goto Case_D5;                           // C red && S+D black
				// Here both nephews are == NIL (first iteration) or black (later).
				if (P->colour == RED) goto Case_D4;
				// Case_D1 (P+C+S+D black):
				S->colour = RED;
				N = P;// new current node (maybe the root)
					// iterate 1 black level
					//   (= 1 tree level) higher
			} while ((P = N->parent) != _sentinel_node);
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
			if (D != _sentinel_node && D->colour == RED) goto Case_D6;// D red && S black
			C = get_child(S, dir);
			if (C != _sentinel_node && C->colour == RED) goto Case_D5;// C red && S+D black
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
			if (N == _sentinel_node) return;

			clear_rec(N->left);
			clear_rec(N->right);

			// todo: use delete_node
			--_size;
			_allocator.destroy(N->val);
			_allocator.deallocate(N->val, 1);
			_node_allocator.destroy(N);
			_node_allocator.deallocate(N, 1);
		}

		void delete_node(node *N)
		{
			// all theses condition should be managed before calling this function
			assert(N->left->parent != N);
			assert(N->right->parent != N);
			assert(_sentinel_node == *_root || N == *_root || N->parent != _sentinel_node);
			assert(N != _begin);
			assert(N != _end);
			assert(_sentinel_node->left == _begin);
			assert(_sentinel_node->right == _end);

			--_size;
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
			if (P == NULL)
				_node_allocator.construct(new_elem, node(vptr, _sentinel_node, _sentinel_node));
			else
				_node_allocator.construct(new_elem, node(vptr, P, _sentinel_node));

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

			assert(S != _sentinel_node);// pointer to true node required
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

			if (C != _sentinel_node) C->parent = P;
			if (dir == LEFT) { S->left = P; }
			else { S->right = P; }
			P->parent = S;
			S->parent = G;

			if (G != _sentinel_node)
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
				if (P == _begin)
				{
					_begin = new_elem;
					_sentinel_node->left = _begin;
				}
				P->left = new_elem;
			}
			else
			{
				if (P == _end)
				{
					_end = new_elem;
					_sentinel_node->right = _end;
				}
				P->right = new_elem;
			}

			do {
				if (P->colour == BLACK) return (new_elem);

				G = P->parent;

				if (G == _sentinel_node) goto case0;

				dir = get_child_dir(P);

				if (dir == LEFT) U = G->right;
				else
					U = G->left;
				if (U == _sentinel_node || U->colour == BLACK) goto case1;

				P->colour = BLACK;
				U->colour = BLACK;
				G->colour = RED;
				N = G;
			} while ((P = N->parent) != _sentinel_node);

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
