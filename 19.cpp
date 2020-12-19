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
#include <future>
#include <atomic>
#include <thread>

using namespace std;



struct Rule {
    string regex;
    int idx;
    vector<vector<pair<int, string>>> dep;
    unordered_set<int> dep_set;

    friend ostream& operator<<(ostream& out, Rule rule);
};

ostream& operator<<(ostream& out, Rule rule) {
    out << rule.idx << ": ";
    if (rule.dep_set.empty()) out << rule.regex << endl;
    else {
        out << rule.dep_set.size() << " - ";
        for (auto& v : rule.dep) {
            for (auto& vv : v) {
                cout << vv.first << ' ';
            }

            out << " | ";
        }

        out << endl;
    }

    return out;
}


unordered_map<int, Rule> rules;
unordered_map<int, set<int>> dep;
unordered_set<int> rules_ready, rules_r;

void parse_rules() {
    string line;
    while (getline(cin, line) && !line.empty()) {
        Rule rule;
        char c = '.';
        
        int RET = sscanf(line.c_str(), "%d: \"%1c\"", &rule.idx, &c);
        if (1 < RET) {
            rule.regex = c;
            rules_ready.insert(rule.idx);
        } else {
            rules_r.insert(rule.idx);

            size_t pos = line.find(':');
            rule.idx = stoi(line.substr(0, pos));
            line = line.substr(pos+1);
            

            stringstream ss(line);
            int r;
            rule.dep.push_back(vector<pair<int, string>> ());
            while (ss >> r) {
                rule.dep_set.insert(r);
                rule.dep.back().push_back({r, ""});

                dep[r].insert(rule.idx);

                if (ss.peek() == ' ') ss.ignore();

                if (ss.peek() == '|') {    
                    ss.ignore();
                    rule.dep.push_back(vector<pair<int, string>> ());
                }
            }
        }

        // cout << rule << endl;
        rules.insert({rule.idx, rule});
    }
}

void build_rules() {
    // List of unready rules
    while (!rules_r.empty()) {
        // List of ready rules
        auto rules_ready_copy = rules_ready;
        for (auto& ready_rule : rules_ready_copy) {
            auto&& RR = rules[ready_rule];
            // List of dependent rules on the current ready rule
            set<int> deps = dep[ready_rule];
            for (auto& d : deps) {
                auto& R = rules[d];

                // Resolve dependency to the ready rule
                R.dep_set.erase(ready_rule);
                dep[ready_rule].erase(R.idx);
                for (auto& v : R.dep) {
                    for (auto& vv : v) {
                        if (vv.first == ready_rule) {
                            vv.second = "(" + RR.regex + ")";
                        }
                    }
                }

                if (R.dep_set.empty()) {
                    rules_ready.insert(R.idx);
                    rules_r.erase(R.idx);

                    for (auto& v : R.dep) {
                        for (auto& vv : v) {
                            R.regex += vv.second;
                        }
                        R.regex += "|";
                    }

                    R.regex.pop_back();
                    // cout << R << endl;
                }
            }
        }
    }
}

atomic<int> counter1{0}, counter2{0};


void match_rules() {
    vector<thread> threads;

    // Part 2
    // 42+ 42 (42 31)* 31
    auto R42 = "(" + rules[42].regex + ")";
    auto R31 = "(" + rules[31].regex + ")";
    string fregex =  "((" + R42 + "+)(";
    for(std::size_t i = 2; i < 10; ++i) {
        fregex += R42 + "{" + to_string(i) + "}"+ R31 + "{" + to_string(i) + "}|";
    }
    fregex += R42 + R31 + "))";

    string line;
    while (getline(cin, line) && !line.empty()) {
        // async(std::launch::async, &X::operator(), x, line);
        threads.push_back(thread([line, fregex] {
            // Part 1
            auto& R = rules[0];
            regex r1(R.regex);
            if (regex_match(line, r1)) counter1++;

            // Part 2
            regex r2(fregex);
            if (regex_match(line, r2)) counter2++;
        }));


    }

    for (auto& t : threads) t.join();

    cout << counter1 << endl << counter2 << endl;
}

int main() {
    parse_rules();
    build_rules();
    match_rules();
}


