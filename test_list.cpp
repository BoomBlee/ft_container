#include <iostream>
#include <list>
#include <iterator>
#include "list.hpp"

using namespace std;

int main() {
	ft::list<int> my_list;
	list<int> list0;
	cout << "list size " <<  list0.size() << endl;
	cout << "my_l size " <<  my_list.size() << endl;
	cout << "list empty " <<  list0.empty() << endl;
	cout << "my_l empty " <<  my_list.empty() << endl;
	cout << "list max_size " <<  list0.max_size() << endl;
	cout << "my_l max_size " <<  my_list.max_size() << endl;
	
		cout << "--------push_back--------" << endl;
	list0.push_back(1);
	list0.push_back(2);
	list0.push_back(3);
	list0.push_back(4);
	list0.push_back(5);
	// list0.pop_front();
	list<int>::iterator it = list0.begin();
	for (list<int>::iterator ite = list0.end(); it!=ite; ++it)
		cout << "p " << *it << endl;

		cout << "--------my_push_back--------" << endl;
	my_list.push_back(1);
	my_list.push_back(2);
	my_list.push_back(3);
	my_list.push_back(4);
	my_list.push_back(5);
	my_list.begin();
	// my_list.pop_front();
	ft::list<int>::iterator my_it = my_list.begin();
	for (ft::list<int>::iterator ite = my_list.end(); my_it!=ite; ++my_it)
		cout << "p " << *my_it << endl;


	ft::list<int> my_list1;
	list<int> list1;
		cout << "--------insert--------" << endl;
	it = list1.begin();
	it = list1.insert(it, 9);
	it = list1.insert(it, 19);
	for (list<int>::iterator ite = list1.end(); it!=ite; ++it)
		cout << "test i " << *it << endl;

	it = list1.begin();
	cout << "   a size " << list1.size() << endl;
	list1.insert(it, 5, 55);
	it = list1.begin();
	cout << "   a size " << list1.size() << endl;
	for (list<int>::iterator ite = list1.end(); it!=ite; ++it)
		cout << "i " << *it << endl;

	// it = list0.end();
	// list0.insert(it, list0.begin(), list0.end());
	// it = list0.begin();
	// for (list<int>::iterator ite = list0.end(); it!=ite; ++it)
	// 	cout << "l " << *it << endl;	

		cout << "--------my_insert--------" << endl;
	my_it = my_list1.begin();
	my_it = my_list1.insert(my_it, 5);
	my_it = my_list1.insert(my_it, 15);
	for (ft::list<int>::iterator ite = my_list1.end(); my_it!=ite; ++my_it)
		cout << "test i " << *my_it << endl;

	my_it = my_list1.begin();
	cout << "   a size " << my_list1.size() << endl;
	my_list1.insert(my_it, 5, 55);
	my_it = my_list1.begin();
	cout << "   a size " << my_list1.size() << endl;
	for (ft::list<int>::iterator ite = my_list1.end(); my_it!=ite; ++my_it)
		cout << "i " << *my_it << endl;

	// my_it = my_list.end();
	// my_list.insert(my_it, my_list.begin(), my_list.end());
	// my_it = my_list.begin();
	// for (ft::list<int>::iterator ite = my_list.end(); my_it!=ite; ++my_it)
	// 	cout << "l " << *my_it << endl;

		cout << "--------assign--------" << endl;
	list<int> list2;
	list2.push_back(2);
	list2.push_front(5);
	list2.assign(1, 100);
	it = list2.begin();
	for (list<int>::iterator ite = list2.end(); it!=ite; ++it)
		cout << "a " << *it << endl;

		cout << "--------my_assign--------" << endl;

	// cout << "my_a size " << my_list1.size() << endl;
	// my_it = my_list1.begin();
	// for (ft::list<int>::iterator ite = my_list1.end(); my_it!=ite; ++my_it)
	// 	cout << "i " << *my_it << endl;

	ft::list<int> my_list2;
	my_list2.push_back(2);
	my_list2.push_front(5);
	cout << "my_a size " << my_list2.size() << endl;
	my_list2.assign(5, 400);
	cout << "my_b size " << my_list2.size() << endl;
	my_it = my_list2.begin();
	for (ft::list<int>::iterator ite = my_list2.end(); my_it!=ite; ++my_it)
		cout << "b " << *my_it << endl;


		cout << "--------test--------" << endl;
	ft::list<int> my_list3;
	my_list3.push_back(123);
	// my_list3.clear();
	// my_list3.push_back(321);
	my_list3.insert(my_list3.begin(),3 ,55);
	// my_list3.push_back(2);
	// my_list3.clear();
	my_list3.insert(my_list3.begin(), 2, 100);
	// my_list3.push_back(976);
	my_list3.resize(10);
	// my_it = my_list3.begin();
	// for (ft::list<int>::iterator ite = my_list3.end(); my_it!=ite; ++my_it)
	// 	cout << "sort " << *my_it << endl;
	my_list3.swap(my_list2);
	cout << "_size " << my_list3.size() << endl;
	my_list3.push_front(256);
	my_list3.push_back(76);
	my_list3.sort();
	// my_list2.reverse();
	// my_list3.merge(my_list2);
	my_it = my_list3.begin();
	for (ft::list<int>::iterator ite = my_list3.end(); my_it!=ite; ++my_it)
		cout << "swap " << *my_it << endl;
	// my_list3.sort();
	// cout << "my_pop " << *my_list3.begin() << endl;
	my_list3.resize(5,654);
	my_list3.resize(10);
	// my_it = my_list3.begin();
	// for (ft::list<int>::iterator ite = my_list3.end(); my_it!=ite; ++my_it)
	// 	cout << "sort " << *my_it << endl;
	my_list3.swap(my_list2);
	cout << "_size " << my_list3.size() << endl;
	my_list3.push_front(256);
	my_list3.push_back(76);
	my_list3.sort();
	my_list2.sort();
	my_list2.reverse();
	// my_it = my_list3.begin();
	// for (ft::list<int>::iterator ite = my_list3.end(); my_it!=ite; ++my_it)
	// 	cout << "list3 " << *my_it << endl;

	cout << "-----reverse-----" << endl;

	my_it = my_list2.begin();
	for (ft::list<int>::iterator ite = my_list2.end(); my_it!=ite; ++my_it)
		cout << "list2 " << *my_it << endl;

	// my_list3.merge(my_list2);
	cout << "-----reverse-----" << endl;

}