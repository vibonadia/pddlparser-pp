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
	out << "Instanced Action(name: " << action._name << ")" << endl;
	if (action._precond) {

		out << "Precond: [" << endl;
		for (auto const& literal : *action._precond) {
			if (literal->second) {
				out << "  " << literal->first;
			}
			else {
				out << "  NOT " << literal->first;
			}
			out <<  endl;
		}
		out << "]" << endl;
	}

	if (action._effects) {

		out << "Effects: [" << endl;
		for (auto const& literal : *action._effects) {
			if (literal->second) {
				out << "  " << literal->first;
			}
			else {
				out << "  NOT " << literal->first;
			}
			out <<  endl;
		}
		out << "]" << endl;
	}
	return out;
}

