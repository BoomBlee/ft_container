#pragma once

#include "iterator.hpp"


namespace ft {


	// template<typename T>
	// class iter_list : std::iterator<bidirectional_iterator_tag, T> {
	// private:
	// 	T*	p;
	// public:
	// 	iter_list() {};
	// 	~iter_list() {};
	// };

	template<typename T, class Alloc = std::allocator<T> >
	class list
	{
	public:
		typedef T											value_type;
		typedef std::allocator<value_type>					allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename ft::iter_list<value_type>			iterator;
		typedef typename ft::const_iter_list<value_type>	const_iterator;
		typedef typename ft::reverse_iter_list<value_type>				reverse_iterator;
		typedef typename ft::reverse_iter_list<const value_type>				const_reverse_iterator;
		typedef std::ptrdiff_t									difference_type;
		typedef size_t										size_type;
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

		void _create_first_node() {
			value_type *new_value = _alloc.allocate(1);

			_alloc.construct(new_value, T());

			_list = _node_alloc.allocate(1);
			_list->next = _list;
			_list->prev = _list;
			_list->value = new_value;
		}

	public:
		explicit list (const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(0) {
			_create_first_node();
		}

		explicit list (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(0) {
			_create_first_node();
			insert(begin(), n, val);
		}

		template <class InputIterator>
		list (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), char (*)[sizeof(*first)] = NULL) : _alloc(alloc), _size(0) {
			_create_first_node();
			insert(this->begin(), first, last);
		}

		list (const list& x) : _size(0) {*this=x;}

		~list() {
			for (Node<T>* tmp = _list->prev; tmp != _list; tmp = tmp->prev)
				_death_node(tmp);
			_death_node(_list);
		}

		list& operator= (const list& x) {
			this->_alloc = x._alloc;
			this->_node_alloc = x._node_alloc;
			_create_first_node();
			for (Node<T>* tmp = x._list->prev; tmp != x._list; tmp = tmp->prev)
				insert(this->begin(), *tmp->value);
			return *this;
		}

	/* Iterators */
		iterator begin() {return iterator(_list->next);}
		const_iterator begin() const {return const_iterator(_list->next);}
		iterator end() {return iterator(_list);}
		const_iterator end() const {return const_iterator(_list);}
		reverse_iterator rbegin() {return reverse_iterator(_list->prev);}
		const_reverse_iterator rbegin() const {return const_reverse_iterator(_list->prev);}
		reverse_iterator rend() {return reverse_iterator(_list);}
		const_reverse_iterator rend() const {return const_reverse_iterator(_list);}
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
		template <class InputIterator>
		void assign (InputIterator first, InputIterator last) {
			clear();
			insert(begin(), first, last);
		}

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
			Node<T>*		node = _node_alloc.allocate(1);

			_alloc.construct(new_value, val);

			_list->next->prev = node;
			node->next = _list->next;
			node->prev = _list;
			node->value = new_value;
			_list->next = node;
			++_size;
		}

		void pop_front() {
			Node<T>* tmp = _list->next->next;
			_list->next->next->prev = _list;
			_death_node(_list->next);
			_list->next = tmp;
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
			return --position;
		}

		// fill (2)	
		void insert (iterator position, size_type n, const value_type& val) {
			while (n--)
				insert(position, val);
			
		}

		// range (3)
		template <class InputIterator>
    	void insert (iterator position, InputIterator first, InputIterator last, char (*)[sizeof(*first)] = NULL) {
			while (first != last)
				insert(position, *(first++));
		}

		iterator erase (iterator position) {
			Node<T>* node = position._p;
			Node<T>* tmp = node->next;

			node->prev->next = node->next;
			node->next->prev = node->prev;
			_death_node(node);
			--_size;
			return iterator(tmp);
		}

		iterator erase (iterator first, iterator last) {
			Node<T>* begin = first._p;
			Node<T>* end = last._p;
			Node<T>* tmp;

			begin->prev->next = end;
			end->prev = begin->prev;
			while (begin != end) {
				tmp = begin;
				begin = begin->next;
				_death_node(tmp);
				--_size;
			}
			return last;
		}

		void swap (list& x) {
			Node<T>* tmp = _list;
			_list = x._list;
			x._list = tmp;
			size_type tmp_size = this->_size;
			this->_size = x._size;
			x._size = tmp_size;
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
		Node<value_type>* tmp = position._p;

		tmp->prev->next = x._list->next;
		x._list->next->prev = tmp->prev;

		tmp->prev = x._list->prev;
		x._list->prev->next = tmp;

		x._list->next = x._list;
		x._list->prev = x._list;

		_size += x._size;
		x._size = 0;
		}

		// single element (2)
		void splice (iterator position, list& x, iterator i) {
			Node<T>* tmp = position._p;
			Node<T>* node = i._p;

			node->prev->next = node->next;
			node->next->prev = node->prev;

			tmp->prev->next = node;
			node->prev = tmp->prev;

			node->next = tmp;
			tmp->prev = node;
			++_size;
			--x._size;
		}

		// element range (3)
		void splice (iterator position, list& x, iterator first, iterator last) {
			Node<T>*	position_node = position._p;
			Node<T>*	first_node = first._p;
			Node<T>*	last_node = last._p;
			Node<T>*	new_last_node = last_node->prev;
			size_type	i = 0;

			for (iterator begin = first; begin != last; ++begin, ++i);

			first_node->prev->next = last_node;
			last_node->prev = first_node->prev;

			position_node->prev->next = first_node;
			first_node->prev = position_node->prev;

			position_node->prev = new_last_node;
			new_last_node->next = position_node;

			_size += i;
			x._size -= i;
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

		void unique() {
			iterator first = begin();
			iterator last = end();
			if (first == last)
				return ;
			iterator next = first;
			while (++next != last) {
				if (*first == *next) {
					erase(next);
				}
				else
					first = next;
				next = first;
			}
		}

		template <class BinaryPredicate>
		void unique (BinaryPredicate binary_pred) {
			iterator first = begin();
			iterator last = end();
			if (first == last)
				return ;

			iterator next = first;
      		while (++next != last) {
				if (binary_pred(*first,*next)) {
					erase(next);
				}
				else
					first = next;
				next = first;
			}
		}

		void merge (list& x) {
			iterator first1 = begin();
			iterator last1 = end();
			iterator first2 = x.begin();
			iterator last2 = x.end();

			while (first1 != last1 && first2 != last2) {
				if (*first2 < *first1) {
					insert(first1, *first2);
					first2 = x.erase(first2);
				}
				else {
					++first1;
				}
			}
		}

		template <class Compare>
		void merge (list& x, Compare comp) {
			iterator first1 = begin();
			iterator last1 = end();
			iterator first2 = x.begin();
			iterator last2 = x.end();

			while (first1 != last1 && first2 != last2) {
				if (comp(*first2, *first1)) {
					insert(first1, *first2);
					first2 = x.erase(first2);
				}
				else {
					++first1;
				}
			}
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
					if (!comp(*list->value, *tmp_node->value)) {
						temp = *list->value;
						*list->value = *tmp_node->value;
						*tmp_node->value = temp;
					}
			}
		}

		void reverse() {
			Node<T>* tmp = _list->next;
			Node<T>* list=_list->next;

			_list->next = _list->prev;
			_list->prev = tmp;

			for (; list != _list; list = tmp) {
				tmp = list->next;
				list->next = list->prev;
				list->prev = tmp;
			}
		}

	};
	
	/* Non-member function overloads */
	template <class T, class Alloc>
	bool operator==(const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs) {
		if (lhs.size() != rhs.size())
			return (false);
		typename ft::list<T>::const_iterator it1 = lhs.begin();
		typename ft::list<T>::const_iterator ite1 = lhs.end();
		typename ft::list<T>::const_iterator it2 = rhs.begin();
		typename ft::list<T>::const_iterator ite2 = rhs.end();

		for (;it1 != ite1; ++it1, ++it2)
			if (it2 == ite2 || *it1 != *it2)
				return false;
		return true;
	}
	template <class T, class Alloc>
	bool operator!=(const list<T,Alloc>& lhs, list<T,Alloc>& rhs) {return !(lhs == rhs);}

	template <class T, class Alloc>
	bool operator<(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
		typename ft::list<T>::const_iterator it1 = lhs.begin();
		typename ft::list<T>::const_iterator ite1 = lhs.end();
		typename ft::list<T>::const_iterator it2 = rhs.begin();
		typename ft::list<T>::const_iterator ite2 = rhs.end();

		for (;it1!=ite1; ++it1, ++it2)
			if (it2==ite2 || *it2<*it1) return false;
			else if (*it1<*it2) return true;
		return (it2!=ite2);
	}

	template <class T, class Alloc>
	bool operator<=(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {return !(rhs<lhs);}

	template <class T, class Alloc>
	bool operator>(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {return rhs < lhs;}

	template <class T, class Alloc>
	bool operator>=(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {return !(lhs<rhs);}

	template <class T, class Alloc>
	void swap(list<T,Alloc>& x, list<T,Alloc>& y) {x.swap(y);}

}
