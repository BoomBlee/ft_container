#include <iostream>

template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
  struct iterator {
    typedef T         value_type;
    typedef Distance  difference_type;
    typedef Pointer   pointer;
    typedef Reference reference;
    typedef Category  iterator_category;
};

class	input_iterator_tag {};

template<typename T>
class iter : iterator<input_iterator_tag, T> {
private:
	T	*p;
public:
};

template<typename T>
bool	operator==(iter<T> const &it1, iter<T> const &it2) {
	return it1.p == it2.p;
}

template<typename T>
class Node {
private:
	T		*value;
	Node	*next;
	Node	*prev;

};

template<typename T>
class list
{
private:
	/* Node(first) & size */
public:
	typedef iter<T> iterator;
	list(/* args */);
	~list();
};

