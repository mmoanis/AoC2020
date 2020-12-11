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

int CC(vector<string> &grid, int row, int col) {
    int count = 0;
    pair<int, int> neighbours[] = {
        {+1, 0},
        {-1, 0},
        {0, +1},
        {0, -1},
        {+1, +1},
        {-1, -1},
        {+1, -1},
        {-1, +1}
    };

    for (auto & n : neighbours) {
        int r = row + n.first;
        int c = col + n.second;
        while (r >= 0 && r < grid.size() && c >= 0 && c < grid[0].size()) {
            if (grid[r][c] == 'L') break;

            if (grid[r][c] == '#') {count++; break;}

            r += n.first;
            c += n.second;
        }
    }

    return count;
}

int populate(vector<string> &grid) {
    int count = 0;
    vector<string> ngrid = grid;

    for (int row = 0; row < grid.size()+0; row++) {
        for (int col = 0; col < grid[row].size(); col++) {
            int occupied = CC(grid, row, col);

            if (grid[row][col] == 'L') {
                if (occupied == 0) {
                    ngrid[row][col] = '#';
                    count++;
                }

            } else if (grid[row][col] == '#') {
                if (occupied >= 5) {
                    ngrid[row][col] = 'L';
                    count++;
                }
            }
        }
    }

    grid = ngrid;
    return count;
}

int main() {
    vector<string> grid;
    string s;
    while (cin >> s) {
        grid.push_back(s);
    }

    while (populate(grid) > 0);

    int count = 0;
    for (auto& s : grid) {
        for (auto&c : s) {
            count += c == '#'? 1 : 0;
        }
    }

    cout << count << endl;
}
