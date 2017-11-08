#ifndef GLOBALS_HH_
#define GLOBALS_HH_

#include "predicate.hh"

using StringList      = std::vector<std::string>;
using TypeDict        = std::map<std::string,std::string>;

using PredicateList     = std::vector<Predicate*>;
using ParameterList     = std::pair<StringList*,TypeDict*>;
using PreconditionList  = std::vector<std::pair<Predicate*,bool>*>;
using EffectList        = std::vector<std::pair<Predicate*,bool>*>;
using NondetEffectList  = std::vector<EffectList*>; // nondeterministic effects list
using ObjectMap         = std::map<std::string, StringList*>; // < object type, objects >
using ConstantsMap		= std::map<std::string, StringList*>; // < constant type, constants >


using Literal           = std::pair<Predicate*,bool>;
using LiteralList       = std::vector<Literal*>;

using InstantiatedLiteral       = std::pair<int, bool>;
using InstantiatedLiteralList	= std::vector<InstantiatedLiteral *>;
using InstantiatedPrecondList	= std::vector<InstantiatedLiteral *>;
using InstantiatedEffectsList	= std::vector<InstantiatedLiteralList *>;


#endif /* GLOBALS_HH_ */


