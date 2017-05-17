#ifndef GLOBALS_HH_
#define GLOBALS_HH_

#include "predicate.hh"

using StringList      = std::vector<std::string>;
using TypeDict        = std::map<std::string,std::string>;

using PredicateList     = std::vector<Predicate*>;
using ParameterList     = std::pair<StringList*,TypeDict*>;
using PreconditionList  = std::vector<std::pair<Predicate*,bool>*>;
using EffectList        = std::vector<std::pair<Predicate*,bool>*>;
using ObjectMap         = std::map<std::string, StringList*>;

using Literal           = std::pair<Predicate*,bool>;
using LiteralList       = std::vector<Literal*>;

using InstancedLiteral      = std::pair<int, bool>;
using InstancedLiteralList  = std::vector<InstancedLiteral *>;


#endif /* GLOBALS_HH_ */
