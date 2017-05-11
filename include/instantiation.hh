#ifndef INSTANTIATION_H_
#define INSTANTIATION_H_

#include <string>
#include <vector>
#include <map>
#include <iostream>

#include "globals.hh"
#include "domain.hh"
#include "problem.hh"
#include "action.hh"
#include "instanced_action.hh"

using InstancedActionList		= std::vector<InstancedAction*>;

class Instantiation {
public:
	Instantiation();
	virtual ~Instantiation();

	InstancedActionList instantiation_typed_actions(Domain *domain, Problem *problem);

private:

	void generate_parameters_combinations(
			const TypeDict *  types_parameters,
			const ObjectMap * types_objects,
			std::vector<StringList> * combinations,
			std::map<std::string, int> * ref_parameter);

	std::vector<std::vector<std::string>> cartesian_product(
			const std::vector<std::vector<std::string>>& v);

	std::string name_instantiate_action
		(Action *action, std::vector<std::string> combination);

	InstancedLiteralList * instantiate_literals(
			std::vector<std::string> combination,
			const PreconditionList * literals,
			std::map<std::string, int> ref_parameter) const;

	InstancedLiteral * instantiate_literal(
			std::vector<std::string> combination,
			Predicate * predicate,
			std::map<std::string, int> ref_parameter,
			bool value) const;
};

#endif /* INSTANTIATION_H_ */
