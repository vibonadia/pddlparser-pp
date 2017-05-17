#include <iostream>
#include <string>
#include <fstream>

#include "pddldriver.hh"
#include "instantiation.hh"

using namespace std;

void usage(char *filename);
void instantiation_output(PDDLDriver driver);

int
main (int argc, char *argv[])
{
    if (argc < 3) {
        usage(argv[0]);
        return -1;
    }

    int result = 0;

    PDDLDriver driver;

    for (int i = 1; i < argc; ++i) {
        if (argv[i] == string ("-p")) {
            driver.trace_parsing = true;
        }
        else if (argv[i] == string ("-s")) {
            driver.trace_scanning = true;
        }
        else if (!driver.parse(argv[i])) {
            cout << "Parsing " << argv[i] << "... ";
            if (!result) cout << "ok!" << endl;
            else cout << "Error!" << endl;
        }
        else {
            result = -2;
            break;
        }
    }

    instantiation_output(driver);
    return result;
}

void
instantiation_output(PDDLDriver driver){
    Instantiation instantiaton;
    InstancedActionList actions	= instantiaton.instantiation_typed_actions(driver.domain, driver.problem);
    InstancedLiteralList state	= instantiaton.instantiaton_state(driver.problem->getInit());
    InstancedLiteralList goal	= instantiaton.instantiaton_state(driver.problem->getGoal());

	ofstream outfile;
	outfile.open("output", ios::out);

	outfile << "begin_predicates" << endl;
	for(auto predicate : instantiaton.instanced_predicates)
		outfile << predicate.first << ","<< predicate.second << endl;
	outfile << "end_predicates" << endl;

	//TODO move logic
	outfile << "begin_initial_state" << endl;
	for(auto literal : state)
	{
		if(literal->second)
			outfile << literal->first;
		else
			outfile << "NOT " << literal->first;
		outfile << endl;
	}
	outfile << "end_initial_state" << endl;

	outfile << "begin_goal" << endl;
	for(auto literal : goal)
	{
		if(literal->second)
			outfile << literal->first;
		else
			outfile << "NOT " << literal->first;
		outfile << endl;
	}
	outfile << "end_goal" << endl;

	outfile << "begin_actions" << std::endl;
	outfile << actions.size() << std::endl;
	for(auto action : actions)
	{
		outfile << "begin_action" << std::endl;
		outfile << *action;
		outfile << "end_action" << std::endl;
	}
	outfile << "end_actions" << std::endl;

	outfile.close();
}

void
usage(char *filename)
{
    cout << "usage: " << filename << " [-s] [-p] <domain.pddl> <problem.pddl>" << endl;
    cout << endl;
    cout << "Domain and problem PDDL parser in C/C++ using Flex & Bison." << endl;
    cout << "https://github.com/thiagopbueno/pddlparser-pp" << endl;
    cout << endl;
    cout << "OPTIONS:" << endl;
    cout << " -s\tenable scanning trace." << endl;
    cout << " -p\tenable parsing trace."  << endl;
}
