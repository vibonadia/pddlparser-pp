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

	if (_precond) delete _precond;
	if (_effects) delete _effects;
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
				out << literal->first;
			}
			else {
				out << "NOT " << literal->first;
			}
			out <<  endl;
		}
	}

	if (action._effects) {

		out << "effects" << endl;
		out << action._effects->size() << endl;
		for (auto const& literal : *action._effects) {
			if (literal->second) {
				out << literal->first;
			}
			else {
				out << "NOT " << literal->first;
			}
			out <<  endl;
		}
	}
	return out;
}

