#include <iostream>
#include <fstream>
#include "test.hpp"
#include <cstring>

void printPicture() {
	std::ifstream file ("test/coffee.txt",std::ifstream::binary);
	if (file.is_open()) {
		file.seekg (0,file.end);
		size_t size = file.tellg();
		file.seekg (0);
		char* coffee = new char[size];
		file.read (coffee, size);
		std::cout << coffee << std::endl;
		delete [] coffee;
	}
}

int main(int ac, char** av) {
	short unsigned int count = 0;
	short unsigned int quantity = 0;

	if (ac == 1) {
		test_vector();
		count += getCount_vector();
		quantity += getQuantity_vector();
		test_list();
		count += getCount_list();
		quantity += getQuantity_list();
		test_map();
		count += getCount_map();
		quantity += getQuantity_map();
		test_stack();
		count += getCount_stack();
		quantity += getQuantity_stack();
		test_queue();
		count += getCount_queue();
		quantity += getQuantity_queue();
		std::cout << CIAN << count << '/' << quantity << RESET << std::endl;
		if (count == quantity) {
			printPicture();
		}
		return 0;
	}
	while(*(++av)) {
		if (!std::strcmp(*av, "vector")) {
			test_vector();
			count += getCount_vector();
			quantity += getQuantity_vector();
		}
		else if (!std::strcmp(*av, "list")) {
			test_list();
			count += getCount_list();
			quantity += getQuantity_list();
		}
		else if (!std::strcmp(*av, "map")) {
			test_map();
			count += getCount_map();
			quantity += getQuantity_map();
		}
		else if (!std::strcmp(*av, "stack")) {
			test_stack();
			count += getCount_stack();
			quantity += getQuantity_stack();
		}
		else if (!std::strcmp(*av, "queue")) {
			test_queue();
			count += getCount_queue();
			quantity += getQuantity_queue();
		}
	}
	std::cout << CIAN << count << '/' << quantity << RESET << std::endl;


	return 0;
}