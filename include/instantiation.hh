#ifndef INSTANTIATION_H_
#define INSTANTIATION_H_

#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <iostream>
#include <tr1/unordered_map>

#include "globals.hh"
#include "domain.hh"
#include "problem.hh"
#include "action.hh"
#include "instantiated_action.hh"

using InstantiatedActionList = std::vector<InstantiatedAction*>;

class Instantiation {
public:
	Instantiation();
	virtual ~Instantiation();

	std::tr1::unordered_map<std::string, int> instantiated_predicates;
	InstantiatedActionList * instantiation_typed_actions(Domain *domain, Problem *problem);
	InstantiatedLiteralList instantiaton_state(LiteralList * state);
	InstantiatedLiteralList instantiaton_initial_state(LiteralList * state);

private:

	int add_predicate(const std::string predicate);

	void generate_parameters_combinations(
			const TypeDict *  types_parameters,
			const ObjectMap * types_objects,
			const ConstantsMap * types_constants,
			std::vector<StringList> * combinations,
			std::map<std::string, int> * ref_parameter);

	std::vector<std::vector<std::string>> cartesian_product(
			const std::vector<std::vector<std::string>>& v) const;

	std::string name_instantiate_action
		(Action *action, std::vector<std::string> combination) const;

	InstantiatedLiteralList * instantiate_literals(
			std::vector<std::string> combination,
			const PreconditionList * literals,
			std::map<std::string, int> ref_parameter);

	InstantiatedLiteral * instantiate_literal(
			std::vector<std::string> combination,
			Predicate * predicate,
			std::map<std::string, int> ref_parameter,
			bool value);

	InstantiatedLiteral * instantiate_literal(
			Predicate * predicate,
			bool value);
};

#endif /* INSTANTIATION_H_ */
