#pragma once

#include <iostream>
#include <iterator>

#define IS_RED true
#define IS_BLACK false

template<typename T>
struct Node {
public:
	T*			value;
	Node*		next;
	Node*		prev;
};

template<typename Key, typename T>
struct node_map {
public:
	std::pair<Key, T>	pair;
	node_map*			parent;
	node_map*			left;
	node_map*			right;
	bool				is_red;
};

template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
struct iterator {
	typedef T			value_type;
	typedef Distance	difference_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
	typedef Category	iterator_category;
};

namespace ft {

	template<typename T>
	class iter {
	private:
		T *p;
	public:
		iter() {};
		iter(T* x) : p(x) {}
		iter(const iter& obj) : p(obj.p) {}
		~iter() {}
		bool operator==(const iter<T> &obj) const {return this->p == obj.p;}
		bool operator!=(const iter<T> &obj) const {return this->p != obj.p;}
		iter& operator++() {++p; return *this;}
		iter operator++(int) {iter tmp(*this); ++p; return tmp;}
		iter& operator--() {--p; return *this;}
		iter operator--(int) {iter tmp(*this); --p; return tmp;}
		T& operator*() const {return *p;}
		bool operator<(const iter& it) const {return this->p < it.p;}
		bool operator>(const iter& it) const {return this->p > it.p;}
		bool operator>=(const iter& it) const {return this->p >= it.p;}
		bool operator<=(const iter& it) const {return this->p <= it.p;}
		T& operator[](size_t i) const {return p[i];}
		iter& operator=(const T& element) {p =element;return *this;}
		T* operator->() const {return p;}
		iter operator+(int n) {p += n; return *this;}
		iter operator-(int n) {p -= n; return *this;}
		iter& operator+=(std::ptrdiff_t n) { p += n; return *this;}
		iter& operator-=(std::ptrdiff_t n) { p -= n; return *this;}
	};

	template<typename T>	
	class reverse_iter {
	private:
		T *p;
	public:
		reverse_iter() {};
		reverse_iter(T* x) : p(x) {}
		reverse_iter(const reverse_iter& obj) : p(obj.p) {}
		~reverse_iter() {}
		bool operator==(const reverse_iter<T> &obj) const {return this->p == obj.p;}
		bool operator!=(const reverse_iter<T> &obj) const {return this->p != obj.p;}
		reverse_iter& operator++() {--p; return *this;}
		reverse_iter operator++(int) {reverse_iter tmp(*this); --p; return tmp;}
		reverse_iter& operator--() {++p; return *this;}
		reverse_iter operator--(int) {reverse_iter tmp(*this); ++p; return tmp;}
		T& operator*() const {return *p;}
		bool operator<(const reverse_iter& it) const {return this->p < it.p;}
		bool operator>(const reverse_iter& it) const {return this->p > it.p;}
		bool operator>=(const reverse_iter& it) const {return this->p >= it.p;}
		bool operator<=(const reverse_iter& it) const {return this->p <= it.p;}
		T& operator[](size_t i) const {return p[-i];}
		reverse_iter& operator=(const T& element) {p = element;return *this;}
		T* operator->() const {return p;}
		reverse_iter operator+(int n) {p -= n; return *this;}
		reverse_iter operator-(int n) {p += n; return *this;}
		reverse_iter& operator+=(std::ptrdiff_t n) { p -= n; return *this;}
		reverse_iter& operator-=(std::ptrdiff_t n) { p += n; return *this;}
	};

	template<typename T>
	class iter_list {
	public:
		Node<T>*	_p;
		iter_list() {};
		iter_list(Node<T>* x) : _p(x) {}
		iter_list(const iter_list& obj) : _p(obj._p) {}
		~iter_list() {};
		bool operator==(const iter_list<T> &obj) const {return this->_p == obj._p;}
		bool operator!=(const iter_list<T> &obj) const {return this->_p != obj._p;}
		iter_list& operator++() {_p = _p->next; return *this;}
		iter_list operator++(int) {iter_list<T> tmp(*this); _p = _p->next; return tmp;}
		iter_list& operator--() {_p = _p->prev; return *this;}
		iter_list operator--(int) {iter_list<T> tmp(*this); _p = _p->prev; return tmp;}
		T& operator*() const {return *_p->value;}
		T* operator->() const {return _p->value;}
		iter_list& operator=(const Node<T>& element) {_p = element; return *this;}
	};

	template<typename T>
	class const_iter_list {
	public:
		const Node<T>*	_p;
		const_iter_list() {};
		const_iter_list(Node<T>* x) : _p(x) {}
		const_iter_list(const const_iter_list& obj) : _p(obj._p) {}
		~const_iter_list() {};
		bool operator==(const const_iter_list<T> &obj) const {return this->_p == obj._p;}
		bool operator!=(const const_iter_list<T> &obj) const {return this->_p != obj._p;}
		const_iter_list& operator++() {_p = _p->next; return *this;}
		const_iter_list operator++(int) {const_iter_list<T> tmp(*this); _p = _p->next; return tmp;}
		const_iter_list& operator--() {_p = _p->prev; return *this;}
		const_iter_list operator--(int) {const_iter_list<T> tmp(*this); _p = _p->prev; return tmp;}
		T& operator*() const {return *_p->value;}
		T* operator->() const {return _p->value;}
		const_iter_list& operator=(const Node<T>& element) {_p = element; return *this;}
	};

	template<typename T>
	class reverse_iter_list {
	public:
		Node<T>*	_p;
		reverse_iter_list() {};
		reverse_iter_list(Node<T>* x) : _p(x) {}
		reverse_iter_list(const reverse_iter_list& obj) : _p(obj._p) {}
		~reverse_iter_list() {};
		bool operator==(const reverse_iter_list<T> &obj) const {return this->_p == obj._p;}
		bool operator!=(const reverse_iter_list<T> &obj) const {return this->_p != obj._p;}
		reverse_iter_list& operator++() {_p = _p->prev; return *this;}
		reverse_iter_list operator++(int) {reverse_iter_list<T> tmp(*this); _p = _p->prev; return tmp;}
		reverse_iter_list& operator--() {_p = _p->next; return *this;}
		reverse_iter_list operator--(int) {reverse_iter_list<T> tmp(*this); _p = _p->next; return tmp;}
		T& operator*() const {return *_p->value;}
		T* operator->() const {return _p->value;}
		reverse_iter_list& operator=(const Node<T>& element) {_p = element; return *this;}
	};

	template<typename Key, typename T>
	class iter_map
	{
	private:
		typedef node_map<Key, T>*	node;
	public:
		node	_p;
		iter_map() : _p(0) {};
		iter_map(node n) : _p(n) {};
		~iter_map() {};
		T& operator*() const {return _p->pair.second;}
	};

}
