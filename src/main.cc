#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

#include "pddldriver.hh"
#include "instantiation.hh"
#include "minimize.hh"

using namespace std;

void usage(char *filename);
void instantiation_output(PDDLDriver &driver);

int
main (int argc, char *argv[])
{
    if (argc < 3) {
        usage(argv[0]);
        return -1;
    }

    int result = 0;

    PDDLDriver driver;

    clock_t timer;
    timer = clock();

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

	cout << endl;
	cout << *(driver.domain)  << endl;
	cout << *(driver.problem) << endl;

    instantiation_output(driver);
    timer = clock() - timer;
    cout << "Parser: " << timer/(double)CLOCKS_PER_SEC << endl;

    return result;
}

void
instantiation_output(PDDLDriver &driver){
    Instantiation instantiaton;
    InstantiatedActionList *actions	= instantiaton.instantiation_typed_actions(driver.domain, driver.problem);
    InstantiatedLiteralList state	= instantiaton.instantiaton_initial_state(driver.problem->get_init());
    InstantiatedLiteralList goal	= instantiaton.instantiaton_state(driver.problem->get_goal());

	ofstream outfile;
	const string filename = driver.problem->get_name() + "_output";
	outfile.open(filename.c_str(), ios::out);

	Minimize minimize_problem;
	InstantiatedProblem problem = minimize_problem.minimize(instantiaton, *actions, state, goal);

	outfile << "begin_problem_name" << endl;
	outfile << driver.problem->get_name() << endl;
	outfile << "end_problem_name" << endl;

	outfile << "begin_predicates" << endl;
	outfile << problem._instantiated_predicates.size() << endl;
	for(auto predicate : problem._instantiated_predicates)
		outfile << predicate.second << " " << predicate.first << endl;
	outfile << "end_predicates" << endl;

	//TODO move logic
	outfile << "begin_initial_state" << endl;
	outfile << problem._intial_state.size() << endl;
	for(auto literal : problem._intial_state)
	{
		if(literal->second)
			outfile << "1 " << literal->first;
		else
			outfile << "0 " << literal->first;
		outfile << endl;
	}
	outfile << "end_initial_state" << endl;

	outfile << "begin_goal" << endl;
	outfile << problem._goal.size() << endl;
	for(auto literal : problem._goal)
	{
		if(literal->second)
			outfile << "1 " << literal->first;
		else
			outfile << "0 " << literal->first;
		outfile << endl;
	}
	outfile << "end_goal" << endl;

	outfile << "begin_actions" << std::endl;
	outfile << problem._actions->size() << std::endl;
	for( auto action : * (problem._actions) )
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
    cout << endl;
    cout << "OPTIONS:" << endl;
    cout << " -s\tenable scanning trace." << endl;
    cout << " -p\tenable parsing trace."  << endl;
}
