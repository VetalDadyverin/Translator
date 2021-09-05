#include"Lexer.h"
#include"Syntaxer.h"
#include"Generate_asm.h"

int main() {

	while (true) {
		int number;
		cout << "Choose wich test will be showed" << endl;
		cout << "1 - test01" << endl;
		cout << "2 - test02" << endl;
		cout << "3 - test03" << endl;
		cout << "4 - test04" << endl;
		cout << "5 - test05" << endl;
		cout << "6 - test06" << endl;
		cout << "7 - exit" << endl;
		cin >> number;

		if (number == 1) {
			Syntaxer synx;
			My_Tree tree = synx.syntaxer_work("./tests/test01/input.sig", "./tests/test01/expected.txt");
			Generate_asm gen(tree, synx.get_mistake());
			gen.generate_work("./tests/test01/expected.txt");

		}
		else if (number == 2) {
			Syntaxer synx1;
			My_Tree tree = synx1.syntaxer_work("./tests/test02/input.sig", "./tests/test02/expected.txt");
			Generate_asm gen1(tree, synx1.get_mistake());
			gen1.generate_work("./tests/test02/expected.txt");
		}
		else if (number == 3) {
			Syntaxer synx2;
			My_Tree tree = synx2.syntaxer_work("./tests/test03/input.sig", "./tests/test03/expected.txt");
			Generate_asm gen2(tree, synx2.get_mistake());
			gen2.generate_work("./tests/test03/expected.txt");
		}
		else if (number == 4) {
			Syntaxer synx3;
			My_Tree tree = synx3.syntaxer_work("./tests/test04/input.sig", "./tests/test04/expected.txt");
			Generate_asm gen3(tree, synx3.get_mistake());
			gen3.generate_work("./tests/test04/expected.txt");
		}
		else if (number == 5) {
			Syntaxer synx4;
			My_Tree tree = synx4.syntaxer_work("./tests/test05/input.sig", "./tests/test05/expected.txt");
			Generate_asm gen4(tree, synx4.get_mistake());
			gen4.generate_work("./tests/test05/expected.txt");
		}
		else if (number == 6) {
			Syntaxer synx5;
			My_Tree tree = synx5.syntaxer_work("./tests/test06/input.sig", "./tests/test06/expected.txt");
			Generate_asm gen5(tree, synx5.get_mistake());
			gen5.generate_work("./tests/test06/expected.txt");
		}
		else if (number == 7) {
			return 0;
		}
		else {
			cout << "Unput number is invalid" << endl;
		}

		cout << endl;
	}
	return 0;
	system("pause");
}