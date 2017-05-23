#include "instanced_action.hh"
using namespace std;

InstancedAction::InstancedAction(
		const std::string&			name,
		const InstancedLiteralList	*precond,
		const InstancedLiteralList	*effects) :
			_name(name),
			_precond(precond),
			_effects(effects)
{

}

InstancedAction::~InstancedAction() {

	for (auto precondition : *_precond) {
		delete precondition;
	}
	if (_precond) delete _precond;

	for (auto effect : *_effects) {
		delete effect;
	}
	delete _effects;
}

ostream &
operator<<(ostream& out, const InstancedAction& action)
{
	out << action._name << endl;
	if (action._precond) {

		out << "preconditions" << endl;
		out << action._precond->size() << endl;
		for (auto const& literal : *action._precond) {
			if (literal->second) {
				out << "1 " << literal->first;
			}
			else {
				out << "0 " << literal->first;
			}
			out <<  endl;
		}
	}

	if (action._effects) {

		out << "effects" << endl;
		out << action._effects->size() << endl;
		for (auto const& literal : *action._effects) {
			if (literal->second) {
				out << "1 " << literal->first;
			}
			else {
				out << "0 " << literal->first;
			}
			out <<  endl;
		}
	}
	return out;
}

