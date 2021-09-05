#pragma once
#include"Lexer.h"
#include"My_Tree.h"


class Syntaxer
{
private:
	My_Tree my_tree;
	vector<Lexer::token> lexems;
	vector<string> mistackes;
	int cur_lexem;
	string mistacke;
	int iter;
	bool no_mistake;

public:
	Syntaxer();

	string current_lexem_line();
	string current_lexem_column();
	string current_lexem_name();
	int current_lexem_code();
	bool program();
	bool procedure_identifier();
	bool block();
	bool declarations();
	bool statemets_list();
	bool constant_declarations();
	bool constant_declarations_list();
	bool constant_declaration();
	bool constant_identifier();
	bool constant();
	bool complex_number();
	bool left_part();
	bool right_part_coma();
	bool right_part_dollar();
	bool get_mistake() {
		return no_mistake;
	}

	bool statement();
	bool else1();


	My_Tree syntaxer_work(string test_name, string output_file);

};

