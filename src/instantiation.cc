#include "instantiation.hh"

Instantiation::Instantiation() {}

Instantiation::~Instantiation() {}


bool criterion_order_literals (InstantiatedLiteral *l1, InstantiatedLiteral *l2)
{
	return (l1->first < l2->first);
}

bool find_predicate(InstantiatedLiteralList * literal_list, int id_predicate)
{
	for(auto literal : *literal_list)
	{
		if(literal->first == id_predicate )
			return true;
	}
	return false;
}

InstantiatedLiteralList
Instantiation::instantiaton_initial_state(LiteralList * state)
{
	InstantiatedLiteralList initial_state;
	initial_state = instantiaton_state(state);

	//Complete initial state
	int predicates = instantiated_predicates.size();
	for (int id_predicate; id_predicate < predicates; id_predicate++)
	{
		bool contain_predicate = find_predicate(&initial_state, id_predicate);
		if(!contain_predicate)
		{
			InstantiatedLiteral * instantiated_literal = new InstantiatedLiteral(id_predicate, 0);
			initial_state.push_back(instantiated_literal);
		}
	}

	std::sort(initial_state.begin(), initial_state.end(), criterion_order_literals);
	return initial_state;
}

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

	std::vector<Action*>  * actions        	= domain->get_actions();
	const ObjectMap       * types_objects  	= problem->get_types_objects();
	const ConstantsMap    * types_constants	= domain->get_types_constants();

	for(auto action : *actions)
	{
		const TypeDict          * types_parameters  = action->get_types();
		const PreconditionList  * preconditions     = action->get_precond();
		const NondetEffectList	* effects           = action->get_effects();

		std::vector<StringList>    * combinations  = new std::vector<StringList>();
		std::map<std::string, int> * ref_parameter = new std::map<std::string, int>();

		generate_parameters_combinations(types_parameters, types_objects, types_constants, combinations, ref_parameter);

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
		const ConstantsMap * types_constants,
		std::vector<StringList> * combinations,
		std::map<std::string, int> * ref_parameter)
{

	std::vector<StringList> combine;
	int i = 0;

	for(auto type_parameter : *types_parameters)
	{
		if (types_objects->find(type_parameter.second) != types_objects->end())
			combine.push_back(*((types_objects->find(type_parameter.second))->second));
		else if (types_constants->find(type_parameter.second) != types_constants->end())
			combine.push_back(*((types_constants->find(type_parameter.second))->second));
		else
		{
			std::cout << "Instantiation error. Missing type";
			exit (EXIT_FAILURE);
		}

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
