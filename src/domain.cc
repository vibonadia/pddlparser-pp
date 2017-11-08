#include "domain.hh"

using namespace std;

Domain::Domain(const string &name) : _name(name)
{
	_types_constants = nullptr;
}

Domain::~Domain()
{
	for (auto predicate : *_predicates) {
		delete predicate;
		predicate = nullptr;
	}
	delete _predicates;

	for (auto action : *_actions) {
		delete action;
		action = nullptr;
	}
	delete _actions;

	if(_types_constants)
		delete _types_constants;
}

void
Domain::set_requirements(std::vector<std::string>* requirements)
{
	_requirements = requirements;
}

void
Domain::set_predicates(std::vector<Predicate*>* predicates)
{
	_predicates = predicates;
}

void
Domain::set_actions(std::vector<Action*>* actions)
{
	_actions = actions;
}

void
Domain::set_constants(ConstantsMap *constants)
{
	_types_constants = constants;
}

std::vector<Action*>*
Domain::get_actions() const
{
	return _actions;
}

const ConstantsMap *
Domain::get_types_constants() const
{
	return _types_constants;
}

std::ostream&
operator<<(std::ostream& out, const Domain& domain)
{
	out << ">> Domain(name:" << domain._name << ")" << endl;
	out << endl;
	out << "Requirements: [";
	for (auto const& requirement : *domain._requirements) {
		out << " " << requirement;
	}
	out << " ]" << endl;

	if(domain._types_constants){
		out << endl << "\tConstants: [";
		for (auto const& typed_constant : *domain._types_constants) {
			out << endl << "\t\t" << typed_constant.first << " - ";

			for (auto const& constants : *typed_constant.second)
				out << constants << " ";
		}
		out << "\t\t]" << endl;
	}
	out << " ]" << endl;
	out << endl;

	out << "Predicates: [";
	for (auto const& predicate : *domain._predicates) {
		out << " " << *predicate;
	}
	out << " ]" << endl;
	out << endl;
	for (auto const& action : *domain._actions) {
		out << *action;
		out << endl;
	}
	return out;
}
