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

	const std::string		get_name() const;
	const TypeDict			* get_types() const;
	const PreconditionList	* get_precond() const;
	const EffectList		* get_effects() const;

	friend std::ostream& operator<<(std::ostream& out, const Action& action);

private:
	std::string				_name;
	const StringList		*_params;
	const TypeDict			*_types; //<name param, type>
	const PreconditionList	*_precond;
	const EffectList		*_effects;
};

#endif // _ACTION_HH_
