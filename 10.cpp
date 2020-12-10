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

int solve(unordered_set<int> &v, int jolt = 0, int diff1 = 0, int diff2 = 0, int diff3 = 0, string ind = "") {
	cout << ind << v.size() << ' ' << jolt << ' ' << diff1 << ' ' << diff2 << ' ' << diff3 << endl;
	
	if (v.empty()) return diff1 * diff3;

	for (int i = 1; i <= 3; i++) {
		int njolt = jolt + i;
		if (v.count(njolt) == 0) continue;

		v.erase(njolt);
		
		int m = solve(v, njolt, (i==1? diff1+1: diff1), (i==2? diff2+1: diff2), (i==3? diff3+1: diff3), ind + " ");
		if (m != -1) return m;

		v.insert(njolt);
	}

	return -1;
}

unsigned long long solve2(unordered_set<int> &v, int mjolt) {
	vector<unsigned long long> dp(v.size()+1, 0);

	dp[0] = 1;
	if (v.count(1) == 1) dp[1] = 1;
	if (v.count(2) == 1) dp[2] = dp[1] + 1;
	if (v.count(3) == 1) dp[3] = dp[1] + dp[2] + 1;

	for (int i = 4; i <= mjolt; i++) {
		if (v.count(i) == 0) continue;

		dp[i] += dp[i-1] + dp[i-2] + dp[i-3];
	}

	return dp[mjolt];
}

int main() {
	int x, m = -1;
	unordered_set<int> v;
	while (cin >> x) {
		m = max(m, x);
		v.insert(x);
	}
	v.insert(m + 3);

	// m = solve(v);
	// cout << m << endl;

	unsigned long long n = solve2(v, m+3);
	cout << n << endl;
}
