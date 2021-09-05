#include"Lexer.h"

Lexer::Lexer(Sorted_tables* tables) {
	this->tables = tables;
}

Lexer::~Lexer() {

}



vector<Lexer::token> Lexer::lexer_work(string file1) {

	fstream file;
	int line = 1, word_column, column = 1;
	string word;
	char buff, previous;
	token tokens_st = {};

	file.open(file1);
	if (!file.is_open()) {
		cout << "File hasn't found" << endl;
		vector<Lexer::token> nothing;
		return nothing;
	}
	buff = file.get();

	while (!file.eof()) {


		if (tables->get_ascii(buff) == 0) {
			if (buff == 9) {
				column += 4;
			}
			if (buff == 32) {
				column++;
			}

			if (buff == 10 || buff == 13) {
				line++;
				column = 1;
			}
			buff = file.get();
		}

		if (tables->get_ascii(buff) == 1) {

			word_column = column;

			while (tables->get_ascii(buff) == 1) {
				word += buff;
				buff = file.get();
				column++;
			}

			if (tables->get_ascii(buff) == 2) {
				cout << "Error cause letter after number" << endl;
				cout << "Error in this line = " << line << " and this column = " << column << endl;
				cout << endl;
				break;
			}

			tables->push_const(word);
			tokens_st = { word, tables->find_const(word), line, word_column };
			tokens.push_back(tokens_st);
			word.clear();

		}

		if (tables->get_ascii(buff) == 2) {
			word_column = column;

			while (tables->get_ascii(buff) == 2 || tables->get_ascii(buff) == 1) {
				word += buff;
				buff = file.get();
				column++;
			}

			if (tables->find_keyword(word) == 0) {
				tables->push_iden(word);
				tokens_st = { word, tables->find_iden(word), line, word_column };
				tokens.push_back(tokens_st);
				word.clear();
			}
			else {
				tokens_st = { word, tables->find_keyword(word), line, word_column };
				tokens.push_back(tokens_st);
				word.clear();
			}
		}

		if (tables->get_ascii(buff) == 3 && buff != '$') {
			if (buff == '(') {
				word_column = column;
				word += buff;
				previous = buff;
				buff = file.get();
				column++;
				if (buff == '*') {

					buff = file.get();
					if (buff == 10 || buff == 13) {
						line++;
						column = 1;
					}
					else
					{
						column++;
					}
					previous = buff;
					buff = file.get();
					column++;



					while (!(previous == '*' && buff == ')'))
					{

						if (tables->get_ascii(buff) == 0) {
							if (buff == 9) {
								column += 4;
							}
							if (buff == 32) {
								column++;
							}

							if (buff == 10 || buff == 13) {
								line++;
								column = 1;
							}
							previous = buff;
							buff = file.get();
						}
						else {
							previous = buff;
							buff = file.get();
							column++;
						}

						if (file.eof()) {
							cout << "Comment hasn't closed" << endl;
							cout << "Error in this line = " << line << " and this column = " << word_column << endl;
							cout << endl;
							break;
						}
					}
					buff = file.get();
					column++;

				}
				else {
					tokens_st = { word, previous, line, word_column };
					tokens.push_back(tokens_st);
				}
				word.clear();
			}
			else {
				word += buff;
				tokens_st = { word, buff, line, column };
				tokens.push_back(tokens_st);
				buff = file.get();
				column++;
			}
			word.clear();

		}

		if (tables->get_ascii(buff) == 3 && buff == '$') {
			word_column = column;
			word += buff;
			buff = file.get();
			column++;
			if (tables->get_ascii(buff) == 2) {

				while (tables->get_ascii(buff) == 2 || tables->get_ascii(buff) == 1) {
					word += buff;
					buff = file.get();
					column++;
				}
				if (tables->find_keyword(word) == 405) {
					tokens_st = { word, tables->find_keyword(word), line, word_column };
					tokens.push_back(tokens_st);
					word.clear();
				}
				else {

					cout << "Error with $EXP" << endl;
					cout << "Error in this line = " << line << " and this column = " << word_column << endl;
					cout << endl;
					break;
				}

			}
			else {

				cout << "Error with $EXP" << endl;
				cout << "Error in this line = " << line << " and this column = " << word_column << endl;
				cout << endl;
				break;
			}

		}



		/*if (buff == '#') {
			word_column = column;
			word += buff;
			buff = file.get();

			while (tables->get_ascii(buff) == 1) {
				word += buff;
				buff = file.get();
				column++;
			}

			if (tables->get_ascii(buff) != 1 && buff != '-') {
				column++;
				cout << "Error, number have to be here" << endl;
				cout << "Error in this line = " << line << " and this column = " << column << endl;
				cout << endl;
				break;
			}

			if (buff == '-') {
				word += buff;
				buff = file.get();
				column++;

				if (tables->get_ascii(buff) == 2) {
					word += buff;
					buff = file.get();
					while (tables->get_ascii(buff) == 2) {
						word += buff;
						buff = file.get();
						column++;
					}
					tables->push_sharp(word);
					tokens_st = { word, tables->find_sharp(word), line, word_column };
					tokens.push_back(tokens_st);
					word.clear();

				}
				else {
					column++;
					cout << "Error, letter have to be here" << endl;
					cout << "Error in this line = " << line << " and this column = " << column << endl;
					cout << endl;
					break;
				}

			}
			else {
				cout << "Error, minus have to be here" << endl;
				cout << "Error in this line = " << line << " and this column = " << column << endl;
				cout << endl;
				break;

			}



		}*/

		if (tables->get_ascii(buff) == 6) {
			cout << "Uncorrect type of symbol" << endl;
			cout << "Error in this line = " << line << " and this column = " << column << endl;
			break;
		}
	}

	file.close();
	return tokens;
}

void Lexer::print(fstream& file) {
	cout << setw(10) << "Line" << " " << setw(10) << "Column" << " " << setw(10) << "Number" << " " << setw(10) << "Name" << " " << endl;
	file << setw(10) << "Line" << " " << setw(10) << "Column" << " " << setw(10) << "Number" << " " << setw(10) << "Name" << " " << endl;
	for (int i = 0; i < tokens.size(); i++) {
		cout << setw(10) << tokens.at(i).line << " " << setw(10) << tokens.at(i).column << " " << setw(10) << tokens.at(i).number << " " << setw(10) << tokens.at(i).name << " " << endl;
		file << setw(10) << tokens.at(i).line << " " << setw(10) << tokens.at(i).column << " " << setw(10) << tokens.at(i).number << " " << setw(10) << tokens.at(i).name << " " << endl;
	}
	cout << endl;
	file << endl;
	tokens.clear();
}

void Lexer::print_const_table(fstream& file) {
	tables->print_const(file);
}

void Lexer::print_iden_table(fstream& file){
	tables->print_iden(file);
}