#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <random>
#include <stack>
#include <list>
#include <climits>
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

#define PREAMBLE 25

bool satisfy(std::vector<unsigned long long > &v, int l, int h, unsigned long long t) {
	unordered_set< unsigned long long> complement;

	for (int i = l; i <= h; i++) {
		unsigned long long r = t - v[i];
		if (complement.count(r) == 1) return true;
		complement.insert(v[i]);
	}

	return false;
}

unsigned long long solve(std::vector<unsigned long long > &v ) {
	int low = 0, high = PREAMBLE - 1;


	for (int i = PREAMBLE; i < v.size()+0; i++,low++, high++) {
		if (!satisfy(v, low, high, v[i])) return v[i];
	}

	return 0;
}

unsigned long long solve2(vector<unsigned long long > &v, unsigned long long m) {
	unsigned long long csum = v[0];
	int low = 0, i = 1;

	for (i = 1; i <= v.size()+0; i++) {
		while (csum > m && low < i - 1) {
			csum = csum - v[low];
			low++;
		}

		if (csum == m) {
			unsigned long long mn = csum, mx = 0;
			for ( int j = low; j < i; j++) {
				mn = min(mn, v[j]);
				mx = max(mx, v[j]);
			}
			
			return mn + mx;
		}

		if (i < v.size()+0) {
			csum += v[i];
		}
	}

	return 0;
}

int main() {

	unsigned long long x;
	vector<unsigned long long> v;
	while (cin >> x) {
		v.push_back(x);
		// cout << x << endl;
	}

	unsigned long long m = solve(v);
	cout << m << endl;

	cout<< solve2(v, m) << endl;
}
