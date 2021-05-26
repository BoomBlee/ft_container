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
			value_type* new_pair = _alloc.allocate(1);
			_alloc.construct(new_pair, std::make_pair(key, val));

			new_node->pair = new_pair;
			new_node->right = 0;
			new_node->left = 0;
			new_node->parent = parent;
			new_node->color = IS_RED;
			return new_node;
		}

		iterator _search_node(const key_type& key, const node n) const {
			if (key == n->pair->first) {
				return iterator(n);
			}
			else if (key < n->pair->first) {
				if (!n->left) {
					return iterator(end());
				}
				return _search_node(key, n->left);
			}
			else {
				if (!n->right) {
					return iterator(end());
				}
				return _search_node(key, n->right);
			}
			return iterator(end());


			// for (iterator it = begin(); it != end(); ++it) {
			// 	if (it._p->pair->first == key) {
			// 		return it;
			// 	}
			// }
			// return NULL;
		}

		node _insert(node n, key_type key, mapped_type val) {
			node ret;
			if (key < n->pair->first) {
				if (!n->left) {
					n->left = _create_node(key, val, n);
					ret = n->left;
					_balance(n->left);
					return ret;
				}
				ret = _insert(n->left, key, val);
				return ret;
			}
			else if (key > n->pair->first) {
				if (!n->right) {
					n->right = _create_node(key, val, n);
					ret = n->right;
					_balance(n->right);
					return ret;
				}
				ret = _insert(n->right, key, val);
				return ret;
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
					if (p->right)
						p->right->parent = g;
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
					p->left = n->right;
					if (p->left)
						p->left->parent = p;
					n->right = p;
					p->parent = n;
					_balance(p);
					return ;
				}
				else { // (g->left == p && p->right == n)
					g->left = n;
					n->parent = g;
					p->right = n->left;
					if (p->right)
						p->right->parent = p;
					n->left = p;
					p->parent = n;
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

		node _brother(node n) {
			if (_right_child(n)) {
				return n->parent->left;
			}
			return n->parent->right;
		}

		void _del_max_left(node n) {
			node del = n->left;

			while (del->right) {
				del = del->right;
			}
			if (_right_child(n))
				n->parent->right = del;
			else
				n->parent->left = del;
			ft::swap(del, n);
			// ft::swap(del->left, n->left);
			// ft::swap(del->right, n->right);
			// ft::swap(del->parent, n->left);
			ft::swap(n->color, del->color);
			ft::swap(n->pair, del->pair);
			// if (n->parent == del) {
			// 	n->parent->left = NULL;
			// }

			_select_delete(n);
		}

		bool _right_child(node n) {
			return n->parent->right == n;
		}

		void _del_red_node_without_child(node n) {
			if (_right_child(n)) {
				n->parent->right = NULL;
			}
			else {
				n->parent->left = NULL;
			}
			// if (n && !(!n->left && !n->right && !n->parent))
				n = _delete_node(n);
			// _node_pointer_null(n);
		}

		void _del_black_node_with_one_child(node n) {
			if (n->left) {
				ft::swap(n->left->pair, n->pair); //ft::swap(n->left, n);
				_del_red_node_without_child(n->left);
			}
			else {
				ft::swap(n->right->pair, n->pair);
				_del_red_node_without_child(n->right);
			}
		}

		void _balance_black_node_without_child(node n) {//TODO
			if (!n->parent) {
				return ;
			}

			if (n->parent->color == IS_RED) {
				_balance_black_node_without_child_parent_red(n);
			}
			else {
				_balance_black_node_without_child_parent_black(n);
			}
			// if (n && !(!n->left && !n->right && !n->parent))
				n = _delete_node(n);
			// _node_pointer_null(n);
		}

		void _balance_black_node_without_child_parent_red(node n) {
			node b = _brother(n);

			if (b->color == IS_BLACK && (!b->left || b->left->color == IS_BLACK) && (!b->right || b->right->color == IS_BLACK)) {
				_balance_rb1(n);
			}
			else if (b->color == IS_BLACK && ((b->left && b->left->color == IS_RED) || (b->right && b->right->color == IS_RED))) {
				_balance_rb2(n);
			}
		}

		void _balance_black_node_without_child_parent_black(node n) {
			node b = _brother(n);

			if (b && b->color == IS_RED) {
				_balance_brother_red(n, b);
			}
			else {
				_balance_brother_black(n, b);
			}
		}

		void _balance_brother_red(node n, node b) { //TODO
			if (_right_child(n)) {
				if (b && b->right && b->right->left && b->right->left->color == IS_RED) {
					_balance_br4(n);
				}
				else {
					_balance_br3(n);
				}
			}
			else {
				if (b && b->left && b->left->right && b->left->right->color == IS_RED) {
					_balance_br4(n);
				}
				else {
					_balance_br3(n);
				}
			}
		}

		void _balance_brother_black(node n, node b) {//TODO
			if (_right_child(n)) {
				if (b && b->right && b->right->color == IS_RED) {
					_balance_bb5(n);
				}
				else {
					_balance_bb6(n);
				}
			}
			else {
				if (b && b->left && b->left->color == IS_RED) {
					_balance_bb5(n);
				}
				else {
					_balance_bb6(n);
				}
			}
		}

		void _balance_rb1(node del) {
			if (_right_child(del)) {
				ft::swap(del->parent->color, del->parent->left->color);
				del->parent->right = NULL;
			}
			else {
				ft::swap(del->parent->color, del->parent->right->color);
				del->parent->left = NULL;
			}
		}

		void _balance_rb2(node del) {
			node p = del->parent;
			node b;

			if (_right_child(del)) {
				b = p->left;
				p->left = b->right;
				if (b->right)
					b->right->parent = p;
				b->right = p;
				if (_right_child(p))
					p->parent->right = b;
				else
					p->parent->left = b;
				b->parent = p->parent;
				p->parent = b;
				p->color = IS_BLACK;
				b->color = IS_RED;
				b->left->color = IS_BLACK;
				p->right = NULL;
			}
			else {
				b = p->right;
				p->right = b->left;
				if (b->left)
					b->left->parent = p;
				b->left = p;
				if (_right_child(p))
					p->parent->right = b;
				else
					p->parent->left = b;
				b->parent = p->parent;
				p->parent = b;
				p->color = IS_BLACK;
				b->color = IS_RED;
				b->right->color = IS_BLACK;
				p->left = NULL;
			}
		}

		void _balance_br3(node del) {
			node p = del->parent;
			node b;
			node n; // nephew

			if (_right_child(del)) {
				b = p->left;
				n = b->right;
				b->right = p;
				b->parent = p->parent;
				p->parent = b;
				if (n) {
					n->parent = p;
					p->left = n;
				}
			}
			else {
				b = p->right;
				n = b->left;
				b->left = p;
				b->parent = p->parent;
				p->parent = b;
				if (n) {
					n->parent = p;
					p->right = n;
				}
			}
		}

		void _balance_br4(node del) {
			node p = del->parent;
			node b = _brother(del);
			node n; // nephew
			node gn;// grandnephew

			if (_right_child(del)) {
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
			node b = _brother(del);
			node n;
			node gn;

			if (_right_child(del)) {
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
			node b = _brother(del);

			if (b)
				b->color = IS_RED;
			_balance_black_node_without_child(del);
		}


		void _select_delete(node del) {
			if (del->color == IS_RED) {
				if (del->left && del->right) {
					_del_max_left(del);
				}
				else {
					_del_red_node_without_child(del);
				}
			}
			else {
				if (del->left && del->right) {
					_del_max_left(del);
				}
				else if (del->left || del->right) {
					_del_black_node_with_one_child(del);
				}
				else {
					_balance_black_node_without_child(del);
				}
			}
		}

		node _delete_node(node del) {
			--_size;
			_alloc.destroy(del->pair);
			_alloc.deallocate(del->pair, 1);
			_node_pointer_null(del);
			_node_alloc.deallocate(del, 1);
			return NULL;
		}

		void _node_pointer_null(node n) {
			n->parent = NULL;
			n->left = NULL;
			n->right = NULL;
		}

	public:
		explicit map (const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) : _size(0), _comp(comp), _alloc(alloc) {}

		template <class InputIterator>
		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) :_size(0), _comp(comp), _alloc(alloc) {
				insert(first, last);
		}

		map (const map& x) :
			_size(x._size), _alloc(x._alloc), _node_alloc(x._node_alloc), _map(x._map), _comp(x._comp) {}

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

		iterator end() const {//delete const
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
		mapped_type& operator[] (const key_type& k) {
			for (iterator it = begin(); it != end(); ++it) {
				if (it._p->pair->first == k) {
					return it._p->pair->second;
				}
			}
			return NULL;
		}

	/* Modifiers */
		std::pair<iterator, bool> insert (const value_type& val) {
			if(empty()) {
				_map = _create_node(val.first, val.second);
				_map->color = IS_BLACK;
				++_size;
				return std::make_pair(iterator(_map), true);
			}
			else if (_search_node(val.first, _map) != end()) {
				iterator it = _search_node(val.first, _map);
				it._p->pair->second = val.second;
				return std::make_pair(it, false);
			}
			++_size;
			return std::make_pair(iterator(_insert(_map, val.first, val.second)), true);
		}

		iterator insert (iterator position, const value_type& val) {
			iterator it;
			if(empty()) {
				_map = _create_node(val.first, val.second);
				_map->color = IS_BLACK;
				++_size;
				return iterator(_map);
			}
			else if (_search_node(val.first, _map) != end()) {
				iterator it = _search_node(val.first, _map);
				it._p->pair->second = val.second;
				return it;
			}
			++_size;
			it = iterator(_insert(_map, val.first, val.second));
			return it;
		}

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last) {
			for (InputIterator it = first; it != last; ++it) {
				insert(*it);
			}
		}

		void erase (iterator position) {
			node del = position._p;

			if (!del)
				return ;

			_select_delete(del);
			// _delete_node(position._p);
		}

		size_type erase(const key_type& k) {
			iterator it = _search_node(k, _map);

			if (it != end()) {
				erase(it);
				return 1;
			}
			return 0;
		}

		void erase(iterator first, iterator last) {
			for (iterator it = first; it != last; ++it) {
				erase(it);
			}
		}

		void swap(map& x) {
			ft::swap(x, *this);
		}

		void clear() {
			for (iterator it = begin(); it != end(); ++it) {
				erase(it);
			}
		}

	/* Operations */
		iterator find(const key_type& k) {
			iterator it = begin();
			for (iterator ite = end(); it != ite; ++it) {
				if (it._p->pair->first == k) {
					break ;
				}
			}
			return it;
		}

		// const_iterator find(const key_type& k) {
		// 	const_iterator it = begin();
		// 	for (const_iterator ite = end(); it != ite; ++it) {
		// 		if (it._p->pair.first == k) {
		// 			break ;
		// 		}
		// 	}
		// 	return it;
		// }

		size_type count(const key_type& k) const {
			if (_search_node(k, _map) != end())
				return 1;
			return 0;
		}
	};
}