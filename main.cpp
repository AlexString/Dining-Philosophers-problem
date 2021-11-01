/*
Author: AlexString
Description:
	This file demonstrates the use of 
	PhilosophersProblem.h	
*/

#include <iostream>
#include <limits>
#include "PhilosophersProblem.h"

using namespace std;

int main(){
	cout << "Philosophers problem.\n" << endl;
	PhilosophersProblem philosopers_problem;

	cout << "Press Enter to Continue";
	cin.ignore(std::numeric_limits<streamsize>::max(),'\n');

	// Executing problem
	philosopers_problem.execute();
	return 0;
}