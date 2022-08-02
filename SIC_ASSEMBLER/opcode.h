#pragma once
#include<map>
#include<iostream>

using namespace std;

string getopcode(string s) {
	map<string, string> rec;
	rec.insert(pair <string, string>("LDA", "00"));
	rec.insert(pair <string, string>("AND", "40"));
	rec.insert(pair <string, string>("DIV", "24"));
	rec.insert(pair <string, string>("SUB", "1C"));
	rec.insert(pair <string, string>("ADD", "18"));
	rec.insert(pair <string, string>("LDL", "08"));
	rec.insert(pair <string, string>("RD", "D8"));
	rec.insert(pair <string, string>("WD", "DC"));
	rec.insert(pair <string, string>("LDCH", "50"));
	rec.insert(pair <string, string>("STX", "10"));
	rec.insert(pair <string, string>("JLT", "38"));
	rec.insert(pair <string, string>("TIX", "2C"));
	rec.insert(pair <string, string>("TD", "E0"));
	rec.insert(pair <string, string>("STCH", "54"));
	rec.insert(pair <string, string>("STL", "14"));
	rec.insert(pair <string, string>("LDX", "04"));
	rec.insert(pair <string, string>("RSUB", "4C"));
	rec.insert(pair <string, string>("STA", "0C"));
	rec.insert(pair <string, string>("J", "3C"));
	rec.insert(pair <string, string>("JEQ", "30"));
	rec.insert(pair <string, string>("COMP", "28"));
	rec.insert(pair <string, string>("COMP", "14"));
	rec.insert(pair <string, string>("JSUB", "48"));
	rec.insert(pair <string, string>("JGT", "34"));
	rec.insert(pair <string, string>("MUL", "20"));
	rec.insert(pair <string, string>("OR", "44"));
	rec.insert(pair <string, string>("STSW", "E8"));

	if (rec.find(s) == rec.end()) {
		return "-1";
	}
	return rec[s];
}