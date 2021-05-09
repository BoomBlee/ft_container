#include <iostream>
#include <map>
#include <iterator>
#include "map.hpp"

using namespace std;

int main() {
	map<int,int> mapp;
	mapp.insert(std::pair<int,int>(55,1));
	mapp.insert(std::pair<int,int>(55,2));
	map<int, int>::iterator it = mapp.begin();
	for (map<int, int>::iterator ite = mapp.end(); it != ite; ++it) {
		cout << it->second << endl;
	}
	return 0;
}