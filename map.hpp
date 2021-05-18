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
		typedef Key							key_type;
		typedef T							mapped_type;
		typedef std::pair<const Key, T>		value_type;
		typedef Compare						key_compare;
		typedef Alloc						allocator_type;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		// typedef typename _Rep_type::iterator		 iterator;
		// typedef typename _Rep_type::const_iterator	 const_iterator;
		// typedef typename _Rep_type::reverse_iterator	 reverse_iterator;
		// typedef typename _Rep_type::const_reverse_iterator const_reverse_iterator;
		typedef ptrdiff_t	 difference_type;
		typedef size_t		 size_type;
	private:
		typedef typename allocator_type::template rebind<node_map<T> >::other	alloc_node;

		allocator_type			_alloc;
		alloc_node				_node_alloc;
		node_map<key_type, mapped_type>*	_map;
		node_map<key_type, mapped_type>*	_first;
		node_map<key_type, mapped_type>*	_last;
		size_type				_size;
		key_compare				_comp;

		void	_create_first_node(key_type& key = key_type(), mapped_type& val = mapped_type()) {
			_map = _node_alloc.allocate(1);
			_map->value = _alloc.allocate(1);
			_alloc.construct(_map->value, val);

			_map->left = _first;
			_map->right = _last;
			_first->parent = _map;
			_last->parent = _map;
		}

		class iterator
		{
		private:
			/* data */
		public:
			iterator(/* args */);
			~iterator();
		};
		



	public:
		explicit map (const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) : _size(0) {
				
		}

		~map() {}
	/* Iterators */


	/* Capacity */
	bool empty() const {return !_size;}
	size_type size() const {return _size;}
	size_type max_size() const {return _node_alloc.max_size();}

	/* Element access */

	/* Modifiers */

	std::pair<iterator, bool> insert (const value_type& val) {
		std::pair<node_map<value_type>, bool>	pair;

		if(empty()) {
			_create_first_node(val);
			// pair = std::make_pair(_tree._root, true);
		}
		else {

		}
		

		return std::make_pair(find(val.first), pair.second);
	}



	/* Operations */



	};
}