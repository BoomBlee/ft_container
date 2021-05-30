#pragma once

#include "vector.hpp"
#include "list.hpp"

namespace ft {
	template <class T, class Container = ft::vector<T> >
	class queue {
		public:
			typedef T											value_type;
			typedef Container									container_type;
			typedef size_t										size_type;
			typedef value_type&									reference;
			typedef value_type const &							const_reference;
			typedef value_type*									pointer;
			typedef value_type const *							const_pointer;
		private:
			Container c;
		public:
			explicit queue(const container_type& ctnr = container_type()) : c(ctnr) {}
			~queue() {}
			bool empty() const					{return c.empty();}
			size_type size() const				{return c.size();}
			reference front() {return c.front();}
			const_reference front() const {return c.front();}
			reference back() {return c.back();}
			const_reference back() const {return c.back();}
			void push(const value_type& __v)	{c.push_back(__v);}
			void pop()							{c.pop_back();}


			template <class Tqueue, class ContainerQueue>
				friend bool operator== (const ft::queue<Tqueue, ContainerQueue>& lhs, const ft::queue<Tqueue, ContainerQueue>& rhs);
			template <class Tqueue, class ContainerQueue>
				friend bool operator!= (const ft::queue<Tqueue, ContainerQueue>& lhs, const ft::queue<Tqueue, ContainerQueue>& rhs);
			template <class Tqueue, class ContainerQueue>
				friend bool operator< (const ft::queue<Tqueue, ContainerQueue>& lhs, const ft::queue<Tqueue, ContainerQueue>& rhs);
			template <class Tqueue, class ContainerQueue>
				friend bool operator<= (const ft::queue<Tqueue, ContainerQueue>& lhs, const ft::queue<Tqueue, ContainerQueue>& rhs);
			template <class Tqueue, class ContainerQueue>
				friend bool operator> (const ft::queue<Tqueue, ContainerQueue>& lhs, const ft::queue<Tqueue, ContainerQueue>& rhs);
			template <class Tqueue, class ContainerQueue>
				friend bool operator>= (const ft::queue<Tqueue, ContainerQueue>& lhs, const ft::queue<Tqueue, ContainerQueue>& rhs);
	};
	template <class T, class Container>
	bool operator== (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
		return lhs.c == rhs.c;
	}
	template <class T, class Container>
	bool operator!= (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
		return !(lhs.c == rhs.c);
	}
	template <class T, class Container>
	bool operator< (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
		return lhs.c < rhs.c;
	}
	template <class T, class Container>
	bool operator<= (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
		return lhs.c <= rhs.c;
	}
	template <class T, class Container>
	bool operator> (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
		return lhs.c > rhs.c;
	}
	template <class T, class Container>
	bool operator>= (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
		return lhs.c >= rhs.c;
	}
}