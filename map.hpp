#pragma once

#include <utility>
#include "iterator.hpp"

namespace ft {
template < class Key,											// map::key_type
		class T,												// map::mapped_type
		class Compare = std::less<Key>,							// map::key_compare
		class Alloc = std::allocator<std::pair<const Key,T> >	// map::allocator_type
		>
	class map {
	public:
		typedef Key												key_type;
		typedef T												mapped_type;
		typedef std::pair<const key_type, mapped_type>			value_type;
		typedef Compare											key_compare;
		typedef Alloc											allocator_type;
		typedef typename allocator_type::pointer				pointer;
		typedef typename allocator_type::const_pointer			const_pointer;
		typedef typename allocator_type::reference				reference;
		typedef typename allocator_type::const_reference		const_reference;
		typedef typename ft::iter_map<key_type, mapped_type>	iterator;
		// typedef typename const_iterator	 const_iterator;
		// typedef typename reverse_iterator	 reverse_iterator;
		// typedef typename const_reverse_iterator const_reverse_iterator;
		typedef ptrdiff_t	 difference_type;
		typedef size_t		 size_type;
	private:
		typedef node_map<key_type, mapped_type>* node;
		typedef typename allocator_type::template rebind<node_map<key_type, mapped_type> >::other	alloc_node;

		allocator_type			_alloc;
		alloc_node				_node_alloc;
		node					_map;
		size_type				_size;
		key_compare				_comp;

		node	_create_node(key_type key = key_type(), mapped_type val = mapped_type(), node parent = NULL) {
			node new_node = _node_alloc.allocate(1);

			new_node->pair = std::make_pair(key, val);
			new_node->right = 0;
			new_node->left = 0;
			new_node->parent = parent;
			new_node->color = IS_RED;
			return new_node;
		}

		iterator _search_node(const value_type& val) {
			for (iterator it = begin(); it != end(); ++it) {
				if (it._p->pair.first == val.first) {
					return it;
				}
			}
			return NULL;
		}

		node _insert(node n, key_type key, mapped_type val) {
			if (key < n->pair.first) {
				if (!n->left) {
					n->left = _create_node(key, val, n);
					_balance(n->left);
					return n->left;
				}
				return _insert(n->left, key, val);
			}
			else if (key > n->pair.first) {
				if (!n->right) {
					n->right = _create_node(key, val, n);
					_balance(n->right);
					return n->right;
				}
				return _insert(n->right, key, val);
			}
			return 0;
		}

		void _balance(node n) {
			node p = n->parent;
			node g = _grandparent(n);
			node u = _uncle(n);

			if (_map == n) {
				_map->color = IS_BLACK;
			}

			if (n->color == IS_RED && p && p->color == IS_RED && g && (!u || u->color == IS_BLACK)) { // case 3
				if (g->left == p && p->left == n) {
					g->left = p->right;
					// p->right->parent = g;
					p->right = g;
					// if (g->parent && )
					// 	g->parent->right = p;
				}
				else if (g->right == p && p->right == n) {
					g->right = p->left;
					if (p->left)
						p->left->parent = g;
					p->left = g;
					// if (g->parent)
					// 	g->parent->right = p;
				}
				else if (g->right == p && p->left == n) {
					g->right = n;
					n->parent = g;
					n->right = p;
					p->parent = n;
					p->left = NULL;
					_balance(p);
					return ;
				}
				else { // (g->left == p && p->right == n)
					g->left = n;
					n->parent = g;
					n->left = p;
					p->parent = n;
					p->right = NULL;
					_balance(p);
					return ;
				}
				if (g->parent && g->parent->left == g)
					g->parent->left = p;
				else if (g->parent && g->parent->right == g)
					g->parent->right = p;
				p->parent = g->parent;
				g->parent = p;
				if (!p->parent)
					_map = p;
				g->color =	IS_RED;
				p->color = IS_BLACK;
			}
			else if (n->color == IS_RED && p && p->color == IS_RED && g && u && u->color == IS_RED) { // case 1
				p->color = IS_BLACK;
				u->color = IS_BLACK;
				if (g->parent) {
					g->color = IS_RED;
				}
			}

			if (n->parent && n->parent->parent)
				_balance(n->parent);

		}

		node _grandparent(node n) {
			if (n && n->parent)
				return n->parent->parent;
			else
				return NULL;
		}

		node _uncle(node n) {
			node g = _grandparent(n);
			if (!g)
				return NULL;
			if (n->parent == g->left)
				return g->right;
			else
				return g->left;
		}

		void _del_max_left(node n) {
			node del = n->left;

			while (del->right) {
				del = del->right;
			}

			ft::swap(n, del);
			ft::swap(n->color, del->color);

			// select delete


			// // swap->parent->right = swap->left;
			// if (swap->left)
			// 	swap->left->parent = swap->parent;
			// if (swap->right)
			// 	swap->parent->right = swap->right;
			// else
			// 	swap->parent->right = swap->left;

			// swap->color = n->color;
			// swap->left = n->left;
			// swap->right = n->right;
			// swap->parent = n->parent;


			// n->left->parent = swap;
			// n->right->parent = swap;

			// // ft::swap(n, swap);
			// if (n->parent->pair.first < n->pair.first) {
			// 	n->parent->right = swap;
			// }
			// else
			// 	n->parent->left = swap;
			// n->parent = swap->parent;
			// if (swap->left)

			// // n->left = swap->left;
			// // n->right = swap->right;
			// _node_alloc.deallocate(n, 1);
			// n = NULL;
		}

		void _del_min_right(node n) {
			node swap = n->right;

			while (swap->left) {
				swap = swap->left;
			}

			ft::swap(n, del);
			ft::swap(n->color, del->color);


			// swap->parent->left = swap->right;

			// swap->color = n->color;
			// swap->left = n->left;
			// swap->right = n->right;
			// swap->parent = n->parent;

			// n->left->parent = swap;
			// n->right->parent = swap;
			
			// _node_alloc.deallocate(n, 1);
		}

		// void _del_red_node(node n) {
		// 	if (n->left) {
		// 		if (n->left->right) {
		// 			_del_red_max_left(n);
		// 		}
		// 		else {
		// 			_del_red_min_right(n);
		// 		}
		// 	}
		// 	else {
				
		// 	}
		// }

		// void _del_black_node(node n) {
		// 	if (n->left) {
		// 		if (n->left->right) {
		// 			_del_red_max_left(n);
		// 		}
		// 		else {
		// 			_del_red_min_right(n);
		// 		}
		// 	}
		// 	else {
				
		// 	}
		// }


		void _del_red_node_without_child(node n) {
			if (n->parent->right == n) {
				n->parent->right = NULL;
			}
			else {
				n->parent->left = NULL;
			}
			_node_alloc.deallocate(n, 1);
		}

		void _del_black_node_with_one_child(node n) {
			if (n->left) {
				ft::swap(n->left->pair, n->pair);
				_del_red_node_without_child(n->left);
			}
			else {
				ft::swap(n->right->pair, n->pair);
				_del_red_node_without_child(n->right);
			}
		}

		void _balance_black_node_without_child(node n) {
			// select balance //no
			_node_alloc.deallocate(n, 1);
		}

		void _balance_rb1(node del) {
			if (n->parent->right == del) {
				ft::swap(del->parent->color, del->parent->left->color);
			}
			else {
				ft::swap(del->parent->color, del->parent->right->color);
			}
		}

		void _balance_rb2(node del) {
			node p = n->parent;
			node b;

			if (p->right == del) {
				b = p->left;
				p->left = b->right;
				b->right->parent = p;
				b->right = p;
				b->parent = p->parent;
				p->parent = b;
				p->color = IS_BLACK;
				b->color = IS_RED;
				b->left->color = IS_BLACK;
			}
			else {
				b = p->right;
				p->right = b->left;
				b->left->parent = p;
				b->left = p;
				b->parent = p->parent;
				p->parent = b;
				p->color = IS_BLACK;
				b->color = IS_RED;
				b->right->color = IS_BLACK;
			}
		}

		void _balance_br3(node del) {
			node p = del->parent;
			node b;
			node n; // nephew

			if (p->right == del) {
				b = p->left;
				n = b->right;
				b->right = p;
				b->parent = p->parent;
				p->parent = b;
				n->parent = p;
				p->left = n;
			}
			else {
				b = p->right;
				n = b->left;
				b->left = p;
				b->parent = p->parent;
				p->parent = b;
				n->parent = p;
				p->right = n;
			}
		}

		void _balance_br4(node del) {
			node p = del->parent;
			node b;
			node n; // nephew
			node gn;// grandnephew

			if (p->right == del) {
				b = p->left;
				n = b->right;
				gn = n->left;
				n->right->parent = p;
				p->left = n->right;
				b->right = gn;
				gn->parent = b;
				gn->color = IS_BLACK;
				n->left = b;
				n->right = p;
				n->parent = p->parent;
				b->parent = n;
				p->parent = n;
			}
			else {
				b = p->right;
				n = b->left;
				gn = n->right;
				n->left->parent = p;
				p->right = n->left;
				b->left = gn;
				gn->parent = b;
				gn->color = IS_BLACK;
				n->right= b;
				n->left = p;
				n->parent = p->parent;
				b->parent = n;
				p->parent = n;
			}
		}

		void _balance_bb5(node del) {
			node p = del->parent;
			node b;
			node n;
			node gn;

			if (p->right == del) {
				b = p->left;
				n = b->right;
				gn = n->left;
				n->right->parent = p;
				p->left = n->right;
				b->right = gn;
				gn->parent = b;
				n->left = b;
				n->right = p;
				n->parent = p->parent;
				b->parent = n;
				p->parent = n;
				n->color = IS_BLACK;
			}
			else {
				b = p->right;
				n = b->left;
				gn = n->right;
				n->left->parent = p;
				p->right = n->left;
				b->left = gn;
				gn->parent = b;
				n->right= b;
				n->left = p;
				n->parent = p->parent;
				b->parent = n;
				p->parent = n;
				n->color = IS_BLACK;
			}
		}

		void _balance_bb6(node del) {
			node p = del->parent;

			if (p->right == del) {
				p->left->color = IS_RED;
			}
			else {
				p->right->color = IS_RED;
			}
			_balance_black_node_without_child(p);
		}

	public:
		explicit map (const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) : _size(0), _comp(comp), _alloc(alloc) {
				
		}

		~map() {}
	/* Iterators */
		iterator begin() {
			node tmp = _map;
			while (tmp) {
				if(!tmp->left) {
					break ;
				}
				tmp = tmp->left;
			}
			return iterator(tmp);
		}

		iterator end() {
			node tmp = _map;
			while (tmp) {
				// if(!tmp->right) {
				// 	break ;
				// }
				tmp = tmp->right;
			}
			return iterator(tmp);
		}

	/* Capacity */
		bool empty() const {return !_size;}
		size_type size() const {return _size;}
		size_type max_size() const {return _node_alloc.max_size();}

	/* Element access */

	/* Modifiers */
		std::pair<iterator, bool> insert (const value_type& val) {
			if(empty()) {
				_map = _create_node(val.first, val.second);
				_map->color = IS_BLACK;
				++_size;
				return std::make_pair(iterator(_map), true);
			}
			else if (_search_node(val) != NULL) {
				iterator it = _search_node(val);
				it._p->pair.second = val.second;
				return std::make_pair(it, false);
			}
			++_size;
			return std::make_pair(iterator(_insert(_map, val.first, val.second)), true);
		}

		iterator insert (iterator position, const value_type& val) {

		}

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last) {
			for (InputIterator it = first; it != last; ++it) {
				insert(*it);
			}
		}

		void erase (iterator position) {
			// if (position._p->color == IS_RED) {
			// 	_del_red_node(position._p);
			// }
			// else {
			// 	_del_black_node(position._p);
			// }

			node n = position._p;
			if (n->left) {
				if (n->left->right) {
					_del_max_left(n);
				}
				else {
					_del_min_right(n);
				}
			}
			else {}

		}

	/* Operations */



	};
}