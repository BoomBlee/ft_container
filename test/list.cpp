#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <iterator>
#include <sys/stat.h>
#include "../list.hpp"
#include "color.hpp"

template <typename T>
bool compareListContent(std::list<T>& stl_list, ft::list<T>& my_list) {
	typename ft::list<T>::iterator ft_it = my_list.begin();
	typename std::list<T>::iterator stl_it = stl_list.begin();
	if (my_list.size() != stl_list.size())
		return false;
	for(typename std::list<T>::iterator ite = stl_list.end(); stl_it != ite; ++ft_it, ++stl_it) {
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
bool compareListAttribues(std::fstream& fs, std::list<T>& stl_list, ft::list<T>& my_list) {
	
	bool empty = equalBool(stl_list.empty(), my_list.empty());
	bool size = equalBool(stl_list.size(), my_list.size());
	bool max_size = equalBool(stl_list.max_size(), my_list.max_size());
	bool content = compareListContent(stl_list, my_list);

	fs << std::endl << "------------------------------" << std::endl;
	fs << "STL : " << std::endl;
	fs << "Empty		: " << stl_list.empty() << std::endl;
	fs << "Size		: " << stl_list.size() << std::endl;
	fs << "Max_size	: " << stl_list.max_size() << std::endl;
	fs << "Content	: " << "{ ";

	typename std::list<T>::iterator stl_it = stl_list.begin();
	typename std::list<T>::iterator ite = stl_list.end();
    while (stl_it != ite) {
        fs << *stl_it;
        if (++stl_it != ite)
            fs << ", ";
    }
    fs << " }" << std::endl << std::endl;


	fs << "FT : " << std::endl;
	fs << "Empty		: " << my_list.empty() << std::endl;
	fs << "Size		: " << my_list.size() << std::endl;
	fs << "Max_size	: " << my_list.max_size() << std::endl;
	fs << "Content	: " << "{ ";

    typename ft::list<T>::iterator ft_it = my_list.begin();
	typename ft::list<T>::iterator ft_ite = my_list.end();
    while(ft_it != ft_ite) {
        fs << *ft_it;
        if (++ft_it != ft_ite)
            fs << ", ";
    }
    fs << " }" << std::endl;

	fs << "------------------------------" << std::endl;

	if (empty && size && max_size && content)
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

void test_list() {
	std::fstream fs;

	std::cout << YELLOW << "LIST :" << RESET <<std::endl;
	mkdir("./test/list_output", 0777);

	/*DEFAULT CONSTRUCTOR*/
	std::cout << "CONSTRUCTOR:";
	{
		std::list<int> stl_list;
		ft::list<int> ft_list;

		fs.open("./test/list_output/constructor_default", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareListAttribues(fs, stl_list, ft_list));
		fs.close();
	}

	{
		std::list<int> stl_list(0);
		ft::list<int> ft_list(0);

		fs.open("./test/list_output/constructor_fill_empty", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareListAttribues(fs, stl_list, ft_list));
		fs.close();
	}

	{
		std::list<int> stl_list(5);
		ft::list<int> ft_list(5);

		fs.open("./test/list_output/constructor_fill", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareListAttribues(fs, stl_list, ft_list));
		fs.close();
	}

	{
		std::list<int> stl_list(11,9);
		ft::list<int> ft_list(11,9);

		fs.open("./test/list_output/constructor_fill_size", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareListAttribues(fs, stl_list, ft_list));
		fs.close();
	}

	{
		std::vector<int> vect;
		vect.push_back(12);
		vect.push_back(765);
		vect.push_back(-35);
		vect.push_back(89);
		vect.push_back(65);

		std::list<int> stl_list(vect.begin(),vect.end());
		ft::list<int> ft_list(vect.begin(),vect.end());

		fs.open("./test/list_output/constructor_range", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareListAttribues(fs, stl_list, ft_list));
		fs.close();
	}

	{
		std::list<int> vect;
		vect.push_back(12);
		vect.push_back(765);
		vect.push_back(-35);
		vect.push_back(89);
		vect.push_back(65);
		vect.push_back(76);

		std::list<int> stl_list(vect.begin(),vect.end());
		ft::list<int> ft_list(vect.begin(),vect.end());

		std::list<int> stl_copy_list(stl_list);
		ft::list<int> ft_copy_list(ft_list);

		fs.open("./test/list_output/constructor_copy", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareListAttribues(fs, stl_copy_list, ft_copy_list));
		fs.close();
	}
	std::cout << std::endl;

	/*ASSIGN*/
	std::cout << "ASSIGN:";
	{
		std::vector<int> vect;
		vect.push_back(765);
		vect.push_back(-35);
		vect.push_back(65);
		vect.push_back(76);

		std::list<int> stl_list(vect.begin(),vect.end());
		ft::list<int> ft_list(vect.begin(),vect.end());

		std::list<int> stl_copy_list = stl_list;
		ft::list<int> ft_copy_list = ft_list;

		fs.open("./test/list_output/operator_assign", std::fstream::in | std::fstream::out | std::fstream::trunc);
		bool one = compareListAttribues(fs, stl_copy_list, ft_copy_list);
		bool two = compareListAttribues(fs, stl_list, ft_list);
		if (one && two)
			printResult(true);
		else
			printResult(false);
		fs.close();
	}
	std::cout << std::endl;

	std::cout << "Iterators:";
	/*BEGIN*/
	{
		std::vector<int> vect;
		vect.push_back(765);
		vect.push_back(-35);
		vect.push_back(65);
		vect.push_back(76);

		std::list<int> stl_list(vect.begin(),vect.end());
		ft::list<int> ft_list(vect.begin(),vect.end());

		int stl_value = *(stl_list.begin());
		int ft_value = *(ft_list.begin());

		fs.open("./test/list_output/iterator_begin", std::fstream::in | std::fstream::out | std::fstream::trunc);
		compareListAttribues(fs, stl_list, ft_list);
		printResult(equalBool(stl_value,ft_value));
		fs.close();
	}

	/*END*/
	{
		std::vector<int> vect;
		vect.push_back(765);
		vect.push_back(-35);
		vect.push_back(65);
		vect.push_back(76);

		std::list<int> stl_list(vect.begin(),vect.end());
		ft::list<int> ft_list(vect.begin(),vect.end());

		int stl_value = *(--stl_list.end());
		int ft_value = *(--ft_list.end());

		fs.open("./test/list_output/iterator_end", std::fstream::in | std::fstream::out | std::fstream::trunc);
		compareListAttribues(fs, stl_list, ft_list);
		printResult(equalBool(stl_value,ft_value));
		fs << "stl_value : " << stl_value << std::endl;
		fs << "ft_value : " << ft_value << std::endl;
		fs.close();
	}

	/*OPERATOR++*/
	{
		std::vector<int> vect;
		vect.push_back(765);
		vect.push_back(-35);
		vect.push_back(65);
		vect.push_back(76);
		vect.push_back(100);
		vect.push_back(94);

		std::list<int> stl_list(vect.begin(),vect.end());
		ft::list<int> ft_list(vect.begin(),vect.end());

		std::list<int>::iterator stl_it = stl_list.begin();
		std::list<int>::iterator stl_it1 = stl_it++;
		std::list<int>::iterator stl_it2 = ++stl_it;

		ft::list<int>::iterator ft_it = ft_list.begin();
		ft::list<int>::iterator ft_it1 = ft_it++;
		ft::list<int>::iterator ft_it2 = ++ft_it;

		if (*stl_it == *ft_it && *stl_it1 == *ft_it1 && *stl_it2 == *ft_it2)
			printResult(true);
		else
			printResult(false);

		fs.open("./test/list_output/iterator_operator++", std::fstream::in | std::fstream::out | std::fstream::trunc);
		compareListAttribues(fs, stl_list, ft_list);

		fs << "stl_value : " << *stl_it << " " << *stl_it1 << " " << *stl_it2 << std::endl;
		fs << "ft_value : " << *ft_it << " " << *ft_it1 << " " << *ft_it2 << std::endl;
		fs.close();
	}

	/*OPERATOR--*/
	{
		std::vector<int> vect;
		vect.push_back(765);
		vect.push_back(-35);
		vect.push_back(65);
		vect.push_back(76);
		vect.push_back(100);
		vect.push_back(94);

		std::list<int> stl_list(vect.begin(),vect.end());
		ft::list<int> ft_list(vect.begin(),vect.end());

		std::list<int>::iterator stl_it = stl_list.begin();
		stl_it++;
		std::list<int>::iterator stl_it1 = stl_it--;
		stl_it++;
		std::list<int>::iterator stl_it2 = --stl_it;

		ft::list<int>::iterator ft_it = ft_list.begin();
		ft_it++;
		ft::list<int>::iterator ft_it1 = ft_it--;
		ft_it++;
		ft::list<int>::iterator ft_it2 = --ft_it;

		if (*stl_it == *ft_it && *stl_it1 == *ft_it1 && *stl_it2 == *ft_it2)
			printResult(true);
		else
			printResult(false);

		fs.open("./test/list_output/iterator_operator--", std::fstream::in | std::fstream::out | std::fstream::trunc);
		compareListAttribues(fs, stl_list, ft_list);

		fs << "stl_value : " << *stl_it << " " << *stl_it1 << " " << *stl_it2 << std::endl;
		fs << "ft_value : " << *ft_it << " " << *ft_it1 << " " << *ft_it2 << std::endl;
		fs.close();
	}

	/*OPERATOR->*/
	{
		std::vector<int> vect;
		vect.push_back(765);
		vect.push_back(-35);
		vect.push_back(65);
		vect.push_back(76);

		std::list<int> stl_list(vect.begin(),vect.end());
		ft::list<int> ft_list(vect.begin(),vect.end());

		std::list<int>::iterator stl_it = stl_list.begin();
		ft::list<int>::iterator ft_it = ft_list.begin();

		fs.open("./test/list_output/iterator_operator->", std::fstream::in | std::fstream::out | std::fstream::trunc);
		compareListAttribues(fs, stl_list, ft_list);
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

		std::list<int> stl_list(lst.begin(),lst.end());
		ft::list<int> ft_list(lst.begin(),lst.end());

		std::list<int>::iterator stl_it = stl_list.begin();
		ft::list<int>::iterator ft_it = ft_list.begin();

		*stl_it = -10000;
		*ft_it = -10000;

		fs.open("./test/list_output/iterator_operator=", std::fstream::in | std::fstream::out | std::fstream::trunc);
		compareListAttribues(fs, stl_list, ft_list);
		printResult(equalBool(*stl_it, *ft_it));
		fs << "stl_value : " << *stl_it << std::endl;
		fs << "ft_value : " << *ft_it << std::endl;
		fs.close();
	}
	std::cout << std::endl;

	std::cout << "Reverse Iterators: ";
	/*BEGIN*/
	{
		std::vector<int> vect;
		vect.push_back(765);
		vect.push_back(-35);
		vect.push_back(65);
		vect.push_back(76);

		std::list<int> stl_list(vect.rbegin(),vect.rend());
		ft::list<int> ft_list(vect.rbegin(),vect.rend());

		int stl_value = *(stl_list.rbegin());
		int ft_value = *(ft_list.rbegin());

		fs.open("./test/list_output/reverse_iterator_begin", std::fstream::in | std::fstream::out | std::fstream::trunc);
		compareListAttribues(fs, stl_list, ft_list);
		printResult(equalBool(stl_value,ft_value));
		fs.close();
	}

	/*END*/
	{
		std::vector<int> vect;
		vect.push_back(765);
		vect.push_back(-35);
		vect.push_back(65);
		vect.push_back(76);

		std::list<int> stl_list(vect.rbegin(),vect.rend());
		ft::list<int> ft_list(vect.rbegin(),vect.rend());

		int stl_value = *(--stl_list.rend());
		int ft_value = *(--ft_list.rend());

		fs.open("./test/list_output/reverse_iterator_end", std::fstream::in | std::fstream::out | std::fstream::trunc);
		compareListAttribues(fs, stl_list, ft_list);
		printResult(equalBool(stl_value,ft_value));
		fs << "stl_value : " << stl_value << std::endl;
		fs << "ft_value : " << ft_value << std::endl;
		fs.close();
	}

	/*OPERATOR++*/
	{
		std::vector<int> vect;
		vect.push_back(765);
		vect.push_back(-35);
		vect.push_back(65);
		vect.push_back(76);
		vect.push_back(100);
		vect.push_back(94);

		std::list<int> stl_list(vect.rbegin(),vect.rend());
		ft::list<int> ft_list(vect.rbegin(),vect.rend());

		std::list<int>::reverse_iterator stl_it = stl_list.rbegin();
		std::list<int>::reverse_iterator stl_it1 = stl_it++;
		std::list<int>::reverse_iterator stl_it2 = ++stl_it;

		ft::list<int>::reverse_iterator ft_it = ft_list.rbegin();
		ft::list<int>::reverse_iterator ft_it1 = ft_it++;
		ft::list<int>::reverse_iterator ft_it2 = ++ft_it;

		if (*stl_it == *ft_it && *stl_it1 == *ft_it1 && *stl_it2 == *ft_it2)
			printResult(true);
		else
			printResult(false);

		fs.open("./test/list_output/reverse_iterator_operator++", std::fstream::in | std::fstream::out | std::fstream::trunc);
		compareListAttribues(fs, stl_list, ft_list);

		fs << "stl_value : " << *stl_it << " " << *stl_it1 << " " << *stl_it2 << std::endl;
		fs << "ft_value : " << *ft_it << " " << *ft_it1 << " " << *ft_it2 << std::endl;
		fs.close();
	}

	/*OPERATOR--*/
	{
		std::vector<int> vect;
		vect.push_back(765);
		vect.push_back(-35);
		vect.push_back(65);
		vect.push_back(76);
		vect.push_back(100);
		vect.push_back(94);

		std::list<int> stl_list(vect.rbegin(),vect.rend());
		ft::list<int> ft_list(vect.rbegin(),vect.rend());

		std::list<int>::reverse_iterator stl_it = stl_list.rbegin();
		stl_it++;
		std::list<int>::reverse_iterator stl_it1 = stl_it--;
		stl_it++;
		std::list<int>::reverse_iterator stl_it2 = --stl_it;

		ft::list<int>::reverse_iterator ft_it = ft_list.rbegin();
		ft_it++;
		ft::list<int>::reverse_iterator ft_it1 = ft_it--;
		ft_it++;
		ft::list<int>::reverse_iterator ft_it2 = --ft_it;

		if (*stl_it == *ft_it && *stl_it1 == *ft_it1 && *stl_it2 == *ft_it2)
			printResult(true);
		else
			printResult(false);

		fs.open("./test/list_output/reverse_iterator_operator--", std::fstream::in | std::fstream::out | std::fstream::trunc);
		compareListAttribues(fs, stl_list, ft_list);

		fs << "stl_value : " << *stl_it << " " << *stl_it1 << " " << *stl_it2 << std::endl;
		fs << "ft_value : " << *ft_it << " " << *ft_it1 << " " << *ft_it2 << std::endl;
		fs.close();
	}

	/*OPERATOR->*/
	{
		std::vector<int> vect;
		vect.push_back(765);
		vect.push_back(-35);
		vect.push_back(65);
		vect.push_back(76);

		std::list<int> stl_list(vect.rbegin(),vect.rend());
		ft::list<int> ft_list(vect.rbegin(),vect.rend());

		std::list<int>::reverse_iterator stl_it = stl_list.rbegin();
		ft::list<int>::reverse_iterator ft_it = ft_list.rbegin();

		fs.open("./test/list_output/reverse_iterator_operator->", std::fstream::in | std::fstream::out | std::fstream::trunc);
		compareListAttribues(fs, stl_list, ft_list);
		printResult(equalBool(*stl_it.operator->(), *ft_it.operator->()));
		fs << "stl_value : " << *stl_it.operator->() << std::endl;
		fs << "ft_value : " << *ft_it.operator->() << std::endl;
		fs.close();
	}
	
	/*OPERATOR=*/
	{
		std::vector<int> vect;
		vect.push_back(765);
		vect.push_back(-35);
		vect.push_back(65);
		vect.push_back(76);

		std::list<int> stl_list(vect.rbegin(),vect.rend());
		ft::list<int> ft_list(vect.rbegin(),vect.rend());

		std::list<int>::reverse_iterator stl_it = stl_list.rbegin();
		ft::list<int>::reverse_iterator ft_it = ft_list.rbegin();

		*stl_it = -10000;
		*ft_it = -10000;

		fs.open("./test/list_output/reverse_iterator_operator=", std::fstream::in | std::fstream::out | std::fstream::trunc);
		compareListAttribues(fs, stl_list, ft_list);
		printResult(equalBool(*stl_it, *ft_it));
		fs << "stl_value : " << *stl_it << std::endl;
		fs << "ft_value : " << *ft_it << std::endl;
		fs.close();
	}
	std::cout << std::endl;

	std::cout << "Capacity:";
	{
		printResult(true);
	}
	std::cout << std::endl;

	std::cout << "Element access:";
	/*FRONT*/
	{
		std::vector<int> vect;
		vect.push_back(765);
		vect.push_back(-35);
		vect.push_back(65);
		vect.push_back(76);

		std::list<int> stl_list(vect.rbegin(),vect.rend());
		ft::list<int> ft_list(vect.rbegin(),vect.rend());

		fs.open("./test/list_output/reverse_iterator_operator->", std::fstream::in | std::fstream::out | std::fstream::trunc);
		compareListAttribues(fs, stl_list, ft_list);
		printResult(equalBool(stl_list.front(), ft_list.front()));
		fs << "stl_value : " << stl_list.front() << std::endl;
		fs << "ft_value : " << ft_list.front() << std::endl;
		fs.close();
	}

	/*BACK*/
	{
		std::vector<int> vect;
		vect.push_back(765);
		vect.push_back(-35);
		vect.push_back(65);
		vect.push_back(76);

		std::list<int> stl_list(vect.rbegin(),vect.rend());
		ft::list<int> ft_list(vect.rbegin(),vect.rend());

		fs.open("./test/list_output/reverse_iterator_operator->", std::fstream::in | std::fstream::out | std::fstream::trunc);
		compareListAttribues(fs, stl_list, ft_list);
		printResult(equalBool(stl_list.back(), ft_list.back()));
		fs << "stl_value : " << stl_list.back() << std::endl;
		fs << "ft_value : " << ft_list.back() << std::endl;
		fs.close();
	}

	std::cout << std::endl;
}

int main(int ac, char** av) {
	test_list();
	return 0;
}