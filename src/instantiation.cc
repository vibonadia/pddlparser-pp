#include "instantiation.hh"

Instantiation::Instantiation() {}

Instantiation::~Instantiation() {}


InstancedActionList
Instantiation::instantiation_typed_actions(Domain *domain, Problem *problem)
{
	InstancedActionList instacedActionList;// = new InstancedActionList;

	std::vector<Action*>	* actions 		= domain->getActions();
	const ObjectMap			* types_objects	= problem->getTypesObjects();

	for(auto action : *actions)
	{

		const TypeDict			* types_parameters	= action->getTypes();
		const PreconditionList	* preconditions		= action->getPrecond();
		const EffectList		* effects			= action->getEffects();

		std::vector<StringList> * combinations = new std::vector<StringList>();
		std::map<std::string, int> * ref_parameter = new std::map<std::string, int>();
		generate_parameters_combinations(
				types_parameters,
				types_objects,
				combinations,
				ref_parameter);

		for (auto combination : *combinations)
		{

			InstancedAction * new_action = new InstancedAction(
					name_instantiate_action(action, combination),
					instantiate_literals(combination, preconditions, *ref_parameter),
					instantiate_literals(combination, effects, *ref_parameter));

			instacedActionList.push_back(new_action);
		}
	}
	return instacedActionList;
}

void
Instantiation::generate_parameters_combinations(
		const TypeDict *  types_parameters,
		const ObjectMap * types_objects,
		std::vector<StringList> * combinations,
		std::map<std::string, int> * ref_parameter){

	std::vector<StringList> combine;
	int i = 0;

	for(auto type_parameter : *types_parameters){
		combine.push_back(*((types_objects->find(type_parameter.second))->second));
		(*ref_parameter)[type_parameter.first] = i;
		i++;
	}
	*combinations = cartesian_product(combine);
}

std::vector<std::vector<std::string>>
Instantiation::cartesian_product (const std::vector<std::vector<std::string>>& v) {

	std::vector<std::vector<std::string>> s = {{}};
    for (const auto& u : v) {
    	std::vector<std::vector<std::string>> r;
        for (const auto& x : s) {
            for (const auto y : u) {
                r.push_back(x);
                r.back().push_back(y);
            }
        }
        s = std::move(r);
    }
    return s;
}

// generate action name
std::string
Instantiation::name_instantiate_action(Action *action, std::vector<std::string> combination){

	std::string name = action->getName();
	for(auto c : combination)
		name += "_" + c;

	return name;
}

InstancedLiteralList *
Instantiation::instantiate_literals (
		std::vector<std::string> combination,
		const std::vector<Literal*> * literals,
		std::map<std::string, int> name_indc) const
{
	InstancedLiteralList * instanced_literals = new InstancedLiteralList;

	for(auto literal : *literals)
	{
		Predicate * predicate = literal->first;
		bool value = literal->second;

		InstancedLiteral * instanced_literal =
				instantiate_literal(combination, predicate, name_indc, value);

		instanced_literals->push_back(instanced_literal);
	}
	return instanced_literals;
}

InstancedLiteral *
Instantiation::instantiate_literal(
		std::vector<std::string> combination,
		Predicate * predicate,
		std::map<std::string, int> name_indc,
		bool value) const
{
	std::string literal;
	literal = predicate->getName();

	for(auto argument : *predicate->getArguments()){
		int i = name_indc.find(argument)->second;
		literal += ("_" + combination[i]);
	}

	InstancedLiteral * instanced_literal = new InstancedLiteral(literal, value);
	return instanced_literal;

}
