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


int main() {


	int valid = 0;
	while (!cin.eof()) {
		unordered_map<char, int> scores;
		string s;
		int count = 0;
		while ( getline(cin, s) && s.length()) {
			unordered_set<char> answers;	
			for (auto c:s) answers.insert(c);
			for (auto c:answers) scores[c]++;
			count++;
		}

		for (char c = 'a'; c <= 'z'; c++) {
			if (scores.count(c) && scores[c] == count) {
				valid++;
			}
		}
	}
	cout << valid << endl;
}
