#include "problem.hh"

using namespace std;

Problem::Problem(const string& name, const string& domain)
	: _name(name), _domain(domain)
{

}

Problem::~Problem()
{
	delete _objects;

	for (auto literal : *_init) {
		delete literal->first;
	}
	delete _init;

	for (auto goal : *_goal) {
		delete goal->first;
	}
	delete _goal;

	//TODO remove types
}

void
Problem::set_objects(ObjectMap *types)
{
	_types_objects = types;
}


void
Problem::set_init_state(LiteralList *init)
{
	_init = init;
}

void
Problem::set_goal_state(LiteralList *goal)
{
	_goal = goal;
}

const ObjectMap *
Problem::getTypesObjects() const {
	return _types_objects;
}

ostream&
operator<<(ostream& out, const Problem& problem)
{
	out << ">> Problem(name:" << problem._name << ", domain:" << problem._domain << ")" << endl;
	out << endl;
	out << "Objects: [";
	if(problem._objects){
		for (auto const& object : *problem._objects) {
			out << " " << object;
		}
	}
	if(problem._types_objects){
		out << endl << "\tTypes: [";
		for (auto const& typed_object : *problem._types_objects) {
			out << endl << "\t\t" << typed_object.first << " - ";

			for (auto const& objects : *typed_object.second)
				out << objects << " ";
		}
		out << "\t\t]" << endl;
	}
	out << " ]" << endl;
	out << endl;
	out << "Init: [" << endl;
	for (auto const& literal : *problem._init) {
		if (literal->second) {
			out << "  " << *(literal->first);
		}
		else {
			out << "  NOT " << *(literal->first);
		}
		out <<  endl;
	}
	out << "]" << endl;
	out << endl;
	out << "Goal: [" << endl;
	for (auto const& literal : *problem._goal) {
		if (literal->second) {
			out << "  " << *(literal->first);
		}
		else {
			out << "  NOT " << *(literal->first);
		}
		out <<  endl;
	}
	out << "]" << endl;

	return out;
}
