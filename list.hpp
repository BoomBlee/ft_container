#include <iostream>

// namespace ft{

// }

template<typename T>
class iter : iterator<bidirectional_iterator_tag, T> {
private:
	T	*p;
public:
};

template<typename T>
class list
{
private:
	/* data */
public:
	typedef T value_type;
	typedef unsigned long size_type;
	typedef iter<T> iterator;
};
