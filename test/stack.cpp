#include <iostream>
#include <fstream>
#include <stack>
#include <list>
#include <iterator>
#include <sys/stat.h>
#include "../stack.hpp"
#include "color.hpp"

short unsigned int count_stack = 0;
short unsigned int quantity_stack = 0;

template <typename T>
static bool equalBool(T t1, T t2) {
	return t1 == t2;
}

template <class T>
static bool compareStackAttribues(std::fstream& fs, std::stack<T>& stl_stack, ft::stack<T>& my_stack) {
	
	bool empty = equalBool(stl_stack.empty(), my_stack.empty());
	bool size = equalBool(stl_stack.size(), my_stack.size());

	fs << std::endl << "------------------------------" << std::endl;
	fs << "STL : " << std::endl;
	fs << "Empty		: " << stl_stack.empty() << std::endl;
	fs << "Size		: " << stl_stack.size() << std::endl;

	fs << "FT : " << std::endl;
	fs << "Empty		: " << my_stack.empty() << std::endl;
	fs << "Size		: " << my_stack.size() << std::endl;

	return empty && size;
}

static void printResult(bool res) {
	++quantity_stack;
	if (res) {
		std::cout << GREEN << " [OK]" << RESET;
		++count_stack;
	}
	else
		std::cout << RED << " [NO]" << RESET;
}
void test_stack() {
	std::fstream fs;

	std::cout << YELLOW << "STACK :" << RESET <<std::endl;
	mkdir("./test/stack_output", 0777);

	std::cout << "Member_function:";
	{
		std::stack<int> stl_stack;
		ft::stack<int> ft_stack;

		fs.open("./test/stack_output/empty", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareStackAttribues(fs, stl_stack, ft_stack));
		fs.close();
	}
	{
		std::stack<int> stl_stack;
		ft::stack<int> ft_stack;

		for (int i = -10; i < 100; ++i) {
			stl_stack.push(i);
			ft_stack.push(i);
		}

		fs.open("./test/stack_output/push", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareStackAttribues(fs, stl_stack, ft_stack));
		fs.close();
	}
	{
		std::stack<int> stl_stack;
		ft::stack<int> ft_stack;

		for (int i = -10; i < 100; ++i) {
			stl_stack.push(i);
			ft_stack.push(i);
		}

		fs.open("./test/stack_output/top", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareStackAttribues(fs, stl_stack, ft_stack) && equalBool(stl_stack.top(), ft_stack.top()));
		fs.close();
	}
	{
		std::stack<int> stl_stack;
		ft::stack<int> ft_stack;

		for (int i = -10; i < 100; ++i) {
			stl_stack.push(i);
			ft_stack.push(i);
		}

		for (int i = 0; i < 50; ++i) {
			stl_stack.pop();
			ft_stack.pop();
		}

		fs.open("./test/stack_output/push", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printResult(compareStackAttribues(fs, stl_stack, ft_stack));
		fs.close();
	}
	std::cout << std::endl;

	std::cout << "Non-member function overloads:";
	{
		ft::stack<int> stack;
		ft::stack<int> stack1;

		for (int i = -10; i < 100; ++i) {
			stack.push(i);
			stack1.push(i);
		}
		printResult(stack == stack1);
	}
	{
		ft::stack<int> stack;
		ft::stack<int> stack1;

		for (int i = -10; i < 100; ++i) {
			stack.push(i);
			stack1.push(i);
		}
		stack.push(1);
		printResult(stack != stack1);
	}
	{
		ft::stack<int> stack;
		ft::stack<int> stack1;

		for (int i = -10; i < 100; ++i) {
			stack.push(i);
			stack1.push(i);
		}
		stack.push(1);
		printResult(stack > stack1);
	}
	{
		ft::stack<int> stack;
		ft::stack<int> stack1;

		for (int i = -10; i < 100; ++i) {
			stack.push(i);
			stack1.push(i);
		}
		stack1.push(1);
		printResult(stack < stack1);
	}
	{
		ft::stack<int> stack;
		ft::stack<int> stack1;

		for (int i = -10; i < 100; ++i) {
			stack.push(i);
			stack1.push(i);
		}
		stack.push(1);
		printResult(stack >= stack1);
	}
	{
		ft::stack<int> stack;
		ft::stack<int> stack1;

		for (int i = -10; i < 100; ++i) {
			stack.push(i);
			stack1.push(i);
		}
		stack1.push(1);
		printResult(stack <= stack1);
	}
	std::cout << std::endl << std::endl;
}

short unsigned int getCount_stack() {return count_stack;}
short unsigned int getQuantity_stack() {return quantity_stack;}