#pragma once

#include <iostream>
#include "iterator.hpp"

namespace ft {
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
	public:
		typedef T											value_type;
		typedef std::allocator<value_type>					allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename ft::iter<value_type>				iterator;
		typedef typename ft::iter<const value_type>			const_iterator;
		// typedef typename reverse_iterator<iterator>			reverse_iterator; //
		// typedef typename reverse_iterator<const_iterator>	const_reverse_iterator; //
		typedef ptrdiff_t									difference_type;
		typedef size_t										size_type;

		vector (const allocator_type& alloc = allocator_type())
		 : _size(0), _capacity(0), _alloc(alloc), _array(nullptr) {};

		~vector() {};
		vector& operator=(const vector& obj){};

	/* Iterators */
		iterator begin() {return _array;}
		const_iterator begin() const {return _array;}
		iterator end() {return _array + _size;}
		const_iterator end() const {return _array + _size;}
		// reverse_iterator rbegin() {return ;} // ?
		// const_reverse_iterator rbegin() {return ;}
		// reverse_iterator rend() {return ;}
		// const_reverse_iterator rend() {return ;}

	/* Capacity */
		size_t size() const {return _size;}
		size_t max_size() {return _alloc.max_size();}
		void resize() {}
		size_t capacity() {return _capacity;}
		bool empty() const {return _size == 0;}
		// reserve() {}

	/* Element access */
		value_type& operator[](const size_t& index) const {return _array[index];}
		value_type& at(const size_t& index) const {
				if (index < 0 || index >= _size)
					throw std::out_of_range("vector");
				return _array[index];
			}
		value_type& front() { return _array[0];}
		value_type& back() {return _array[_size-1];}

	/* Modifiers */

		// range (1)
		template <class InputIterator>
		void assign (InputIterator first, InputIterator last);
		// fill (2)
		void assign (size_type n, const value_type& val);

		void push_back(const value_type& val) {
			if (_capacity == 0){
				_array = _alloc.allocate(1);
				_alloc.construct(_array, val);
				_size = 1;
				_capacity = 1;
			} else {
				size_type newCap = (_size + 1 > _capacity) ? _size * 2 : _capacity;
				pointer newARR = _alloc.allocate(newCap);
				for (size_type i = 0; i < _size; ++i)
					_alloc.construct(newARR + i, _array[i]);
				_alloc.deallocate(_array, _size);
				_capacity = newCap;
				_array = newARR;
				_alloc.construct(_array + _size, val);
				++_size;
			}
		}
		void pop_back() {
			_alloc.destroy(&this->back());
			--_size;
		}

		// single element (1)
		iterator insert (iterator position, const value_type& val) {position.p=val;return position;};

		// fill (2)
    	void insert (iterator position, size_type n, const value_type& val);

		// range (3)
		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last);


		iterator erase (iterator position);

		iterator erase (iterator first, iterator last);


		void swap(vector& x) {}

		void clear() {}

	


	private:
		allocator_type	_alloc;
		pointer			_array;
		size_t			_size;
		size_t			_capacity;
	};

	/* Non-member function overloads */
	template <class T, class Alloc>
	bool operator== (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
		if (lhs.size() != rhs.size())
			return (false);
		typename ft::vector<T>::const_iterator it1 = lhs.begin();
		typename ft::vector<T>::const_iterator ite1 = lhs.end();
		typename ft::vector<T>::const_iterator it2 = rhs.begin();
		typename ft::vector<T>::const_iterator ite2 = rhs.end();

		for (;it1 != ite1; ++it1, ++it2)
			if (it2 == ite2 || *it1 != *it2)
				return false;
		return true;
	}
	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, vector<T,Alloc>& rhs) {return !(lhs == rhs);}

	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		typename ft::vector<T>::const_iterator it1 = lhs.begin();
		typename ft::vector<T>::const_iterator ite1 = lhs.end();
		typename ft::vector<T>::const_iterator it2 = rhs.begin();
		typename ft::vector<T>::const_iterator ite2 = rhs.end();

		for (;it1!=ite1; ++it1, ++it2)
			if (it2==ite2 || *it2<*it1) return false;
			else if (*it1<*it2) return true;
		return (it2!=ite2);
	}

	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {return !(rhs<lhs);}

	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {return rhs < lhs;}

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {return !(lhs<rhs);}
}