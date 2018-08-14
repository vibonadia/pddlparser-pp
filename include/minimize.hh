#ifndef MINIMIZE_H_
#define MINIMIZE_H_

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <tr1/unordered_map>

#include "instantiation.hh"
#include "instantiated_problem.hh"

class Minimize {
public:
	Minimize();
	virtual ~Minimize();

	InstantiatedProblem minimize(
			Instantiation &instantiation,
			InstantiatedActionList &actions,
			InstantiatedLiteralList &initial_state,
			InstantiatedLiteralList goal);

private:

	std::vector<int> _invariants_predicates;

	void detect_predicates_invariants(
			std::tr1::unordered_map<std::string, int> predicates,
			InstantiatedActionList &actions,
			InstantiatedLiteralList &initial_state);

};

#endif /* MINIMIZE_H_ */
