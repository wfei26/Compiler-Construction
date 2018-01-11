/***************************************************************************
 *Name: Wei Fei
 *KUID: 2538810
 *Date: 09/26/15
 *File: ConvertOperation.cpp
 *Course: EECS665 - Compiler Construction
 *Project: Assignment 1: nfa2dfa - Subset construction to convert NFA to DFA
 ****************************************************************************/

#include "ConvertOperation.h"

/*
 * Constructor
 */
ConvertOperation::ConvertOperation()
{
}


/*
 * Destructor
 */
ConvertOperation::~ConvertOperation()
{
}


/*
 * Read file and get data by using the way of reading standard input,
 * and set transition table for Nfa
 */
void ConvertOperation::readStandardInput()
{
    /*
     * @param pos   the current position of the tokon that we need
     * @param numOfAlphabet   tatol number of alphabets in Nfa
     * @param stateNum   the current number of state
     * @param bufStr   save a specific line's information when we read the standard input
     * @param tempStr   save the rest of edited buffer string
     */
    int pos, numOfAlphabet, stateNum;
    string bufStr, tempStr;
    
    /*extracts characters for first three lines in order to prepare getting
     the data information of initial state, final state and total state number*/
    getline(cin, bufStr);
    getline(cin, bufStr);
    //cout << "bufStr: " << bufStr << endl;
    
    for(int i = 0; i < bufStr.size(); i++)
    {
        if((bufStr[i - 1] == '{' && bufStr[i + 1] == ',') || (bufStr[i - 1] == ',' && bufStr[i + 1] == ',') || (bufStr[i - 1] == ',' && bufStr[i + 1] == '}') || (bufStr[i-  1] == '{' && bufStr[i + 1] == '}'))
        {
            int tempValue = bufStr[i]-'0';
            myFinalStates.push_back(tempValue);           
        }
        else if((bufStr[i - 1] == '{' && isdigit(bufStr[i + 1])) || (bufStr[i - 1] == ',' && isdigit(bufStr[i + 1])))
        {
            int tempValue2;
            string newstr;
            newstr += bufStr[i];
            newstr += bufStr[i + 1];
            tempValue2 = atoi(newstr.c_str());
            myFinalStates.push_back(tempValue2);
        }
    }
    
    for(int i = 0; i < myFinalStates.size(); i++)
    {
        arr[i] = myFinalStates.at(i);
    }
    
    getline(cin, bufStr);
    
    //find the position of space for the last occurrence of the third line
    pos = bufStr.rfind(' ');
    
    //for testing
    //cout << "pos: " << pos << " length: " << newStr.length() << endl;
    
    /*after reading data as string type, we need to interprete the data as
     an interger, and save the value for number of state*/
    stateNum = stoi(bufStr.substr(pos + 1, bufStr.length() - 1 - pos));
    
    getline(cin, bufStr);
    //find the position of epsilon
    pos = bufStr.rfind('E') - 1;
    //cout << "pos: " << pos << endl;
    
    //reach the first alphabet by using while loop
    while (bufStr[pos] < 'a' || bufStr[pos] > 'z')
    {
        //cout << newStr[pos] << endl;
        pos = pos - 1;
        //cout << "pos: " << pos << endl;
    }
    numOfAlphabet = bufStr[pos] + 1 - 'a';
    
    for(int i = 0; i < stateNum; i++)
    {
        set<int> bufSet;
        NfaNode bufNfa;
        
        getline(cin, bufStr);
        pos = bufStr.find(' ');
        
        bufNfa.setNfaAlphabetNum(numOfAlphabet);
        //reset nfa state number when the loop reaches each line
        bufNfa.setNfaStateNum(stoi(bufStr.substr(0, pos)));
        
        for (int j = 0; j < numOfAlphabet; j++)
        {
            bufSet.clear();
            pos = saveValueToSet(bufSet, pos, bufStr);
            //cout << "pos: " << i << " " << j << " " << pos << endl;
            bufNfa.nfaVector.push_back(bufSet);
        }
        saveValueToSet(bufNfa.nfaSet, pos, bufStr);
        
        //after saving all transition inforamtion of a state in set, then save set in Nfa vector
        myNfa.push_back(bufNfa);
    }
}


/*
 * Get data from Nfa and convert to Dfa, also save Dfa data in sets
 */
void ConvertOperation::convertNfaToDfa()
{
    set<int>::iterator myItera1, myItera2;
    set<int> bufSet1;
    
    cout << "E-closure(I0) = ";
    
    //get and print the first epsilon closure set from start state
    epsilonClosureSet(bufSet1, 1);
    printSet(bufSet1);
    cout << " = 1\n\n";
    
    //after getting the epsilon closure set, push into dfa vector
    myDfaVector.push_back(bufSet1);
    
    set<int> bufSet2, bufSet3;
    //follow the algorithm to print all dfa transitions and epsilon closure set
    for(int i = 1; i < myDfaVector.size() + 1; i++)
    {
        cout << "Mark " << i << "\n";
        DfaNode tempDfa;
        set<int> tempSet1, tempSet2;
        
        tempSet1 = myDfaVector[i-1];
        
        for(int j = 0; j < myNfa[0].getNfaAlphabetNum(); j++)
        {
            //clear sets at the beginning of each round
            bufSet2.clear();
            bufSet3.clear();
            
            for(myItera1 = tempSet1.begin(); myItera1 != tempSet1.end(); myItera1++)
            {
                tempSet2 = myNfa[*myItera1 - 1].nfaVector[j];
                
                //check if the set is full
                if(tempSet2.size())
                {
                    for(myItera2 = tempSet2.begin(); myItera2 != tempSet2.end(); myItera2++)
                    {
                        bufSet2.insert(*myItera2);
                    }
                }
            }
            
            if(bufSet2.size())
            {
                printSet(myDfaVector[i - 1]);
                cout << " --" << (char)('a' + j) << "--> ";
                
                printSet(bufSet2);
                cout << "\n";
                
                bufSet1.clear();
                
                for(myItera1 = bufSet2.begin(); myItera1 != bufSet2.end(); myItera1++)
                {
                    epsilonClosureSet(bufSet1, *myItera1);
                }
                
                cout << "E-closure";
                printSet(bufSet2);
                
                cout << " = ";
                printSet(bufSet1);
                
                cout << " = ";
                
                int l = 0;
                for(l = 0; l < myDfaVector.size(); l++)
                {
                    if(bufSet1 == myDfaVector[l])
                    {
                        break;
                    }
                }
                if(l == myDfaVector.size())
                {
                    myDfaVector.push_back(bufSet1);
                }
                cout << l + 1 << endl;
                bufSet3.insert(l + 1);
            }
            
            tempDfa.dfaVector.push_back(bufSet3);
        }
        cout << "\n";
        
        tempDfa.setDfaStateNum(i);
        tempDfa.setDfaAlphabetNum(myNfa[0].getNfaAlphabetNum());
        myDfaTable.push_back(tempDfa);
    }
    
    /*
     for (int i = 0; i < myDfaVector.size(); i++)
     {
     printSet(myDfaVector[i]);
     cout << "\n";
     }*/
    
    //get all states' number in final state
    cout << "Initial State: {1}\n" << "Final States: ";
    set<int> finalState;
    finalState.insert(myDfaTable.size());
    //cout << myDfaTable.size() << " and " << myDfaVector.size() << endl;
    
    
    for (int i = 0; i < myFinalStates.size(); i++)
    {
        for (int j = 0; j < myDfaTable.size(); j++)
        {
	    //use set iterator to compare each element in every dfa set
            set<int>::iterator tempItera = myDfaVector.at(j).begin();
            for (int k = 0; k < myFinalStates.size(); k++)
            {
                tempItera = myDfaVector.at(j).find(arr[k]);
                if (tempItera != myDfaVector.at(j).end())
                {
		    //save correct final state number
                    finalState.insert(j + 1);
                }
            }
        }
    }
    
    printSet(finalState);
    
    //print final transition table
    cout << "\nState";
    for(int i = 0; i < myDfaTable[0].getDfaAlphabetNum(); i++)
    {
        cout << "\t" << (char)('a' + i);
    }
    cout << "\n";
    
    for(int i = 0; i < myDfaTable.size() ; i++)
    {
        cout << myDfaTable[i].getDfaStateNum();
        for(int j = 0; j < myDfaTable[0].getDfaAlphabetNum(); j++)
        {
            cout << "\t";
            printSet(myDfaTable[i].dfaVector[j]);
        }
        cout << "\n";
    }
}


/*
 * Get data from vectors and put in temp set
 * @param newBufSet   the empty set to save transition information of each state
 * @param beginPos   set current position as start point
 * @param newstr   save a specific line's information when we read the standard input
 * @return endPos   the position of end point
 */
int ConvertOperation::saveValueToSet(set<int> &newBufSet, int beginPos, string newstr)
{
    int endPos;
    
    //check current position until reach the symbol "{" (front bracket)
    while(newstr[beginPos] != '{')
    {
        beginPos++;
    }
    
    //check if the bracket is empty
    if(newstr[++beginPos] == '}')
    {
        return ++beginPos;
    }
    endPos = beginPos;
    
    //get all data from the set, and divide different data in set by using comma
    while(true)
    {
        if(newstr[endPos++] == ',' || newstr[endPos] == '}')
        {
            newBufSet.insert(stoi(newstr.substr(beginPos, endPos - beginPos)));
            beginPos = endPos;
        }
        if('}' == newstr[endPos])
        {
            break;
        }
    }
    return endPos;
}


/*
 * Recursively figure out the epsilon closure set
 * @param newBufSet   the empty set to save transition information of each state
 * @param newStateNum   current state number
 */
void ConvertOperation::epsilonClosureSet(set<int> &newBufSet, int newStateNum)
{
    //check if the state that passed in function is the only state in current epsilon closure set
    if(newBufSet.find(newStateNum) != newBufSet.end())
    {
        return;
    }
    
    newBufSet.insert(newStateNum);
    set<int>::iterator myItera;
    set<int> tempSet = myNfa[newStateNum - 1].nfaSet;
    
    //recursion step
    for(myItera = tempSet.begin(); myItera != tempSet.end(); myItera++)
    {
        epsilonClosureSet(newBufSet, *myItera);
    }
    
}


/*
 * Print all values of a set
 * @param newSet   pass the set that we want to print
 */
void ConvertOperation::printSet(set<int> newSet)
{
    cout << "{";
    
    //returns an iterator referring to the first element in the set container
    set<int>::iterator myItera = newSet.begin();
    
    //print all elements until reaching the end position of a set
    while(myItera != newSet.end())
    {
        cout << *myItera++;
        if(myItera != newSet.end())
        {
            cout << ",";
        }
    }
    cout << "}";
}





