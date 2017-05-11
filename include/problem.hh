#ifndef _PROBLEM_HH_
#define _PROBLEM_HH_

#include <string>
#include <iostream>
#include <vector>
#include <tuple>

#include "predicate.hh"
#include "globals.hh"

using StringList    = std::vector<std::string>;
using Literal       = std::pair<Predicate*,bool>;
using LiteralList   = std::vector<Literal*>;

class Problem {
public:
	Problem(const std::string& name, const std::string& domain);
	virtual ~Problem();

	//TODO Check unused methods and remove
//	void set_objects(StringList *objects);
	void set_objects(ObjectMap	*types);

	void set_init_state(LiteralList *init);
	void set_goal_state(LiteralList *goal);

	const ObjectMap* getTypesObjects() const;

	friend std::ostream &operator<<(std::ostream& out, const Problem& problem);

private:
	std::string _name;
	std::string _domain;

	StringList	*_objects;
	ObjectMap	*_types_objects;//<type, Objects>
	LiteralList	*_init;
	LiteralList	*_goal;
};

#endif // _PROBLEM_HH_
