#include <iostream>
#include <unordered_set>
#include <cmath>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <cstdio>
using namespace std;

unsigned long long  i(int x) { return x == 0? 1 : x; }

int main() {

	//vector<string> grid;

	string row;
	cin >> row;
	int pos13 = 1, pos31 = 3, pos51 = 5, pos71 = 7, pos12 = 1;
	int l = row.size();
	int trees13 = 0, trees31 = 0, trees51 = 0, trees71 = 0, trees12 = 0;
	bool flip = false;
	while (cin >> row) {
		trees13 += (row[pos13 % l] == '#') ? 1 : 0;
		trees31 += (row[pos31 % l] == '#') ? 1 : 0;
		trees51 += (row[pos51 % l] == '#') ? 1 : 0;
		trees71 += (row[pos71 % l] == '#') ? 1 : 0;

		trees12 += (flip && row[pos12 % l] == '#') ? 1 : 0;
		pos12 += flip? 1 : 0;
		flip = !flip;


		pos13 += 1;
		pos31 += 3;
		pos51 += 5;
		pos71 += 7;
	}

	cout << trees13 << ' ' << trees31 << ' ' << trees51 << ' ' <<  trees71 << ' ' << trees12 << endl;
	cout << i(trees13) * i(trees31) * i(trees51) * i(trees71) * i(trees12) << endl;

}