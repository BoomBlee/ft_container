#include <iostream>
#include <map>
#include <iterator>
#include "map.hpp"
#include "iterator.hpp"

// using namespace std;

int main() {
	{
		// std::map<int,int> mapp;
		
		// mapp.insert(std::pair<int,int>(5,5));
		// mapp.insert(std::pair<int,int>(1,1));
		// mapp.insert(std::pair<int,int>(24,24));
		// mapp.insert(std::pair<int,int>(15,15));
		// mapp.insert(std::pair<int,int>(3,3));
		// mapp.insert(std::pair<int,int>(8,8));
		// std::map<int, int>::iterator it = mapp.begin();
		// for (std::map<int, int>::iterator ite = mapp.end(); it != ite; ++it) {
		// 	std::cout << it->second << std::endl;
		// }

		ft::map<int, int> ft_map;
		ft_map.insert(std::pair<int, int>(50, 50));
		ft_map.insert(std::pair<int, int>(60, 60));
		ft_map.insert(std::pair<int, int>(70, 70));
		// ft_map.insert(std::pair<int, int>(100, 100));
		ft_map.insert(std::pair<int, int>(80, 80));
		// ft_map.insert(std::pair<int, int>(65, 65));
		// ft_map.insert(std::pair<int, int>(20, 20));
		// ft_map.insert(std::pair<int, int>(30, 30));
		// ft_map.insert(std::pair<int, int>(63, 63));
		// ft_map.insert(std::pair<int, int>(55, 55));
		// ft_map.insert(std::pair<int, int>(62, 62));
		// ft_map.insert(std::pair<int, int>(61, 61));
		// ft_map.insert(std::pair<int, int>(64, 64));
		ft_map.insert(std::pair<int, int>(90, 90));
		ft_map.insert(std::pair<int, int>(100, 100));
		ft_map.insert(std::pair<int, int>(85, 85));
		ft_map.insert(std::pair<int, int>(110, 110));
		ft_map.insert(std::pair<int, int>(105, 105));
		ft_map.insert(std::pair<int, int>(102, 102));

		// std::cout << *ft_map.begin() << std::endl;
	}

	{
		std::map<int, int> mapp;
		mapp.insert(std::pair<int, int>(50, 50));
		mapp.insert(std::pair<int, int>(60, 60));
		mapp.insert(std::pair<int, int>(70, 70));
		mapp.insert(++mapp.begin(), std::pair<int, int>(65, 65));

		std::map<int, int>::iterator it = mapp.begin();
		// it.operator*();
		std::pair<int, int> p = *(++it);
		// for (; it != mapp.end(); ++it) {
		// 	std::cout << mapp[60] << std::endl;
		// }
	}

	{
		ft::map<int, int> ft_map;
		ft_map.insert(std::pair<int, int>(50, 50));
		ft_map.insert(std::pair<int, int>(60, 60));
		ft_map.insert(std::pair<int, int>(40, 40));
		ft_map.insert(std::pair<int, int>(25, 25));
		ft_map.insert(std::pair<int, int>(45, 45));
		ft_map.insert(std::pair<int, int>(30, 30));
		ft_map.insert(std::pair<int, int>(10, 10));
		ft_map.insert(std::pair<int, int>(15, 15));
		ft_map.insert(std::pair<int, int>(15, 15));
	}

	{
		ft::map<int, int> ft_map;
		ft_map.insert(std::pair<int, int>(40, 40));
		ft_map.insert(std::pair<int, int>(60, 60));
		ft_map.insert(std::pair<int, int>(30, 30));
		ft_map.insert(std::pair<int, int>(25, 25));
		ft_map.insert(std::pair<int, int>(80, 80));
		ft_map.insert(std::pair<int, int>(27, 27));
		ft_map.insert(std::pair<int, int>(100, 100));
	}

	{
		ft::map<int, int> ft_map;
		ft_map.insert(std::pair<int, int>(40, 40));
		ft_map.insert(std::pair<int, int>(60, 60));
		ft_map.insert(std::pair<int, int>(30, 30));
		ft_map.insert(std::pair<int, int>(25, 25));
		ft_map.insert(std::pair<int, int>(80, 80));
		ft_map.insert(std::pair<int, int>(27, 27));
		ft_map.insert(std::pair<int, int>(100, 100));

		ft::map<int, int>::iterator it = ft_map.begin();
		for (ft::map<int, int>::iterator ite = ft_map.end(); it != ite; ++it) {
			std::cout << it._p->pair.second << std::endl;
		}
	}

	{
		std::cout << "erase RED2 max_left" << std::endl;

		ft::map<int, int> ft_map;
		ft_map.insert(std::pair<int, int>(40, 40));
		ft_map.insert(std::pair<int, int>(50, 50));
		ft_map.insert(std::pair<int, int>(30, 30));
		ft_map.insert(std::pair<int, int>(25, 25));
		ft_map.insert(std::pair<int, int>(10, 10));
		ft_map.insert(std::pair<int, int>(20, 20));

		ft::map<int, int>::iterator it = ft_map.begin();
		for (ft::map<int, int>::iterator ite = ft_map.end(); it != ite; ++it) {
			std::cout << it._p->pair.second << std::endl;
		}
		it = ft_map.begin();
		for (ft::map<int, int>::iterator ite = ft_map.end(); it != ite; ++it) {
			if (it._p->pair.first == 25) {
				std::cout << "found it=" << it._p->pair.first << std::endl;
				break ;
			}
		}
	

		ft_map.erase(it);
		it = ft_map.begin();
		for (ft::map<int, int>::iterator ite = ft_map.end(); it != ite; ++it) {
			std::cout << it._p->pair.second << std::endl;
		}

	}

	{
		std::cout << "erase BLACK2 max_left" << std::endl;

		ft::map<int, int> ft_map;
		ft_map.insert(std::pair<int, int>(50, 50));
		ft_map.insert(std::pair<int, int>(40, 40));
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

		ft::map<int, int>::iterator it = ft_map.begin();
		for (ft::map<int, int>::iterator ite = ft_map.end(); it != ite; ++it) {
			std::cout << it._p->pair.second << std::endl;
		}
		it = ft_map.begin();
		for (ft::map<int, int>::iterator ite = ft_map.end(); it != ite; ++it) {
			if (it._p->pair.first == 85) {
				std::cout << "found it=" << it._p->pair.first << std::endl;
				break ;
			}
		}
	

		ft_map.erase(it);
		it = ft_map.begin();
		for (ft::map<int, int>::iterator ite = ft_map.end(); it != ite; ++it) {
			std::cout << it._p->pair.second << std::endl;
		}

	}
	return 0;
}