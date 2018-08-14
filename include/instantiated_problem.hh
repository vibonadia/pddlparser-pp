#ifndef INSTANTIATED_PROBLEM_H_
#define INSTANTIATED_PROBLEM_H_

#include <iostream>
#include <string>
#include <tr1/unordered_map>

#include "globals.hh"
#include "instantiated_action.hh"
#include "instantiation.hh"

class InstantiatedProblem{
public:

	InstantiatedProblem();
	virtual ~InstantiatedProblem();

	std::map<int, std::string> _instantiated_predicates;
	InstantiatedActionList *_actions;
	InstantiatedLiteralList _intial_state;
	InstantiatedLiteralList _goal;

private:



};

#endif /* INSTANTIATED_PROBLEM_H_ */
