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


struct bag {
	unordered_map<string, int> rbags;
	unordered_map<string, int> fbags;
	string name;

bool operator==(const bag &other) const { return name == other.name;}
};
unordered_map<string, bag> bags;
unordered_set<string> visited;
string gold = "shiny gold";
int answer = 0;


void dfs1(string root, string ind = "") {
	cout << ind << root << " tree=" << bags.count(root)
        <<  " vistited=" << visited.count(root)
        << " answer=" << answer << endl;

	if (visited.count(root) == 1) return;
	visited.insert(root);

	if (root != gold) answer++;

	unordered_map<string, int> &bagss = bags[root].rbags;
	for (auto p : bagss) {
		dfs1(p.first, ind + " ");
	}
}

int dfs2(string root, string ind = "") {
	cout << ind << root << " tree=" << bags.count(root) <<  " vistited=" << visited.count(root) << endl;

	if (bags.count(root) == 0) return 0;

	int x = 0;
	unordered_map<string, int> &bagss = bags[root].fbags;
	for (auto p : bagss) {
		x += p.second  + p.second * dfs2(p.first, ind + " ");
	}

	cout << ind << ' ' << x << endl;

	return x;
}


int main() {

	string s;
	string token = "bags contain", token1 = "bag", token3 = "no other bags";
	while ( !cin.eof() && getline(cin, s) && s.length()) {
		size_t idx = s.find(token3);
		if (idx != string::npos) continue;

		idx = s.find(token);
		string name = s.substr(0, idx-1);
		s = s.substr(idx + token.size());

		while (true) {
			int num = s[1] - '0';
			idx = s.find(token1);
			string oname = s.substr(3, idx-4);

			// part 1
			// bags[oname].rbags[name] += num;

			// part 2
			bags[name].fbags[oname] += num;

			s = s.substr(idx + token1.size());
			// cout << s << endl;	
			if (s == "." || s == "s.") break;
			if (s[0] == 's') s = s.substr(2);
			else s = s.substr(1);
		}
	}

	// part 1
	// dfs1(gold);
	// cout << answer << endl;


	// part 2
	cout << dfs2(gold) << endl;
}
