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
				if (it->second == val) {
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
					p->right = g;
					// if (g->parent && )
					// 	g->parent->right = p;
				}
				else if (g->right == p && p->right == n) {
					g->right = p->left;
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

		// void _rotate_left(node n) {
		// 	node pivot = n->right;

		// 	pivot->parent = n->parent;
		// 	if (n->parent != NULL) {
		// 		if (n->parent->left == n)
		// 			n->parent->left = pivot;
		// 		else
		// 			n->parent->right = pivot;
		// 	}		

		// 	n->right = pivot->left;
		// 	if (pivot->left != NULL)
		// 		pivot->left->parent = n;

		// 	n->parent = pivot;
		// 	pivot->left = n;
		// }

		// void _rotate_right(node n) {
		// 	node pivot = n->left;
			
		// 	pivot->parent = n->parent;
		// 	if (n->parent != NULL) {
		// 		if (n->parent->left == n)
		// 			n->parent->left = pivot;
		// 		else
		// 			n->parent->right = pivot;
		// 	}		
			
		// 	n->left = pivot->right;
		// 	if (pivot->right != NULL)
		// 		pivot->right->parent = n;

		// 	n->parent = pivot;
		// 	pivot->right = n;
		// }

		// void _insert_case1(node n) {
		// 	if (!n->parent)
		// 		n->color = IS_BLACK;
		// 	else
		// 		_insert_case2(n);
		// }

		// void _insert_case2(node n) {
		// 	if (n->parent->color == IS_BLACK)
		// 		return ;
		// 	else
		// 		_insert_case3(n);
		// }

		// void _insert_case3(node n) {
		// 	node u = _uncle(n);
		// 	node g = _grandparent(n);

		// 	if ((u != NULL) && (u->color == IS_RED)) {
		// 		n->parent->color = IS_BLACK;
		// 		u->color = IS_BLACK;
		// 		g->color = IS_RED;
		// 		_insert_case1(g);
		// 	}
		// 	else {
		// 		_insert_case4(n);
		// 	}
		// }

		// void _insert_case4(node n) {
		// 	node g = _grandparent(n);

		// 	if (n == n->parent->right && n->parent == g->left) {
		// 		_rotate_left(n->parent);
		// 		n = n->left;
		// 	}
		// 	else if (n == n->parent->left && n->parent == g->right) {
		// 		_rotate_right(n->parent);
		// 		n = n->left;
		// 	}
		// 	_insert_case5(n);
		// }

		// void _insert_case5(node n) {
		// 	node g = _grandparent(n);

		// 	n->parent->color = IS_BLACK;
		// 	g->color = IS_RED;
		// 	if (n == n->parent->left && n->parent == g->left)
		// 		_rotate_right(g);
		// 	else
		// 		_rotate_left(g);
		// }


		// node _insert(node n, key_type key, mapped_type val) {
		// 	if (key < n->pair.first) {
		// 		if (!n->left) {
		// 			n->left = _create_node(key, val, n);
		// 			_insert_case1(n->left);
		// 			return n->left;
		// 		}
		// 		return _insert(n->left, key, val);
		// 	}
		// 	else if (key > n->pair.first) {
		// 		if (!n->right) {
		// 			n->right = _create_node(key, val, n);
		// 			_insert_case1(n->right);
		// 			return n->right;
		// 		}
		// 		return _insert(n->right, key, val);
		// 	}
		// 	return 0;
		// }


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
				// _insert_case1(_map);
				_map->color = IS_BLACK;
				++_size;
				return std::make_pair(iterator(_map), true);
			}
			// else if (_search_node()) {
			// 	return std::make_pair(_search_node(), false);
			// }
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

	/* Operations */



	};
}