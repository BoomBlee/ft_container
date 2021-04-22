#pragma once

#include <iostream>
#include <iterator>

template<typename T>
struct Node {
public:
	T*			value;
	Node*		next;
	Node*		prev;
};

template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
struct iterator {
	typedef T			value_type;
	typedef Distance	difference_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
	typedef Category	iterator_category;
};

namespace ft {

	template<typename T>
	class iter : iterator<std::random_access_iterator_tag, T> {
	private:
		T *p;
	public:
		iter() {};
		iter(T* x) : p(x) {}
		iter(const iter& obj) : p(obj.p) {}
		~iter(){}
		bool operator==(const iter<T> &obj) const {return this->p==obj.p;}
		bool operator!=(const iter<T> &obj) const {return this->p!=obj.p;}
		iter& operator++() {++p;return *this;}
		iter operator++(int) {iter tmp(*this); ++p; return tmp;}
		iter& operator--() {--p;return *this;}
		iter operator--(int) {iter tmp(*this); --p; return tmp;}
		T& operator*() const {return *p;}
		bool operator<(const iter& it) const {return this->p < it.p;}
		bool operator>(const iter& it) const {return this->p > it.p;}
		bool operator>=(const iter& it) const {return this->p >= it.p;}
		bool operator<=(const iter& it) const {return this->p <= it.p;}
		// bool operator+=() const {return p+=;}
		T& operator[](int i) const {return p[i];}
		iter& operator=(const T& element) {p=element;return *this;}
		T& operator->() const {return *p;}
	};
	
	template<typename T>
	class iter_list : iterator<std::bidirectional_iterator_tag, T> {
	private:
	public:
		Node<T>*	_p;
		iter_list() {};
		iter_list(Node<T>* x) : _p(x) {}
		iter_list(const iter_list& obj) : _p(obj._p) {}
		~iter_list() {};
		bool operator==(const iter_list<T> &obj) const {return this->_p==obj._p;}
		bool operator!=(const iter_list<T> &obj) const {return this->_p!=obj._p;}
		iter_list& operator++() {_p=_p->next;return *this;}
		iter_list operator++(int) {iter_list<T> tmp(*this); _p=_p->next; return tmp;}
		iter_list& operator--() {_p=_p->prev;return *this;}
		iter_list operator--(int) {iter_list<T> tmp(*this); _p=_p->prev; return tmp;}
		T& operator*() const {return *_p->value;}
		T& operator->() const {return _p->value;}
		iter_list& operator=(const Node<T>& element) {_p=element;return *this;}
	};

	// template<class Iterator>
	// class reverse_iterator : reverse_iterator<iterator>
	// {
	// public:
	// 	typedef Iterator										iterator_type;
	// 	typedef iterator_traits<Iterator>::iterator_caterogy	iterator_category;
	// 	typedef iterator_traits<Iterator>::value_type			value_type;
	// 	typedef iterator_traits<Iterator>::difference_type		difference_type;
	// 	typedef iterator_traits<Iterator>::pointer				pointer;
	// 	typedef iterator_traits<Iterator>::reference			reference;
	// 	reverse_iterator();
	// private:
	// 	pointer p;
	// };

}
