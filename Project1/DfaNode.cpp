/***************************************************************************
 *Name: Wei Fei
 *KUID: 2538810
 *Date: 09/26/15
 *File: DfaNode.cpp
 *Course: EECS665 - Compiler Construction
 *Project: Assignment 1: nfa2dfa - Subset construction to convert NFA to DFA
 ****************************************************************************/

#include "DfaNode.h"

/*
 * Constructor
 * @param dfaAlphabetNum   the number of alphabets in Dfa
 * @param dfaStateNum   the current state number in Dfa
 */
DfaNode::DfaNode()
{
    dfaAlphabetNum = 0;
    dfaStateNum = 0;
}


/*
 * Destructor
 */
DfaNode::~DfaNode()
{
}


/*
 * Set current state number in Dfa
 * @param newNumOfAlphabet   the current state number in Dfa
 */
void DfaNode::setDfaStateNum(int newNumOfState)
{
    dfaStateNum = newNumOfState;
}


/*
 * Get current state number in Dfa
 * @return dfaStateNum   the current state number in Dfa
 */
int DfaNode::getDfaStateNum()
{
    return dfaStateNum;
}


/*
 * Set new value for num of alphabet of Dfa
 * @param newNumOfAlphabet   the number of alphabets in Dfa
 */
void DfaNode::setDfaAlphabetNum(int newNumOfAlphabet)
{
    dfaAlphabetNum = newNumOfAlphabet;
}


/*
 * Get the number of alphabets in Dfa
 * @return dfaAlphabetNum   the number of alphabets in Dfa
 */
int DfaNode::getDfaAlphabetNum()
{
    return dfaAlphabetNum;
}




