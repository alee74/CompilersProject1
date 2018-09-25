/* * * * * * * * * * * * * * * * * * * * * * * * *
 *                              				 *
 * main.cpp										 *
 *												 *
 * main for Scanner and Parser implementations.	 *
 * expects file as command line argument.		 *
 * uses file to construct Parser, which in turn	 *
 * constructs Scanner, and parses file.			 *
 * accepts one additional command line argument. *
 * run with [-h --help] option for additional 	 *
 * info.										 *
 * 												 *
 * Written by: Austin James Lee					 *
 *                              				 *
 * * * * * * * * * * * * * * * * * * * * * * * * */

#define MAX_ARGS 3

#include "parser.h"
#include <cstring>	// strcmp()

using std::strcmp;

bool validFile(string filename);
void printIR(Parser& p);


/// main ///
int main(int argc, char* argv[]) {
	string infile = "";
	bool printTokens = false;	// -t
	bool printILOC = false;		// -p
	string usage = "usage: reader [-t] [-p] [-h --help] filename";
	string help = "\n"
		"\'reader\' is a naive implementation of the front end of a compiler\n"
		"for ILOC code. It takes a file as input and scans and parses its\n"
		"contents, generating an intermediate representation (IR).\n\n"
		+ usage + "\n\n"
		"Argument options:\n"
		"-t  prints a list of the tokens scanned, each on its own line.\n"
		"    tokens are of the form <TOKEN_TYPE, lexeme>\n"
		"-p  prints the legal ILOC code that can be constructed from IR.\n"
		"-h  prints this help summary and exits the simulation.\n"
		"    --help is the verbose form of this option.\n\n"
		"Only one option is permitted. If no option is specified, the\n"
		"intermediate representation will be printed in tabular form.\n";
		

	// ensure correct number of arguments
	if (argc < 2) {
		cerr << "error: no arguments"
			<< endl << usage << endl;
		return 1;
	} else if (argc > MAX_ARGS) {
		cerr << "error: too many arguments"
			<< endl << usage << endl;
		return 1;
	// parse arguments
	} else {
		// parse -h & --help
		if (strcmp(argv[1], "-h") == 0 ||
			strcmp(argv[1], "--help") == 0) {
				cout << help << endl;
				return 0;
		// parse -t
		} else if (strcmp(argv[1], "-t") == 0)
			printTokens = true;
		// parse -p
		else if (strcmp(argv[1], "-p") == 0)
			printILOC = true;
		// parse filename for argc == 2
		else if (validFile(argv[1]))
			infile = argv[1];
		// bad filename
		else if (argc == 2) {
			cerr << "error: invalid filename: " 
				<< argv[1] << endl << usage << endl;
			return 1;
		// bad argument
		} else {
			cerr << "error: invalid argument: "
				<< argv[1] << endl << usage << endl;
			return 1;
		}
		// parse filename for argc == 3
		if (argc == 3) {
			if (infile == "") {
				if (validFile(argv[2]))
					infile = argv[2];
				// bad filename
				else {
					cerr << "error: invalid filename: " 
						<< argv[2] << endl << usage << endl;
					return 1;
				}
			// excess arguments
			} else {
				cerr << "error: invalid arguments following filename"
					<< endl << usage << endl;
				return 1;
			}
		}
	}


	// create Parser
	// (automatically parses due to parse call in constructor)
	Parser parser(infile, printTokens, printILOC);

	if (!printTokens && !printILOC)
		printIR(parser);


	return 0;
}


// tests for valid file
bool validFile(string filename) {
	bool valid = false;
	ifstream f(filename);
	if (f) {
		valid = true;
		f.close();
	}
	return valid;
}


// print intermediate representation as a table
void printIR(Parser& p) {
	// print column headers
	cout << "|index| opcode\t|| op1\t| op2 |dest|" << endl
		 << "|     | \t||  sr\t|  sr | sr |" << endl;
	// print rest of IR as table
	int i = 0;
	list<Instruction>::iterator it = p.intRep.begin();
	while (it != p.intRep.end()) {
		// print index	-- table rows will become skewed
		//					for >100,000 lines
		cout << "|" << i;
		if (i < 10)
			cout << "    | ";
		else if (i < 100)
			cout << "   | ";
		else if (i < 1000)
			cout << "  | ";
		else if (i < 10000)
			cout << " | ";
		else if (i < 100000)
			cout << "| ";
		// print rest of line
		switch (it->op) {

			case load:
				cout << "load\t|| r" << it->src1
					<< "\t|  -  | r" << it->dest;
				// ensure even spacing of dest column
				if (it->dest < 10)
					cout << " ";
				cout << "|";
				break;

			case loadI:
				cout << "loadI\t|| " << it->src1
					<< "\t|  -  | r" << it->dest;
				// ensure even spacing of dest column
				if (it->dest < 10)
					cout << " ";
				cout << "|";
				break;

			case store:
				cout << "store\t|| r" << it->src1
					<< "\t| r" << it->src2;
				// ensure even spacing of op2 column
				if (it->src2 < 10)
					cout << " ";
				cout << " | -  |";
				break;

			case output:
				cout << "output\t|| " << it->src1
					<< "\t|  -  | -  |";
				break;

			case nop:
				cout << "nop\t|| -\t| -  | -  |";
				break;

			// arithmetic instructions
			default:
				// print opcode
				switch (it->op) {
					case add:
						cout << "add";
						break;
					case sub:
						cout << "sub";
						break;
					case mult:
						cout << "mult";
						break;
					case lshift:
						cout << "lshift";
						break;
					case rshift:
						cout << "rshift";
						break;
					default:
						cout << "oh shat";
						break;
				}
				// print rest of instruction
				cout << "\t|| r" << it->src1
					<< "\t| r" << it->src2;
				// ensure even spacing of op2 column
				if (it->src2 < 10)
					cout << " ";
				cout << " | r" << it->dest;
				// ensure even spacing of dest column
				if (it->dest < 10)
					cout << " ";
				cout << "|";
				break;
		}
		cout << endl;
		++it;
		++i;
	}
}
