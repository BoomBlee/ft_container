#pragma once

#include <iostream>
#include <iterator>
#include "iterator.hpp"


namespace ft{


	// template<typename T>
	// class iter_list : std::iterator<bidirectional_iterator_tag, T> {
	// private:
	// 	T*	p;
	// public:
	// 	iter_list() {};
	// 	~iter_list() {};
	// };

	template<typename T>
	class list
	{
	public:
		typedef T											value_type;
		typedef std::allocator<value_type>					allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename ft::iter_list<value_type>				iterator;
		typedef typename ft::iter_list<const value_type>			const_iterator;
		// typedef typename iter_list<value_type>				reverse_iterator;
		// typedef typename iter_list<value_type>				const_reverse_iterator;
		typedef ptrdiff_t									difference_type;
		typedef size_t										size_type;
		// typedef typename std::allocator<int>::template rebind<Node<T>>::other	alloc_node;
	private:
		

		typedef typename allocator_type::template rebind<Node<T> >::other	alloc_node;

		allocator_type		_alloc;
		alloc_node			_node_alloc;
		Node<T>*			_list;
		size_type			_size;

		void		_death_node(Node<T>* node) {
			_alloc.destroy(node->value);
			_alloc.deallocate(node->value, 1);
			_node_alloc.deallocate(node, 1);
			--_size;
		}

		Node<T>* _create_node(const value_type& val) {
			value_type*	new_value = _alloc.allocate(1);
			Node<T>*	node = _node_alloc.allocate(1);

			_alloc.construct(new_value, val);

			node->next = node;
			node->prev = node;
			node->value = new_value;
			return node;
		}

		void _swap_node(Node<T>* x, Node<T>* y) {
			Node<T>* tmp;
			tmp = x;
			x = y;
			y = tmp;
			
		}

	public:
		explicit list (const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(0) {
			value_type *new_value = _alloc.allocate(1);

			_alloc.construct(new_value, T());

			_list = _node_alloc.allocate(1);
			_list->next = _list;
			_list->prev = _list;
			_list->value = new_value;
		}

		explicit list (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _alloc(alloc) {}

		template <class InputIterator>
		list (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());

		list (const list& x) {*this=x;}

		~list() {
			// while (_size)
			// 	pop_back();
			// _death_node(_list);
		}

		list& operator= (const list& x) {
			this->_alloc = x._alloc;
			this->_size = x._size;
			this->_node_alloc = x._node_alloc;
			this->_list = x._list;
			return *this;
		}

	/* Iterators */
		iterator begin() {return iterator(_list->next);}
		const_iterator begin() const {return const_iterator(_list->next);}
		iterator end() {return iterator(_list);}
		const_iterator end() const {return const_iterator(_list);}
		// reverse_iterator rbegin() {}
		// const_reverse_iterator rbegin() const {}
		// reverse_iterator rend() {}
		// const_reverse_iterator rend() const {}
	/* Capacity */
		bool empty() const {return !_size;}
		size_type size() const {return _size;}
		size_type max_size() const {return _node_alloc.max_size();}
	/* Element access */
		reference front() {return *_list->next->value;}
		const_reference front() const {return *_list->next->value;}
		reference back() {return *_list->prev->value;}
		const_reference back() const {return *_list->prev->value;}
	/* Modifiers */

		// range (1)
		// template <class InputIterator>
		// void assign (InputIterator first, InputIterator last) {
		// 	while (_size)
		// 		pop_back();
		// 	// insert(begin(), first, last);
		// }

		// fill (2)
		void assign (size_type n, const value_type& val) {
			clear();
			while (n--)
				push_back(val);
		}

		void push_back (const value_type& val) {
			value_type*	new_value = _alloc.allocate(1);
			Node<T>*	node = _node_alloc.allocate(1);

			_alloc.construct(new_value, val);

			_list->prev->next = node;
			node->next = _list;
			node->prev = _list->prev;
			node->value = new_value;
			_list->prev = node;
			++_size;
		}

		void pop_back() {
			_list->prev->prev->next = _list;
			_death_node(_list->prev);
			_list->prev = _list->prev->prev;
			--_size;
		}

		void push_front (const value_type& val) {
			value_type*	new_value = _alloc.allocate(1);
			Node<T>*		node = _node_alloc.allocate(1);;

			_alloc.construct(new_value, val);

			_list->next->prev = node;
			node->next = _list->next;
			node->prev = _list;
			node->value = new_value;
			_list->next = node;
			++_size;
		}

		void pop_front() {
			_list->next->next->prev = _list;
			_death_node(_list->next);
			_list->next = _list->next->next;
			--_size;
		}

		// single element (1)
		iterator insert (iterator position, const value_type& val) {
			Node<T>*		node = _create_node(val);

			Node<T>*	tmp = position._p;

			node->prev = tmp->prev;
			tmp->prev->next = node;
			node->next = tmp;
			tmp->prev = node;

			++_size;
			return position;
		}

		// fill (2)	
		void insert (iterator position, size_type n, const value_type& val) {
			while (n--)
				insert(position, val);
			
		}

		// range (3)
		template <class InputIterator>
    	void insert (iterator position, InputIterator first, InputIterator last, char (*)[sizeof(*first)] = NULL) {
			for (int i=0; first != last && i < 10; ++first, ++i)
				insert(position, *first);
		}

		iterator erase (iterator position) {
			Node<T>* node = position._p;

			node->prev->next = node->next;
			node->next->prev = node->prev;
			_death_node(node);
			return position;
		}

		iterator erase (iterator first, iterator last) {
			for (; first != last; ++first)
				erase(first);
			return first;
		}

		void swap (list& x) {
			Node<T>* tmp = _list;
			_list = x._list;
			x._list = tmp;
		}

		void resize (size_type n, value_type val = value_type()) {
				if (_size > n)
					while (_size > n)
						pop_back();
				else
					insert(end(), n - _size, val);
		}

		void clear() {
			while (_size)
				pop_back();
			_list->next = _list;
			_list->prev = _list;
		}
	/* Operations */

		// entire list (1)
		void splice (iterator position, list& x) {
			insert(position, x.begin(), x.end());
		}

		// single element (2)
		void splice (iterator position, list& x, iterator i) {
			iterator it = x.begin();
			for (iterator ite = x.end(); it != ite; ++it)
				if (it == i) {
					insert(position, i._p->value);
					break ;
				}
		}

		// element range (3)
		void splice (iterator position, list& x, iterator first, iterator last) {
			iterator it = first;
			iterator tmp = position;
			for (iterator ite = last; it!=ite; ++it)
				insert(tmp++, it._p->value);
		}

		void remove (const value_type& val) {
		iterator it = begin();
		for (iterator ite = end(); it!=ite; ++it)
			if (*it == val)
				erase(it);
		}

		template <class Predicate>
		void remove_if (Predicate pred) {
			iterator it = begin();
			for (iterator ite = end(); it!=ite; ++it)
				if (pred(*it))
					erase(it);
		}

		void sort() {
			Node<T>* list = _list->next;
			Node<T>* tmp_node;

			for (; list != _list->prev; list = list->next) {
				tmp_node = list->next;
				for (value_type temp; tmp_node != _list; tmp_node = tmp_node->next)
					if (*list->value > *tmp_node->value) {
						temp = *list->value;
						*list->value = *tmp_node->value;
						*tmp_node->value = temp;
					}
			}
		}

		template <class Compare>
		void sort(Compare comp) {
			Node<T>* list = _list->next;
			Node<T>* tmp_node;

			for (; list != _list->prev; list = list->next) {
				tmp_node = list->next;
				for (value_type temp; tmp_node != _list; tmp_node = tmp_node->next)
					if (comp(*list->value, *tmp_node->value)) {
						temp = *list->value;
						*list->value = *tmp_node->value;
						*tmp_node->value = temp;
					}
			}
		}



		void reverse() {
			_swap_node(_list->next, _list->prev);
			for (Node<T>* list=_list->prev; list != _list; list = list->prev)
				_swap_node(_list->next, _list->prev);
		}

	};
}

// insert (3)