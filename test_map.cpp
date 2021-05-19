#include <iostream>
#include <map>
#include <iterator>
#include "map.hpp"
#include "iterator.hpp"

// using namespace std;

int main() {
	std::map<int,int> mapp;
	
	mapp.insert(std::pair<int,int>(5,5));
	mapp.insert(std::pair<int,int>(1,1));
	mapp.insert(std::pair<int,int>(24,24));
	mapp.insert(std::pair<int,int>(15,15));
	mapp.insert(std::pair<int,int>(3,3));
	mapp.insert(std::pair<int,int>(8,8));
	std::map<int, int>::iterator it = mapp.begin();
	for (std::map<int, int>::iterator ite = mapp.end(); it != ite; ++it) {
		std::cout << it->second << std::endl;
	}

	ft::map<int, int> ft_map;
	ft_map.insert(std::pair<int, int>(50, 1));
	ft_map.insert(std::pair<int, int>(40, 2));
	ft_map.insert(std::pair<int, int>(30, 3));
	ft_map.insert(std::pair<int, int>(70, 4));
	ft_map.insert(std::pair<int, int>(60, 5));

	std::cout << *ft_map.end() << std::endl;

	return 0;
}