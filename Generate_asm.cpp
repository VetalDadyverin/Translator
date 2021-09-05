#include "Generate_asm.h"
#include <sstream>
#include <math.h>

Generate_asm::Generate_asm(My_Tree input, bool inpt) {
	my_tree = input;
	no_mistake = inpt;
	name_second_time = true;
}


void Generate_asm::generate_work(string output_file) {
	std::ofstream outfile;
	outfile.open(output_file, std::ios_base::app); // append instead of overwrite
	asm_code.clear();
	my_tree.set_start();
	program();
	cout << asm_code;
	outfile << asm_code;
}

void Generate_asm::program() {
	
	if (no_mistake) {
		if (my_tree.get_current_node()->node_value.name == "<program>") {
			procedure_identifier();
			block();
		}
	}
	else {
		cout << "Syntaxer gave error and because of that generator isn't working" << endl;
		asm_code = "\nSyntaxer gave error and because of that generator isn't working";
	}
}

void Generate_asm::procedure_identifier() {
	my_tree.next_node(2);
	if (my_tree.get_current_node()->node_value.name == "<procedure-identifier>") {
		my_tree.next_node(1);
		my_tree.next_node(1);
		prog_name = my_tree.get_current_node()->node_value.name;
		my_tree.go_back();
		my_tree.go_back();
	}
	my_tree.go_back();
}

void Generate_asm::block() {
	my_tree.next_node(4);
	if (my_tree.get_current_node()->node_value.name == "<block>") {
		declarations();
		if (!name_second_time) {
			return;
		}
		statement_list();
	}
	my_tree.go_back();
}

void Generate_asm::declarations() {
	asm_code.append("\nDATA SEGMENT\n");
	my_tree.next_node(1);
	if (my_tree.get_current_node()->node_value.name == "<declarations>") {
		constant_declarations();
	}
	if (!name_second_time) {
		return;
	}
	asm_code.append("DATA ENDS\n");
	my_tree.go_back();
}

void Generate_asm::statement_list() {
	asm_code.append("CODE SEGMENT\n  ASSUME CS:CODE, DS:DATA\n");
	asm_code.append("  " + prog_name + ":\n");
	asm_code.append("  MOV AH, 4Ch\n  INT 21h\nCODE ENDS\nEND " + prog_name + "\n");

}

void Generate_asm::constant_declarations() {
	my_tree.next_node(1);
	if (my_tree.return_amount_of_branches() > 1) {
		my_tree.next_node(2);
		my_tree.next_node(1);
		if (!(my_tree.get_current_node()->node_value.name == "<empty>")){
			my_tree.go_back();
			my_tree.go_back();
			while (true) {
				iter++;
				my_tree.next_node(2);
				my_tree.next_node(1);
				if (my_tree.get_current_node()->node_value.name == "<empty>") {
					my_tree.go_back();
					break;
				}
				else {
					constant_identifier();
					if (!name_second_time) {
						return;
					}
					constant();
				}
				my_tree.go_back();
			}
			for (int i = 0; i < iter; i++) {
				my_tree.go_back();
			}
		}
	}
	
	my_tree.go_back();
}

void Generate_asm::constant_identifier() {
	my_tree.next_node(1);
	my_tree.next_node(1);
	my_tree.next_node(1);
	if (names.size() != 0) {
		for (int i = 0; i < names.size() ; i++) {
			if (my_tree.get_current_node()->node_value.name == names[i]) {
				name_second_time = false;
				asm_code.append("\n  Error: second time lexem with the name " + my_tree.get_current_node()->node_value.name + ", in line = " + to_string(my_tree.get_current_node()->node_value.line) + " and column = " + to_string(my_tree.get_current_node()->node_value.column) + "\n ");
			}
		}
		if (!name_second_time) {
			return;
		}

	}

	names.push_back(my_tree.get_current_node()->node_value.name);
	asm_code.append("  " + my_tree.get_current_node()->node_value.name + " DD ");
	my_tree.go_back();
	my_tree.go_back();
	my_tree.go_back();
	
}

void Generate_asm::constant() {
	my_tree.next_node(3);
	my_tree.next_node(2);
	left_part();
	right_part();
	my_tree.go_back();
	my_tree.go_back();

}


void Generate_asm::left_part() {
	my_tree.next_node(1);
	my_tree.next_node(1);
	if (my_tree.return_amount_of_branches() == 0) {
		//asm_code.append(hex_convert("0"));
		buff_left = 0;
	}
	else {
		my_tree.next_node(1);
		//asm_code.append(hex_convert(my_tree.get_current_node()->node_value.name));
		buff_left = stoi(my_tree.get_current_node()->node_value.name);
		my_tree.go_back();
	}
	my_tree.go_back();
	my_tree.go_back();

}

void Generate_asm::right_part() {
	my_tree.next_node(2);
	my_tree.next_node(1);
	if (my_tree.get_current_node()->node_value.number == 44) {
		my_tree.go_back();
		my_tree.next_node(2);
		my_tree.next_node(1);
		if (buff_left == 0) {
			Re = 0;
			Im = 0;
		}
		else {
			Re = buff_left * cos(stof(my_tree.get_current_node()->node_value.name));
			Im = buff_left * sin(stof(my_tree.get_current_node()->node_value.name));
		}
		asm_code.append(to_string(Re) + ", " + to_string(Im) + "\n");
		//asm_code.append(hex_convert(my_tree.get_current_node()->node_value.name) + "h\n");
		my_tree.go_back();
		my_tree.go_back();
	}
	else {
		if (my_tree.get_current_node()->node_value.number == 405) {
			my_tree.go_back();
			my_tree.next_node(3);
			my_tree.next_node(1);
			if (buff_left == 0) {
				Re = 0;
				Im = 0;
			}
			else {
				Re = buff_left * cos(exp(stof(my_tree.get_current_node()->node_value.name)));
				Im = buff_left * sin(exp(stof(my_tree.get_current_node()->node_value.name)));
			}
			asm_code.append(to_string(Re) + ", " + to_string(Im) + "\n");
			//asm_code.append(hex_convert(exponent(my_tree.get_current_node()->node_value.name)) + "h\n");
			my_tree.go_back();
			my_tree.go_back();
		}
		else {
			my_tree.go_back();
			if (buff_left == 0) {
				Re = 0;
				Im = 0;
			}
			else {
				Re = buff_left * cos(0);
				Im = buff_left * sin(0);
			}
			asm_code.append(to_string(Re) + ", " + to_string(Im) + "\n");
		}
	}
	my_tree.go_back();
	
}
