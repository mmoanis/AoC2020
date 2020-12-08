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

struct inst {
	string op;
	long long arg = 0;
};

bool execute(long long &acc, unordered_map<int, inst> &prog) {
	unordered_set<unsigned long long> visited;
	acc = 0;

	for (unsigned long long i = 0; ;) {
		if (prog.count(i) == 0) return true;

		if (visited.count(i) == 1) return false;
		visited.insert(i);

		inst &it = prog[i];
		if (it.op == "nop") i++;
		else if (it.op == "acc") {
			acc += it.arg;
			i++;
		}
		else if (it.op == "jmp") i += it.arg;
	}

	return false;
}


int main() {
	string s; long long value;
	unordered_map<int, inst> prog;

	long long  acc = 0;
	int ip = 0;

	while (!cin.eof() && cin >> s && cin >> value) {
		inst i;
		i.op = s;
		i.arg = value;

		prog.insert(make_pair(ip++, i));
	}

	for (int i = 0; i < ip; i++) {
		string op = prog[i].op;

		if (prog[i].op == "nop") prog[i].op = "jmp";
		else if (prog[i].op == "jmp") prog[i].op = "nop";

		if (execute(acc, prog)) {
			cout << "Corrupt Instruction " << i << ' ' << op << endl;
			break;
		}

		prog[i].op = op;
	}

	cout << acc << endl;
}
