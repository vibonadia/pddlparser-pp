#ifndef INSTANCED_ACTION_H_
#define INSTANCED_ACTION_H_

#include <iostream>
#include <string>

#include "globals.hh"

class InstancedAction {
public:

	InstancedAction(
		const std::string&			name,
		const InstancedLiteralList	*precond,
		const InstancedLiteralList	*effects
	);
	virtual ~InstancedAction();

	friend std::ostream& operator<<(std::ostream& out, const InstancedAction& action);

private:
	std::string 				 _name;
	const InstancedLiteralList *_precond;
	const InstancedLiteralList *_effects;

};

#endif /* INSTANCED_ACTION_H_ */
