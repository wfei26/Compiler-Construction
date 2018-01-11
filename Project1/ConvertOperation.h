/***************************************************************************
*Name: Wei Fei
*KUID: 2538810
*Date: 09/26/15
*File: ConvertOperation.h
*Course: EECS665 - Compiler Construction
*Project: Assignment 1: nfa2dfa - Subset construction to convert NFA to DFA
****************************************************************************/

#ifndef CONVERTOPERATION_H_
#define CONVERTOPERATION_H_
#include "NfaNode.h"
#include "DfaNode.h"


class ConvertOperation
{
private:
    vector<NfaNode> myNfa;
    vector<DfaNode> myDfaTable;
    vector<int> myFinalStates;
    vector<set<int> > myDfaVector;
    int arr[100];
    

public:
    /*
     * Constructor
     */
	ConvertOperation();
	
    
    /*
     * Destructor
     */
    ~ConvertOperation();
    
    
    /*
     * Read file and get data by using the way of reading standard input,
     * and set transition table for Nfa
     */
    void readStandardInput();
    
    
    /*
     * Get data from Nfa and convert to Dfa, also save Dfa data in sets
     */
    void convertNfaToDfa();
    
    
    /*
     * Get data from vectors and put in temp set
     * @param newBufSet   the empty set to save transition information of each state
     * @param beginPos   set current position as start point
     * @param newstr   save a specific line's information when we read the standard input
     * @return endPos   the position of end point
     */
    int saveValueToSet(set<int> &newBufSet, int beginPos, string newstr);
    
    
    /*
     * Recursively figure out the epsilon closure set
     * @param newBufSet   the empty set to save transition information of each state
     * @param newStateNum   current state number
     */
    void epsilonClosureSet(set<int> &newBufSet, int newStateNum);
    
    
    /*
     * Print all values of a set
     * @param newSet   pass the set that we want to print
     */
    void printSet(set<int> newSet);
};

#endif
