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
#include <bitset>
#include <limits.h>

using namespace std;


int main() {
    unordered_map<long long, long long> nums{
        {6, 1},
        {4, 2},
        {12, 3},
        {1, 4},
        {20, 5},
        {0, 6},
        {16, 7}
    };

    unordered_set<long long> seen{6, 4, 12, 1, 20, 0};

    int prev = 16; 
    for (int i = 8; i <= 30000000; i++) {
        if (seen.count(prev) == 0) {
            seen.insert(prev);
            nums[prev] = i - 1;
            prev = 0;
        } else {
            auto x = nums[prev];
            nums[prev] = i - 1;
            prev = i - 1 - x;
        }

            
    }cout << prev << endl;

}
