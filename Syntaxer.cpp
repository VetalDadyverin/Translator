#include "Syntaxer.h"

Syntaxer::Syntaxer() {
	cur_lexem = 0;
	no_mistake = true;
	iter = 0;
}

int Syntaxer::current_lexem_code() {
	cur_lexem++;
	return lexems[cur_lexem - 1].number;
}

string Syntaxer::current_lexem_line() {
	return to_string(lexems[cur_lexem - 1].line);
}

string Syntaxer::current_lexem_column() {
	return to_string(lexems[cur_lexem - 1].column);
}

string Syntaxer::current_lexem_name() {
	return lexems[cur_lexem - 1].name;
}

My_Tree Syntaxer::syntaxer_work(string test_name, string output_file) {
	std::ofstream ofs;
	ofs.open(output_file, std::ofstream::out | std::ofstream::trunc);
	ofs.close();
	fstream file;
	file.open(output_file);
	file.clear();
	Sorted_tables* tables = new Sorted_tables();
	Lexer lex(tables);
	lexems = lex.lexer_work(test_name);
	cout << " Lexems_table" << endl;
	file << " Lexems_table" << endl;
	lex.print(file);
	cout << " Const_table" << endl;
	file << " Const_table" << endl;
	lex.print_const_table(file);
	cout << " Iden_table" << endl;
	file << " Iden_table" << endl;
	lex.print_iden_table(file);

	if (program()) {
		cout << "|-------------------------------|" << endl;
		cout << "|Program has no syntax mistackes|" << endl;
		cout << "|-------------------------------|" << endl;
		file << "|-------------------------------|" << endl;
		file << "|Program has no syntax mistackes|" << endl;
		file << "|-------------------------------|" << endl;
		my_tree.print_all(file);
	}
	else
	{	
		no_mistake = false;
		cout << mistackes[0] << endl;
		file << mistackes[0] << endl;
		my_tree.print_all(file);

	
	}
	file.close();
	return my_tree;
}

bool Syntaxer::program() {
	my_tree.add_node_simple_value("<program>");
	if ((cur_lexem == lexems.size())) {
		mistacke = "Error : There is PROGRAM ";
		mistackes.push_back(mistacke);
		mistacke.clear();
		return false;
	}
	if (lexems[cur_lexem].number == 401) {
		cur_lexem++;
		my_tree.add_node_lexer_value(lexems[cur_lexem - 1]);
		my_tree.go_back();
		if (!procedure_identifier()) {
			return false;
		}
		if ((cur_lexem == lexems.size())) {
			mistacke = "Error : There is no Semicolon";
			mistackes.push_back(mistacke);
			mistacke.clear();
			return false;
		}

		if (!(lexems[cur_lexem].number == 59)) {
			mistacke = "Error : There is lexem with name = '" + current_lexem_name() + "', in line =  " + current_lexem_line() + " and column = " + current_lexem_column() + " instead of ';'";
			mistackes.push_back(mistacke);
			mistacke.clear();
			return false;
		}
		cur_lexem++;
		my_tree.add_node_lexer_value(lexems[cur_lexem - 1]);
		my_tree.go_back();
		
		if (!block()) {
			return false;
		}

		if ((cur_lexem == lexems.size())) {
			mistacke = "Error : There is no dot ";
			mistackes.push_back(mistacke);
			mistacke.clear();
			return false;
		}

		if (!(lexems[cur_lexem].number == 46)) {
			mistacke = "Error : There is lexem with name = '" + current_lexem_name() + "', in line =  " + current_lexem_line() + " and column = " + current_lexem_column() + " instead of '.'";
			mistackes.push_back(mistacke);
			mistacke.clear();
			return false;
		}
		cur_lexem++;
		my_tree.add_node_lexer_value(lexems[cur_lexem - 1]);
		my_tree.go_back();
	}
	else {
		mistacke = "Error : There is lexem with name = '" + current_lexem_name() + "', in line =  " + current_lexem_line() + " and column = " + current_lexem_column() + " instead of PROGRAM";
		mistackes.push_back(mistacke);
		mistacke.clear();
		return false;
	}
	return true;
}

bool Syntaxer::procedure_identifier() {

	if (!(current_lexem_code() > 1000)) {
		mistacke = "Error : There is lexem with name = '" + current_lexem_name() + "', in line =  " + current_lexem_line() + " and column = " + current_lexem_column() + " instead of identificatore type of lexer";
		mistackes.push_back(mistacke);
		mistacke.clear();
		return false;
		}
	my_tree.add_node_simple_value("<procedure-identifier>");
	my_tree.add_node_simple_value("<identifier>");
	my_tree.add_node_lexer_value(lexems[cur_lexem - 1]);
	my_tree.go_back();
	my_tree.go_back();
	my_tree.go_back();
	return true;
}

bool Syntaxer::block() {

	my_tree.add_node_simple_value("<block>");
	if (!declarations()) {
		return false;
	}
	if ((cur_lexem == lexems.size())) {
		mistacke = "Error : There is no Begin " ;
		mistackes.push_back(mistacke);
		mistacke.clear();
		return false;
	}
	if (!(lexems[cur_lexem].number == 402)) {
		mistacke = "Error : There is lexem with name = '" + current_lexem_name() + "', in line =  " + current_lexem_line() + " and column = " + current_lexem_column() + " instead of BEGIN";
		mistackes.push_back(mistacke);
		mistacke.clear();
		return false;
	}
	cur_lexem++;
	
	my_tree.add_node_lexer_value(lexems[cur_lexem - 1]);
	my_tree.go_back();

	if (!statemets_list()) {
		return false;
	}

	if ((cur_lexem == lexems.size())) {
		mistacke = "Error : There is no END ";
		mistackes.push_back(mistacke);
		mistacke.clear();
		return false;
	}

	if (!(lexems[cur_lexem].number == 403)) {
		mistacke = "Error : There is lexem with name = '" + current_lexem_name() + "', in line =  " + current_lexem_line() + " and column = " + current_lexem_column() + " instead of END";
		mistackes.push_back(mistacke);
		mistacke.clear();
		return false;
	}
	cur_lexem++;
	my_tree.add_node_lexer_value(lexems[cur_lexem - 1]);
	my_tree.go_back();
	my_tree.go_back();

	return true;
}




bool Syntaxer::declarations() {
	my_tree.add_node_simple_value("<declarations>");
	my_tree.add_node_simple_value("<const-declarations>");
	if (!(lexems[cur_lexem].number == 404)) {
		my_tree.add_node_simple_value("<empty>");
		my_tree.go_back();
	}
	else {
		cur_lexem++;
		my_tree.add_node_lexer_value(lexems[cur_lexem - 1]);
		my_tree.go_back();
		if (!constant_declarations_list()) {
			return false;
		}
	}
		
	my_tree.go_back();
	my_tree.go_back();
	return true;
}



bool Syntaxer::statemets_list() {
	my_tree.add_node_simple_value("<statements-list>");
	my_tree.add_node_simple_value("<empty>");
	my_tree.go_back();
	my_tree.go_back();
		return true;
	
}



bool Syntaxer::constant_declarations_list() {
	
			my_tree.add_node_simple_value("<constant-declaration-list>");
			if (constant_declaration()) {
				constant_declarations_list();
				my_tree.go_back();
			}
			else {
				
				my_tree.add_node_simple_value("<empty>");
				my_tree.go_back();
				my_tree.go_back();
			}


	return true;
}

bool Syntaxer::constant_declaration() {
	
	if (constant_identifier()) {
		if (!(lexems[cur_lexem].number == 61)) {
			mistacke = "Error : There is lexem with name = '" + current_lexem_name() + "', in line =  " + current_lexem_line() + " and column = " + current_lexem_column() + " instead of '='";
			mistackes.push_back(mistacke);
			mistacke.clear();
			return false;
		}
		cur_lexem++;
		my_tree.add_node_lexer_value(lexems[cur_lexem - 1]);
		my_tree.go_back();

		if (!constant()) {
			return false;
		}

		if (!(lexems[cur_lexem].number == 59)) {
			mistacke = "Error : There is lexem with name = '" + current_lexem_name() + "', in line =  " + current_lexem_line() + " and column = " + current_lexem_column() + " instead of ';'";
			mistackes.push_back(mistacke);
			mistacke.clear();
			return false;
		}
		cur_lexem++;
		my_tree.add_node_lexer_value(lexems[cur_lexem - 1]);
		my_tree.go_back();
		my_tree.go_back();
		return true;
	}
	else {
		return false;
	}
}

bool Syntaxer::constant_identifier() {
	if (cur_lexem == lexems.size()) {
		return false;
	}
	if (!(lexems[cur_lexem].number > 1000)) {
		return false;

	}
	cur_lexem++;
	my_tree.add_node_simple_value("<constant-declaration>");
	my_tree.add_node_simple_value("<constant-identifier>");
	my_tree.add_node_simple_value("<identifier>");
	my_tree.add_node_lexer_value(lexems[cur_lexem - 1]);
	my_tree.go_back();
	my_tree.go_back();
	my_tree.go_back();
	return true;

}

bool Syntaxer::constant() {
	my_tree.add_node_simple_value("<constant>");
	if (!(lexems[cur_lexem].number == 39)) {
		mistacke = "Error : There is lexem with name = '" + current_lexem_name() + "', in line =  " + current_lexem_line() + " and column = " + current_lexem_column() + " instead of '''";
		mistackes.push_back(mistacke);
		mistacke.clear();
		return false;
	}
	cur_lexem++;
	my_tree.add_node_lexer_value(lexems[cur_lexem - 1]);
	my_tree.go_back();

	if (!complex_number()) {
		return false;
	}

	if (!(lexems[cur_lexem].number == 39)) {
		mistacke = "Error : There is lexem with name = '" + current_lexem_name() + "', in line =  " + current_lexem_line() + " and column = " + current_lexem_column() + " instead of '''";
		mistackes.push_back(mistacke);
		mistacke.clear();
		return false;
	}
	cur_lexem++;
	my_tree.add_node_lexer_value(lexems[cur_lexem - 1]);
	my_tree.go_back();

	my_tree.go_back();
	return true;

}

bool Syntaxer::complex_number() {
	my_tree.add_node_simple_value("<complex-number>");
	if (!left_part()) {
		return false;
	}

	if (lexems[cur_lexem].number == 44) {
		cur_lexem++;
		my_tree.add_node_simple_value("<right-part>");
		my_tree.add_node_lexer_value(lexems[cur_lexem - 1]);
		my_tree.go_back();
		if (!right_part_coma()) {
			return false;
		}
		my_tree.go_back();
		
	}
	else {
		if (!(lexems[cur_lexem].number == 405)) {
			if (!(lexems[cur_lexem].number == 39)) {
				mistacke = "Error : There is lexem with name = '" + current_lexem_name() + "', in line =  " + current_lexem_line() + " and column = " + current_lexem_column() + " instead of ',' or '$EXP'";
				mistackes.push_back(mistacke);
				mistacke.clear();
				return false;
			}
			else {
				my_tree.add_node_simple_value("<right-part>");
				my_tree.add_node_simple_value("<empty>");
				my_tree.go_back();
				my_tree.go_back();
				
				
			}
		}
		else
		{
			cur_lexem++;
			my_tree.add_node_simple_value("<right-part>");
			my_tree.add_node_lexer_value(lexems[cur_lexem - 1]);
			my_tree.go_back();
			if (!right_part_dollar()) {
				return false;
			}
			my_tree.go_back();

		}
	}

	my_tree.go_back();
	return true;
}

bool Syntaxer::left_part() {
	if (!((lexems[cur_lexem].number < 1001) && (lexems[cur_lexem].number > 500))) {
		cur_lexem++;
		if (!(lexems[cur_lexem - 1].number == 44) && !(lexems[cur_lexem - 1].number == 405) && !(lexems[cur_lexem - 1].number == 39)) {
			mistacke = "Error : There is lexem with name = '" + current_lexem_name() + "', in line =  " + current_lexem_line() + " and column = " + current_lexem_column() + " instead of usigned-integer1";
			mistackes.push_back(mistacke);
			mistacke.clear();
			cur_lexem--;
			return false;
		}
		else {
			my_tree.add_node_simple_value("<left-part>");
			my_tree.add_node_simple_value("<empty>");
			my_tree.go_back();
			my_tree.go_back();
			cur_lexem--;
		}
	}
	else {
		cur_lexem++;
		my_tree.add_node_simple_value("<left-part>");
		my_tree.add_node_simple_value("<unsighned-integer>");
		my_tree.add_node_lexer_value(lexems[cur_lexem - 1]);
		my_tree.go_back();
		my_tree.go_back();
		my_tree.go_back();
	}
	return true;
	
}

bool Syntaxer::right_part_coma() {
	if (!((lexems[cur_lexem].number < 1001) && (lexems[cur_lexem].number > 500))) {
		cur_lexem++;
		if (lexems[cur_lexem - 1].name == ",") {
			cur_lexem++;
			mistacke = "Error : There is lexem with name = '" + current_lexem_name() + "', in line =  " + current_lexem_line() + " and column = " + current_lexem_column() + " instead of usigned-integer2";
		}
		else {
			mistacke = "Error : There is lexem with name = '" + current_lexem_name() + "', in line =  " + current_lexem_line() + " and column = " + current_lexem_column() + " instead of usigned-integer2";

		}
		mistackes.push_back(mistacke);
		mistacke.clear();
		return false;
	}
	cur_lexem++;
	my_tree.add_node_simple_value("<unsighned-integer>");
	my_tree.add_node_lexer_value(lexems[cur_lexem - 1]);
	my_tree.go_back();
	my_tree.go_back();
	return true;
}

bool Syntaxer::right_part_dollar() {
	if (!(lexems[cur_lexem].number == 40)) {
		mistacke = "Error : There is lexem with name = '" + current_lexem_name() + "', in line =  " + current_lexem_line() + " and column = " + current_lexem_column() + " instead of '('";
		mistackes.push_back(mistacke);
		mistacke.clear();
		return false;
	}
	cur_lexem++;
	my_tree.add_node_lexer_value(lexems[cur_lexem - 1]);
	my_tree.go_back();

	if (!((lexems[cur_lexem].number < 1001) && (lexems[cur_lexem].number > 500))) {
		cur_lexem++;
		if(lexems[cur_lexem - 1].name == "("){
			cur_lexem++;
			mistacke = "Error : There is lexem with name = '" + current_lexem_name() + "', in line =  " + current_lexem_line() + " and column = " + current_lexem_column() + " instead of usigned-integer3";
		}
		else {
			mistacke = "Error : There is lexem with name = '" + current_lexem_name() + "', in line =  " + current_lexem_line() + " and column = " + current_lexem_column() + " instead of usigned-integer3";

		}
		mistackes.push_back(mistacke);
		mistacke.clear();
		return false;
	}
	cur_lexem++;
	my_tree.add_node_simple_value("<unsighned-integer>");
	my_tree.add_node_lexer_value(lexems[cur_lexem - 1]);
	my_tree.go_back();
	my_tree.go_back();

	if (!(current_lexem_code() == 41)) {
		mistacke = "Error : There is lexem with name = '" + current_lexem_name() + "', in line =  " + current_lexem_line() + " and column = " + current_lexem_column() + " instead of ')'";
		mistackes.push_back(mistacke);
		mistacke.clear();
		return false;
	}
	my_tree.add_node_lexer_value(lexems[cur_lexem - 1]);
	my_tree.go_back();
	return true;
}