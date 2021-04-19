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

	ft::vector<int> vect_copy;
	vect_copy = vec2;
	// ft::vector<int>::iterator itc = vec2.begin();
	// for (ft::vector<int>::iterator ite = vec2.end(); itc != ite; ++itc)
	// 	cout << "vec2 " << *itc << endl;
	// itc = vect_copy.begin();
	// for (ft::vector<int>::iterator ite = vect_copy.end(); itc != ite; ++itc)
	// 	cout << "vcpy " << *itc << endl;
	cout << "vcpy " << vect_copy.size() << endl;
	cout << "vec2 " << vec2.size() << endl;
	cout << "vcpy " << vect_copy.capacity() << endl;
	cout << "vec2 " << vec2.capacity() << endl << endl;

	// vector<int> vec_copy;
	vector<int> vec3;

	for (int i = 0; i < 100; ++i) {
		vec3.push_back(i);
	}

	// vec_copy = vec3;
	vector<int> vec_copy(vec3);
	cout << "vcpy " << vec_copy.size() << endl;
	cout << "vec3 " << vec3.size() << endl;
	cout << "vcpy " << vec_copy.capacity() << endl;
	cout << "vec3 " << vec3.capacity() << endl;
	// vector<int>::iterator itc = vec_copy.begin();
	// for (vector<int>::iterator ite = vec_copy.end(); itc != ite; ++itc)
	// 	cout << "vcpy " << *itc << endl;

	vector<int> test;
	for (size_t i=0; i < 5; ++i)
		test.push_back(i);
	test.assign(10, 5);
	vector<int>::iterator t = test.begin();
	// for(vector<int>::iterator te = test.end(); t != te; ++t)
	// 	cout << "t " << *t << endl;
	cout << "t size " << test.size() << endl;
	cout << "t cap " << test.capacity() << endl;
	for (size_t i=0; i < 100; ++i)
		test.push_back(i);
	cout << "t size " << test.size() << endl;
	cout << "t cap " << test.capacity() << endl;

	vector<int> test1;
	for (size_t i=0; i < 5; ++i)
		test1.push_back(i);
	test1.assign(10, 5);
	vector<int>::iterator t1 = test1.begin();
	// for(vector<int>::iterator te = test1.end(); t1 != te; ++t1)
	// 	cout << "t " << *t1 << endl;
	cout << "t1 size " << test1.size() << endl;
	cout << "t1 cap " << test1.capacity() << endl;
	for (size_t i=0; i < 100; ++i)
		test1.push_back(i);
	cout << "t1 size " << test1.size() << endl;
	cout << "t1 cap " << test1.capacity() << endl;

	cout << "--------insert--------" << endl;
	vector<int> insert;
	insert.insert(insert.begin(),10);
	insert.insert(insert.begin(),20);
	insert.insert(insert.begin(),30);
	insert.insert(insert.begin(),40);
	insert.insert(insert.begin(),50);
	vector<int>::iterator inst = insert.begin();
	vector<int>::iterator inst0 = insert.begin();
	insert.insert(++inst0,60);
	insert.erase(--inst0);
	for(vector<int>::iterator te = insert.end(); inst != te; ++inst)
		cout << "t " << *inst << endl;
	cout << "inst size " << insert.size() << endl;
	cout << "inst cap " << insert.capacity() << endl;

	cout << "--------my insert--------" << endl;
	ft::vector<int> ins1;
	ins1.insert(ins1.begin(),10);
	ins1.insert(ins1.begin(),20);
	ins1.insert(ins1.begin(),30);
	ins1.insert(ins1.begin(),40);
	ins1.insert(ins1.begin(),50);
	ft::vector<int>::iterator inst1 = ins1.begin();

	ft::vector<int>::iterator inst2 = ins1.begin();
	ins1.insert(++inst2,60);
	ins1.erase(--inst2);
	for(ft::vector<int>::iterator te1 = ins1.end(); inst1 != te1; ++inst1)
		cout << "t1 " << *inst1 << endl;
	cout << "inst1 size " << ins1.size() << endl;
	cout << "inst1 cap " << ins1.capacity() << endl;


	cout << "--------resize--------" << endl;
	vector<int> vect_resize;
	for (size_t i=0; i < 6; ++i)
		vect_resize.push_back(i);
	
	vector<int>::iterator it_resize = vect_resize.begin();
	for (vector<int>::iterator ite = vect_resize.end(); it_resize != ite; ++it_resize)
		cout << "rs " << *it_resize << endl;
	vect_resize.resize(10, 99);

	it_resize = vect_resize.begin();
	for (vector<int>::iterator ite = vect_resize.end(); it_resize != ite; ++it_resize)
		cout << "rss " << *it_resize << endl;
	// cout << "vect_resize [4] " << vect_resize[4] << endl;
	cout << "vect_resize size " << vect_resize.size() << endl;
	cout << "vect_resize cap " << vect_resize.capacity() << endl;

		cout << "--------my_resize--------" << endl;
	vector<int> my_vect_resize;
	for (size_t i=0; i < 6; ++i)
		my_vect_resize.push_back(i);
	
	vector<int>::iterator my_it_resize = my_vect_resize.begin();
	for (vector<int>::iterator ite = my_vect_resize.end(); my_it_resize != ite; ++my_it_resize)
		cout << "rs " << *my_it_resize << endl;
	my_vect_resize.resize(10, 99);

	my_it_resize = my_vect_resize.begin();
	for (vector<int>::iterator ite = my_vect_resize.end(); my_it_resize != ite; ++my_it_resize)
		cout << "rss " << *my_it_resize << endl;
	// cout << "my_vect_resize [4] " << my_vect_resize[4] << endl;
	cout << "my_vect_resize size " << my_vect_resize.size() << endl;
	cout << "my_vect_resize cap " << my_vect_resize.capacity() << endl;


		cout << "--------construstor--------" << endl;
	vector<int> vect_constr(0,5);
	vector<int>::iterator it_vc = vect_constr.begin();
	for(vector<int>::iterator ite = vect_constr.end(); it_vc != ite; ++it_vc)
		cout << "vs " << *it_vc << endl;
	cout << "vc size " << vect_constr.size() << endl;
	cout << "vc cap " << vect_constr.capacity() << endl;
	
	vect_constr.push_back(10);

	it_vc = vect_constr.begin();
	for(vector<int>::iterator ite = vect_constr.end(); it_vc != ite; ++it_vc)
		cout << "vs " << *it_vc << endl;	
	cout << "vc size " << vect_constr.size() << endl;
	cout << "vc cap " << vect_constr.capacity() << endl;

			cout << "--------my_construstor--------" << endl;
	vector<int> my_vect_constr(0,5);
	vector<int>::iterator it_vc_my = my_vect_constr.begin();
	for(vector<int>::iterator ite = my_vect_constr.end(); it_vc_my != ite; ++it_vc_my)
		cout << "vs " << *it_vc_my << endl;
	cout << "vc size " << my_vect_constr.size() << endl;
	cout << "vc cap " << my_vect_constr.capacity() << endl;
	
	my_vect_constr.push_back(10);

	it_vc_my = my_vect_constr.begin();
	for(vector<int>::iterator ite = my_vect_constr.end(); it_vc_my != ite; ++it_vc_my)
		cout << "vs " << *it_vc_my << endl;	
	cout << "vc size " << my_vect_constr.size() << endl;
	cout << "vc cap " << my_vect_constr.capacity() << endl;
}

// check iter in function
// test swap
// assign(iter)
// insert
// erase