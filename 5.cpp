#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <cstdio>
#include <sstream>
#include <functional>
#include <assert.h>
#include <regex>
using namespace std;


int bb(string &s, int L, int R, int I, int K, char C) {
	int l =L, r=R, i = I, m;

	for (; i<=K; i++) {
		m = l + ((r+1) - l)/2;

		if (s[i] == C)
			r = m -1;
		else l = m;
	}
	return s[i] == C? r : l;
}

int sisi(string &s) {
	assert(s.size() == 10);
	int row = bb(s, 0, 127, 0, 6, 'F');
	int col = bb(s, 0, 7, 7, 9, 'L');
	// cout << row * 8 + col << endl;
	return row * 8 + col;
}


int main() {
	string s;
	int max_s = 0;
	unordered_set<int> seats;
	while (cin >> s) {
		// max_s = max(sisi(s), max_s);
		seats.insert(sisi(s));
	}

	bool flip = true;
	for (int i =0; i < 1024; i++) {
		if (!flip && seats.count(i) == 0) {
			cout << i << endl;
			break;
		}
		if (flip && seats.count(i) == 1) {
			flip = !flip;
		}
	}
}
