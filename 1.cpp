// AOC 1


#include <iostream>
#include <unordered_set>
#include <cmath>
#include <vector>
using namespace std;

int main() {

	unsigned long long max_result_seen = 0;


	vector<int> v;

	int x;

	// x + y + z = 2020
	// 2020 - x =  y + z

	while (cin >> x) {
		v.push_back(x);
	}

	for (int i =0; i < v.size(); i++ ) {
		int R = 2020 - v[i];

		

		unordered_set< int> complement;
		for (int j = 0; j < v.size(); j++) {
			if (i == j) continue;


			int r = R - v[j];

			if (complement.count(r) == 1) {
				unsigned long long result = v[i] * v[j] * r;
				cout << v[i] << ' ' << v[j] << ' ' << r << ' ' << result << ' ' << max_result_seen << endl;

				max_result_seen = max(max_result_seen, result);
			}

			complement.insert(v[j]);
		}
	}


	cout << max_result_seen << endl;
}
