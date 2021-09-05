#pragma once
#include "Syntaxer.h"

class Generate_asm
{

private:
	My_Tree my_tree;
	int curr_my_tree_elem;
	string asm_code;
	vector<string> names;
	bool name_second_time;
	string prog_name;
	int buff_left;
	float Re;
	float Im;
	bool no_mistake;
	int iter;

public :
	Generate_asm(My_Tree input, bool inpt);
	void constant_declarations();
	void generate_work(string output_file);
	void program();
	void procedure_identifier();
	void block();
	void declarations();
	void statement_list();
	void constant_identifier();
	void constant();
	void left_part();
	void right_part();


};

