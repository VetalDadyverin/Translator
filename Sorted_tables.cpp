#include"Sorted_tables.h"

Sorted_tables::Sorted_tables() {

	for (int i = 0; i < 8; i++) {
		ascii[i] = 6;
	}

	for (int i = 8; i < 11; i++) {
		ascii[i] = 0;
	}

	ascii[11] = 6;
	ascii[12] = 6;
	ascii[13] = 0;

	for (int i = 14; i < 36; i++) {
		ascii[i] = 6;
	}

	ascii[32] = 0;
	ascii[36] = 3;

	for (int i = 37; i < 39; i++) {
		ascii[i] = 6;
	}

	for (int i = 39; i < 42; i++) {
		ascii[i] = 3;
	}


	for (int i = 42; i < 45; i++) {
		ascii[i] = 6;
	}

	ascii[44] = 3;
	ascii[45] = 6;
	ascii[46] = 3;
	ascii[47] = 6;

	for (int i = 48; i < 58; i++) {
		ascii[i] = 1;
	}

	ascii[58] = 6;
	ascii[59] = 3;
	ascii[60] = 6;
	ascii[61] = 3;

	for (int i = 62; i < 65; i++) {
		ascii[i] = 6;
	}

	for (int i = 65; i < 91; i++) {
		ascii[i] = 2;
	}

	for (int i = 91; i < 97; i++) {
		ascii[i] = 6;
	}

	for (int i = 97; i < 123; i++) {
		ascii[i] = 2;
	}

	for (int i = 123; i < 127; i++) {
		ascii[i] = 6;
	}

	keywords.insert(pair<string, int>("PROGRAM", key_id));
	keywords.insert(pair<string, int>("BEGIN", ++key_id));
	keywords.insert(pair<string, int>("END", ++key_id));
	keywords.insert(pair<string, int>("CONST", ++key_id));
	keywords.insert(pair<string, int>("$EXP", ++key_id));

}


void Sorted_tables::push_const(string item) {
	if (const_items.find(item) != const_items.end()) {

	}
	else
	{
		const_items.insert(pair<string, int>(item, const_id++));
	}

}

int Sorted_tables::find_const(string item) {
	return const_items.find(item)->second;
}

void Sorted_tables::push_iden(string iden) {
	if (identificators.find(iden) != identificators.end()) {

	}
	else
	{
		identificators.insert(pair<string, int>(iden, iden_id++));
	}
}

int Sorted_tables::find_iden(string iden) {
	return identificators.find(iden)->second;
}

int Sorted_tables::get_ascii(char buff) {
	return ascii[buff];
}

int Sorted_tables::find_keyword(string key) {
	if (keywords.find(key) != keywords.end()) {
		return keywords.find(key)->second;
	}
	else
	{
		return 0;
	}
}

int Sorted_tables::find_sharp(string sharp1) {
	return sharp.find(sharp1)->second;
}

void Sorted_tables::push_sharp(string sharp1) {
	if (sharp.find(sharp1) != sharp.end()) {

	}
	else
	{
		sharp.insert(pair<string, int>(sharp1, sharp9++));
	}
}

void Sorted_tables::print_const(fstream& file) {
	cout << "|" << setw(10) << "Name" << "|" << setw(10) << "Number" << "|" << endl;
	file << "|" << setw(10) << "Name" << "|" << setw(10) << "Number" << "|" << endl;
	for (const auto& x : const_items) {
		cout << "|" << setw(10) << x.first << "|" << setw(10) << x.second << "|" << endl;
		file << "|" << setw(10) << x.first << "|" << setw(10) << x.second << "|" << endl;
	}
	cout << endl;
	file << endl;
}

void Sorted_tables::print_iden(fstream& file){
	cout << "|" << setw(10) << "Name" << "|" << setw(10) << "Number" << "|" << endl; 
	file << "|" << setw(10) << "Name" << "|" << setw(10) << "Number" << "|" << endl;
	for (const auto& x : identificators) {
		cout << "|" << setw(10) << x.first << "|" << setw(10) << x.second << "|" << endl;
		file << "|" << setw(10) << x.first << "|" << setw(10) << x.second << "|" << endl;
	}
	cout << endl; 
	file << endl;
}