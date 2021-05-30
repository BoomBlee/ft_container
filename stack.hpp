#pragma once

#include "vector.hpp"

namespace ft {
	template <class T, class Container = ft::vector<T> >
	class stack {
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
			explicit stack(const container_type& ctnr = container_type()) : c(ctnr) {}
			~stack() {}
			bool empty() const					{return c.empty();}
			size_type size() const				{return c.size();}
			reference top()						{return c.back();}
			const_reference top() const 		{return c.back();}
			void push(const value_type& __v)	{c.push_back(__v);}
			void pop()							{c.pop_back();}

			template <class Tstack, class ContainerStack>
				friend bool operator== (const ft::stack<Tstack, ContainerStack>& lhs, const ft::stack<Tstack, ContainerStack>& rhs);
			template <class Tstack, class ContainerStack>
				friend bool operator!= (const ft::stack<Tstack, ContainerStack>& lhs, const ft::stack<Tstack, ContainerStack>& rhs);
			template <class Tstack, class ContainerStack>
				friend bool operator< (const ft::stack<Tstack, ContainerStack>& lhs, const ft::stack<Tstack, ContainerStack>& rhs);
			template <class Tstack, class ContainerStack>
				friend bool operator<= (const ft::stack<Tstack, ContainerStack>& lhs, const ft::stack<Tstack, ContainerStack>& rhs);
			template <class Tstack, class ContainerStack>
				friend bool operator> (const ft::stack<Tstack, ContainerStack>& lhs, const ft::stack<Tstack, ContainerStack>& rhs);
			template <class Tstack, class ContainerStack>
				friend bool operator>= (const ft::stack<Tstack, ContainerStack>& lhs, const ft::stack<Tstack, ContainerStack>& rhs);
	};
	template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return lhs.c == rhs.c;
	}
	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return !(lhs.c == rhs.c);
	}
	template <class T, class Container>
	bool operator< (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return lhs.c < rhs.c;
	}
	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return lhs.c <= rhs.c;
	}
	template <class T, class Container>
	bool operator> (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return lhs.c > rhs.c;
	}
	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return lhs.c >= rhs.c;
	}
}