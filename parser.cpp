/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                              						 *
 * parser.cpp											 *
 *														 *
 * Contains implementations for everything in parser.h.	 *
 * Methods appear in same order as they do in parser.h	 *
 * with the exception of Instruction's print function,	 *
 * which is at the end of the file.						 *
 * 														 *
 * Written by: Austin James Lee							 *
 *                              						 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#pragma once

#include "parser.h"



//// Instruction constructors ////


// default consturctor
Instruction::Instruction()
			:src1(INVALID), src2(INVALID), dest(INVALID) {}


// overloaded constructor
Instruction::Instruction(Opcode o)
			:op(o), src1(INVALID), src2(INVALID), dest(INVALID) {}



//// Parser methods ////


// constructor (public)
// takes file name and "scanner print" bool to construct Scanner,
// and another bool "parser print" indicating whether to print IR
Parser::Parser(string infile, bool sp, bool pp) :scanner(Scanner(infile, sp)) {
	// parse until EOF or error
	parse();
	// print?
	if (pp) {
		list<Instruction>::iterator it = intRep.begin();
		while (it != intRep.end()) {
			cout << *it;
			it++;
		}
	}
}


// main parse function (private; called from constructor)
// requests an instruction token, then builds an
// Instruction based on its Opcode and adds it to the
// end of the intermediate representation (intRep)
void Parser::parse() {
	// scan next Instruction
	Token t = scanner.scanInstruction();
	// check for EOF (only time Invalid Token is returned)
	if (t.cat == INVALID)
		return;

	Instruction i((Opcode)t.value);
	switch (i.op) {

		case load:
			i.src1 = (scanner.scanRegister()).value;
			scanner.scanArrow();
			i.dest = (scanner.scanRegister()).value;
			break;

		case loadI:
			i.src1 = (scanner.scanConstant()).value;
			scanner.scanArrow();
			i.dest = (scanner.scanRegister()).value;
			break;

		case store:
			i.src1 = (scanner.scanRegister()).value;
			scanner.scanArrow();
			i.src2 = (scanner.scanRegister()).value;
			break;

		case output:
			i.src1 = (scanner.scanConstant()).value;
			break;

		case nop:
			break;

		// arithmetic operations
		default:
			i.src1 = (scanner.scanRegister()).value;
			scanner.scanComma();
			i.src2 = (scanner.scanRegister()).value;
			scanner.scanArrow();
			i.dest = (scanner.scanRegister()).value;
			break;
	}

	// add Instruction to end of IR
	intRep.push_back(i);

	// continue parsing
	parse();
}



//// Instruction print function ////


// overloaded << operator for printing Instructions
ostream& operator<<(ostream& os, const Instruction& i) {
	switch (i.op) {

		case load:
			os << "load" << "\t" << "r" << i.src1
				<< "\t" << "=>  " << "r" << i.dest;
			break;

		case loadI:
			os << "loadI" << "\t" << i.src1 << "\t"
				<< "=>  " << "r" << i.dest;
			break;

		case store:
			os << "store" << "\t" << "r" << i.src1
				<< "\t" << "=>  " << "r" << i.src2;
			break;

		case output:
			os << "output" << "\t" << i.src1;
			break;

		case nop:
			os << "nop";
			break;

		default:
			switch (i.op) {
				case add:
					os << "add";
					break;
				case sub:
					os << "sub";
					break;
				case mult:
					os << "mult";
					break;
				case lshift:
					os << "lshift";
					break;
				case rshift:
					os << "rshift";
					break;
				default:
					os << "uh oh... somethin' done goofed.";
					break;
			}
			os << "\t" << "r" << i.src1 << ", r" << i.src2
				<< "\t" << "=>  " << "r" << i.dest;
			break;
	}

	os << endl;
	return os;
}

