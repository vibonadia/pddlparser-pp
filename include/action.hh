#ifndef _ACTION_HH_
#define _ACTION_HH_

#include "predicate.hh"
#include "globals.hh"

#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <iostream>


class Action {
public:
	Action(
		const std::string&		name,
		const ParameterList		*params,
		const PreconditionList	*precond,
		const EffectList		*effects
	);

	virtual ~Action();

	const std::string		getName() const;
	const TypeDict			* getTypes() const;
	const PreconditionList	* getPrecond() const;
	const EffectList		* getEffects() const;

	friend std::ostream& operator<<(std::ostream& out, const Action& action);

private:
	std::string				_name;
	const StringList		*_params;
	const TypeDict			*_types; //<name param, type>
	const PreconditionList	*_precond;
	const EffectList		*_effects;
};

#endif // _ACTION_HH_
