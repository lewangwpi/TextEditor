//
//  editClass.hpp
//  edit
//
//  Created by Le Wang on 5/7/19.
//  Copyright © 2019 Le. All rights reserved.
//

#ifndef editClass_hpp
#define editClass_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <sstream>
#include <stack>
#include <map>

#include "opObj.hpp"

using namespace std;

class editClass{

public:
    editClass(); // Constructor 
    virtual ~editClass(); // Destructor
    /** Member functions */
    /** Insert a substring (subStr) at a position (pos) */
    string insertStr(string subStr, unsigned long pos);
	/** Append a substring at the end of text */
    string appendStr(string subStr);    
    /** Erase n characters (length) at a given position (pos) */
    string eraseStr(unsigned long pos, unsigned long length);
	/** Erase trailing n (length) characters */
    string eraseTrail(unsigned long length);
	/** Replace all occurrences of a substring (needle) by another (subStr) */
    string replaceStr(string needle, string subStr);         
	/** Undo operation*/
    string undoOP();
    /** Redo operation*/
    string redoOP();
    /** Load from TXT file */
    string openFile(string fname);    
	/** Save to TXT file */
    void saveFile(); // used if no file name is provided
    void saveFile(string fname); //used if file name is provided
	/** others */                    
    void newFile(); // create new file
    void displayTXT(); //display the content of text
    
private:
	/** Member variables */
    stack<opObj> undoBuff; // stack buffer for undo operations
    stack<opObj> redoBuff; // stack buffer for redo operations
    string content; // store text content
    map<string, int> catalog; // stores operation name and id for redo/undo

	/** Member functions */
	/** Insert string at specific position */
    void addStr (unsigned long pos, string str);
    /** Delete string at specific position */ 
    void deleteStr(unsigned long pos, unsigned long length);
    /** Replace needle by str */
    void replace(string needle, string str);
    /** Push operation object into stack */    
    void inStack(int whichStack, opObj OP);
    /** Pop operation object out of stack */
    opObj outStack(int whichStack);
    /** Generate operation object */
    opObj objGen(string action, vector<string> strParam, vector<unsigned long> numParam);
};

#endif /* editClass_hpp */
