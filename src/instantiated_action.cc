#include "instantiated_action.hh"
using namespace std;

InstantiatedAction::InstantiatedAction(
		const std::string&            name,
		const InstantiatedPrecondList *precond,
		const InstantiatedEffectsList *effects) :
			_name(name),
			_precond(precond),
			_effects(effects)
{

}

InstantiatedAction::~InstantiatedAction() {

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
operator<<(ostream& out, const InstantiatedAction& action)
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
		out << "begin_nd_effects" << endl;
		out << action._effects->size() << endl;

		for ( auto effect : *action._effects){
			out << "effects" << endl;
			out << effect->size() << endl;

			for (auto const& literal : *effect) {
				if (literal->second) {
					out << "1 " << literal->first;
				}
				else {
					out << "0 " << literal->first;
				}
				out <<  endl;
			}
		}
		out << "end_nd_effects" << endl;
	}
	return out;
}

