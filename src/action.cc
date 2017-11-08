#include "action.hh"

using namespace std;

Action::Action(
	const string&           name,
	const ParameterList     *params,
	const PreconditionList  *precond,
	const NondetEffectList  *effects) :
		_name(name),
		_params(params->first), _types(params->second),
		_precond(precond), _effects(effects)
{

}

Action::~Action()
{
	if (_params) delete _params;
	if (_types) delete _types;

	for (auto precondition : *_precond) {
		delete precondition;
	}
	if (_precond) delete _precond;

	for (auto effect : *_effects) {
		delete effect;
	}
	delete _effects;
}

const std::string
Action::get_name() const
{
	return _name;
}

const TypeDict *
Action::get_types() const
{
	return _types;
}

const PreconditionList *
Action::get_precond() const
{
	return _precond;
}

const NondetEffectList *
Action::get_effects() const
{
	return _effects;
}

ostream &
operator<<(ostream& out, const Action& action)
{
	out << "Action(name:" << action._name << ")" << endl;
	if (action._params) {
		out << ">> params:[";
		auto size = action._params->size();
		for (decltype(size) i = 0; i < size; ++i) {
			auto parameter = (*action._params)[i];
			if (i == 0) {
				out << parameter;
			}
			else {
				out << ", " << parameter;
			}
			if (action._types && action._types->find(parameter) != action._types->end()) {
				out << " - " << action._types->at(parameter);
			}
		}
		out << "]" << endl;
	}
	out << ">> precond:[";
	auto size = action._precond->size();
	for (decltype(size) i = 0; i < size; ++i) {
		auto literal   = (*action._precond)[i];
		auto predicate = literal->first;
		bool positive  = literal->second;
		if (i == 0) {
			if (!positive) out << "NOT ";
			out << *predicate;
		}
		else {
			out << ", ";
			if (!positive) out << "NOT ";
			out << *predicate;
		}
	}
	out << "]" << endl;

	out << ">> non-deterministic effects:[" << endl;
	for (auto effects :  *action._effects){
		out << ">>> effects: ";
		size = effects->size();
		for (decltype(size) i = 0; i < size; ++i) {
			auto literal   = (*effects)[i];
			auto predicate = literal->first;
			bool positive  = literal->second;
			if (i == 0) {
				if (!positive) out << "NOT ";
				out << *predicate;
			}
			else {
				out << ", ";
				if (!positive) out << "NOT ";
				out << *predicate;
			}
		}
		out << endl;
	}
	out << "])" << endl;
	return out;
}
