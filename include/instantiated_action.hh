#ifndef INSTANTIATED_ACTION_H_
#define INSTANTIATED_ACTION_H_

#include <iostream>
#include <string>

#include "globals.hh"

class InstantiatedAction {
public:

	InstantiatedAction(
		const std::string&           	name,
		const InstantiatedPrecondList  *precond,
		const InstantiatedEffectsList  *effects
	);
	virtual ~InstantiatedAction();

	const InstantiatedEffectsList * get_effects() const;
	bool has_predicate(int predicate_id);

	friend std::ostream& operator<<(std::ostream& out, const InstantiatedAction& action);

private:
	std::string                   _name;
	const InstantiatedPrecondList *_precond;
	const InstantiatedEffectsList *_effects;

};

#endif /* INSTANTIATED_ACTION_H_ */
