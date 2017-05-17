#ifndef INSTANTIATION_H_
#define INSTANTIATION_H_

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <tr1/unordered_map>

#include "globals.hh"
#include "domain.hh"
#include "problem.hh"
#include "action.hh"
#include "instanced_action.hh"

using InstancedActionList = std::vector<InstancedAction*>;

class Instantiation {
public:
	Instantiation();
	virtual ~Instantiation();

	std::tr1::unordered_map<std::string, int> instanced_predicates;
	InstancedActionList instantiation_typed_actions(Domain *domain, Problem *problem);
	InstancedLiteralList instantiaton_state(LiteralList * state);

private:

	int add_predicate(const std::string predicate);

	void generate_parameters_combinations(
			const TypeDict *  types_parameters,
			const ObjectMap * types_objects,
			std::vector<StringList> * combinations,
			std::map<std::string, int> * ref_parameter);

	std::vector<std::vector<std::string>> cartesian_product(
			const std::vector<std::vector<std::string>>& v) const;

	std::string name_instantiate_action
		(Action *action, std::vector<std::string> combination) const;

	InstancedLiteralList * instantiate_literals(
			std::vector<std::string> combination,
			const PreconditionList * literals,
			std::map<std::string, int> ref_parameter);

	InstancedLiteral * instantiate_literal(
			std::vector<std::string> combination,
			Predicate * predicate,
			std::map<std::string, int> ref_parameter,
			bool value);

	InstancedLiteral * instantiate_literal(
			Predicate * predicate,
			bool value);
};

#endif /* INSTANTIATION_H_ */
