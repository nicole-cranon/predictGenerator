/*
	nicole cranon <nicole.cranon@ucdenver.edu>
	csci 4640, fall 2015
	assignment 6 - predict generator
 */

#ifndef _PREDICT_GENERATOR
#define _PREDICT_GENERATOR

#include <set>
#include <vector>
#include <string>
#include <unordered_map>

namespace predict {
	typedef std::unordered_map<std::string,bool> markedVocabulary;
	typedef std::unordered_map<std::string,std::set<std::string>> symbolMap;
	typedef std::vector<std::vector<std::string>> symbolArr;

	extern markedVocabulary derivesLambda;
	extern symbolMap firstSet, 
		followSet;


	symbolArr getRHS_stringList (std::vector<std::string> RHSList);

	// remove white space in string s
	std::string normalize (const std::string& s);

	void markLambda (const std::vector<std::string>& lhs,
		const std::vector<std::vector<std::string> >& RHSStringList);

	void computeFirst (const std::vector<std::vector<std::string> >& RHSStringList,
		std::set<std::string>& terminalSet);

	void fillFirstSet (const std::set<std::string> nonterminals, 
		const std::set<std::string> terminals,
		const std::vector<std::string> LHS,
		const std::vector<std::string> RHS);

	void fillFollowSet ();


};

#endif
