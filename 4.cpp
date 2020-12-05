#include <iostream>
#include <unordered_set>
#include <unordered_map>
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
//xoxoxoxoxoo regex


bool isdigit(string &s) {
	return s.find_first_not_of("0123456789") == string::npos;
}

bool byr(string s) {
	//byr (Birth Year) - four digits; at least 1920 and at most 2002
	return s.size() == 4 && isdigit(s) && stoi(s) >= 1920 && stoi(s) <= 2002;
}

bool iyr(string s) {
	//iyr (Issue Year) - four digits; at least 2010 and at most 2020
	return s.size() == 4 && isdigit(s) && stoi(s) >= 2010 && stoi(s) <= 2020;
}

bool eyr(string s) {
	//eyr (Expiration Year) - four digits; at least 2020 and at most 2030
	return s.size() == 4 && isdigit(s) && stoi(s) >= 2020 && stoi(s) <= 2030;
}

bool hgt(string s) {
	//If cm, the number must be at least 150 and at most 193.
	regex base_regex1("1[5-8][0-9]cm");
	regex base_regex2("19[0-3]cm");
	//If in, the number must be at least 59 and at most 76.
	regex base_regex3("59in");
	regex base_regex4("6[0-9]in");
	regex base_regex5("7[0-6]in");
	smatch base_match;

	return regex_match(s, base_match, base_regex1) ||
	regex_match(s, base_match, base_regex2) || 
	regex_match(s, base_match, base_regex3) ||
	regex_match(s, base_match, base_regex4) ||
	regex_match(s, base_match, base_regex5);
}

bool hcl(string s) {
	// hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f.
	regex base_regex1("#[0-9|a-f]{6}");
	smatch base_match;
	return regex_match(s, base_match, base_regex1);
	// return s.size() == 7 && s[0] == '#' && s.substr(1).find_first_not_of("0123456789abcdefghijklmnopqrstuvwxyz") == string::npos;

}

bool ecl(string s) {
	// ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth.
	static unordered_set<string> values{
		"amb", "blu", "brn", "gry", "grn", "hzl", "oth"
	};

	return values.count(s) == 1;

}

bool pid(string s) {
	//pid (Passport ID) - a nine-digit number, including leading zeroes.
	return s.size() == 9 && isdigit(s);
}


int main() {
	vector<pair<string, bool(*)(string)>> mh = {
		make_pair("byr", &byr),
		make_pair( "iyr", &iyr),
		make_pair( "eyr", &eyr),
		make_pair( "hgt", &hgt),
		make_pair( "hcl", &hcl),
		make_pair( "ecl", &ecl),
		make_pair( "pid", &pid)
	};

	string s;
	int valid = 0;
	while (!cin.eof()) {
		unordered_map<string, string> pass;//xoxoxxoxo set
		while ( getline(cin, s) && s.length()) {
			stringstream ss;
			ss << s;

			string sss;
			while (ss >> sss) {
				string key, value;
				size_t pos = sss.find(':');
				assert(pos != string::npos);

				key = sss.substr(0, pos);
				value = sss.substr(pos+1);
				cout << key << ' ' << value << endl;

				pass.insert(make_pair(key, value));
			}
    	}
    	cout << endl;

    	bool b = true;
    	for (auto p : mh) {
    		auto key = p.first;
    		auto f = p.second;
    		if (pass.find(key) == pass.end() || !f(pass[key])) {
    			b = false;;
    			break;
    		}
    	}

    	if (b)valid++;
	}

	cout << valid << endl;
}