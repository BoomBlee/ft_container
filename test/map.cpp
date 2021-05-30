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

template <typename T>
static bool compareVectorContent(std::vector<T>& stl_vect, std::vector<T>& my_vect) {
	typename std::vector<T>::iterator ft_it = my_vect.begin();
	typename std::vector<T>::iterator stl_it = stl_vect.begin();
	if (my_vect.size() != stl_vect.size())
		return false;
	for(typename std::vector<T>::iterator ite = stl_vect.end(); stl_it != ite; ++ft_it, ++stl_it) {
		if (*ft_it != *stl_it)
			return false;
	}
	return true;
}

template <class T>
static bool compareVectorAttribues(std::fstream& fs, std::vector<T>& stl_vect, std::vector<T>& my_vect) {
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

    typename std::vector<T>::iterator ft_it = my_vect.begin();
	typename std::vector<T>::iterator ft_ite = my_vect.end();
    while(ft_it != ft_ite) {
        fs << *ft_it;
        if (++ft_it != ft_ite)
            fs << ", ";
    }
    fs << " }" << std::endl;

	fs << "------------------------------" << std::endl;

	return stl_vect == my_vect;
}

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
	fs << "Content Key	: " << "{ ";

	typename std::map<Key, T>::iterator stl_it = stl_map.begin();
	typename std::map<Key, T>::iterator ite = stl_map.end();
    while (stl_it != ite) {
        fs << (*stl_it).first;
        if (++stl_it != ite)
            fs << ", ";
    }
    fs << " }" << std::endl;
	fs << "Content Val	: " << "{ ";

	stl_it = stl_map.begin();
	ite = stl_map.end();
    while (stl_it != ite) {
        fs << (*stl_it).second;
        if (++stl_it != ite)
            fs << ", ";
    }
    fs << " }" << std::endl << std::endl;


	fs << "FT : " << std::endl;
	fs << "Empty		: " << my_map.empty() << std::endl;
	fs << "Size		: " << my_map.size() << std::endl;
	fs << "Max_size	: " << my_map.max_size() << std::endl;
	fs << "Content Key	: " << "{ ";

	typename ft::map<Key, T>::iterator ft_it = my_map.begin();
	typename ft::map<Key, T>::iterator ft_ite = my_map.end();
    while(ft_it != ft_ite) {
        fs << (*ft_it).first;
        if (++ft_it != ft_ite)
            fs << ", ";
    }
    fs << " }" << std::endl;
	fs << "Content Val	: " << "{ ";

	ft_it = my_map.begin();
	ft_ite = my_map.end();
    while(ft_it != ft_ite) {
        fs << (*ft_it).second;
        if (++ft_it != ft_ite)
            fs << ", ";
    }
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

	std::cout << "Constructor:";
	/*DEFAULT CONSTRUCTOR*/
	{
		std::map<int, int> stl_map;
		ft::map<int, int> ft_map;

		fs.open("./test/map_output/constructor_default", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareMapAttribues(fs, stl_map, ft_map));
		fs.close();
	}
	{
		std::map<int, int> map;
		map.insert(std::pair<int, int>(50, 51));
		map.insert(std::pair<int, int>(40, 41));
		map.insert(std::pair<int, int>(60, 60));
		map.insert(std::pair<int, int>(55, 55));
		map.insert(std::pair<int, int>(80, 80));
		map.insert(std::pair<int, int>(70, 70));
		map.insert(std::pair<int, int>(75, 75));
		map.insert(std::pair<int, int>(90, 90));
		map.insert(std::pair<int, int>(85, 85));
		map.insert(std::pair<int, int>(200, 200));
		map.insert(std::pair<int, int>(250, 250));
		map.insert(std::pair<int, int>(300, 300));
		map.insert(std::pair<int, int>(77, 77));

		std::map<int, int> stl_map(map.begin(), map.end());
		ft::map<int, int> ft_map(map.begin(), map.end());

		fs.open("./test/map_output/constructor_range", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareMapAttribues(fs, stl_map, ft_map));
		fs.close();

	}
	{
		std::map<int, int> map;
		map.insert(std::pair<int, int>(50, 51));
		map.insert(std::pair<int, int>(40, 41));
		map.insert(std::pair<int, int>(60, 60));
		map.insert(std::pair<int, int>(55, 55));
		map.insert(std::pair<int, int>(80, 80));
		map.insert(std::pair<int, int>(70, 70));
		map.insert(std::pair<int, int>(75, 75));
		map.insert(std::pair<int, int>(90, 90));
		map.insert(std::pair<int, int>(85, 85));
		map.insert(std::pair<int, int>(200, 200));
		map.insert(std::pair<int, int>(250, 250));
		map.insert(std::pair<int, int>(300, 300));
		map.insert(std::pair<int, int>(77, 77));

		std::map<int, int> stl_map(map.begin(), map.end());
		ft::map<int, int> ft_map(map.begin(), map.end());

		std::map<int, int> stl_map_copy(map.begin(), map.end());
		ft::map<int, int> ft_map_copy(map.begin(), map.end());


		fs.open("./test/map_output/constructor_copy", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareMapAttribues(fs, stl_map, ft_map) && compareMapAttribues(fs, stl_map_copy, ft_map_copy));
		fs.close();

	}
	std::cout << std::endl;

	std::cout << "Itearators:";
	{
		std::map<int, int> map;
		map.insert(std::pair<int, int>(50, 50));
		map.insert(std::pair<int, int>(40, 40));
		map.insert(std::pair<int, int>(60, 60));

		std::map<int, int> stl_map(map.begin(), map.end());
		ft::map<int, int> ft_map(map.begin(), map.end());

		std::vector<int> vect_stl, vect_ft;

		std::map<int, int>::iterator stl_it = stl_map.begin();
		ft::map<int, int>::iterator ft_it = ft_map.begin();


		for (; ft_it != ft_map.end(); ++stl_it, ++ft_it) {
			vect_stl.push_back((*stl_it).first);
			vect_ft.push_back((*ft_it).first);
		}

		fs.open("./test/map_output/iterator++", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareVectorAttribues(fs, vect_stl, vect_ft));
		fs.close();
	}
	{
		std::map<int, int> map;
		map.insert(std::pair<int, int>(50, 50));
		map.insert(std::pair<int, int>(40, 40));
		map.insert(std::pair<int, int>(60, 60));

		std::map<int, int> stl_map(map.begin(), map.end());
		ft::map<int, int> ft_map(map.begin(), map.end());

		std::vector<int> vect_stl, vect_ft;

		std::map<int, int>::reverse_iterator stl_it = stl_map.rbegin();
		ft::map<int, int>::reverse_iterator ft_it = ft_map.rbegin();


		for (; ft_it != ft_map.rend(); ++stl_it, ++ft_it) {
			vect_stl.push_back((*stl_it).first);
			vect_ft.push_back((*ft_it).first);
		}

		fs.open("./test/map_output/reverse_iterator++", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareVectorAttribues(fs, vect_stl, vect_ft));
		fs.close();
	}
	{
		std::map<int, int> map;
		map.insert(std::pair<int, int>(50, 50));
		map.insert(std::pair<int, int>(40, 40));
		map.insert(std::pair<int, int>(60, 60));

		std::map<int, int> stl_map(map.begin(), map.end());
		ft::map<int, int> ft_map(map.begin(), map.end());

		std::vector<int> vect_stl, vect_ft;

		std::map<int, int>::iterator stl_it = stl_map.begin();
		ft::map<int, int>::iterator ft_it = ft_map.begin();

		stl_it++;
		ft_it++;

		std::map<int, int>::iterator stl_it1 = --stl_it;
		ft::map<int, int>::iterator ft_it1 = --ft_it;

		bool one = equalBool(*stl_it1, *ft_it1);

		stl_it++;
		ft_it++;

		stl_it1 = stl_it--;
		ft_it1 = ft_it--;

		bool two = equalBool(*stl_it1, *ft_it1);

		fs.open("./test/map_output/iterator--", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareVectorAttribues(fs, vect_stl, vect_ft) && one && two);
		fs.close();
	}
	std::cout << std::endl;

	std::cout << "Element acces:";
	{
		std::map<int, int> map;
		map.insert(std::pair<int, int>(50, 51));
		map.insert(std::pair<int, int>(40, 41));
		map.insert(std::pair<int, int>(60, 60));
		map.insert(std::pair<int, int>(55, 55));
		map.insert(std::pair<int, int>(80, 80));
		map.insert(std::pair<int, int>(70, 70));
		map.insert(std::pair<int, int>(75, 75));
		map.insert(std::pair<int, int>(90, 90));
		map.insert(std::pair<int, int>(85, 85));
		map.insert(std::pair<int, int>(200, 200));
		map.insert(std::pair<int, int>(250, 250));
		map.insert(std::pair<int, int>(300, 300));
		map.insert(std::pair<int, int>(77, 77));

		std::map<int, int> stl_map(map.begin(), map.end());
		ft::map<int, int> ft_map(map.begin(), map.end());

		fs.open("./test/map_output/operator[]", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(equalBool(stl_map[60], ft_map[60]) && equalBool(stl_map[61], ft_map[61]) && compareMapAttribues(fs, stl_map, ft_map));
		fs.close();
	}
	std::cout << std::endl;

	std::cout << "Modifiers:";
	/*INSERT*/
	{
		std::map<int, int> stl_map;
		ft::map<int, int> ft_map;

		ft_map.insert(std::pair<int, int>(50, 51));
		ft_map.insert(std::pair<int, int>(40, 41));
		ft_map.insert(std::pair<int, int>(60, 60));
		ft_map.insert(std::pair<int, int>(55, 55));
		ft_map.insert(std::pair<int, int>(80, 80));
		ft_map.insert(std::pair<int, int>(70, 70));
		ft_map.insert(std::pair<int, int>(75, 75));
		ft_map.insert(std::pair<int, int>(90, 90));
		ft_map.insert(std::pair<int, int>(85, 85));
		ft_map.insert(std::pair<int, int>(200, 200));
		ft_map.insert(std::pair<int, int>(250, 250));
		ft_map.insert(std::pair<int, int>(300, 300));
		ft_map.insert(std::pair<int, int>(77, 77));

		stl_map.insert(std::pair<int, int>(50, 51));
		stl_map.insert(std::pair<int, int>(40, 41));
		stl_map.insert(std::pair<int, int>(60, 60));
		stl_map.insert(std::pair<int, int>(55, 55));
		stl_map.insert(std::pair<int, int>(80, 80));
		stl_map.insert(std::pair<int, int>(70, 70));
		stl_map.insert(std::pair<int, int>(75, 75));
		stl_map.insert(std::pair<int, int>(90, 90));
		stl_map.insert(std::pair<int, int>(85, 85));
		stl_map.insert(std::pair<int, int>(200, 200));
		stl_map.insert(std::pair<int, int>(250, 250));
		stl_map.insert(std::pair<int, int>(300, 300));
		stl_map.insert(std::pair<int, int>(77, 77));

		fs.open("./test/map_output/Insert_1", std::fstream::in | std::fstream::out | std::fstream::trunc);
		bool one = compareMapAttribues(fs, stl_map, ft_map);
		fs.close();

		std::map<int, int>::iterator stl_it = stl_map.insert(stl_map.begin(), std::pair<int, int>(170, 170));
		ft::map<int, int>::iterator ft_it = ft_map.insert(ft_map.begin(), std::pair<int, int>(170, 170));
		bool two = equalBool(*stl_it, *ft_it);

		stl_it = stl_map.insert(stl_it, std::pair<int, int>(270, 270));
		ft_it = ft_map.insert(ft_it, std::pair<int, int>(270, 270));
		bool three = equalBool(*stl_it, *ft_it);

		fs.open("./test/map_output/Insert_2", std::fstream::in | std::fstream::out | std::fstream::trunc);
		bool four = compareMapAttribues(fs, stl_map, ft_map);
		fs.close();


		std::map<int, int> stl_map2;
		ft::map<int, int> ft_map2;

		stl_map2.insert(std::pair<int, int>(350, 350));
		stl_map2.insert(std::pair<int, int>(100, 100));
		stl_map2.insert(stl_map.begin(), stl_map.end());

		ft_map2.insert(std::pair<int, int>(350, 350));
		ft_map2.insert(std::pair<int, int>(100, 100));
		ft_map2.insert(ft_map.begin(), ft_map.end());

		fs.open("./test/map_output/Insert_3", std::fstream::in | std::fstream::out | std::fstream::trunc);
		bool five = compareMapAttribues(fs, stl_map2, ft_map2);
		fs.close();

		printResult(one && two && three && four && five);

	}
	/*ERASE*/
	{
		std::map<int, int> stl_map;
		ft::map<int, int> ft_map;

		ft_map.insert(std::pair<int, int>(50, 51));
		ft_map.insert(std::pair<int, int>(40, 41));
		ft_map.insert(std::pair<int, int>(60, 60));
		ft_map.insert(std::pair<int, int>(55, 55));
		ft_map.insert(std::pair<int, int>(80, 80));
		ft_map.insert(std::pair<int, int>(70, 70));
		ft_map.insert(std::pair<int, int>(75, 75));
		ft_map.insert(std::pair<int, int>(90, 90));
		ft_map.insert(std::pair<int, int>(85, 85));
		ft_map.insert(std::pair<int, int>(200, 200));
		ft_map.insert(std::pair<int, int>(250, 250));
		ft_map.insert(std::pair<int, int>(300, 300));
		ft_map.insert(std::pair<int, int>(77, 77));

		stl_map.insert(std::pair<int, int>(50, 51));
		stl_map.insert(std::pair<int, int>(40, 41));
		stl_map.insert(std::pair<int, int>(60, 60));
		stl_map.insert(std::pair<int, int>(55, 55));
		stl_map.insert(std::pair<int, int>(80, 80));
		stl_map.insert(std::pair<int, int>(70, 70));
		stl_map.insert(std::pair<int, int>(75, 75));
		stl_map.insert(std::pair<int, int>(90, 90));
		stl_map.insert(std::pair<int, int>(85, 85));
		stl_map.insert(std::pair<int, int>(200, 200));
		stl_map.insert(std::pair<int, int>(250, 250));
		stl_map.insert(std::pair<int, int>(300, 300));
		stl_map.insert(std::pair<int, int>(77, 77));

		size_t stl_num = stl_map.erase(85);
		size_t ft_num = ft_map.erase(85);

		fs.open("./test/map_output/Erase_1", std::fstream::in | std::fstream::out | std::fstream::trunc);
		bool one = compareMapAttribues(fs, stl_map, ft_map) && equalBool(stl_num, ft_num);
		fs.close();

		stl_num = stl_map.erase(80);
		ft_num = ft_map.erase(80);

		fs.open("./test/map_output/Erase_2", std::fstream::in | std::fstream::out | std::fstream::trunc);
		bool two = compareMapAttribues(fs, stl_map, ft_map) && equalBool(stl_num, ft_num);
		fs.close();


		std::map<int, int>::iterator stl_it = stl_map.begin();
		ft::map<int, int>::iterator ft_it = ft_map.begin();		
		for (; (*stl_it).first != 90; ++stl_it, ++ft_it);

		stl_map.erase(stl_it);
		ft_map.erase(ft_it);

		fs.open("./test/map_output/Erase_3", std::fstream::in | std::fstream::out | std::fstream::trunc);
		bool three = compareMapAttribues(fs, stl_map, ft_map) && equalBool(stl_num, ft_num);
		fs.close();

		stl_num = stl_map.erase(50);
		ft_num = ft_map.erase(50);

		fs.open("./test/map_output/Erase_4", std::fstream::in | std::fstream::out | std::fstream::trunc);
		bool four = compareMapAttribues(fs, stl_map, ft_map) && equalBool(stl_num, ft_num);
		fs.close();


		printResult(one && two && three && four);

	}
	/*SWAP*/
	{
		std::map<int, int> stl_map;
		ft::map<int, int> ft_map;

		ft_map.insert(std::pair<int, int>(50, 51));
		ft_map.insert(std::pair<int, int>(40, 41));
		ft_map.insert(std::pair<int, int>(60, 60));
		ft_map.insert(std::pair<int, int>(55, 55));
		ft_map.insert(std::pair<int, int>(80, 80));
		ft_map.insert(std::pair<int, int>(70, 70));
		ft_map.insert(std::pair<int, int>(75, 75));
		ft_map.insert(std::pair<int, int>(90, 90));
		ft_map.insert(std::pair<int, int>(85, 85));
		ft_map.insert(std::pair<int, int>(200, 200));
		ft_map.insert(std::pair<int, int>(250, 250));
		ft_map.insert(std::pair<int, int>(300, 300));
		ft_map.insert(std::pair<int, int>(77, 77));

		stl_map.insert(std::pair<int, int>(50, 51));
		stl_map.insert(std::pair<int, int>(40, 41));
		stl_map.insert(std::pair<int, int>(60, 60));
		stl_map.insert(std::pair<int, int>(55, 55));
		stl_map.insert(std::pair<int, int>(80, 80));
		stl_map.insert(std::pair<int, int>(70, 70));
		stl_map.insert(std::pair<int, int>(75, 75));
		stl_map.insert(std::pair<int, int>(90, 90));
		stl_map.insert(std::pair<int, int>(85, 85));
		stl_map.insert(std::pair<int, int>(200, 200));
		stl_map.insert(std::pair<int, int>(250, 250));
		stl_map.insert(std::pair<int, int>(300, 300));
		stl_map.insert(std::pair<int, int>(77, 77));

		std::map<int, int> stl_map_swap;
		ft::map<int, int> ft_map_swap;

		ft_map_swap.insert(std::pair<int, int>(50, 51));
		ft_map_swap.insert(std::pair<int, int>(40, 41));
		ft_map_swap.insert(std::pair<int, int>(60, 60));
		stl_map_swap.insert(std::pair<int, int>(50, 51));
		stl_map_swap.insert(std::pair<int, int>(40, 41));
		stl_map_swap.insert(std::pair<int, int>(60, 60));

		ft_map.swap(ft_map_swap);
		stl_map.swap(stl_map_swap);

		fs.open("./test/map_output/swap", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareMapAttribues(fs, stl_map, ft_map) && compareMapAttribues(fs, stl_map_swap, ft_map_swap));
		fs.close();
	}
	/*CLEAR*/
	{
		std::map<int, int> stl_map;
		ft::map<int, int> ft_map;

		ft_map.insert(std::pair<int, int>(50, 51));
		ft_map.insert(std::pair<int, int>(40, 41));
		ft_map.insert(std::pair<int, int>(60, 60));
		ft_map.insert(std::pair<int, int>(55, 55));
		ft_map.insert(std::pair<int, int>(80, 80));
		ft_map.insert(std::pair<int, int>(70, 70));
		ft_map.insert(std::pair<int, int>(75, 75));
		ft_map.insert(std::pair<int, int>(90, 90));
		ft_map.insert(std::pair<int, int>(85, 85));
		ft_map.insert(std::pair<int, int>(200, 200));
		ft_map.insert(std::pair<int, int>(250, 250));
		ft_map.insert(std::pair<int, int>(300, 300));
		ft_map.insert(std::pair<int, int>(77, 77));

		stl_map.insert(std::pair<int, int>(50, 51));
		stl_map.insert(std::pair<int, int>(40, 41));
		stl_map.insert(std::pair<int, int>(60, 60));
		stl_map.insert(std::pair<int, int>(55, 55));
		stl_map.insert(std::pair<int, int>(80, 80));
		stl_map.insert(std::pair<int, int>(70, 70));
		stl_map.insert(std::pair<int, int>(75, 75));
		stl_map.insert(std::pair<int, int>(90, 90));
		stl_map.insert(std::pair<int, int>(85, 85));
		stl_map.insert(std::pair<int, int>(200, 200));
		stl_map.insert(std::pair<int, int>(250, 250));
		stl_map.insert(std::pair<int, int>(300, 300));
		stl_map.insert(std::pair<int, int>(77, 77));

		ft_map.clear();
		stl_map.clear();

		fs.open("./test/map_output/clear", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareMapAttribues(fs, stl_map, ft_map));
		fs.close();
	}
	std::cout << std::endl;

	std::cout << "Operations:";
	/*FIND*/
	{
		std::map<int, int> stl_map;
		ft::map<int, int> ft_map;

		ft_map.insert(std::pair<int, int>(50, 51));
		ft_map.insert(std::pair<int, int>(40, 41));
		ft_map.insert(std::pair<int, int>(60, 60));
		ft_map.insert(std::pair<int, int>(55, 55));
		ft_map.insert(std::pair<int, int>(80, 80));
		ft_map.insert(std::pair<int, int>(70, 70));
		ft_map.insert(std::pair<int, int>(75, 75));
		ft_map.insert(std::pair<int, int>(90, 90));
		ft_map.insert(std::pair<int, int>(85, 85));
		ft_map.insert(std::pair<int, int>(200, 200));
		ft_map.insert(std::pair<int, int>(250, 250));
		ft_map.insert(std::pair<int, int>(300, 300));
		ft_map.insert(std::pair<int, int>(77, 77));

		stl_map.insert(std::pair<int, int>(50, 51));
		stl_map.insert(std::pair<int, int>(40, 41));
		stl_map.insert(std::pair<int, int>(60, 60));
		stl_map.insert(std::pair<int, int>(55, 55));
		stl_map.insert(std::pair<int, int>(80, 80));
		stl_map.insert(std::pair<int, int>(70, 70));
		stl_map.insert(std::pair<int, int>(75, 75));
		stl_map.insert(std::pair<int, int>(90, 90));
		stl_map.insert(std::pair<int, int>(85, 85));
		stl_map.insert(std::pair<int, int>(200, 200));
		stl_map.insert(std::pair<int, int>(250, 250));
		stl_map.insert(std::pair<int, int>(300, 300));
		stl_map.insert(std::pair<int, int>(77, 77));

		std::map<int, int>::iterator stl_it = stl_map.find(80);
		ft::map<int, int>::iterator ft_it = ft_map.find(80);

		fs.open("./test/map_output/find", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareMapAttribues(fs, stl_map, ft_map) && equalBool((*stl_it).second, (*ft_it).second));
		fs << "stl_value : " << (*stl_it).first << " " << (*stl_it).second << std::endl;
		fs << "ft_value : " << (*ft_it).first << " " << (*ft_it).second << std::endl;
		fs.close();


	}
	/*COUNT*/
	{
		std::map<int, int> stl_map;
		ft::map<int, int> ft_map;

		ft_map.insert(std::pair<int, int>(50, 51));
		ft_map.insert(std::pair<int, int>(40, 41));
		ft_map.insert(std::pair<int, int>(60, 60));
		ft_map.insert(std::pair<int, int>(55, 55));
		ft_map.insert(std::pair<int, int>(80, 80));
		ft_map.insert(std::pair<int, int>(70, 70));
		ft_map.insert(std::pair<int, int>(75, 75));
		ft_map.insert(std::pair<int, int>(90, 90));
		ft_map.insert(std::pair<int, int>(85, 85));
		ft_map.insert(std::pair<int, int>(200, 200));
		ft_map.insert(std::pair<int, int>(250, 250));
		ft_map.insert(std::pair<int, int>(300, 300));
		ft_map.insert(std::pair<int, int>(77, 77));

		stl_map.insert(std::pair<int, int>(50, 51));
		stl_map.insert(std::pair<int, int>(40, 41));
		stl_map.insert(std::pair<int, int>(60, 60));
		stl_map.insert(std::pair<int, int>(55, 55));
		stl_map.insert(std::pair<int, int>(80, 80));
		stl_map.insert(std::pair<int, int>(70, 70));
		stl_map.insert(std::pair<int, int>(75, 75));
		stl_map.insert(std::pair<int, int>(90, 90));
		stl_map.insert(std::pair<int, int>(85, 85));
		stl_map.insert(std::pair<int, int>(200, 200));
		stl_map.insert(std::pair<int, int>(250, 250));
		stl_map.insert(std::pair<int, int>(300, 300));
		stl_map.insert(std::pair<int, int>(77, 77));

		bool res = true;

		for (int i = 0; i < 100; ++i) {
			if (!equalBool(stl_map.count(i), ft_map.count(i))) {
				res = false;
				break ;
			}
		}

		fs.open("./test/map_output/count", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(res);
		fs.close();
	}
	/*LOWER_BOUND*/
	{
		std::map<int, int> stl_map;
		ft::map<int, int> ft_map;

		ft_map.insert(std::pair<int, int>(50, 51));
		ft_map.insert(std::pair<int, int>(40, 41));
		ft_map.insert(std::pair<int, int>(60, 60));
		ft_map.insert(std::pair<int, int>(55, 55));
		ft_map.insert(std::pair<int, int>(80, 80));
		ft_map.insert(std::pair<int, int>(70, 70));
		ft_map.insert(std::pair<int, int>(75, 75));
		ft_map.insert(std::pair<int, int>(90, 90));
		ft_map.insert(std::pair<int, int>(85, 85));
		ft_map.insert(std::pair<int, int>(200, 200));
		ft_map.insert(std::pair<int, int>(250, 250));
		ft_map.insert(std::pair<int, int>(300, 300));
		ft_map.insert(std::pair<int, int>(77, 77));

		stl_map.insert(std::pair<int, int>(50, 51));
		stl_map.insert(std::pair<int, int>(40, 41));
		stl_map.insert(std::pair<int, int>(60, 60));
		stl_map.insert(std::pair<int, int>(55, 55));
		stl_map.insert(std::pair<int, int>(80, 80));
		stl_map.insert(std::pair<int, int>(70, 70));
		stl_map.insert(std::pair<int, int>(75, 75));
		stl_map.insert(std::pair<int, int>(90, 90));
		stl_map.insert(std::pair<int, int>(85, 85));
		stl_map.insert(std::pair<int, int>(200, 200));
		stl_map.insert(std::pair<int, int>(250, 250));
		stl_map.insert(std::pair<int, int>(300, 300));
		stl_map.insert(std::pair<int, int>(77, 77));

		std::map<int, int>::iterator stl_it = stl_map.lower_bound(80);
		ft::map<int, int>::iterator ft_it = ft_map.lower_bound(80);

		fs.open("./test/map_output/lower_bound", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareMapAttribues(fs, stl_map, ft_map) && equalBool((*stl_it).second, (*ft_it).second));
		fs << "stl_value : " << (*stl_it).first << " " << (*stl_it).second << std::endl;
		fs << "ft_value : " << (*ft_it).first << " " << (*ft_it).second << std::endl;
		fs.close();
	}
	/*UPPER_BOUND*/
	{
		std::map<int, int> stl_map;
		ft::map<int, int> ft_map;

		ft_map.insert(std::pair<int, int>(50, 51));
		ft_map.insert(std::pair<int, int>(40, 41));
		ft_map.insert(std::pair<int, int>(60, 60));
		ft_map.insert(std::pair<int, int>(55, 55));
		ft_map.insert(std::pair<int, int>(80, 80));
		ft_map.insert(std::pair<int, int>(70, 70));
		ft_map.insert(std::pair<int, int>(75, 75));
		ft_map.insert(std::pair<int, int>(90, 90));
		ft_map.insert(std::pair<int, int>(85, 85));
		ft_map.insert(std::pair<int, int>(200, 200));
		ft_map.insert(std::pair<int, int>(250, 250));
		ft_map.insert(std::pair<int, int>(300, 300));
		ft_map.insert(std::pair<int, int>(77, 77));

		stl_map.insert(std::pair<int, int>(50, 51));
		stl_map.insert(std::pair<int, int>(40, 41));
		stl_map.insert(std::pair<int, int>(60, 60));
		stl_map.insert(std::pair<int, int>(55, 55));
		stl_map.insert(std::pair<int, int>(80, 80));
		stl_map.insert(std::pair<int, int>(70, 70));
		stl_map.insert(std::pair<int, int>(75, 75));
		stl_map.insert(std::pair<int, int>(90, 90));
		stl_map.insert(std::pair<int, int>(85, 85));
		stl_map.insert(std::pair<int, int>(200, 200));
		stl_map.insert(std::pair<int, int>(250, 250));
		stl_map.insert(std::pair<int, int>(300, 300));
		stl_map.insert(std::pair<int, int>(77, 77));

		std::map<int, int>::iterator stl_it = stl_map.upper_bound(80);
		ft::map<int, int>::iterator ft_it = ft_map.upper_bound(80);

		fs.open("./test/map_output/upper_bound", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareMapAttribues(fs, stl_map, ft_map) && equalBool((*stl_it).second, (*ft_it).second));
		fs << "stl_value : " << (*stl_it).first << " " << (*stl_it).second << std::endl;
		fs << "ft_value : " << (*ft_it).first << " " << (*ft_it).second << std::endl;
		fs.close();
	}
	/*EQUAL_RANGE*/
	{
		std::map<int, int> stl_map;
		ft::map<int, int> ft_map;

		ft_map.insert(std::pair<int, int>(50, 51));
		ft_map.insert(std::pair<int, int>(40, 41));
		ft_map.insert(std::pair<int, int>(60, 60));
		ft_map.insert(std::pair<int, int>(55, 55));
		ft_map.insert(std::pair<int, int>(80, 80));
		ft_map.insert(std::pair<int, int>(70, 70));
		ft_map.insert(std::pair<int, int>(75, 75));
		ft_map.insert(std::pair<int, int>(90, 90));
		ft_map.insert(std::pair<int, int>(85, 85));
		ft_map.insert(std::pair<int, int>(200, 200));
		ft_map.insert(std::pair<int, int>(250, 250));
		ft_map.insert(std::pair<int, int>(300, 300));
		ft_map.insert(std::pair<int, int>(77, 77));

		stl_map.insert(std::pair<int, int>(50, 51));
		stl_map.insert(std::pair<int, int>(40, 41));
		stl_map.insert(std::pair<int, int>(60, 60));
		stl_map.insert(std::pair<int, int>(55, 55));
		stl_map.insert(std::pair<int, int>(80, 80));
		stl_map.insert(std::pair<int, int>(70, 70));
		stl_map.insert(std::pair<int, int>(75, 75));
		stl_map.insert(std::pair<int, int>(90, 90));
		stl_map.insert(std::pair<int, int>(85, 85));
		stl_map.insert(std::pair<int, int>(200, 200));
		stl_map.insert(std::pair<int, int>(250, 250));
		stl_map.insert(std::pair<int, int>(300, 300));
		stl_map.insert(std::pair<int, int>(77, 77));

		std::pair<std::map<int,int>::iterator,std::map<int,int>::iterator> stl_it = stl_map.equal_range(80);
		std::pair<ft::map<int,int>::iterator,ft::map<int,int>::iterator> ft_it = ft_map.equal_range(80);

		fs.open("./test/map_output/equal_range", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareMapAttribues(fs, stl_map, ft_map) && equalBool((*stl_it.second).first, (*ft_it.second).first));
		fs << "stl_value : " << (*stl_it.first).first << " " << (*stl_it.second).first << std::endl;
		fs << "ft_value : " << (*ft_it.first).first << " " << (*ft_it.second).first << std::endl;
		fs.close();
	}


	std::cout << std::endl;

}

short unsigned int getCount_map() {return count_map;}
short unsigned int getQuantity_map() {return quantity_map;}
