/***************************************************************************
 *Name: Wei Fei
 *KUID: 2538810
 *Date: 09/26/15
 *File: DfaNode.h
 *Course: EECS665 - Compiler Construction
 *Project: Assignment 1: Dfa2dfa - Subset construction to convert Dfa to DFA
 ****************************************************************************/

#ifndef DFANODE_H_
#define DFANODE_H_
#include <iostream>
#include <string>
#include <set>
#include <vector>

using namespace std;

class DfaNode
{
private:
    int dfaAlphabetNum, dfaStateNum;

public:
    vector<set<int> > dfaVector;

    /*
     * Constructor
     * @param dfaAlphabetNum   the number of alphabets in Dfa
     * @param dfaStateNum   the current state number in Dfa
     */
    DfaNode();
    
    
    /*
     * Destructor
     */
    ~DfaNode();
    
    
    /*
     * Set current state number in Dfa
     * @param newNumOfAlphabet   the current state number in Dfa
     */
    void setDfaStateNum(int newNumOfState);
    
    
    /*
     * Get current state number in Dfa
     * @return dfaStateNum   the current state number in Dfa
     */
    int getDfaStateNum();
    
    
    /*
     * Set new value for num of alphabet of Dfa
     * @param newNumOfAlphabet   the number of alphabets in Dfa
     */
    void setDfaAlphabetNum(int newNumOfAlphabet);
    
    
    /*
     * Get the number of alphabets in Dfa
     * @return dfaAlphabetNum   the number of alphabets in Dfa
     */
    int getDfaAlphabetNum();
};

#endif


