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
		typedef typename ft::reverse_iter<value_type>			reverse_iterator;
		typedef typename ft::reverse_iter<const value_type>	const_reverse_iterator;
		typedef std::ptrdiff_t								difference_type;
		typedef size_t										size_type;

	private:
		allocator_type	_alloc;
		pointer			_array;
		size_t			_size;
		size_t			_capacity;

	public:
		explicit vector (const allocator_type& alloc = allocator_type())
		 : _size(0), _capacity(0), _alloc(alloc), _array(NULL) {};

		explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _capacity(n), _size(0) {
			_array = _alloc.allocate(n);
			insert(begin(), n, val);
		}

		template <class InputIterator>
		vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), char (*)[sizeof(*first)] = NULL) : _alloc(alloc), _size(0) {
			size_type n = 0;
			for (InputIterator it=first; it != last; ++it)
				++n;
			_array = _alloc.allocate(n);
			_capacity = n;
			insert(begin(), first, last);
		}

		vector (const vector& x) {*this=x;};

		~vector() {clear();_alloc.deallocate(_array, _capacity);};

		vector& operator=(const vector& obj){
			this->_alloc = obj._alloc;
			this->_capacity = obj._size;
			this->_size = obj._size;
			this->_array = _alloc.allocate(_capacity);
			for (size_type i = 0; i < _size; ++i)
				_alloc.construct(_array + i, obj._array[i]);
			return *this;
		};

	/* Iterators */
		iterator begin() {return _array;}
		const_iterator begin() const {return _array;}
		iterator end() {return _array + _size;}
		const_iterator end() const {return _array + _size;}
		reverse_iterator rbegin() {return _array + _size - 1;}
		const_reverse_iterator rbegin() const {return _array + _size - 1;}
		reverse_iterator rend() {return  _array - 1;}
		const_reverse_iterator rend() const {return  _array - 1;}

	/* Capacity */
		size_t size() const {return _size;}
		size_t max_size() {return _alloc.max_size();}
		void resize(size_type n, value_type val = value_type()) {
			if (n > max_size())
				throw std::out_of_range("vector");
			else if (!n)
				return ;
			else if (n < _size) {
				for (size_type i = 0; n + i < _size; i++)
					_alloc.destroy(_array + n + i);
				_size = n;
			}
			else
				insert(end(), n - _size, val);
		}
		size_t capacity() {return _capacity;}
		bool empty() const {return _size == 0;}
		void reserve (size_type n) {
			if (n <= _capacity)
				return ;
			size_type newCap = n;
			pointer newARR = _alloc.allocate(newCap);
			for (size_type i = 0; i < _size; ++i)
				_alloc.construct(newARR + i, _array[i]);
			_alloc.deallocate(_array, _size);
			_capacity = newCap;
			_array = newARR;
		}

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
		void assign (InputIterator first, InputIterator last, char (*)[sizeof(*first)] = NULL) {
			clear();
			for (; first != last; ++first)
				push_back(*first);
		}
		// fill (2)
		void assign (size_type n, const value_type& val) {
			clear();
			_alloc.deallocate(_array, _capacity);
			_array = _alloc.allocate(n);
			_capacity = n;
			_size = n;
			for (size_type i = 0; i < n; ++i)
				_alloc.construct(_array + i, val);
		}

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
		iterator insert (iterator position, const value_type& val) {
			size_type i=0;
			for (; _array + i != &(*position); ++i); // search pos

			if (_capacity == 0)
				reserve(1);
			else
				reserve((_size + 1 > _capacity) ? _capacity * 2 : _capacity);

			for (size_type k = 0; _array + i != _array + _size - k; ++k) {
				_alloc.construct(_array + _size - k, _array[_size - k - 1]);
				_alloc.destroy(_array + _size - k - 1);
			}
			_alloc.construct(_array + i, val);
			++_size;
			return (position);
		}

		// fill (2)
    	void insert (iterator position, size_type n, const value_type& val) {
			size_type i=0;
			for (; _array + i != &(*position); ++i);

			size_type newCap = _capacity ? _capacity : n;
			while (_size + n > newCap)
				newCap = 2 * _size;

			reserve(newCap);
			if (_size) {
				for (size_type k = 0; _array + i != _array + _size - k; ++k) {
					_alloc.construct(_array + _size + n - k, _array[_size - k - 1]);
					_alloc.destroy(_array + _size - k - 1);
				}
			}
			_size += n;
			while (n--)
				_alloc.construct(_array + i + n, val);// check -1
		}

		// range (3)
		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last, char (*)[sizeof(*first)] = NULL) {
			size_type pos=0;
			for (; _array + pos != &(*position); ++pos);

			size_type n = 0;
			for (InputIterator it=first; it != last; ++it)
				++n;

			size_type newCap = _capacity;
			while (_size + n < newCap)
				newCap *= 2;

			reserve(newCap);
			for (size_type k = 0; _array + pos != _array + _size - k; ++k) {
				_alloc.construct(_array + _size + n - k - 1, _array[_size - k - 1]);
				_alloc.destroy(_array + _size - k - 1);
			}
			_size += n;

			for (size_type i = 0; i < n; ++i) {
				_alloc.construct(_array + pos + i, *first);
				++first;
			}

		}


		iterator erase (iterator position) {
			size_type k=0;
			for (; _array + k != &(*position); ++k);

			for (size_type i = k; _array + i != _array + _size; ++i) {
				_alloc.construct(_array + i, _array[i + 1]);
				_alloc.destroy(_array + i + 1);
			}
			--_size;
			return (iterator(_array + k));
		}

		iterator erase (iterator first, iterator last) {
			size_type k = 0;
			size_type i = 0;
			size_type frst = 0;

			for (; _array + i != &(*first); ++i);
			frst = i;

			for (iterator begin = first; begin != last; ++begin, ++k);

			for (iterator begin = first; begin != last; ++begin, ++i, --_size) {
				_alloc.destroy(_array + i);
				_alloc.construct(_array + i, _array[i + k]);
				_alloc.destroy(_array + i + k);
			}
			return (iterator(_array + frst));
		}


		void swap(vector& x) {
			allocator_type	tmp_alloc = _alloc;
			pointer 		tmp_array = _array;
			size_t			tmp_size = _size;
			size_t			tmp_capacity = _capacity;

			_alloc = x._alloc;
			_array = x._array;
			_size = x._size;
			_capacity = x._capacity;

			x._alloc = tmp_alloc;
			x._array = tmp_array;
			x._size = tmp_size;
			x._capacity = tmp_capacity;
		}

		void clear() {
			if (_array != NULL) {
				for(size_type i=0; i < _size; ++i)
					_alloc.destroy(_array + i);
				_size = 0;	
			}
		}

	};

	/* Non-member function overloads */
	template <class T, class Alloc>
	bool operator==(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
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
	bool operator!=(const vector<T,Alloc>& lhs, vector<T,Alloc>& rhs) {return !(lhs == rhs);}

	template <class T, class Alloc>
	bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
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
	bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {return !(rhs<lhs);}

	template <class T, class Alloc>
	bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {return rhs < lhs;}

	template <class T, class Alloc>
	bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {return !(lhs<rhs);}

	template <class T, class Alloc>
	void swap(vector<T,Alloc>& x, vector<T,Alloc>& y) {x.swap(y);}
	
}

// exception
// reverse_iterator
// check iter in function (return)
// iterator constr copy