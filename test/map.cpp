#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <iterator>
#include <sys/stat.h>
#include "../vector.hpp"
#include "color.hpp"
#include <map>
#include "../map.hpp"

short unsigned int count_map = 0;
short unsigned int quantity_map = 0;
bool costil_map = false;

template <typename Key, typename T>
static bool compareMapContent(std::map<Key, T>& stl_map, ft::map<Key, T>& my_map) {
	typename ft::map<Key, T>::iterator ft_it = my_map.begin();
	typename std::map<Key, T>::iterator stl_it = stl_map.begin();
	if (my_map.size() != stl_map.size())
		return false;
	for(typename std::map<Key, T>::iterator ite = stl_map.end(); stl_it != ite; ++ft_it, ++stl_it) {
		if (*ft_it != *stl_it)
			return false;
	}
	return true;
}

template <typename T>
static bool equalBool(T t1, T t2) {
	return t1 == t2;
}

template <typename Key, typename T>
static bool compareMapAttribues(std::fstream& fs, std::map<Key, T>& stl_map, ft::map<Key, T>& my_map) {
	
	bool empty = equalBool(stl_map.empty(), my_map.empty());
	bool size = equalBool(stl_map.size(), my_map.size());
	bool max_size = equalBool(stl_map.max_size(), my_map.max_size());
	bool content = compareMapContent(stl_map, my_map);

	fs << std::endl << "------------------------------" << std::endl;
	fs << "STL : " << std::endl;
	fs << "Empty		: " << stl_map.empty() << std::endl;
	fs << "Size		: " << stl_map.size() << std::endl;
	fs << "Max_size	: " << stl_map.max_size() << std::endl;
	fs << "Content	: " << "{ ";

	typename std::map<Key, T>::iterator stl_it = stl_map.begin();
	typename std::map<Key, T>::iterator ite = stl_map.end();
    while (stl_it != ite) {
        fs << (*stl_it).first;
        if (++stl_it != ite)
            fs << ", ";
    }
    fs << " }" << std::endl << std::endl;


	fs << "FT : " << std::endl;
	fs << "Empty		: " << my_map.empty() << std::endl;
	fs << "Size		: " << my_map.size() << std::endl;
	fs << "Max_size	: " << my_map.max_size() << std::endl;
	fs << "Content	: " << "{ ";

	typename ft::map<Key, T>::iterator ft_it = my_map.begin();
	typename ft::map<Key, T>::iterator ft_ite = my_map.end();
    // while(ft_it != ft_ite) {
    //     fs << *ft_it;
    //     if (++ft_it != ft_ite)
    //         fs << ", ";
    // }
    fs << " }" << std::endl;

	fs << "------------------------------" << std::endl;

	if (empty && size && max_size && content)
		return true;
	else if (empty && size && !max_size && content)
		costil_map = true;
	return false;
}

static void printResult(bool res) {
	++quantity_map;
	if (res) {
		std::cout << GREEN << " [OK]" << RESET;
		++count_map;
		return ;
	}
	if (costil_map) {
		std::cout << YELLOW << " [OK]" << RESET;
		costil_map = false;
		++count_map;
		return ;
	}
	std::cout << RED << " [NO]" << RESET;
}
void test_map() {
	std::fstream fs;

	std::cout << YELLOW << "MAP :" << RESET <<std::endl;
	mkdir("./test/map_output", 0777);

	/*DEFAULT CONSTRUCTOR*/
	std::cout << "CONSTRUCTOR:";
	{
		std::map<int, int> stl_map;
		ft::map<int, int> ft_map;

		fs.open("./test/map_output/constructor_default", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareMapAttribues(fs, stl_map, ft_map));
		fs.close();
	}
}

short unsigned int getCount_map() {return count_map;}
short unsigned int getQuantity_map() {return quantity_map;}

int main() {
	test_map();
	return 0;
}