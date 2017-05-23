#ifndef _PROBLEM_HH_
#define _PROBLEM_HH_

#include <iostream>
#include <string>
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

//	void set_objects(StringList *objects);
	void set_objects(ObjectMap	*types);

	void set_init_state(LiteralList *init);
	void set_goal_state(LiteralList *goal);

	const ObjectMap* get_types_objects() const;

	friend std::ostream &operator<<(std::ostream& out, const Problem& problem);

	const std::string& get_name() const {
		return _name;
	}

	LiteralList* get_goal() const {
		return _goal;
	}

	LiteralList* get_init() const {
		return _init;
	}

private:
	std::string _name;
	std::string _domain;

	StringList	*_objects;
	ObjectMap	*_types_objects;//<type, Objects>
	LiteralList	*_init;
	LiteralList	*_goal;
};

#endif // _PROBLEM_HH_
