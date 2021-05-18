#include <iostream>
#include <fstream>
#include "test.hpp"


void printPicture() {
	std::ifstream file ("test/coffee.txt",std::ifstream::binary);
	if (file.is_open()) {
		file.seekg (0,file.end);
		size_t size = file.tellg();
		file.seekg (0);
		char* coffee = new char[size];
		file.read (coffee, size - 1);
		std::cout << coffee << std::endl;
		delete [] coffee;
	}
}

int main(int ac, char** av) {
	short unsigned int count = 0;
	short unsigned int quantity = 0;

	test_vector();
	count += getCount_vector();
	quantity += getQuantity_vector();
	test_list();
	count += getCount_list();
	quantity += getQuantity_list();

	std::cout << CIAN << count << '/' << quantity << RESET << std::endl;
	if (count == quantity) {
		printPicture();
	}

	return 0;
}