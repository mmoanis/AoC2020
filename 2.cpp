

#include <iostream>
#include <unordered_set>
#include <cmath>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <cstdio>
using namespace std;



int main() {
	string s1, s2, s3;
	int valid = 0;

	while (cin >> s1 >> s2 >> s3) {
		int mn = -1, mx = -1;

		if (s2.size() != 2) {
			cerr << "SECOND SUBSTRING HAS DIFFERENT SIZE "  << s2.size() << endl;
			exit(1);
		}


		sscanf(s1.c_str(), "%d-%d", &mn, &mx);
		if (mn == -1 || mx == -1) {
			cerr << "FIRST SUBSTRING HAS DIFFERENT SYNTAX " << s1 << endl;
			exit(1);
		}


		// size_t n = std::count(s3.begin(), s3.end(), s2[0]);
		// valid  += (n >= mn && n <= mx)? 1 : 0;

		bool first = s3[mn-1] == s2[0], second = s3[mx-1] == s2[0];

		valid += (!first != !second)? 1 : 0;
	}

	cout << valid << endl;


}