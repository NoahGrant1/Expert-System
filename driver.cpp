/*
 * driver.cpp
 *
 *  Created on: 21 Sep,2020
 *      Author: antec
 */

#include <iostream>
#include "functions.h"
using namespace std;

/*
 * Limitations:
 * questions are case sensitive exact values must be used for correct answer
 * question formats must be precisely followed or else no answer is provided
 * unit names and references names must have caps used as the program wont recognise them otherise.
 *
 * Features:
 * works for all example questions and has some flexibility in
 * questions allow for other references and units to be questioned as well.
 */


int main()
{
	cout << "Welcome the Reference Advisor system" << endl;
	ReferenceAdvisor data;

	data.addDictInfo();
	data.addUnitInfo();
	data.addReferenceInfo();
	data.userQuestions();

}




