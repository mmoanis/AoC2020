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


void generate(unordered_map<unsigned long long, unsigned long long> &mem, string &mask,
    bitset<36> index, unsigned long long value, size_t pos) {
    // cout << ind << pos << index << endl;
    if (pos == mask.size()) {
        unsigned long long x = index.to_ullong();
        mem[x] = value;

        // cout << x << '=' << value  << endl;
        return;
    }

    int i = pos;
    for (; i < mask.size()+0; i++) {
        if (mask[i] == 'X') break;
    }

    if (i < mask.size()+0) {
        index.reset(35-i);
        generate(mem, mask, index, value, i+1);
        index.set(35-i);
        generate(mem, mask, index, value, i+1);
    } else {
        unsigned long long x = index.to_ullong();
        mem[x] = value;
    }
}

int main() {
    unordered_map<unsigned long long, unsigned long long> mem;
    string line;
    string mask;

    while (getline(cin, line) && !line.empty()) {
        if (line.rfind("mask", 0) == 0) {
            mask = line.substr(line.rfind("=")+2);
            // cout << mask << endl;
            continue;
        }

        size_t end = line.rfind("]"), start = line.rfind("[");
        unsigned long long index = stoi(line.substr(start+1, end-start-1));
        unsigned long long value = stoi(line.substr(line.rfind("=")+2));

        bitset<36> bits = index;

        for (int i = 0; i < mask.size()+0; i++) {
            if (mask[i] == '1') bits.set(35-i);
        }

        generate(mem, mask, bits, value, 0);
    }

    unsigned long long sum = 0;
    for (auto&p : mem) sum = sum + p.second;

    cout << sum << endl;
}
