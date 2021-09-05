#pragma once

#include"Sorted_tables.h"



class Lexer {

public:

	Lexer(Sorted_tables* tables);
	~Lexer();
	struct token {
		string name;
		int number;
		int line;
		int column;
	};

	vector<token> lexer_work(string file);
	void print(fstream& file);
	void print_iden_table(fstream& file);
	void print_const_table(fstream& file);
	
private:
	vector<token> tokens;
	Sorted_tables* tables;
};