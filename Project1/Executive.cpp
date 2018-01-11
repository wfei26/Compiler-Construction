/***************************************************************************
*Name: Wei Fei
*KUID: 2538810
*Date: 09/26/15
*File: Executive.cpp
*Course: EECS665 - Compiler Construction
*Project: Assignment 1: nfa2dfa - Subset construction to convert NFA to DFA
****************************************************************************/

#include "Executive.h"

/*
 * Constructor
 */
Executive::Executive()
{
}


/*
 * Destructor
 */
Executive::~Executive()
{
}

void Executive::printFinalOutput()
{
    ConvertOperation convertMyNfaToDfa;
    convertMyNfaToDfa.readStandardInput();
    convertMyNfaToDfa.convertNfaToDfa();
}
