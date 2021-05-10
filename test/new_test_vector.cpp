#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <iterator>
#include <sys/stat.h>
#include "../vector.hpp"
#include "color.hpp"

template <typename T>
bool compareVectorContent(std::vector<T>& stl_vect, ft::vector<T>& my_vect) {
	typename ft::vector<T>::iterator ft_it = my_vect.begin();
	typename std::vector<T>::iterator stl_it = stl_vect.begin();
	if (my_vect.size() != stl_vect.size())
		return false;
	for(typename std::vector<T>::iterator ite = stl_vect.end(); stl_it != ite; ++ft_it, ++stl_it) {
		if (*ft_it != *stl_it)
			return false;
	}
	return true;
}

template <typename T>
bool equalBool(T t1, T t2) {
	return t1 == t2;
}

template <class T>
bool compareVectorAttribues(std::fstream& fs, std::vector<T>& stl_vect, ft::vector<T>& my_vect) {
	
	bool empty = equalBool(stl_vect.empty(), my_vect.empty());
	bool size = equalBool(stl_vect.size(), my_vect.size());
	bool capacity = equalBool(stl_vect.capacity(), my_vect.capacity());
	bool max_size = equalBool(stl_vect.max_size(), my_vect.max_size());
	bool content = compareVectorContent(stl_vect, my_vect);

	fs << std::endl << "------------------------------" << std::endl;
	fs << "STL : " << std::endl;
	fs << "Empty		: " << stl_vect.empty() << std::endl;
	fs << "Size		: " << stl_vect.size() << std::endl;
	fs << "Capacity	: " << stl_vect.capacity() << std::endl;
	fs << "Max_size	: " << stl_vect.max_size() << std::endl;
	fs << "Content	: " << "{ ";

	typename std::vector<T>::iterator stl_it = stl_vect.begin();
	typename std::vector<T>::iterator ite = stl_vect.end();
    while (stl_it != ite) {
        fs << *stl_it;
        if (++stl_it != ite)
            fs << ", ";
    }
    fs << " }" << std::endl << std::endl;


	fs << "FT : " << std::endl;
	fs << "Empty		: " << my_vect.empty() << std::endl;
	fs << "Size		: " << my_vect.size() << std::endl;
	fs << "Capacity	: " << my_vect.capacity() << std::endl;
	fs << "Max_size	: " << my_vect.max_size() << std::endl;
	fs << "Content	: " << "{ ";

    typename ft::vector<T>::iterator ft_it = my_vect.begin();
	typename ft::vector<T>::iterator ft_ite = my_vect.end();
    while(ft_it != ft_ite) {
        fs << *ft_it;
        if (++ft_it != ft_ite)
            fs << ", ";
    }
    fs << " }" << std::endl;

	fs << "------------------------------" << std::endl;

	if (empty && size && max_size && capacity && content)
		return true;
	return false;
}

void printResult(bool res) {
	if (res) {
		std::cout << GREEN << " [OK]" << RESET;
		return ;
	}
	std::cout << RED << " [NO]" << RESET;
}

void test_vector() {
	std::fstream fs;

	std::cout << YELLOW << "VECTOR :" << RESET <<std::endl;
	mkdir("./test/vector_output", 0777);

	/*DEFAULT CONSTRUCTOR*/
	std::cout << "CONSTRUCTOR:";
	{
		std::vector<int> stl_vector;
		ft::vector<int> ft_vector;

		fs.open("./test/vector_output/constructor_default", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareVectorAttribues(fs, stl_vector, ft_vector));
		fs.close();
	}

	{
		std::vector<int> stl_vector(0);
		ft::vector<int> ft_vector(0);

		fs.open("./test/vector_output/constructor_fill_empty", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareVectorAttribues(fs, stl_vector, ft_vector));
		fs.close();
	}

	{
		std::vector<int> stl_vector(5);
		ft::vector<int> ft_vector(5);

		fs.open("./test/vector_output/constructor_fill", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareVectorAttribues(fs, stl_vector, ft_vector));
		fs.close();
	}

	{
		std::vector<int> stl_vector(11,9);
		ft::vector<int> ft_vector(11,9);

		fs.open("./test/vector_output/constructor_fill_size", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareVectorAttribues(fs, stl_vector, ft_vector));
		fs.close();
	}

	{
		std::list<int> lst;
		lst.push_back(12);
		lst.push_back(765);
		lst.push_back(-35);
		lst.push_back(89);
		lst.push_back(65);

		std::vector<int> stl_vector(lst.begin(),lst.end());
		ft::vector<int> ft_vector(lst.begin(),lst.end());

		fs.open("./test/vector_output/constructor_range", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareVectorAttribues(fs, stl_vector, ft_vector));
		fs.close();
	}

	{
		std::list<int> lst;
		lst.push_back(12);
		lst.push_back(765);
		lst.push_back(-35);
		lst.push_back(89);
		lst.push_back(65);
		lst.push_back(76);

		std::vector<int> stl_vector(lst.begin(),lst.end());
		ft::vector<int> ft_vector(lst.begin(),lst.end());

		std::vector<int> stl_copy_vector(stl_vector);
		ft::vector<int> ft_copy_vector(ft_vector);

		fs.open("./test/vector_output/constructor_copy", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareVectorAttribues(fs, stl_copy_vector, ft_copy_vector));
		fs.close();
	}
	std::cout << std::endl;

	/*ASSIGN*/
	std::cout << "ASSIGN:";
	{
		std::list<int> lst;
		lst.push_back(765);
		lst.push_back(-35);
		lst.push_back(65);
		lst.push_back(76);

		std::vector<int> stl_vector(lst.begin(),lst.end());
		ft::vector<int> ft_vector(lst.begin(),lst.end());

		std::vector<int> stl_copy_vector = stl_vector;
		ft::vector<int> ft_copy_vector = ft_vector;

		fs.open("./test/vector_output/operator_assign", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareVectorAttribues(fs, stl_copy_vector,ft_copy_vector));
		fs.close();
	}
	std::cout << std::endl;

	std::cout << "Iterators:";
	/*BEGIN*/
	{
		std::list<int> lst;
		lst.push_back(765);
		lst.push_back(-35);
		lst.push_back(65);
		lst.push_back(76);

		std::vector<int> stl_vector(lst.begin(),lst.end());
		ft::vector<int> ft_vector(lst.begin(),lst.end());

		int stl_value = *(stl_vector.begin());
		int ft_value = *(ft_vector.begin());

		fs.open("./test/vector_output/iterator_begin", std::fstream::in | std::fstream::out | std::fstream::trunc);
		compareVectorAttribues(fs, stl_vector, ft_vector);
		printResult(equalBool(stl_value,ft_value));
		fs.close();
	}

	/*END*/
	{
		std::list<int> lst;
		lst.push_back(765);
		lst.push_back(-35);
		lst.push_back(65);
		lst.push_back(76);

		std::vector<int> stl_vector(lst.begin(),lst.end());
		ft::vector<int> ft_vector(lst.begin(),lst.end());

		int stl_value = *(stl_vector.end() - 1);
		int ft_value = *(ft_vector.end() - 1);

		fs.open("./test/vector_output/iterator_end", std::fstream::in | std::fstream::out | std::fstream::trunc);
		compareVectorAttribues(fs, stl_vector, ft_vector);
		printResult(equalBool(stl_value,ft_value));
		fs << "stl_value : " << stl_value << std::endl;
		fs << "ft_value : " << ft_value << std::endl;
		fs.close();
	}

	/*OPERATOR++*/
	{
		std::list<int> lst;
		lst.push_back(765);
		lst.push_back(-35);
		lst.push_back(65);
		lst.push_back(76);
		lst.push_back(100);
		lst.push_back(94);

		std::vector<int> stl_vector(lst.begin(),lst.end());
		ft::vector<int> ft_vector(lst.begin(),lst.end());

		std::vector<int>::iterator stl_it = stl_vector.begin();
		std::vector<int>::iterator stl_it1 = stl_it++;
		std::vector<int>::iterator stl_it2 = ++stl_it;

		ft::vector<int>::iterator ft_it = ft_vector.begin();
		ft::vector<int>::iterator ft_it1 = ft_it++;
		ft::vector<int>::iterator ft_it2 = ++ft_it;

		if (*stl_it == *ft_it && *stl_it1 == *ft_it1 && *stl_it2 == *ft_it2)
			printResult(true);
		else
			printResult(false);

		fs.open("./test/vector_output/iterator_operator++", std::fstream::in | std::fstream::out | std::fstream::trunc);
		compareVectorAttribues(fs, stl_vector, ft_vector);

		fs << "stl_value : " << *stl_it << " " << *stl_it1 << " " << *stl_it2 << std::endl;
		fs << "ft_value : " << *ft_it << " " << *ft_it1 << " " << *ft_it2 << std::endl;
		fs.close();
	}

	/*OPERATOR--*/
	{
		std::list<int> lst;
		lst.push_back(765);
		lst.push_back(-35);
		lst.push_back(65);
		lst.push_back(76);
		lst.push_back(100);
		lst.push_back(94);

		std::vector<int> stl_vector(lst.begin(),lst.end());
		ft::vector<int> ft_vector(lst.begin(),lst.end());

		std::vector<int>::iterator stl_it = stl_vector.begin();
		stl_it++;
		std::vector<int>::iterator stl_it1 = stl_it--;
		stl_it++;
		std::vector<int>::iterator stl_it2 = --stl_it;

		ft::vector<int>::iterator ft_it = ft_vector.begin();
		ft_it++;
		ft::vector<int>::iterator ft_it1 = ft_it--;
		ft_it++;
		ft::vector<int>::iterator ft_it2 = --ft_it;

		if (*stl_it == *ft_it && *stl_it1 == *ft_it1 && *stl_it2 == *ft_it2)
			printResult(true);
		else
			printResult(false);

		fs.open("./test/vector_output/iterator_operator--", std::fstream::in | std::fstream::out | std::fstream::trunc);
		compareVectorAttribues(fs, stl_vector, ft_vector);

		fs << "stl_value : " << *stl_it << " " << *stl_it1 << " " << *stl_it2 << std::endl;
		fs << "ft_value : " << *ft_it << " " << *ft_it1 << " " << *ft_it2 << std::endl;
		fs.close();
	}

	/*OPERATOR+-=*/
	{
		std::list<int> lst;
		lst.push_back(765);
		lst.push_back(-35);
		lst.push_back(65);
		lst.push_back(76);
		lst.push_back(100);
		lst.push_back(94);

		std::vector<int> stl_vector(lst.begin(),lst.end());
		ft::vector<int> ft_vector(lst.begin(),lst.end());

		std::vector<int>::iterator stl_it = stl_vector.begin();
		stl_it += 3;

		ft::vector<int>::iterator ft_it = ft_vector.begin();
		ft_it += 3;

		fs.open("./test/vector_output/iterator_operator+=", std::fstream::in | std::fstream::out | std::fstream::trunc);
		compareVectorAttribues(fs, stl_vector, ft_vector);
		fs << "stl_value : " << *stl_it << std::endl;
		fs << "ft_value : " << *ft_it << std::endl;
		fs.close();

		if (!equalBool(*stl_it, *ft_it)) {
			printResult(false);
			return ;
		}

		stl_it -= 2;
		ft_it -= 2;

		fs.open("./test/vector_output/iterator_operator-=", std::fstream::in | std::fstream::out | std::fstream::trunc);
		compareVectorAttribues(fs, stl_vector, ft_vector);
		fs << "stl_value : " << *stl_it << std::endl;
		fs << "ft_value : " << *ft_it << std::endl;
		fs.close();

		if (equalBool(*stl_it, *ft_it))
			printResult(true);
		else
			printResult(false);
	}

	/*OPERATOR []*/
	{
		std::list<int> lst;
		lst.push_back(765);
		lst.push_back(-35);
		lst.push_back(65);
		lst.push_back(76);

		std::vector<int> stl_vector(lst.begin(),lst.end());
		ft::vector<int> ft_vector(lst.begin(),lst.end());

		std::vector<int>::iterator stl_it = stl_vector.begin();
		ft::vector<int>::iterator ft_it = ft_vector.begin();

		fs.open("./test/vector_output/iterator_operator[]", std::fstream::in | std::fstream::out | std::fstream::trunc);
		compareVectorAttribues(fs, stl_vector, ft_vector);
		printResult(equalBool(stl_it[3], ft_it[3]) && equalBool(stl_it[2], ft_it[2]));
		fs << "stl_value : " << stl_it[3] << " " << stl_it[2] << std::endl;
		fs << "ft_value : " << ft_it[3] << " " << ft_it[2] << std::endl;
		fs.close();
	}

	/*OPERATOR->*/
	{
		std::list<int> lst;
		lst.push_back(765);
		lst.push_back(-35);
		lst.push_back(65);
		lst.push_back(76);

		std::vector<int> stl_vector(lst.begin(),lst.end());
		ft::vector<int> ft_vector(lst.begin(),lst.end());

		std::vector<int>::iterator stl_it = stl_vector.begin();
		ft::vector<int>::iterator ft_it = ft_vector.begin();

		fs.open("./test/vector_output/iterator_operator->", std::fstream::in | std::fstream::out | std::fstream::trunc);
		compareVectorAttribues(fs, stl_vector, ft_vector);
		printResult(equalBool(*stl_it.operator->(), *ft_it.operator->()));
		fs << "stl_value : " << *stl_it.operator->() << std::endl;
		fs << "ft_value : " << *ft_it.operator->() << std::endl;
		fs.close();
	}
	
	/*OPERATOR=*/
	{
		std::list<int> lst;
		lst.push_back(765);
		lst.push_back(-35);
		lst.push_back(65);
		lst.push_back(76);

		std::vector<int> stl_vector(lst.begin(),lst.end());
		ft::vector<int> ft_vector(lst.begin(),lst.end());

		std::vector<int>::iterator stl_it = stl_vector.begin();
		ft::vector<int>::iterator ft_it = ft_vector.begin();

		*stl_it = -10000;
		*ft_it = -10000;

		fs.open("./test/vector_output/iterator_operator=", std::fstream::in | std::fstream::out | std::fstream::trunc);
		compareVectorAttribues(fs, stl_vector, ft_vector);
		printResult(equalBool(*stl_it, *ft_it));
		fs << "stl_value : " << *stl_it << std::endl;
		fs << "ft_value : " << *ft_it << std::endl;
		fs.close();
	}
	std::cout << std::endl;

	std::cout << "Reverse Iterators: ";
	/*BEGIN*/
	{
		std::list<int> lst;
		lst.push_back(765);
		lst.push_back(-35);
		lst.push_back(65);
		lst.push_back(76);

		std::vector<int> stl_vector(lst.rbegin(),lst.rend());
		ft::vector<int> ft_vector(lst.rbegin(),lst.rend());

		int stl_value = *(stl_vector.rbegin());
		int ft_value = *(ft_vector.rbegin());

		fs.open("./test/vector_output/reverse_iterator_begin", std::fstream::in | std::fstream::out | std::fstream::trunc);
		compareVectorAttribues(fs, stl_vector, ft_vector);
		printResult(equalBool(stl_value,ft_value));
		fs.close();
	}

	/*END*/
	{
		std::list<int> lst;
		lst.push_back(765);
		lst.push_back(-35);
		lst.push_back(65);
		lst.push_back(76);

		std::vector<int> stl_vector(lst.rbegin(),lst.rend());
		ft::vector<int> ft_vector(lst.rbegin(),lst.rend());

		int stl_value = *(stl_vector.rend() - 1);
		int ft_value = *(ft_vector.rend() - 1);

		fs.open("./test/vector_output/reverse_iterator_end", std::fstream::in | std::fstream::out | std::fstream::trunc);
		compareVectorAttribues(fs, stl_vector, ft_vector);
		printResult(equalBool(stl_value,ft_value));
		fs << "stl_value : " << stl_value << std::endl;
		fs << "ft_value : " << ft_value << std::endl;
		fs.close();
	}

	/*OPERATOR++*/
	{
		std::list<int> lst;
		lst.push_back(765);
		lst.push_back(-35);
		lst.push_back(65);
		lst.push_back(76);
		lst.push_back(100);
		lst.push_back(94);

		std::vector<int> stl_vector(lst.rbegin(),lst.rend());
		ft::vector<int> ft_vector(lst.rbegin(),lst.rend());

		std::vector<int>::reverse_iterator stl_it = stl_vector.rbegin();
		std::vector<int>::reverse_iterator stl_it1 = stl_it++;
		std::vector<int>::reverse_iterator stl_it2 = ++stl_it;

		ft::vector<int>::reverse_iterator ft_it = ft_vector.rbegin();
		ft::vector<int>::reverse_iterator ft_it1 = ft_it++;
		ft::vector<int>::reverse_iterator ft_it2 = ++ft_it;

		if (*stl_it == *ft_it && *stl_it1 == *ft_it1 && *stl_it2 == *ft_it2)
			printResult(true);
		else
			printResult(false);

		fs.open("./test/vector_output/reverse_iterator_operator++", std::fstream::in | std::fstream::out | std::fstream::trunc);
		compareVectorAttribues(fs, stl_vector, ft_vector);

		fs << "stl_value : " << *stl_it << " " << *stl_it1 << " " << *stl_it2 << std::endl;
		fs << "ft_value : " << *ft_it << " " << *ft_it1 << " " << *ft_it2 << std::endl;
		fs.close();
	}

	/*OPERATOR--*/
	{
		std::list<int> lst;
		lst.push_back(765);
		lst.push_back(-35);
		lst.push_back(65);
		lst.push_back(76);
		lst.push_back(100);
		lst.push_back(94);

		std::vector<int> stl_vector(lst.rbegin(),lst.rend());
		ft::vector<int> ft_vector(lst.rbegin(),lst.rend());

		std::vector<int>::reverse_iterator stl_it = stl_vector.rbegin();
		stl_it++;
		std::vector<int>::reverse_iterator stl_it1 = stl_it--;
		stl_it++;
		std::vector<int>::reverse_iterator stl_it2 = --stl_it;

		ft::vector<int>::reverse_iterator ft_it = ft_vector.rbegin();
		ft_it++;
		ft::vector<int>::reverse_iterator ft_it1 = ft_it--;
		ft_it++;
		ft::vector<int>::reverse_iterator ft_it2 = --ft_it;

		if (*stl_it == *ft_it && *stl_it1 == *ft_it1 && *stl_it2 == *ft_it2)
			printResult(true);
		else
			printResult(false);

		fs.open("./test/vector_output/reverse_iterator_operator--", std::fstream::in | std::fstream::out | std::fstream::trunc);
		compareVectorAttribues(fs, stl_vector, ft_vector);

		fs << "stl_value : " << *stl_it << " " << *stl_it1 << " " << *stl_it2 << std::endl;
		fs << "ft_value : " << *ft_it << " " << *ft_it1 << " " << *ft_it2 << std::endl;
		fs.close();
	}

	/*OPERATOR+-=*/
	{
		std::list<int> lst;
		lst.push_back(765);
		lst.push_back(-35);
		lst.push_back(65);
		lst.push_back(76);
		lst.push_back(100);
		lst.push_back(94);

		std::vector<int> stl_vector(lst.rbegin(),lst.rend());
		ft::vector<int> ft_vector(lst.rbegin(),lst.rend());

		std::vector<int>::reverse_iterator stl_it = stl_vector.rbegin();
		stl_it += 3;

		ft::vector<int>::reverse_iterator ft_it = ft_vector.rbegin();
		ft_it += 3;

		fs.open("./test/vector_output/reverse_iterator_operator+=", std::fstream::in | std::fstream::out | std::fstream::trunc);
		compareVectorAttribues(fs, stl_vector, ft_vector);
		fs << "stl_value : " << *stl_it << std::endl;
		fs << "ft_value : " << *ft_it << std::endl;
		fs.close();

		if (!equalBool(*stl_it, *ft_it)) {
			printResult(false);
			return ;
		}

		stl_it -= 2;
		ft_it -= 2;

		fs.open("./test/vector_output/reverse_iterator_operator-=", std::fstream::in | std::fstream::out | std::fstream::trunc);
		compareVectorAttribues(fs, stl_vector, ft_vector);
		fs << "stl_value : " << *stl_it << std::endl;
		fs << "ft_value : " << *ft_it << std::endl;
		fs.close();

		if (equalBool(*stl_it, *ft_it))
			printResult(true);
		else
			printResult(false);
	}

	/*OPERATOR []*/
	{
		std::list<int> lst;
		lst.push_back(765);
		lst.push_back(-35);
		lst.push_back(65);
		lst.push_back(76);

		std::vector<int> stl_vector(lst.rbegin(),lst.rend());
		ft::vector<int> ft_vector(lst.rbegin(),lst.rend());

		std::vector<int>::reverse_iterator stl_it = stl_vector.rbegin();
		ft::vector<int>::reverse_iterator ft_it = ft_vector.rbegin();

		fs.open("./test/vector_output/reverse_iterator_operator[]", std::fstream::in | std::fstream::out | std::fstream::trunc);
		compareVectorAttribues(fs, stl_vector, ft_vector);
		printResult(equalBool(stl_it[3], ft_it[3]) && equalBool(stl_it[2], ft_it[2]));
		fs << "stl_value : " << stl_it[3] << " " << stl_it[2] << std::endl;
		fs << "ft_value : " << ft_it[3] << " " << ft_it[2] << std::endl;
		// for (ft::vector<int>::reverse_iterator ft_ite = ft_vector.rend(); ft_it != ft_ite; ++ft_it) {
		// 	std::cout << *ft_it << ",";
		// }
		fs.close();
	}

	/*OPERATOR->*/
	{
		std::list<int> lst;
		lst.push_back(765);
		lst.push_back(-35);
		lst.push_back(65);
		lst.push_back(76);

		std::vector<int> stl_vector(lst.rbegin(),lst.rend());
		ft::vector<int> ft_vector(lst.rbegin(),lst.rend());

		std::vector<int>::reverse_iterator stl_it = stl_vector.rbegin();
		ft::vector<int>::reverse_iterator ft_it = ft_vector.rbegin();

		fs.open("./test/vector_output/reverse_iterator_operator->", std::fstream::in | std::fstream::out | std::fstream::trunc);
		compareVectorAttribues(fs, stl_vector, ft_vector);
		printResult(equalBool(*stl_it.operator->(), *ft_it.operator->()));
		fs << "stl_value : " << *stl_it.operator->() << std::endl;
		fs << "ft_value : " << *ft_it.operator->() << std::endl;
		fs.close();
	}

	/*OPERATOR=*/
	{
		std::list<int> lst;
		lst.push_back(765);
		lst.push_back(-35);
		lst.push_back(65);
		lst.push_back(76);

		std::vector<int> stl_vector(lst.rbegin(),lst.rend());
		ft::vector<int> ft_vector(lst.rbegin(),lst.rend());

		std::vector<int>::reverse_iterator stl_it = stl_vector.rbegin();
		ft::vector<int>::reverse_iterator ft_it = ft_vector.rbegin();

		*stl_it = -10000;
		*ft_it = -10000;

		fs.open("./test/vector_output/reverse_iterator_operator=", std::fstream::in | std::fstream::out | std::fstream::trunc);
		compareVectorAttribues(fs, stl_vector, ft_vector);
		printResult(equalBool(*stl_it, *ft_it));
		fs << "stl_value : " << *stl_it << std::endl;
		fs << "ft_value : " << *ft_it << std::endl;
		fs.close();
	}
	std::cout << std::endl;

	std::cout << "Capacity:";
	/*RESIZE*/
	{
		std::vector<int> stl_vector;
		ft::vector<int> ft_vector;

		bool one, two, three, four, five;

		stl_vector.resize(0);
		ft_vector.resize(0);

		fs.open("./test/vector_output/resize", std::fstream::in | std::fstream::out | std::fstream::trunc);
		one = compareVectorAttribues(fs, stl_vector, ft_vector);

		stl_vector.resize(10);
		ft_vector.resize(10);
		two = compareVectorAttribues(fs, stl_vector, ft_vector);

		stl_vector.resize(7, 1);
		ft_vector.resize(7, 1);
		three = compareVectorAttribues(fs, stl_vector, ft_vector);

		stl_vector.resize(12);
		ft_vector.resize(12);
		four = compareVectorAttribues(fs, stl_vector, ft_vector);

		stl_vector.resize(15, 100);
		ft_vector.resize(15, 100);
		five = compareVectorAttribues(fs, stl_vector, ft_vector);

		if (one && two && three && four && five)
			printResult(true);
		else
			printResult(false);

		fs.close();
	}

	/*REVERSE*/
	{
		std::list<int> lst;
		lst.push_back(765);
		lst.push_back(-35);
		lst.push_back(65);
		lst.push_back(76);
		lst.push_back(100);
		lst.push_back(94);

		std::vector<int> stl_vector(lst.begin(),lst.end());
		ft::vector<int> ft_vector(lst.begin(),lst.end());

		bool one, two;

		fs.open("./test/vector_output/reserve", std::fstream::in | std::fstream::out | std::fstream::trunc);
		stl_vector.reserve(5);
		ft_vector.reserve(5);
		one = compareVectorAttribues(fs, stl_vector, ft_vector);

		stl_vector.reserve(7);
		ft_vector.reserve(7);
		two = compareVectorAttribues(fs, stl_vector, ft_vector);

		if (one && two)
			printResult(true);
		else
			printResult(false);

		fs.close();
	}
	std::cout << std::endl;

	std::cout << "Element access:";
	/*OPERATOR[]*/
	{
		std::list<int> lst;
		lst.push_back(765);
		lst.push_back(-35);
		lst.push_back(65);
		lst.push_back(76);

		std::vector<int> stl_vector(lst.begin(),lst.end());
		ft::vector<int> ft_vector(lst.begin(),lst.end());

		fs.open("./test/vector_output/operator[]", std::fstream::in | std::fstream::out | std::fstream::trunc);
		compareVectorAttribues(fs, stl_vector, ft_vector);
		printResult(equalBool(stl_vector[3], ft_vector[3]) && equalBool(stl_vector[2], ft_vector[2]));
		fs << "stl_value : " << stl_vector[3] << " " << stl_vector[2] << std::endl;
		fs << "ft_value : " << ft_vector[3] << " " << ft_vector[2] << std::endl;
		fs.close();
	}

	/*AT*/
	{
		std::list<int> lst;
		lst.push_back(765);
		lst.push_back(-35);
		lst.push_back(65);
		lst.push_back(76);

		std::vector<int> stl_vector(lst.begin(),lst.end());
		ft::vector<int> ft_vector(lst.begin(),lst.end());

		fs.open("./test/vector_output/at", std::fstream::in | std::fstream::out | std::fstream::trunc);
		compareVectorAttribues(fs, stl_vector, ft_vector);
		bool res = equalBool(stl_vector.at(3), ft_vector.at(3)) && equalBool(stl_vector.at(2), ft_vector.at(2));
		fs << "stl_value : " << stl_vector.at(3) << " " << stl_vector.at(2) << std::endl;
		fs << "ft_value : " << ft_vector.at(3) << " " << ft_vector.at(2) << std::endl;

		bool except_stl = false;
		bool except_ft = false;

		try {
			stl_vector.at(4);
		}
		catch(const std::exception& e) {
			fs << e.what() << '\n';
			except_stl = true;
		}
		try {
			ft_vector.at(4);
		}
		catch(const std::exception& e) {
			fs << e.what() << '\n';
			except_ft = true;
		}

		if (res && except_ft && except_stl)
			printResult(true);
		else
			printResult(false);

		fs.close();
	}

	/*FRONT*/
	{
		std::list<int> lst;
		lst.push_back(765);
		lst.push_back(-35);
		lst.push_back(65);
		lst.push_back(76);

		std::vector<int> stl_vector(lst.begin(),lst.end());
		ft::vector<int> ft_vector(lst.begin(),lst.end());

		fs.open("./test/vector_output/front", std::fstream::in | std::fstream::out | std::fstream::trunc);
		compareVectorAttribues(fs, stl_vector, ft_vector);
		printResult(equalBool(stl_vector.front(), ft_vector.front()));
		fs << "stl_value : " << stl_vector.front() << std::endl;
		fs << "ft_value : " << ft_vector.front() << std::endl;
		fs.close();
	}

	/*BACK*/
	{
		std::list<int> lst;
		lst.push_back(765);
		lst.push_back(-35);
		lst.push_back(65);
		lst.push_back(76);

		std::vector<int> stl_vector(lst.begin(),lst.end());
		ft::vector<int> ft_vector(lst.begin(),lst.end());

		fs.open("./test/vector_output/back", std::fstream::in | std::fstream::out | std::fstream::trunc);
		compareVectorAttribues(fs, stl_vector, ft_vector);
		printResult(equalBool(stl_vector.back(), ft_vector.back()));
		fs << "stl_value : " << stl_vector.back() << std::endl;
		fs << "ft_value : " << ft_vector.back() << std::endl;
		fs.close();
	}
	std::cout << std::endl;

	std::cout << "Modifiers:";
	/*ASSIGN*/
	{
		std::list<int> lst;
		lst.push_back(765);
		lst.push_back(-35);
		lst.push_back(65);
		lst.push_back(76);

		std::vector<int> stl_vector;
		ft::vector<int> ft_vector;
		stl_vector.assign(lst.begin(), lst.end());
		ft_vector.assign(lst.begin(), lst.end());
		fs.open("./test/vector_output/assign", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareVectorAttribues(fs, stl_vector, ft_vector));

		stl_vector.assign(11, 55);
		ft_vector.assign(11, 55);
		printResult(compareVectorAttribues(fs, stl_vector, ft_vector));
		
		fs.close();
	}

	/*PUSH_BACK*/
	{
		std::vector<int> stl_vector;
		ft::vector<int> ft_vector;
		
		for (size_t i = 0; i < 33; ++i) {
			stl_vector.push_back(i);
			ft_vector.push_back(i);
		}
		

		fs.open("./test/vector_output/push_back", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareVectorAttribues(fs, stl_vector, ft_vector));

		fs.close();
	}
	
	/*POP_BACK*/
	{
		std::vector<int> stl_vector;
		ft::vector<int> ft_vector;
		
		for (size_t i = 0; i < 33; ++i) {
			stl_vector.push_back(i);
			ft_vector.push_back(i);
		}	
		for (size_t i = 0; i < 10; ++i) {
			stl_vector.pop_back();
			ft_vector.pop_back();
		}

		fs.open("./test/vector_output/pop_back", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareVectorAttribues(fs, stl_vector, ft_vector));

		fs.close();
	}

	/*INSERT*/
	{
		std::list<int> lst;
		lst.push_back(765);
		lst.push_back(-35);
		lst.push_back(65);
		lst.push_back(76);

		std::vector<int> stl_vector;
		ft::vector<int> ft_vector;
		std::vector<int>::iterator stl_it;
		ft::vector<int>::iterator ft_it;
		
		for (size_t i = 0; i < 10; ++i) {
			stl_it = stl_vector.insert(stl_vector.begin(), i);
			ft_it = ft_vector.insert(ft_vector.begin(), i);
		}

		fs.open("./test/vector_output/insert", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareVectorAttribues(fs, stl_vector, ft_vector));

		stl_vector.insert(stl_vector.end(), 2, 79);
		ft_vector.insert(ft_vector.end(), 2, 79);
		printResult(compareVectorAttribues(fs, stl_vector, ft_vector));

		stl_vector.insert(stl_vector.begin(), lst.begin(), lst.end());
		ft_vector.insert(ft_vector.begin(), lst.begin(), lst.end());
		printResult(compareVectorAttribues(fs, stl_vector, ft_vector));

		printResult(equalBool(*stl_it, *ft_it));
		fs << "stl_value : " << *stl_it << std::endl;
		fs << "ft_value : " << *ft_it << std::endl;

		fs.close();
	}

	/*ERASE*/
	{
		std::vector<int> stl_vector;
		ft::vector<int> ft_vector;
		
		for (size_t i = 0; i < 10; ++i) {
			stl_vector.insert(stl_vector.begin(), i);
			ft_vector.insert(ft_vector.begin(), i);
		}

		stl_vector.erase(stl_vector.begin());
		ft_vector.erase(ft_vector.begin());

		stl_vector.erase(stl_vector.begin() + 3);
		ft_vector.erase(ft_vector.begin() + 3);

		fs.open("./test/vector_output/erase", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareVectorAttribues(fs, stl_vector, ft_vector));

		fs.close();
	}

	/*SWAP*/
	{
		std::vector<int> stl_vector;
		ft::vector<int> ft_vector;
		std::vector<int> stl_swap_vector;
		ft::vector<int> ft_swap_vector;
		
		for (size_t i = 0; i < 10; ++i) {
			stl_vector.push_back(i);
			ft_vector.push_back(i);
		}		
		for (size_t i = 100; i > 87; --i) {
			stl_swap_vector.push_back(i);
			ft_swap_vector.push_back(i);
		}

		stl_vector.swap(stl_swap_vector);
		ft_vector.swap(ft_swap_vector);

		fs.open("./test/vector_output/swap", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareVectorAttribues(fs, stl_vector, ft_vector) &&
				compareVectorAttribues(fs, stl_swap_vector, ft_swap_vector));

		fs.close();
	}

	/*CLEAR*/
	{
		std::vector<int> stl_vector;
		ft::vector<int> ft_vector;
		
		for (size_t i = 0; i < 100; ++i) {
			stl_vector.push_back(i);
			ft_vector.push_back(i);
		}

		stl_vector.clear();
		ft_vector.clear();

		fs.open("./test/vector_output/clear", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareVectorAttribues(fs, stl_vector, ft_vector));

		fs.close();
	}
	std::cout << std::endl;

	std::cout << "Non-member function overloads:";
	/*OPERATOR==*/
	{
		std::vector<int> stl_vector;
		ft::vector<int> ft_vector;
		bool one=false, two=false;
		
		for (size_t i = 0; i < 100; ++i) {
			stl_vector.push_back(i);
			ft_vector.push_back(i);
		}

		std::vector<int> stl_copy_vector(stl_vector);
		ft::vector<int> ft_copy_vector(ft_vector);

		fs.open("./test/vector_output/operator==", std::fstream::in | std::fstream::out | std::fstream::trunc);
		compareVectorAttribues(fs, stl_vector, ft_vector);
		compareVectorAttribues(fs, stl_copy_vector, ft_copy_vector);
		one = ((stl_vector == stl_copy_vector) && (ft_vector == ft_copy_vector));

		stl_vector.erase(stl_vector.begin() + 3);
		ft_vector.erase(ft_vector.begin() + 3);

		compareVectorAttribues(fs, stl_vector, ft_vector);
		compareVectorAttribues(fs, stl_copy_vector, ft_copy_vector);
		two = (!(stl_vector == stl_copy_vector) && !(ft_vector == ft_copy_vector));

		if (one && two)
			printResult(true);
		else
			printResult(false);
		fs.close();
	}

	/*OPERATOR!=*/
	{
		std::vector<int> stl_vector;
		ft::vector<int> ft_vector;
		bool one=false, two=false;
		
		for (size_t i = 0; i < 100; ++i) {
			stl_vector.push_back(i);
			ft_vector.push_back(i);
		}

		std::vector<int> stl_copy_vector(stl_vector);
		ft::vector<int> ft_copy_vector(ft_vector);

		fs.open("./test/vector_output/operato !=", std::fstream::in | std::fstream::out | std::fstream::trunc);
		compareVectorAttribues(fs, stl_vector, ft_vector);
		compareVectorAttribues(fs, stl_copy_vector, ft_copy_vector);
		one = (!(stl_vector != stl_copy_vector) && !(ft_vector != ft_copy_vector));

		stl_vector.erase(stl_vector.begin() + 3);
		ft_vector.erase(ft_vector.begin() + 3);

		compareVectorAttribues(fs, stl_vector, ft_vector);
		compareVectorAttribues(fs, stl_copy_vector, ft_copy_vector);
		two = ((stl_vector != stl_copy_vector) && (ft_vector != ft_copy_vector));

		if (one && two)
			printResult(true);
		else
			printResult(false);
		fs.close();
	}

	/*OPERATOR<*/
	{
		std::vector<int> stl_vector;
		ft::vector<int> ft_vector;
		bool one=false, two=false, three=false;
		
		for (size_t i = 0; i < 100; ++i) {
			stl_vector.push_back(i);
			ft_vector.push_back(i);
		}

		std::vector<int> stl_copy_vector(stl_vector);
		ft::vector<int> ft_copy_vector(ft_vector);

		stl_copy_vector.erase(stl_copy_vector.begin() + 3);
		ft_copy_vector.erase(ft_copy_vector.begin() + 3);

		fs.open("./test/vector_output/operator<", std::fstream::in | std::fstream::out | std::fstream::trunc);
		compareVectorAttribues(fs, stl_vector, ft_vector);
		compareVectorAttribues(fs, stl_copy_vector, ft_copy_vector);
		one = ((stl_vector < stl_copy_vector) && (ft_vector < ft_copy_vector));

		stl_vector.erase(stl_vector.begin() + 3);
		ft_vector.erase(ft_vector.begin() + 3);

		compareVectorAttribues(fs, stl_vector, ft_vector);
		compareVectorAttribues(fs, stl_copy_vector, ft_copy_vector);
		two = (!(stl_vector < stl_copy_vector) && !(ft_vector < ft_copy_vector));

		stl_vector.erase(stl_vector.begin());
		ft_vector.erase(ft_vector.begin());

		compareVectorAttribues(fs, stl_vector, ft_vector);
		compareVectorAttribues(fs, stl_copy_vector, ft_copy_vector);
		three = (!(stl_vector < stl_copy_vector) && !(ft_vector < ft_copy_vector));

		if (one && two && three)
			printResult(true);
		else
			printResult(false);
		fs.close();
	}

	/*OPERATOR<=*/
	{
		std::vector<int> stl_vector;
		ft::vector<int> ft_vector;
		bool one=false, two=false, three=false;
		
		for (size_t i = 0; i < 100; ++i) {
			stl_vector.push_back(i);
			ft_vector.push_back(i);
		}

		std::vector<int> stl_copy_vector(stl_vector);
		ft::vector<int> ft_copy_vector(ft_vector);

		stl_copy_vector.erase(stl_copy_vector.begin() + 3);
		ft_copy_vector.erase(ft_copy_vector.begin() + 3);

		fs.open("./test/vector_output/operator<=", std::fstream::in | std::fstream::out | std::fstream::trunc);
		compareVectorAttribues(fs, stl_vector, ft_vector);
		compareVectorAttribues(fs, stl_copy_vector, ft_copy_vector);
		one = ((stl_vector <= stl_copy_vector) && (ft_vector <= ft_copy_vector));

		stl_vector.erase(stl_vector.begin() + 3);
		ft_vector.erase(ft_vector.begin() + 3);

		compareVectorAttribues(fs, stl_vector, ft_vector);
		compareVectorAttribues(fs, stl_copy_vector, ft_copy_vector);
		two = ((stl_vector <= stl_copy_vector) && (ft_vector <= ft_copy_vector));

		stl_vector.erase(stl_vector.begin());
		ft_vector.erase(ft_vector.begin());

		compareVectorAttribues(fs, stl_vector, ft_vector);
		compareVectorAttribues(fs, stl_copy_vector, ft_copy_vector);
		three = (!(stl_vector <= stl_copy_vector) && !(ft_vector <= ft_copy_vector));

		if (one && two && three)
			printResult(true);
		else
			printResult(false);
		fs.close();
	}

	/*OPERATOR>*/
	{
		std::vector<int> stl_vector;
		ft::vector<int> ft_vector;
		bool one=false, two=false, three=false;
		
		for (size_t i = 0; i < 100; ++i) {
			stl_vector.push_back(i);
			ft_vector.push_back(i);
		}

		std::vector<int> stl_copy_vector(stl_vector);
		ft::vector<int> ft_copy_vector(ft_vector);

		stl_copy_vector.erase(stl_copy_vector.begin() + 3);
		ft_copy_vector.erase(ft_copy_vector.begin() + 3);

		fs.open("./test/vector_output/operator>", std::fstream::in | std::fstream::out | std::fstream::trunc);
		compareVectorAttribues(fs, stl_vector, ft_vector);
		compareVectorAttribues(fs, stl_copy_vector, ft_copy_vector);
		one = (!(stl_vector > stl_copy_vector) && !(ft_vector > ft_copy_vector));

		stl_vector.erase(stl_vector.begin() + 3);
		ft_vector.erase(ft_vector.begin() + 3);

		compareVectorAttribues(fs, stl_vector, ft_vector);
		compareVectorAttribues(fs, stl_copy_vector, ft_copy_vector);
		two = (!(stl_vector > stl_copy_vector) && !(ft_vector > ft_copy_vector));

		stl_vector.erase(stl_vector.begin());
		ft_vector.erase(ft_vector.begin());

		compareVectorAttribues(fs, stl_vector, ft_vector);
		compareVectorAttribues(fs, stl_copy_vector, ft_copy_vector);
		three = ((stl_vector > stl_copy_vector) && (ft_vector > ft_copy_vector));

		if (one && two && three)
			printResult(true);
		else
			printResult(false);
		fs.close();
	}

	/*OPERATOR>=*/
	{
		std::vector<int> stl_vector;
		ft::vector<int> ft_vector;
		bool one=false, two=false, three=false;

		for (size_t i = 0; i < 100; ++i) {
			stl_vector.push_back(i);
			ft_vector.push_back(i);
		}

		std::vector<int> stl_copy_vector(stl_vector);
		ft::vector<int> ft_copy_vector(ft_vector);

		stl_copy_vector.erase(stl_copy_vector.begin() + 3);
		ft_copy_vector.erase(ft_copy_vector.begin() + 3);

		fs.open("./test/vector_output/operator>=", std::fstream::in | std::fstream::out | std::fstream::trunc);
		compareVectorAttribues(fs, stl_vector, ft_vector);
		compareVectorAttribues(fs, stl_copy_vector, ft_copy_vector);
		one = (!(stl_vector >= stl_copy_vector) && !(ft_vector >= ft_copy_vector));

		stl_vector.erase(stl_vector.begin() + 3);
		ft_vector.erase(ft_vector.begin() + 3);

		compareVectorAttribues(fs, stl_vector, ft_vector);
		compareVectorAttribues(fs, stl_copy_vector, ft_copy_vector);
		two = ((stl_vector >= stl_copy_vector) && (ft_vector >= ft_copy_vector));

		stl_vector.erase(stl_vector.begin());
		ft_vector.erase(ft_vector.begin());

		compareVectorAttribues(fs, stl_vector, ft_vector);
		compareVectorAttribues(fs, stl_copy_vector, ft_copy_vector);
		three = ((stl_vector >= stl_copy_vector) && (ft_vector >= ft_copy_vector));

		if (one && two && three)
			printResult(true);
		else
			printResult(false);

		fs.close();
	}
	std::cout << std::endl;

	std::cout << "Random:";
	{
		std::cout << RED << " currently is under development" << RESET;
	}
	std::cout << std::endl;
}

int main(int ac, char** av) {
	test_vector();
	return 0;
}