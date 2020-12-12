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

void move(char a, int v, int &x, int &y) {
    switch (a)
    {
        case 'N':
            x += v;
            break;
        
        case 'S':
            x -= v;
            break;

        case 'E':
            y += v;
            break;

        case 'W':
            y -= v;
            break;
        default: assert(0);
    }
}

char rotate_acw(char cc, int value) {
    unordered_map<char, int> m {
        {'N', 0},
        {'W', 1},
        {'S', 2},
        {'E', 3}
    };
    char C[] = {'N', 'W', 'S', 'E'};

    int idx = m[cc];

    return C[(idx + value) % 4];
}

char rotate_cw(char cc, int value) {
    unordered_map<char, int> m {
        {'N', 0},
        {'W', 3},
        {'S', 2},
        {'E', 1}
    };
    char C[] = {'N', 'E', 'S', 'W'};

    int idx = m[cc];

    return C[(idx + value) % 4];
}

void rotate_L(int &x, int &y) {
    swap(x, y);
    y = -y;
}

void rotate_R(int &x, int &y) {
    swap(x, y);
    x = -x;
}

int main() {
    int x=1, y=10;
    int sx=0, sy =0;
    string line;
    char cc = 'E';
    while (cin >> line) {
        char action;
        int value;

        sscanf(line.c_str(), "%c%d", &action, &value);

        switch (action)
        {
            case 'N':
            case 'S':
            case 'E':
            case 'W':
                move(action, value, x, y);
                break;
            
            case 'F':
            // move(cc, x, y);
                sx += x* value;
                sy += y*value;
                break;

            case 'L':
                // cc = rotate_acw(cc, value);
                value = value / 90;
                while(value--) rotate_L(x, y);
                break;

            case 'R':
                value = value / 90;
                while(value--) rotate_R(x, y);
                // cc = rotate_cw(cc, value);
                break;


            default: assert(0);
        }
    }

    cout << abs(sx) + abs(sy) << endl;
}
