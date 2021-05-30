#include <iostream>
#include <fstream>
#include <queue>
#include <list>
#include <iterator>
#include <sys/stat.h>
#include "../queue.hpp"
#include "color.hpp"

short unsigned int count_queue = 0;
short unsigned int quantity_queue = 0;

template <typename T>
static bool equalBool(T t1, T t2) {
	return t1 == t2;
}

template <class T>
static bool compareQueueAttribues(std::fstream& fs, std::queue<T>& stl_queue, ft::queue<T>& my_queue) {
	
	bool empty = equalBool(stl_queue.empty(), my_queue.empty());
	bool size = equalBool(stl_queue.size(), my_queue.size());

	fs << std::endl << "------------------------------" << std::endl;
	fs << "STL : " << std::endl;
	fs << "Empty		: " << stl_queue.empty() << std::endl;
	fs << "Size		: " << stl_queue.size() << std::endl;

	fs << "FT : " << std::endl;
	fs << "Empty		: " << my_queue.empty() << std::endl;
	fs << "Size		: " << my_queue.size() << std::endl;

	return empty && size;
}

static void printResult(bool res) {
	++quantity_queue;
	if (res) {
		std::cout << GREEN << " [OK]" << RESET;
		++count_queue;
	}
	else
		std::cout << RED << " [NO]" << RESET;
}
void test_queue() {
	std::fstream fs;

	std::cout << YELLOW << "queue :" << RESET <<std::endl;
	mkdir("./test/queue_output", 0777);

	std::cout << "Member_function:";
	{
		std::queue<int> stl_queue;
		ft::queue<int> ft_queue;

		fs.open("./test/queue_output/empty", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareQueueAttribues(fs, stl_queue, ft_queue));
		fs.close();
	}
	{
		std::queue<int> stl_queue;
		ft::queue<int> ft_queue;

		for (int i = -10; i < 100; ++i) {
			stl_queue.push(i);
			ft_queue.push(i);
		}

		fs.open("./test/queue_output/push", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareQueueAttribues(fs, stl_queue, ft_queue));
		fs.close();
	}
	{
		std::queue<int> stl_queue;
		ft::queue<int> ft_queue;

		for (int i = -10; i < 100; ++i) {
			stl_queue.push(i);
			ft_queue.push(i);
		}

		fs.open("./test/queue_output/front", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareQueueAttribues(fs, stl_queue, ft_queue) && equalBool(stl_queue.front(), ft_queue.front()));
		fs.close();
	}
	{
		std::queue<int> stl_queue;
		ft::queue<int> ft_queue;

		for (int i = -10; i < 100; ++i) {
			stl_queue.push(i);
			ft_queue.push(i);
		}

		fs.open("./test/queue_output/back", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareQueueAttribues(fs, stl_queue, ft_queue) && equalBool(stl_queue.back(), ft_queue.back()));
		fs.close();
	}
	{
		std::queue<int> stl_queue;
		ft::queue<int> ft_queue;

		for (int i = -10; i < 100; ++i) {
			stl_queue.push(i);
			ft_queue.push(i);
		}

		for (int i = 0; i < 50; ++i) {
			stl_queue.pop();
			ft_queue.pop();
		}

		fs.open("./test/queue_output/pop", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareQueueAttribues(fs, stl_queue, ft_queue));
		fs.close();
	}
	std::cout << std::endl;

	std::cout << "Non-member function overloads:";
	{
		ft::queue<int> queue;
		ft::queue<int> queue1;

		for (int i = -10; i < 100; ++i) {
			queue.push(i);
			queue1.push(i);
		}
		printResult(queue == queue1);
	}
	{
		ft::queue<int> queue;
		ft::queue<int> queue1;

		for (int i = -10; i < 100; ++i) {
			queue.push(i);
			queue1.push(i);
		}
		queue.push(1);
		printResult(queue != queue1);
	}
	{
		ft::queue<int> queue;
		ft::queue<int> queue1;

		for (int i = -10; i < 100; ++i) {
			queue.push(i);
			queue1.push(i);
		}
		queue.push(1);
		printResult(queue > queue1);
	}
	{
		ft::queue<int> queue;
		ft::queue<int> queue1;

		for (int i = -10; i < 100; ++i) {
			queue.push(i);
			queue1.push(i);
		}
		queue1.push(1);
		printResult(queue < queue1);
	}
	{
		ft::queue<int> queue;
		ft::queue<int> queue1;

		for (int i = -10; i < 100; ++i) {
			queue.push(i);
			queue1.push(i);
		}
		queue.push(1);
		printResult(queue >= queue1);
	}
	{
		ft::queue<int> queue;
		ft::queue<int> queue1;

		for (int i = -10; i < 100; ++i) {
			queue.push(i);
			queue1.push(i);
		}
		queue1.push(1);
		printResult(queue <= queue1);
	}
	std::cout << std::endl << std::endl;
}

short unsigned int getCount_queue() {return count_queue;}
short unsigned int getQuantity_queue() {return quantity_queue;}