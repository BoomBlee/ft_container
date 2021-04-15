#include <iostream>
#include <vector>
#include <iterator>
#include "vector.hpp"

using namespace std;

int main() {
	vector<int> vect;
	ft::vector<int> my_vect;
	cout << "empty " << my_vect.empty() << endl;
	cout << "empty " << vect.empty() << endl;
	// for(int i=0; i < 18; ++i)
		vect.push_back(2);
	// vector<int>::iterator it = vect.begin();
	// vector<int>::iterator ite = vect.end();
	
	// cout << *it << endl;
	// it[10] = 54;
	// cout << *it << endl;

	// vector<int>::iterator new_it = it + 3;
	// cout << "++it " << *new_it << endl;
	my_vect.push_back(2);
	my_vect.front();
	cout << "size my  " << my_vect.size() << endl;
	cout << "size org " << vect.size() << endl;
	cout << "cap my  " << my_vect.capacity() << endl;
	cout << "cap org " << vect.capacity() << endl;
	cout << "max_size my  " << my_vect.max_size() << "!" << endl;
	cout << "max_size org " << vect.max_size() << "!"  << endl;
	cout << "[0] my  " << my_vect[0] << endl;
	cout << "[0] org " << vect[0] << endl;


	vect.push_back(5);
	my_vect.push_back(5);
	vect.push_back(90);
	my_vect.push_back(90);
	vect.push_back(789);
	my_vect.push_back(789);
	cout << "size my  " << my_vect.size() << endl;
	cout << "size org " << vect.size() << endl;
	cout << "cap my  " << my_vect.capacity() << endl;
	cout << "cap org " << vect.capacity() << endl;

	ft::vector<int>::iterator it1 = my_vect.begin();
	for (ft::vector<int>::iterator ite = my_vect.end(); it1 != ite; ++it1)
		cout << *it1 << endl;

	std::vector<int>::iterator it2 = vect.begin();
	for (std::vector<int>::iterator ite = vect.end(); it2 != ite; ++it2)
		cout << *it2 << endl;

	vect.pop_back();
	my_vect.pop_back();
	try	{
		cout << ".at() my  " << my_vect.at(4) << endl;
	} catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	try	{
		cout << ".at() org " << vect.at(4) << endl;
	} catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	cout << "front my  " << my_vect.front() << endl;
	cout << "front org " << vect.front() << endl;

	cout << "back my  " << my_vect.back() << endl;
	cout << "back org " << vect.back() << endl;


	ft::vector<int> vec1;
	ft::vector<int> vec2;
	for (int i = 0; i < 100; ++i) {
		vec1.push_back(i);
		vec2.push_back(i);
	}
	vec1.push_back(453);
	if ((vec1 > vec2))
		cout << "true" << endl;
	else
		cout << "false" << endl;
	
	std::vector<int>::iterator it4 = vect.begin();
	for (std::vector<int>::iterator ite = vect.end(); it4 != ite; ++it4)
		cout << "it4 " << *it4 << endl;
	vect.clear();
	std::vector<int>::iterator it5 = vect.begin();
	for (std::vector<int>::iterator ite = vect.end(); it5 != ite; ++it5)
		cout << "it5 " << *it5 << endl;
	cout << "clear size " << vect.size() << endl;
	cout << "[] size " << vect[1] << endl;



	ft::vector<int>::iterator it6 = my_vect.begin();
	for (ft::vector<int>::iterator ite = my_vect.end(); it6 != ite; ++it6)
		cout << "it6 " << *it6 << endl;
	my_vect.clear();
	ft::vector<int>::iterator it7 = my_vect.begin();
	for (ft::vector<int>::iterator ite = my_vect.end(); it7 != ite; ++it7)
		cout << "it7 " << *it7 << endl;
	cout << "clear size " << my_vect.size() << endl;
	cout << "[] size " << my_vect[1] << endl;


	cout << "vect cap " << vect.capacity() << endl;
	vect.reserve(5);
	cout << "vect new cap " << vect.capacity() << endl;
	for (size_t i = 0; i < 15; ++i)
		vect.push_back(i);
	std::vector<int>::iterator it8 = vect.begin();
	for (std::vector<int>::iterator ite = vect.end(); it8 != ite; ++it8)
		cout << "it8 " << *it8 << endl;
	cout << "vect new cap before push[15] " << vect.capacity() << endl;


	cout << "my_vect cap " << my_vect.capacity() << endl;
	my_vect.reserve(5);
	cout << "my_vect new cap " << my_vect.capacity() << endl;
	for (size_t i = 0; i < 15; ++i)
		my_vect.push_back(i);
	ft::vector<int>::iterator it9 = my_vect.begin();
	for (ft::vector<int>::iterator ite = my_vect.end(); it9 != ite; ++it9)
		cout << "it9 " << *it9 << endl;
	cout << "my_vect new cap before push[15] " << my_vect.capacity() << endl;

	
	vector<int> vect3;
	cout << "size v3  " << vect3.size() << endl;
	vect3.insert(vect3.end(), 10);
	cout << "size v3  " << vect3.size() << endl;
	vect3.insert(vect3.end(), 20);
	cout << "size v3  " << vect3.size() << endl;
	vect3.insert(vect3.begin(), 50);

	std::vector<int>::iterator it3 = vect3.begin();
	for (std::vector<int>::iterator ite = vect3.end(); it3 != ite; ++it3)
		cout << *it3 << endl;

	vector<bool> vectBool;
	vectBool.push_back(2);
	cout << vectBool.at(0) << endl;
	vectBool.flip();
	cout << vectBool.at(0) << endl;

	// ft::vector<int> vectSwap;
	// swap(my_vect, vectSwap);
	// ft::vector<int>::iterator itSwap = vectSwap.begin();
	// for (ft::vector<int>::iterator ite = vectSwap.end(); itSwap != ite; ++itSwap)
	// 	cout << *itSwap << endl;
}
