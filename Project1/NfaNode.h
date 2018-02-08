/***************************************************************************
*Name: Wei Fei
*KUID: 2538810
*Date: 09/26/15
*File: NfaNode.h
*Course: EECS665 - Compiler Construction
*Project: Assignment 1: nfa2Dfa - Subset construction to convert NFA to Dfa
****************************************************************************/

#ifndef NFANODE_H_
#define NFANODE_H_
#include <iostream>
#include <string>
#include <set>
#include <vector>

using namespace std;

class NfaNode
{
private:
    int nfaAlphabetNum, nfaStateNum;

public:
    set<int> nfaSet;
    vector<set<int> > nfaVector;
    
    /*
     * Constructor
     * @param nfaAlphabetNum   the number of alphabets in Nfa
     * @param nfaStateNum   the current state number in Nfa
     */
	NfaNode();
    
    
    /*
     * Destructor
     */
	~NfaNode();
    
    
    /*
     * Set current state number in Nfa
     * @param newNumOfState   the current state number in Nfa
     */
    void setNfaStateNum(int newNumOfState);
    
    
    /*
     * Get current state number in Nfa
     * @return nfaStateNum   the current state number in Nfa
     */
    int getNfaStateNum();
    
    
    /*
     * Set new value for num of alphabet of Nfa
     * @param newNumOfAlphabet   the number of alphabets in Nfa
     */
    void setNfaAlphabetNum(int newNumOfAlphabet);
    
    
    /*
     * Get the number of alphabets in Nfa
     * @return nfaAlphabetNum   the number of alphabets in Nfa
     */
    int getNfaAlphabetNum();

};

#endif




