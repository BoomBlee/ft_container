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
		typedef typename allocator_type::template rebind<node>::other	alloc_node;

		allocator_type			_alloc;
		alloc_node				_node_alloc;
		node					_map;
		size_type				_size;
		key_compare				_comp;

		node	_create_node(key_type key = key_type(), mapped_type val = mapped_type(), node parent = NULL, bool color = IS_BLACK) {
			node new_node = new node_map<key_type, mapped_type>();
			
			new_node->pair = std::make_pair(key, val);
			new_node->right = 0;
			new_node->left = 0;
			new_node->parent = parent;
			new_node->is_red = color;
			return new_node;
		}

		node _insert(node n, key_type key, mapped_type val) {
			if (key < n->pair.first) {
				if (!n->left) {
					n->left = _create_node(key, val, n, IS_RED);
					//balance
					return n->left;
				}
				return _insert(n->left, key, val);
			}
			else if (key > n->pair.first) {
				if (!n->right) {
					n->right = _create_node(key, val, n);
					//balance
					return n->right;
				}
				return _insert(n->right, key, val);
			}
			return 0;
		}


	public:
		explicit map (const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) : _size(0) {
				
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
				if(!tmp->right) {
					break ;
				}
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
				++_size;
				return std::make_pair(iterator(_map), true);
			}
			// else {
			// 	_insert(_map, val.first, val.second);
			// }
			// else if () find node
			++_size;
			return std::make_pair(iterator(_insert(_map, val.first, val.second)), true);
		}



	/* Operations */



	};
}