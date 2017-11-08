#include "instantiation.hh"

Instantiation::Instantiation() {}

Instantiation::~Instantiation() {}

InstantiatedLiteralList
Instantiation::instantiaton_state(LiteralList * state)
{
	InstantiatedLiteralList instantiated_state;
	for (auto literal : *state)
	{
		instantiated_state.push_back(instantiate_literal(literal->first,literal->second));
	}

	return instantiated_state;
}

InstantiatedActionList *
Instantiation::instantiation_typed_actions(Domain *domain, Problem *problem)
{
	InstantiatedActionList * instantiated_actions = new InstantiatedActionList;

	std::vector<Action*>  * actions        = domain->get_actions();
	const ObjectMap       * types_objects  = problem->get_types_objects();
	//TODO get constants

	for(auto action : *actions)
	{
		const TypeDict          * types_parameters  = action->get_types();
		const PreconditionList  * preconditions     = action->get_precond();
		const NondetEffectList	* effects           = action->get_effects();

		std::vector<StringList>    * combinations  = new std::vector<StringList>();
		std::map<std::string, int> * ref_parameter = new std::map<std::string, int>();

		// TODO CONSIDERAR AS CONSTANTES NA COMBINAÇÃO
		generate_parameters_combinations(types_parameters, types_objects, combinations, ref_parameter);

		for ( auto combination : *combinations )
		{
			InstantiatedPrecondList * instantiate_precond = instantiate_literals(combination, preconditions, *ref_parameter);
			InstantiatedEffectsList * instantiate_eff = new InstantiatedEffectsList;

			for ( auto effect : *effects )
				instantiate_eff->push_back( instantiate_literals(combination, effect, *ref_parameter) );

			InstantiatedAction * new_action = new InstantiatedAction(
					name_instantiate_action(action, combination),
					instantiate_precond, instantiate_eff);

			instantiated_actions->push_back(new_action);
		}
	}
	return instantiated_actions;
}

void
Instantiation::generate_parameters_combinations(
		const TypeDict *  types_parameters,
		const ObjectMap * types_objects,
		std::vector<StringList> * combinations,
		std::map<std::string, int> * ref_parameter)
{

	std::vector<StringList> combine;
	int i = 0;

	for(auto type_parameter : *types_parameters)
	{
		combine.push_back(*((types_objects->find(type_parameter.second))->second));
		(*ref_parameter)[type_parameter.first] = i;
		i++;
	}
	*combinations = cartesian_product(combine);
}

std::vector<std::vector<std::string>>
Instantiation::cartesian_product (const std::vector<std::vector<std::string>>& v) const
{
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
Instantiation::name_instantiate_action(Action *action, std::vector<std::string> combination) const
{
	std::string name = action->get_name();
	for(auto c : combination)
		name += "_" + c;

	return name;
}

InstantiatedLiteralList *
Instantiation::instantiate_literals (
		std::vector<std::string> combination,
		const std::vector<Literal*> * literals,
		std::map<std::string, int> name_indc)
{
	InstantiatedLiteralList * instantiated_literals = new InstantiatedLiteralList;

	for( auto literal : *literals )
	{
		Predicate * predicate = literal->first;
		bool value = literal->second;

		InstantiatedLiteral * instantiated_literal = instantiate_literal(combination, predicate, name_indc, value);

		instantiated_literals->push_back(instantiated_literal);
	}
	return instantiated_literals;
}

InstantiatedLiteral *
Instantiation::instantiate_literal(
		std::vector<std::string> combination,
		Predicate * predicate,
		std::map<std::string, int> name_indc,
		bool value)
{
	std::string literal;
	literal = predicate->get_name();

	for(auto argument : *predicate->get_arguments()){
		int i = name_indc.find(argument)->second;
		literal += ("_" + combination[i]);
	}

	int predicate_number = add_predicate(literal);
	InstantiatedLiteral * instantiated_literal = new InstantiatedLiteral(predicate_number, value);
	return instantiated_literal;
}

InstantiatedLiteral *
Instantiation::instantiate_literal(
		Predicate * predicate,
		bool value)
{
	std::string predicate_name;
	predicate_name = predicate->get_name();

	for(auto argument : *predicate->get_arguments()){
		predicate_name+= "_" + argument;
	}

	int predicate_number = add_predicate(predicate_name);
	InstantiatedLiteral * instantiated_literal = new InstantiatedLiteral(predicate_number, value);
	return instantiated_literal;
}

int
Instantiation::add_predicate(const std::string predicate)
{
	std::tr1::unordered_map<std::string, int>::const_iterator iterator = instantiated_predicates.find(predicate);
	int value = instantiated_predicates.size();

	if (iterator == instantiated_predicates.end()){
		std::pair<std::string, int> pair (predicate, value);
		instantiated_predicates.insert(pair);
		return value;
	}else{
		value = (*iterator).second;
	}

	return value;
}
