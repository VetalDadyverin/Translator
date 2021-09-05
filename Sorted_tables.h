#pragma once

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include<iomanip>
#include<fstream>

using namespace std;

class Sorted_tables {

public:
	Sorted_tables();
	~Sorted_tables();
	void push_const(string item);
	void push_iden(string iden);
	void push_sharp(string sharp1);
	int find_sharp(string sharp1);
	int find_const(string item);
	int find_iden(string iden);
	int find_keyword(string key);
	int get_ascii(char buff);
	void print_const(fstream& file);
	void print_iden(fstream& file);


private:

	map <string, int> const_items;
	map <string, int> identificators;
	map <string, int> keywords = {
		{"PROGRAM", 401},
		{"BEGIN", 402},
		{"END", 403},
		{"CONST", 404},
		{"$EXP", 405}
	};

	map <string, int> sharp;


	int iden_id = 1001;
	int const_id = 501;
	int key_id = 401;
	int sharp9 = 2001;
	int ascii[128];


};