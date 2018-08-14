#include "minimize.hh"

Minimize::Minimize(){}

Minimize::~Minimize() {}

InstantiatedProblem
Minimize::minimize(Instantiation &instantiation,InstantiatedActionList &actions,
			InstantiatedLiteralList &initial_state,InstantiatedLiteralList goal)
{
	InstantiatedProblem problem;

	detect_predicates_invariants(instantiation.instantiated_predicates, actions, initial_state);


	// remove invariants from the predicates list
	for ( auto in_predicate : instantiation.instantiated_predicates)
	{
		bool valid_predicate = true;
		for(auto predicate : _invariants_predicates)
		{
			if(in_predicate.second == predicate)
			{
				valid_predicate = false;
				break;
			}
		}
		if(valid_predicate)
			problem._instantiated_predicates.insert(std::pair<int, std::string>(in_predicate.second, in_predicate.first) );
	}

	// remove invariants from the actions list
	for(unsigned i = 0; i < actions.size(); i++)
	{
		bool invalid_action = false;
		for(auto predicate : _invariants_predicates)
		{
			if( actions[i]->has_predicate(predicate) )
			{
				invalid_action = true;
				break;
			}
		}
		if(!invalid_action) problem._actions->push_back(actions[i]);
	}

	// remove invariants from the initial state
	LiteralList initial;
	for(auto literal : initial_state)
	{
		bool valid_literal = true;
		for(auto predicate : _invariants_predicates)
		{
			if(literal->first == predicate)
			{
				valid_literal = false;
				break;
			}
		}
		if(valid_literal)
		{
			InstantiatedLiteral * instantiated_literal = new InstantiatedLiteral(literal->first, literal->second);
			problem._intial_state.push_back(instantiated_literal);
		}
	}

	problem._goal = goal;

	return problem;
}


void
Minimize::detect_predicates_invariants( std::tr1::unordered_map<std::string, int> predicates,
		InstantiatedActionList &actions, InstantiatedLiteralList &initial_state)
{
	bool invariant = true;

	for(auto predicate : predicates)
	{
		//search predicate in initial state
		invariant = true;
		for(auto literal : initial_state)
		{
			if (predicate.second == literal->first)
			{
				if(literal->second) invariant = false;

				break;
			}
		}
		if(invariant)
		{
			// search in effects
			invariant = true;
			for(auto action : actions)
			{
				if(!invariant) break;

				for ( auto effect : *action->get_effects())
				{
					for (auto const& literal : *effect)
					{
						if(literal->first == predicate.second && literal->second) invariant = false;
					}

				}
			}
		}
		if(invariant) _invariants_predicates.push_back(predicate.second);
	}
}
