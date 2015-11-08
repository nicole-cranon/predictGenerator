/*
	nicole cranon <nicole.cranon@ucdenver.edu>
	csci 4640, fall 2015
	assignment 6 - predicate generator
 */

#include "predictGenerator.h"
#include "grammeranalyzer.h"
#include <iostream>

int main (int argc, char *argv[]) {
	if (argc < 2) {
		std::cerr << "\nNot enough arguments provided!\n";
		return 0;
	}

	std::vector<std::string> ingrammer,
		outgrammer,
		RHSList,
		LHSList;

	std::set<std::string> nonterminals,
		terminals,
		symbols;

	ga::read_productions (argv[1], ingrammer);

	ga::analyze (ingrammer, outgrammer, nonterminals, terminals, symbols, 
			LHSList, RHSList);
	//TODO Change these for loops to traditional for loops as they are not
	//changing the values in normalize
	// normalize the grammer (remove spaces)
	for (auto og : outgrammer) {
		predict::normalize (og);
		//std::cout << "\nOutgrammer->" << og << "<-\n";
	}
	for (unsigned i = 0; i < RHSList.size(); ++i) {
		RHSList[i] = predict::normalize (RHSList[i]);
		//std::cout << "\nRHS->" << RHSList[i] << "<-\n";
	}
	for (auto l : LHSList) {
		predict::normalize (l);
		//std::cout << "\nLHS->" << l << "<-\n";
	}
	for (auto s : symbols) {
		predict::normalize (s);
		//std::cout << "\nSymbol->" << s << "<-\n";
	}
	for (auto nt : nonterminals) {
		predict::normalize (nt);
		//std::cout << "\nNormalized Nonterminal->" << nt << "<-\n";
	}
	for (auto t: terminals) {
		predict::normalize (t);
	//	std::cout << "\nNormalized Terminal->" << t << "<-\n";
	}

	std::vector<std::vector<std::string> > RHSStringList = predict::getRHS_stringList (RHSList);

	//predict::markLambda (nonterminals, derivesLambda);

//	for (auto d : derivesLambda) {
//		std::cout << "\nDerives Lambda->" << std::boolalpha <<  d << "<-\n";
//	}

}
