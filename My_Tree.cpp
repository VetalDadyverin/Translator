#include "My_Tree.h"

My_Tree::My_Tree() {
	main_parent = new node_type;
	main_parent->parent = nullptr;
	main_parent->node_value.name = "<signal-program>";
	main_parent->node_value.number = 0;
	main_parent->node_value.line = 0;
	main_parent->node_value.column = 0;
	current_node = main_parent;
}

void My_Tree::add_node_simple_value(string node_name) {
	node_type* buff = new node_type;
	buff->parent = this->current_node;
	buff->node_value.name = node_name;
	buff->node_value.number = 0;
	buff->node_value.line = 0;
	buff->node_value.column = 0;
	current_node->branches.push_back(buff);
	current_node = buff;
}

void My_Tree::add_node_lexer_value(Lexer::token smth) {
	node_type* buff = new node_type;
	buff->parent = this->current_node;
	buff->node_value = smth;
	current_node->branches.push_back(buff);
	current_node = buff;
}

void My_Tree::next_node(int numb) {
	current_node = current_node->branches[numb - 1];
}


void My_Tree::go_back() {
	current_node = current_node->parent;
}

void My_Tree::print_all(fstream& file) {
	if (main_parent != nullptr)
		print(main_parent, "-", file);
}

void My_Tree::print(node_type* node, string lines, fstream& file)
{
	if(node->node_value.number != 0){
	cout << lines << node->node_value.name << "                         code = "  << node->node_value.number << endl;
	file << lines << node->node_value.name << "                         code = " << node->node_value.number << endl;
	}
	else {
	cout << lines << node->node_value.name << endl;
	file << lines << node->node_value.name << endl;
	}
	if (node->branches.empty())
		return;
	for (auto& buff : node->branches)
	{
		print(buff, lines + "--", file);
	}
}