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
	
	std::vector<std::vector<std::string> > getRHS_stringList (
		std::vector<std::string> RHSList) {
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
	std::cout << "\nRHS List of Symbols " << i << " ";
				for (auto v : x) {
					std::cout << v << ',';
				}
				std::cout <<'\n';
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

std::cout << "\nlhs-> " << lhsList[i] << " derives lamda " << derivesLambda[lhsList[i]] << '\n';

				for (unsigned j = 0; j < RHSStringList[i].size(); ++j) {
					rhsDerivesLambda = rhsDerivesLambda && derivesLambda[RHSStringList[i][j]];
				}

				if (rhsDerivesLambda && !(derivesLambda[lhsList[i]])) {
					changes = true;

					derivesLambda[lhsList[i]] = true;
					std::cout << "\nlhs-> " << lhsList[i] << " derives lamda " << derivesLambda[lhsList[i]] << '\n';
				}
			}
		}
	}

	void computeFirst (const std::string& RHS,
			std::set<std::string>& terminalSet) {

	}

	void fillFirstSet () {

	}

	void fillFollowSet () {

	}


}
