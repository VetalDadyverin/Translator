#pragma once
#include"Sorted_tables.h"
#include"Lexer.h"

class My_Tree
{
public:

	struct node_type {
		Lexer::token node_value;
		node_type* parent;
		vector<node_type*> branches;
	};

	node_type* get_current_node() {
		return current_node;
	}
	
	My_Tree();
	void add_node_simple_value(string node_name);
	int return_amount_of_branches() {
		return current_node->branches.size();
	}
	void add_node_lexer_value(Lexer::token smth);
	void next_node(int numb);
	void go_back();
	void set_start() {
		current_node = main_parent->branches[0];
	}
	void print_all(fstream& file);
	void print(node_type* node, string lines, fstream& file);
private:
	

	node_type* main_parent;
	node_type* current_node;

};

