/***************************************************************************
*Name: Wei Fei
*KUID: 2538810
*Date: 09/26/15
*File: NfaNode.cpp
*Course: EECS665 - Compiler Construction
*Project: Assignment 1: nfa2Dfa - Subset construction to convert NFA to Dfa
****************************************************************************/

#include "NfaNode.h"

/*
 * Constructor
 * @param nfaAlphabetNum   the number of alphabets in Nfa
 * @param nfaStateNum   the current state number in Nfa
 */
NfaNode::NfaNode()
{
    nfaAlphabetNum = 0;
    nfaStateNum = 0;
}


/*
 * Destructor
 */
NfaNode::~NfaNode()
{
}


/*
 * Set current state number in Nfa
 * @param newNumOfState   the current state number in Nfa
 */
void NfaNode::setNfaStateNum(int newNumOfState)
{
    nfaStateNum = newNumOfState;
}


/*
 * Get current state number in Nfa
 * @return nfaStateNum   the current state number in Nfa
 */
int NfaNode::getNfaStateNum()
{
    return nfaStateNum;
}


/*
 * Set new value for num of alphabet of Nfa
 * @param newNumOfAlphabet   the number of alphabets in Nfa
 */
void NfaNode::setNfaAlphabetNum(int newNumOfAlphabet)
{
    nfaAlphabetNum = newNumOfAlphabet;
}


/*
 * Get the number of alphabets in Nfa
 * @return nfaAlphabetNum   the number of alphabets in Nfa
 */
int NfaNode::getNfaAlphabetNum()
{
    return nfaAlphabetNum;
}





