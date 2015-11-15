/*
	nicole cranon <nicole.cranon@ucdenver.edu>
	csci 4640, fall 2015
	assignment 6 - predicate generator
 */

#include "predictGenerator.h"
#include "grammeranalyzer.h"
#include <iostream>
#include <algorithm>

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
	auto tmpnonterminals = nonterminals;
	for (std::set<std::string>::iterator itr = tmpnonterminals.begin(); itr != tmpnonterminals.end(); ++itr) {
		auto temp = predict::normalize (*itr);
		nonterminals.insert(temp);
		nonterminals.erase(*itr);
	}
	auto tmpterminals = terminals;
	for (std::set<std::string>::iterator itr = tmpterminals.begin(); itr != tmpterminals.end(); ++itr) {
		auto temp = predict::normalize (*itr);
		terminals.insert(temp);
		terminals.erase(*itr);
	}
	auto tmpsymbols = symbols;
	for (std::set<std::string>::iterator itr = tmpsymbols.begin(); itr != tmpsymbols.end(); ++itr) {
		auto temp = predict::normalize (*itr);
		symbols.insert(temp);
		symbols.erase(*itr);
	}


	auto RHSStringList = predict::getRHS_stringList (RHSList);

	predict::markLambda (LHSList, RHSStringList);

	for (auto d : predict::derivesLambda) {
		// std::cout << "\nDerives Lambda-> " << std::boolalpha <<  d.first << ' ' << d.second << " <-\n";
	}

	predict::fillFirstSet (nonterminals, terminals, LHSList, RHSList, RHSStringList);

	for (auto f : predict::firstSet) {
		std::cout << f.first << " = {" ;
		for (auto k : f.second) {
			std::cout << k << ' ';
		}
		std::cout << "}\n";
	}
}
