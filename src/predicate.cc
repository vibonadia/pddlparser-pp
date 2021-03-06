#include "predicate.hh"
using namespace std;

Predicate::Predicate(string name, ArgumentList *args) :
	_name(name), _args(args->first), _types(args->second)
{

}

Predicate::~Predicate()
{
	if (_args)  delete _args;
	if (_types) delete _types;
}

const std::string
Predicate::get_name() const
{
	return _name;
}

StringList *
Predicate::get_arguments() const{
	return _args;
}

ostream&
operator<<(ostream& out, const Predicate& predicate)
{
	out << predicate._name << "(";
	int i = 0;
	for (auto arg : *(predicate._args)) {
		if (i == 0) {
			out << arg;
		}
		else {
			out << "," << arg;
		}
		++i;
	}
	out << ")";
	return out;
}
