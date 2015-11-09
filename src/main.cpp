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

	for (unsigned i = 0; i < RHSList.size(); ++i) {
		RHSList[i] = predict::normalize (RHSList[i]);
		//std::cout << "\nRHS->" << RHSList[i] << "<-\n";
	}
	for (unsigned i = 0; i < LHSList.size(); ++i) {
		LHSList[i] = predict::normalize (LHSList[i]);
		//std::cout << "\nLHS->" << l << "<-\n";
	}

	auto RHSStringList = predict::getRHS_stringList (RHSList);

	predict::markLambda (LHSList, RHSStringList);

	for (auto d : predict::derivesLambda) {
		std::cout << "\nDerives Lambda-> " << std::boolalpha <<  d.first << ' ' << d.second << " <-\n";
	}

}
