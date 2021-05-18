#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <iterator>
#include <sys/stat.h>
#include <cmath>
#include "../list.hpp"
#include "color.hpp"

short unsigned int count_list = 0;
short unsigned int quantity_list = 0;
bool costil_list = false;

static bool func(const int& value) {return value%2;}

static bool func1(const int& first, const int& second) {return std::abs(first - second) < 30;}

static bool compare_nocase(const std::string& first, const std::string& second)
{
  unsigned int i=0;
  while ( (i<first.length()) && (i<second.length()) )
  {
    if (tolower(first[i])<tolower(second[i])) return true;
    else if (tolower(first[i])>tolower(second[i])) return false;
    ++i;
  }
  return ( first.length() < second.length() );
}

static bool func2 (int first, int second) {return first > second;}

template <typename T>
static bool compareListContent(std::list<T>& stl_list, ft::list<T>& my_list) {
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
static bool equalBool(T t1, T t2) {
	return t1 == t2;
}

template <class T>
static bool compareListAttribues(std::fstream& fs, std::list<T>& stl_list, ft::list<T>& my_list) {
	
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
	if (empty && size && !max_size && content)
		costil_list = true;
	return false;
}

static void printResult(bool res) {
	++quantity_list;
	if (res) {
		std::cout << GREEN << " [OK]" << RESET;
		++count_list;
		return ;
	}
	if (costil_list) {
		std::cout << YELLOW << " [OK]" << RESET;
		costil_list = false;
		++count_list;
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
		
		printResult(one && two);
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

		printResult(*stl_it == *ft_it && *stl_it1 == *ft_it1 && *stl_it2 == *ft_it2);

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

		printResult(*stl_it == *ft_it && *stl_it1 == *ft_it1 && *stl_it2 == *ft_it2);

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

		printResult(*stl_it == *ft_it && *stl_it1 == *ft_it1 && *stl_it2 == *ft_it2);

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

		printResult(*stl_it == *ft_it && *stl_it1 == *ft_it1 && *stl_it2 == *ft_it2);

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
		std::list<int> stl_list;
		ft::list<int> ft_list;

		fs.open("./test/list_output/capacity", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareListAttribues(fs, stl_list, ft_list));
		fs.close();
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

		fs.open("./test/list_output/front", std::fstream::in | std::fstream::out | std::fstream::trunc);
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

		fs.open("./test/list_output/back", std::fstream::in | std::fstream::out | std::fstream::trunc);
		compareListAttribues(fs, stl_list, ft_list);
		printResult(equalBool(stl_list.back(), ft_list.back()));
		fs << "stl_value : " << stl_list.back() << std::endl;
		fs << "ft_value : " << ft_list.back() << std::endl;
		fs.close();
	}
	std::cout << std::endl;

	std::cout << "Modifiers:";
	/*ASSIGN*/
	{
		std::vector<int> vect;
		vect.push_back(765);
		vect.push_back(-35);
		vect.push_back(65);
		vect.push_back(76);

		std::list<int> stl_list;
		ft::list<int> ft_list;
		stl_list.assign(vect.begin(), vect.end());
		ft_list.assign(vect.begin(), vect.end());
		fs.open("./test/list_output/assign", std::fstream::in | std::fstream::out | std::fstream::trunc);
		bool one = compareListAttribues(fs, stl_list, ft_list);

		stl_list.assign(11, 55);
		ft_list.assign(11, 55);
		bool two = compareListAttribues(fs, stl_list, ft_list);

		printResult(one && two);
		fs.close();
	}

	/*PUSH_FRONT*/
	{
		std::list<int> stl_list(2, 5);
		ft::list<int> ft_list(2, 5);

		for (size_t i = 0; i < 33; ++i) {
			stl_list.push_front(i);
			ft_list.push_front(i);
		}
		

		fs.open("./test/list_output/push_front", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareListAttribues(fs, stl_list, ft_list));

		fs.close();
	}
	
	/*POP_FRONT*/
	{
		std::list<int> stl_list(2, 5);
		ft::list<int> ft_list(2, 5);
		
		for (size_t i = 0; i < 33; ++i) {
			stl_list.push_front(i);
			ft_list.push_front(i);
		}	
		for (size_t i = 0; i < 10; ++i) {
			stl_list.pop_front();
			ft_list.pop_front();
		}

		fs.open("./test/list_output/pop_front", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareListAttribues(fs, stl_list, ft_list));

		fs.close();
	}

	/*PUSH_BACK*/
	{
		std::list<int> stl_list;
		ft::list<int> ft_list;
		
		for (size_t i = 0; i < 33; ++i) {
			stl_list.push_back(i);
			ft_list.push_back(i);
		}
		

		fs.open("./test/list_output/push_back", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareListAttribues(fs, stl_list, ft_list));

		fs.close();
	}
	
	/*POP_BACK*/
	{
		std::list<int> stl_list;
		ft::list<int> ft_list;
		
		for (size_t i = 0; i < 33; ++i) {
			stl_list.push_back(i);
			ft_list.push_back(i);
		}	
		for (size_t i = 0; i < 10; ++i) {
			stl_list.pop_back();
			ft_list.pop_back();
		}

		fs.open("./test/list_output/pop_back", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareListAttribues(fs, stl_list, ft_list));

		fs.close();
	}

	/*INSERT*/
	{
		std::vector<int> vect;
		vect.push_back(765);
		vect.push_back(-35);
		vect.push_back(65);
		vect.push_back(76);

		std::list<int> stl_list;
		ft::list<int> ft_list;
		std::list<int>::iterator stl_it;
		ft::list<int>::iterator ft_it;
		
		for (size_t i = 0; i < 10; ++i) {
			stl_it = stl_list.insert(stl_list.begin(), i);
			ft_it = ft_list.insert(ft_list.begin(), i);
		}

		fs.open("./test/list_output/insert", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareListAttribues(fs, stl_list, ft_list));

		stl_list.insert(stl_list.end(), 2, 79);
		ft_list.insert(ft_list.end(), 2, 79);
		printResult(compareListAttribues(fs, stl_list, ft_list));

		stl_list.insert(stl_list.begin(), vect.begin(), vect.end());
		ft_list.insert(ft_list.begin(), vect.begin(), vect.end());
		printResult(compareListAttribues(fs, stl_list, ft_list));

		printResult(equalBool(*stl_it, *ft_it));
		fs << "stl_value : " << *stl_it << std::endl;
		fs << "ft_value : " << *ft_it << std::endl;

		fs.close();
	}

	/*ERASE*/
	{
		std::list<int> stl_list;
		ft::list<int> ft_list;
		std::list<int>::iterator stl_it;
		ft::list<int>::iterator ft_it;

		std::list<int>::iterator stl_it1;
		ft::list<int>::iterator ft_it1;
		std::list<int>::iterator stl_it2;
		ft::list<int>::iterator ft_it2;

		
		for (size_t i = 2; i < 20; ++i) {
			stl_list.insert(stl_list.begin(), i);
			ft_list.insert(ft_list.begin(), i);
		}

		stl_it = stl_list.erase(stl_list.begin());
		ft_it = ft_list.erase(ft_list.begin());

		fs.open("./test/list_output/erase", std::fstream::in | std::fstream::out | std::fstream::trunc);
		bool one = compareListAttribues(fs, stl_list, ft_list);
		bool two = equalBool(*stl_it, *ft_it);
		fs << "stl_value : " << *stl_it << std::endl;
		fs << "ft_value : " << *ft_it << std::endl;

		stl_it1 = stl_list.begin();
		ft_it1 = ft_list.begin();
		stl_it2 = stl_list.end();
		ft_it2 = ft_list.end();

		for (size_t i = 0; i < 4; ++i) {
			++stl_it1;
			--stl_it2;
			++ft_it1;
			--ft_it2;
		}

		stl_it = stl_list.erase(stl_it1, stl_it2);
		ft_it = ft_list.erase(ft_it1, ft_it2);

		bool three = compareListAttribues(fs, stl_list, ft_list);
		bool four = equalBool(*stl_it, *ft_it);

		fs << "stl_value : " << *stl_it << std::endl;
		fs << "ft_value : " << *ft_it << std::endl;

		printResult(one && two && three && four);

		fs.close();
	}

	/*SWAP*/
	{
		std::list<int> stl_list;
		ft::list<int> ft_list;
		std::list<int> stl_swap_list;
		ft::list<int> ft_swap_list;
		
		for (size_t i = 0; i < 10; ++i) {
			stl_list.push_back(i);
			ft_list.push_back(i);
		}		
		for (size_t i = 100; i > 87; --i) {
			stl_swap_list.push_back(i);
			ft_swap_list.push_back(i);
		}

		stl_list.swap(stl_swap_list);
		ft_list.swap(ft_swap_list);

		fs.open("./test/list_output/swap", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareListAttribues(fs, stl_list, ft_list) &&
				compareListAttribues(fs, stl_swap_list, ft_swap_list));

		fs.close();
	}

	/*RESIZE*/
	{
		std::list<int> stl_list;
		ft::list<int> ft_list;

		bool one, two, three, four, five;

		stl_list.resize(0);
		ft_list.resize(0);

		fs.open("./test/list_output/resize", std::fstream::in | std::fstream::out | std::fstream::trunc);
		one = compareListAttribues(fs, stl_list, ft_list);

		stl_list.resize(10);
		ft_list.resize(10);
		two = compareListAttribues(fs, stl_list, ft_list);

		stl_list.resize(7, 1);
		ft_list.resize(7, 1);
		three = compareListAttribues(fs, stl_list, ft_list);

		stl_list.resize(12);
		ft_list.resize(12);
		four = compareListAttribues(fs, stl_list, ft_list);

		stl_list.resize(15, 100);
		ft_list.resize(15, 100);
		five = compareListAttribues(fs, stl_list, ft_list);

		printResult(one && two && three && four && five);

		fs.close();
	}

	/*CLEAR*/
	{
		std::list<int> stl_list;
		ft::list<int> ft_list;
		
		for (size_t i = 0; i < 100; ++i) {
			stl_list.push_back(i);
			ft_list.push_back(i);
		}

		stl_list.clear();
		ft_list.clear();

		fs.open("./test/list_output/clear", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareListAttribues(fs, stl_list, ft_list));

		fs.close();
	}
	std::cout << std::endl;

	std::cout << "Operations:";
	/*SPLICE*/
	{
		std::list<int> stl_list;
		ft::list<int> ft_list;
		std::list<int> stl_list_copy;
		ft::list<int> ft_list_copy;
		std::list<int> stl_list_copy1;
		ft::list<int> ft_list_copy1;

		std::list<int>::iterator stl_it;
		ft::list<int>::iterator ft_it;
		std::list<int>::iterator stl_copy_it;
		ft::list<int>::iterator ft_copy_it;
		std::list<int>::iterator stl_copy_it1;
		ft::list<int>::iterator ft_copy_it1;

		for (size_t i = 0; i < 27; ++i) {
			stl_list.push_back(i);
			ft_list.push_back(i);
			stl_list_copy.push_back(i + 50);
			ft_list_copy.push_back(i + 50);
			stl_list_copy1.push_back(i * -1);
			ft_list_copy1.push_back(i * -1);
		}

		stl_it = stl_list.begin();
		ft_it = ft_list.begin();
		stl_copy_it = stl_list_copy.end();
		ft_copy_it = ft_list_copy.end();

		for (size_t i = 0; i < 9; ++i) {
			++stl_it;
			--stl_copy_it;
			++ft_it;
			--ft_copy_it;
		}

		stl_list.splice(++stl_it, stl_list_copy);
		ft_list.splice(++ft_it, ft_list_copy);

		fs.open("./test/list_output/splice", std::fstream::in | std::fstream::out | std::fstream::trunc);
		bool one = compareListAttribues(fs, stl_list, ft_list);
		bool two = compareListAttribues(fs, stl_list_copy, ft_list_copy);

		stl_it = stl_list.begin();
		ft_it = ft_list.begin();
		stl_copy_it = stl_list_copy.end();
		ft_copy_it = ft_list_copy.end();

		stl_it = stl_list.begin();
		ft_it = ft_list.begin();
		stl_copy_it1 = stl_list_copy1.end();
		ft_copy_it1 = ft_list_copy1.end();

		for (size_t i = 0; i < 12; ++i) {
			++stl_it;
			--stl_copy_it1;
			++ft_it;
			--ft_copy_it1;
		}

		stl_list.splice(stl_it, stl_list_copy, stl_copy_it1++);
		ft_list.splice(ft_it, ft_list_copy, ft_copy_it1++);
		bool three = compareListAttribues(fs, stl_list, ft_list);
		bool four = compareListAttribues(fs, stl_list_copy1, ft_list_copy1);

		stl_list.splice(stl_it, stl_list_copy, stl_copy_it1, stl_list_copy1.end());
		ft_list.splice(ft_it, ft_list_copy, ft_copy_it1, ft_list_copy1.end());
		bool five = compareListAttribues(fs, stl_list, ft_list);
		bool six = compareListAttribues(fs, stl_list_copy1, ft_list_copy1);



		printResult(one && two && three && four && five && six);
		fs.close();
	}

	/*REMOVE*/
	{
		std::list<int> stl_list(10,2);
		ft::list<int> ft_list(10,2);

		stl_list.insert(stl_list.end(), 10, 13);
		ft_list.insert(ft_list.end(), 10, 13);

		stl_list.insert(stl_list.begin(), 3, 5);
		ft_list.insert(ft_list.begin(), 3, 5);

		stl_list.remove(2);
		ft_list.remove(2);

		fs.open("./test/list_output/remove", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareListAttribues(fs, stl_list, ft_list));

		fs.close();
	}

	/*REMOVE_IF*/
	{
		std::list<int> stl_list(10,2);
		ft::list<int> ft_list(10,2);

		for (size_t i = 0; i < 27; ++i) {
			stl_list.push_back(i);
			ft_list.push_back(i);
			stl_list.push_back(i + 50);
			ft_list.push_back(i + 50);
			stl_list.push_back(i * -1);
			ft_list.push_back(i * -1);
		}

		stl_list.remove_if(func);
		ft_list.remove_if(func);

		fs.open("./test/list_output/remove_if", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareListAttribues(fs, stl_list, ft_list));

		fs.close();
	}

	/*UNIQUE*/
	{
		std::list<int> stl_list(10,2);
		ft::list<int> ft_list(10,2);

		for (size_t i = 0; i < 27; ++i) {
			stl_list.push_back(i);
			ft_list.push_back(i);
			stl_list.push_back(i + 50);
			ft_list.push_back(i + 50);
			stl_list.push_back(i * -1);
			ft_list.push_back(i * -1);
		}

		stl_list.unique();
		ft_list.unique();

		fs.open("./test/list_output/unique", std::fstream::in | std::fstream::out | std::fstream::trunc);
		bool one = compareListAttribues(fs, stl_list, ft_list);

		stl_list.unique(func1);
		ft_list.unique(func1);

		bool two = compareListAttribues(fs, stl_list, ft_list);

		fs.close();
	}

	/*MERGE*/
	{
		std::list<int> stl_list(10,2);
		ft::list<int> ft_list(10,2);
		std::list<int> stl_list1(10,2);
		ft::list<int> ft_list1(10,2);

		for (size_t i = 0; i < 27; ++i) {
			stl_list.push_back(i);
			ft_list.push_back(i);
			stl_list1.push_back(i % 5 + 3);
			ft_list1.push_back(i % 5 + 3);
		}

		stl_list.sort();
		ft_list.sort();
		stl_list1.sort();
		ft_list1.sort();

		stl_list.merge(stl_list1);
		ft_list.merge(ft_list1);

		fs.open("./test/list_output/merge", std::fstream::in | std::fstream::out | std::fstream::trunc);
		bool one = compareListAttribues(fs, stl_list, ft_list) && compareListAttribues(fs, stl_list1, ft_list1);

		stl_list.clear();
		ft_list.clear();
		stl_list1.clear();
		ft_list1.clear();

		for (size_t i = 0; i < 27; ++i) {
			stl_list.push_back(i);
			ft_list.push_back(i);
			stl_list1.push_back(i % 5 + 3);
			ft_list1.push_back(i % 5 + 3);
		}

		stl_list.sort();
		ft_list.sort();
		stl_list1.sort();
		ft_list1.sort();

		stl_list.merge(stl_list1, func2);
		ft_list.merge(ft_list1, func2);

		bool two = compareListAttribues(fs, stl_list, ft_list) && compareListAttribues(fs, stl_list1, ft_list1);
		printResult(one && two);

		fs.close();
	}

	/*SORT*/
	{
		std::list<int> stl_list(10,2);
		ft::list<int> ft_list(10,2);
		std::list<int> stl_list1(2,3);
		ft::list<int> ft_list1(2,3);
		// std::list<std::string> stl_list_str(10, "tr");
		// ft::list<std::string> ft_list_str(10, "tr");

		for (size_t i = 0; i < 27; ++i) {
			stl_list.push_back(i);
			ft_list.push_back(i);
			stl_list.push_back(i + 50);
			ft_list.push_back(i + 50);
			stl_list.push_back(i * -1);
			ft_list.push_back(i * -1);
			stl_list1.push_back(i);
			ft_list1.push_back(i);
			stl_list1.push_back(i + 50);
			ft_list1.push_back(i + 50);
			stl_list1.push_back(i * -1);
			ft_list1.push_back(i * -1);
		}

		stl_list.sort();
		ft_list.sort();

		fs.open("./test/list_output/sort", std::fstream::in | std::fstream::out | std::fstream::trunc);
		bool one = compareListAttribues(fs, stl_list, ft_list);

		// stl_list_str.push_back("RfeG");
		// ft_list_str.push_back("RfeG");
		// stl_list_str.push_back("yYCFCRFCcfrfrfcrGRC");
		// ft_list_str.push_back("yYCFCRFCcfrfrfcrGRC");

		// stl_list_str.sort(compare_nocase);
		// ft_list_str.sort(compare_nocase);

		// bool two = compareListAttribues(fs, stl_list_str, ft_list_str);
	
		stl_list.sort(func2);
		ft_list.sort(func2);
		bool two = compareListAttribues(fs, stl_list1, ft_list1);

		printResult(one && two);
		fs.close();
	}

	/*REVERSE*/
	{
		std::list<int> stl_list(10,2);
		ft::list<int> ft_list(10,2);
		std::list<std::string> stl_list_str(10, "tr");
		ft::list<std::string> ft_list_str(10, "tr");

		for (size_t i = 0; i < 27; ++i) {
			stl_list.push_back(i);
			ft_list.push_back(i);
			stl_list.push_back(i + 50);
			ft_list.push_back(i + 50);
			stl_list.push_back(i * -1);
			ft_list.push_back(i * -1);
		}

		stl_list.reverse();
		ft_list.reverse();

		fs.open("./test/list_output/reverse", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareListAttribues(fs, stl_list, ft_list));
		fs.close();
	}
	std::cout << std::endl;

	std::cout << "Non-member function overloads:";
	/*OPERATOR==*/
	// {
	// 	std::list<int> stl_list;
	// 	ft::list<int> ft_list;
	// 	bool one=false, two=false;
		
	// 	for (size_t i = 0; i < 100; ++i) {
	// 		stl_list.push_back(i);
	// 		ft_list.push_back(i);
	// 	}

	// 	std::list<int> stl_copy_list(stl_list);
	// 	ft::list<int> ft_copy_list(ft_list);

	// 	fs.open("./test/list_output/operator==", std::fstream::in | std::fstream::out | std::fstream::trunc);
	// 	compareListAttribues(fs, stl_list, ft_list);
	// 	compareListAttribues(fs, stl_copy_list, ft_copy_list);
	// 	one = ((stl_list == stl_copy_list) && (ft_list == ft_copy_list));

	// 	stl_list.erase(++(++stl_list.begin()));
	// 	ft_list.erase(++(++ft_list.begin()));

	// 	compareListAttribues(fs, stl_list, ft_list);
	// 	compareListAttribues(fs, stl_copy_list, ft_copy_list);
	// 	two = (!(stl_list == stl_copy_list) && !(ft_list == ft_copy_list));

	// 	printResult(one && two);
	// 	fs.close();
	// }

	// /*OPERATOR!=*/
	// {
	// 	std::list<int> stl_list;
	// 	ft::list<int> ft_list;
	// 	bool one=false, two=false;
		
	// 	for (size_t i = 0; i < 100; ++i) {
	// 		stl_list.push_back(i);
	// 		ft_list.push_back(i);
	// 	}

	// 	std::list<int> stl_copy_list(stl_list);
	// 	ft::list<int> ft_copy_list(ft_list);

	// 	fs.open("./test/list_output/operato !=", std::fstream::in | std::fstream::out | std::fstream::trunc);
	// 	compareListAttribues(fs, stl_list, ft_list);
	// 	compareListAttribues(fs, stl_copy_list, ft_copy_list);
	// 	one = (!(stl_list != stl_copy_list) && !(ft_list != ft_copy_list));

	// 	stl_list.erase(++(++stl_list.begin()));
	// 	ft_list.erase(++(++ft_list.begin()));

	// 	compareListAttribues(fs, stl_list, ft_list);
	// 	compareListAttribues(fs, stl_copy_list, ft_copy_list);
	// 	two = ((stl_list != stl_copy_list) && (ft_list != ft_copy_list));

	// 	printResult(one && two);
	// 	fs.close();
	// }

	// /*OPERATOR<*/
	// {
	// 	std::list<int> stl_list;
	// 	ft::list<int> ft_list;
	// 	bool one=false, two=false, three=false;
		
	// 	for (size_t i = 0; i < 100; ++i) {
	// 		stl_list.push_back(i);
	// 		ft_list.push_back(i);
	// 	}

	// 	std::list<int> stl_copy_list(stl_list);
	// 	ft::list<int> ft_copy_list(ft_list);

	// 	stl_copy_list.erase(++(++stl_copy_list.begin()));
	// 	ft_copy_list.erase(++(++ft_copy_list.begin()));

	// 	fs.open("./test/list_output/operator<", std::fstream::in | std::fstream::out | std::fstream::trunc);
	// 	compareListAttribues(fs, stl_list, ft_list);
	// 	compareListAttribues(fs, stl_copy_list, ft_copy_list);
	// 	one = ((stl_list < stl_copy_list) && (ft_list < ft_copy_list));

	// 	stl_list.erase(++(++stl_list.begin()));
	// 	ft_list.erase(++(++ft_list.begin()));

	// 	compareListAttribues(fs, stl_list, ft_list);
	// 	compareListAttribues(fs, stl_copy_list, ft_copy_list);
	// 	two = (!(stl_list < stl_copy_list) && !(ft_list < ft_copy_list));

	// 	stl_list.erase(stl_list.begin());
	// 	ft_list.erase(ft_list.begin());

	// 	compareListAttribues(fs, stl_list, ft_list);
	// 	compareListAttribues(fs, stl_copy_list, ft_copy_list);
	// 	three = (!(stl_list < stl_copy_list) && !(ft_list < ft_copy_list));

	// 	printResult(one && two && three);
	// 	fs.close();
	// }

	// /*OPERATOR<=*/
	// {
	// 	std::list<int> stl_list;
	// 	ft::list<int> ft_list;
	// 	bool one=false, two=false, three=false;
		
	// 	for (size_t i = 0; i < 100; ++i) {
	// 		stl_list.push_back(i);
	// 		ft_list.push_back(i);
	// 	}

	// 	std::list<int> stl_copy_list(stl_list);
	// 	ft::list<int> ft_copy_list(ft_list);

	// 	stl_copy_list.erase(++(++stl_copy_list.begin()));
	// 	ft_copy_list.erase(++(++ft_copy_list.begin()));

	// 	fs.open("./test/list_output/operator<=", std::fstream::in | std::fstream::out | std::fstream::trunc);
	// 	compareListAttribues(fs, stl_list, ft_list);
	// 	compareListAttribues(fs, stl_copy_list, ft_copy_list);
	// 	one = ((stl_list <= stl_copy_list) && (ft_list <= ft_copy_list));

	// 	stl_list.erase(++(++stl_list.begin()));
	// 	ft_list.erase(++(++ft_list.begin()));

	// 	compareListAttribues(fs, stl_list, ft_list);
	// 	compareListAttribues(fs, stl_copy_list, ft_copy_list);
	// 	two = ((stl_list <= stl_copy_list) && (ft_list <= ft_copy_list));

	// 	stl_list.erase(stl_list.begin());
	// 	ft_list.erase(ft_list.begin());

	// 	compareListAttribues(fs, stl_list, ft_list);
	// 	compareListAttribues(fs, stl_copy_list, ft_copy_list);
	// 	three = (!(stl_list <= stl_copy_list) && !(ft_list <= ft_copy_list));

	// 	printResult(one && two && three);
	// 	fs.close();
	// }

	// /*OPERATOR>*/
	// {
	// 	std::list<int> stl_list;
	// 	ft::list<int> ft_list;
	// 	bool one=false, two=false, three=false;
		
	// 	for (size_t i = 0; i < 100; ++i) {
	// 		stl_list.push_back(i);
	// 		ft_list.push_back(i);
	// 	}

	// 	std::list<int> stl_copy_list(stl_list);
	// 	ft::list<int> ft_copy_list(ft_list);

	// 	stl_copy_list.erase(++(++stl_copy_list.begin()));
	// 	ft_copy_list.erase(++(++ft_copy_list.begin()));

	// 	fs.open("./test/list_output/operator>", std::fstream::in | std::fstream::out | std::fstream::trunc);
	// 	compareListAttribues(fs, stl_list, ft_list);
	// 	compareListAttribues(fs, stl_copy_list, ft_copy_list);
	// 	one = (!(stl_list > stl_copy_list) && !(ft_list > ft_copy_list));

	// 	stl_list.erase(++(++stl_list.begin()));
	// 	ft_list.erase(++(++ft_list.begin()));

	// 	compareListAttribues(fs, stl_list, ft_list);
	// 	compareListAttribues(fs, stl_copy_list, ft_copy_list);
	// 	two = (!(stl_list > stl_copy_list) && !(ft_list > ft_copy_list));

	// 	stl_list.erase(stl_list.begin());
	// 	ft_list.erase(ft_list.begin());

	// 	compareListAttribues(fs, stl_list, ft_list);
	// 	compareListAttribues(fs, stl_copy_list, ft_copy_list);
	// 	three = ((stl_list > stl_copy_list) && (ft_list > ft_copy_list));

	// 	printResult(one && two && three);
	// 	fs.close();
	// }

	// /*OPERATOR>=*/
	// {
	// 	std::list<int> stl_list;
	// 	ft::list<int> ft_list;
	// 	bool one=false, two=false, three=false;

	// 	for (size_t i = 0; i < 100; ++i) {
	// 		stl_list.push_back(i);
	// 		ft_list.push_back(i);
	// 	}

	// 	std::list<int> stl_copy_list(stl_list);
	// 	ft::list<int> ft_copy_list(ft_list);

	// 	stl_copy_list.erase(++(++stl_copy_list.begin()));
	// 	ft_copy_list.erase(++(++ft_copy_list.begin()));

	// 	fs.open("./test/list_output/operator>=", std::fstream::in | std::fstream::out | std::fstream::trunc);
	// 	compareListAttribues(fs, stl_list, ft_list);
	// 	compareListAttribues(fs, stl_copy_list, ft_copy_list);
	// 	one = (!(stl_list >= stl_copy_list) && !(ft_list >= ft_copy_list));

	// 	stl_list.erase(++(++stl_list.begin()));
	// 	ft_list.erase(++(++ft_list.begin()));

	// 	compareListAttribues(fs, stl_list, ft_list);
	// 	compareListAttribues(fs, stl_copy_list, ft_copy_list);
	// 	two = ((stl_list >= stl_copy_list) && (ft_list >= ft_copy_list));

	// 	stl_list.erase(stl_list.begin());
	// 	ft_list.erase(ft_list.begin());

	// 	compareListAttribues(fs, stl_list, ft_list);
	// 	compareListAttribues(fs, stl_copy_list, ft_copy_list);
	// 	three = ((stl_list >= stl_copy_list) && (ft_list >= ft_copy_list));

	// 	printResult(one && two && three);

	// 	fs.close();
	// }
	std::cout << RED << " NO WORK" << RESET;
	std::cout << std::endl;

	std::cout << "Random:";
	{
		std::cout << RED << " currently is under development" << RESET;
	}


	std::cout << std::endl;

}

short unsigned int getCount_list() {return count_list;}
short unsigned int getQuantity_list() {return quantity_list;}

// int main(int ac, char** av) {
// 	test_list();
// 	std::cout << CIAN << count_list << "/" << quantity_list << RESET << std::endl;
// 	return 0;
// }