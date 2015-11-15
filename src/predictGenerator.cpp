/*
	nicole cranon <nicole.cranon@ucdenver.edu>
	csci 4640, fall 2015
	assignment 6 - predict generator
 */

#include "predictGenerator.h"
#include <algorithm>
#include <iostream>

namespace predict {
	markedVocabulary derivesLambda;
	symbolMap firstSet, 
		followSet;

	symbolArr getRHS_stringList (std::vector<std::string> RHSList) {
			std::string symbol;
		unsigned split_pos = 0,
			i = 0;

		std::vector<std::vector<std::string> > RHS_stringList;
		std::vector<std::string> RHSSet;

		for(unsigned i = 0; i< RHSList.size(); ++i) {
			while (!RHSList[i].empty()) {
				split_pos = RHSList[i].find("><");

				if (split_pos != std::string::npos 
					&& split_pos+1 != RHSList[i].length()) {

					symbol = RHSList[i].substr(0, split_pos+1);
				
					RHSList[i] = RHSList[i].substr(split_pos+1);
				} else {
					symbol = RHSList[i];
					RHSList[i] = "";
				}
				RHSSet.push_back (symbol);
			}


			RHS_stringList.push_back(RHSSet);
			RHSSet.clear();
		}

			i = 0;
			for (auto x : RHS_stringList) {
				// std::cout << "\nRHS List of Symbols " << i << " ";

				for (auto v : x) {
					// std::cout << v << ',';
				}
				// std::cout <<'\n';
				++i;
			}

		return RHS_stringList;
	}

	// remove white space in string s
	std::string normalize (const std::string& s) {
		std::string temp = "";

		for (unsigned i = 0; i < s.size(); ++i) {
			if (s[i] != ' ') {
				temp += s[i];
			}
		}

		return temp;
	}

	void markLambda (const std::vector<std::string>& lhsList, 
			const std::vector<std::vector<std::string> >& RHSStringList) {
		bool changes = true,
			rhsDerivesLambda;

		for (unsigned i = 0; i < lhsList.size(); ++i) {
			derivesLambda[lhsList[i]] = false;
		}

		while (changes) {
			changes = false;

			for (unsigned i = 0; i < lhsList.size(); ++i) {
				rhsDerivesLambda = true;

				for (unsigned j = 0; j < RHSStringList[i].size(); ++j) {
					rhsDerivesLambda = rhsDerivesLambda && derivesLambda[RHSStringList[i][j]];
				}

				if (rhsDerivesLambda && !(derivesLambda[lhsList[i]])) {
					changes = true;

					derivesLambda[lhsList[i]] = true;
					// std::cout << "\nlhs-> " << lhsList[i] << " yields lamda " << derivesLambda[lhsList[i]] << '\n';
				}
			}
		}
	}

	std::set<std::string> computeFirst (const std::vector<std::string>& RHSString) {
		std::set<std::string> terminalSet;

		if (RHSString.size() == 0) {
			terminalSet.insert("");
		}
		else {
			terminalSet = firstSet[RHSString[0]];
			terminalSet.erase("");

			unsigned i = 0;
			while (i < RHSString.size() && firstSet[RHSString[0]].find("") != firstSet[RHSString[i]].cend()) {
				++i;
				terminalSet.insert (firstSet[RHSString[i]].cbegin(), firstSet[RHSString[i]].cend());
				terminalSet.erase ("");
			}

			if ((i == RHSString.size() - 1) && firstSet[RHSString[i]].find("") != firstSet[RHSString[i]].cend()) {
				terminalSet.insert ("");
			}
		}
		
		return terminalSet;
	}

	void fillFirstSet (const std::set<std::string> nonterminals, 
		const std::set<std::string> terminals,
		const std::vector<std::string> LHS,
		const std::vector<std::string> RHS,
		const std::vector<std::vector<std::string>>& RHSStringList) {

		auto ntItr = nonterminals.begin();
		auto tItr = terminals.begin();

		for (; ntItr != nonterminals.end(); ++ntItr) {
			if (derivesLambda [*ntItr]) {
				firstSet[*ntItr].insert ("");
			} else {
				firstSet[*ntItr].clear ();
			}
		}

		for (; tItr != terminals.end(); ++tItr) {
			if (tItr->compare("") != 0){
				firstSet[*tItr].insert (*tItr);
			}

			for (ntItr = nonterminals.begin(); ntItr != nonterminals.end(); ++ntItr) {
/*				if (derives(*ntItr, *tItr, LHS, RHS, RHSStringList)) {
					firstSet[*ntItr].insert (*tItr);
					// std::cout << "\nnonterminal " << *ntItr << " derives " << *tItr << '\n'; 
				}*/
				if (yields(*ntItr, *tItr, LHS, RHS)) {
					firstSet[*ntItr].insert (*tItr);
					// std::cout << "\nnonterminal " << *ntItr << " derives " << *tItr << '\n'; 
				}
			}
		}
/*
		for (auto i : firstSet) {
			std::cout << "\nfirst set of " << i.first << " " ;
			for (auto elem : i.second) {
				std::cout << elem << ", ";
			}
		}*/

		bool changes = true;
		while (changes) {
			auto prevFirstSet = firstSet;

			for (unsigned i = 0; i < LHS.size(); ++i) {
				auto rhsFirst = computeFirst (RHSStringList[i]);
				firstSet[LHS[i]].insert(rhsFirst.begin(), rhsFirst.end());
/*
				std::cout << '\n' << LHS[i] << "{" ;
				for (auto k : firstSet[LHS[i]]) {
					std::cout << k << ' ';
				}
				std::cout << "}\n";*/
/*				std::cout << '\n' << LHS[i] << " computefirst elements " ;
				for (auto r: rhsFirst) {
					std::cout << r << ' ';
				}*/
			}

			if (prevFirstSet == firstSet) {
				changes = false;
			}
		}


	}

	void fillFollowSet () {

	}

	bool derives (const std::string& nonterminal,
		const std::string& terminal,
		const std::vector<std::string> LHS,
		const std::vector<std::string> RHS,
		const std::vector<std::vector<std::string> >& RHSStringList) {
		for (unsigned i = 0; i < LHS.size(); ++i) {
			if (LHS[i].compare(nonterminal) == 0) {
				for (unsigned j = 0; j < RHSStringList[i].size(); ++j) {
					if (RHSStringList[i][j].compare(terminal) == 0) {
						return true;
					}
					if (yields (RHSStringList[i][j], terminal, LHS, RHS)) {
						return true;
					}
				}
			}
		}

		return false;
	}

	bool yields (const std::string& nonterminal,
		const std::string& terminal,
		const std::vector<std::string> LHS,
		const std::vector<std::string> RHS) {
		for (unsigned i = 0; i < LHS.size(); ++i) {
			if (LHS[i].compare(nonterminal) == 0 && RHS[i].compare (terminal) == 0) {
				return true;
			}
		}

		return false;
	}

}


// bool contains (const std::vector<std::string>& v, const std::string& target) {
// 	for (auto i : v) {
// 		if (i.compare (target) == 0) {
// 			return true;
// 		}
// 	}

// 	return false;
// }