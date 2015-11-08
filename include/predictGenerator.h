/*
	nicole cranon <nicole.cranon@ucdenver.edu>
	csci 4640, fall 2015
	assignment 6 - predict generator
 */

#include <set>
#include <vector>
#include <string>

namespace predict {
	struct markedVocabulary {
		bool is_true;
		std::string symbol;
	};

	std::vector<std::vector<std::string> > getRHS_stringList (
		std::vector<std::string> RHSList);
	
	// remove white space in string s
	std::string normalize (const std::string& s);

	void markLambda (const std::set<std::string>& LHS, 
		std::vector<markedVocabulary>& derivesLambda);

	void computeFirst (const std::string& RHS,
		std::set<std::string>& terminalSet);

	void fillFirstSet ();

	void fillFollowSet ();


}
