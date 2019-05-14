//
//  editClass.cpp
//  edit
//
//  Created by Le Wang on 5/7/19.
//  Copyright © 2019 Le. All rights reserved.
//

#include "editClass.hpp"
/*********************** Start: Public Member Functions ******************************/
editClass::editClass(){
    this->openFile("a.txt");
    this->catalog["insertStr"] = 1;
    this->catalog["appendStr"] = 2;
    this->catalog["eraseStr"] = 3;
    this->catalog["eraseTrail"] = 4;
    this->catalog["replaceStr"] = 5;    
}

editClass::~editClass(){ }

string editClass::insertStr(string str, unsigned long pos) {
	if (pos > this->content.size()){
		throw invalid_argument("Error(insertStr): Position index should be less than content size.");
	}
	
    int bufferType = 0;
    string action = "insertStr";
    vector<unsigned long> nParam;
    nParam.push_back(pos);
    vector<string> sParam;
    sParam.push_back(str);
    opObj OP = objGen(action, sParam, nParam);
    inStack(bufferType, OP);
    addStr(pos, str);
    return this->content;
}

string editClass::appendStr(string str){
    int bufferType = 0;
    string action = "appendStr";
    vector<unsigned long> nParam;
    nParam.push_back(this->content.size() - 1);
    vector<string> sParam;
    sParam.push_back(str);
    opObj OP = objGen(action, sParam, nParam);
    inStack(bufferType, OP);
    addStr(this->content.size() - 1, str);
    return this->content;
}

string editClass::eraseStr(unsigned long pos, unsigned long length){
	if (pos > this->content.size()){
		throw invalid_argument("Error(eraseStr): Position index should be less than content size.");
	}
    string str = this->content.substr(pos,length);
    int bufferType = 0;
    string action = "eraseStr";
    vector<unsigned long> nParam;
    nParam.push_back(pos);
    vector<string> sParam;
    sParam.push_back(str);
    opObj OP = objGen(action, sParam, nParam);
    inStack(bufferType, OP);
    deleteStr(pos, length);
    return this->content;
}

string editClass::eraseTrail(unsigned long length){
	if (length > this->content.size()){
		throw invalid_argument("Error(eraseTrail): Length should be less than content size.");
	}
    unsigned long pos = this->content.size() - 1 - length;
    string str = this->content.substr(pos,length);
    int bufferType = 0;
    string action = "eraseTrail";
    vector<unsigned long> nParam;
    vector<string> sParam;
    sParam.push_back(str);
    opObj OP = objGen(action, sParam, nParam);
    inStack(bufferType, OP);
    deleteStr(pos, length);
	return this->content;
}


string editClass::replaceStr(string needle, string str){
	if (needle.size()<=0) {
		throw invalid_argument("Error(replaceStr): target string cannot be empty.");
	}
    int bufferType = 0;
    string action = "replaceStr";
    vector<unsigned long> nParam;
    vector<string> sParam;
    sParam.push_back(needle);
    sParam.push_back(str);        
    opObj OP = objGen(action, sParam, nParam);
    inStack(bufferType, OP);
    replace(needle, str);
	return this->content;
}

// undo operation  and  redo operation
string editClass::undoOP(){
    int whichStack = 1;
    opObj op = outStack(whichStack);
    inStack(whichStack, op);
    string action = op.opName;
    
    switch (this->catalog[action]) {
        case 1: //undo insert
        {
            unsigned long pos = op.numParam.back();
            string s = op.strParam.back();
            unsigned long len = s.size();
            deleteStr(pos, len);
            break;
        }
        case 2: //undo append
        {
            unsigned long pos = op.numParam.back();
            string s = op.strParam.back();
            unsigned long len = s.size();
            deleteStr(pos, len);
            break;
        }
        case 3: // undo erase
        {
            unsigned long pos = op.numParam.back();
            string str = op.strParam.back();
            addStr(pos, str);
            break;
        }
        case 4: // undo erase trailling
        {
            unsigned long pos = this->content.size()-1;
            string str = op.strParam.back();
            addStr(pos, str);
            break;
        }
        case 5: // undo replace
        {
            string needle = op.strParam.back();
            op.strParam.pop_back();
            string str = op.strParam.back();
            replace(needle, str);
            break;
        }
        default:
            break;
    }
    return this->content;
}

string editClass::redoOP(){
    int whichStack = 0;
    opObj op = outStack(whichStack);
    inStack(whichStack, op);
    string action = op.opName;
    
    switch (this->catalog[action]) {
        case 1: //redo insert
        {
            unsigned long pos = op.numParam.back();
            string s = op.strParam.back();
            this->content = this->content.insert(pos,s);
            break;
        }
        case 2: //redo append
        {
            unsigned long pos = op.numParam.back();
            string s = op.strParam.back();
            
            this->content = this->content.insert(pos,s);
            break;
        }
        case 3: // redo erase
        {
            unsigned long pos = op.numParam.back();
            string subStr = op.strParam.back();
            unsigned long length = subStr.size();
            this->content = this->content.erase(pos,length);
            break;
        }
        case 4: // redo erase trailling
        {
            string subStr = op.strParam.back();
            unsigned long length = subStr.size();
            unsigned long pos = this->content.size()-1-length;
            this->content = this->content.erase(pos,length);
            break;
        }
        case 5: // redo replace
        {
            string needle = op.strParam.back();
            op.strParam.pop_back();
            string subStr = op.strParam.back();
            swap(needle, subStr);
            while (this->content.find(needle) != -1){
                unsigned long pos = this->content.find(needle);
                unsigned long len = needle.length();
                this->content.replace(pos, len, subStr);
            }
            break;
        }
        default:
            break;
    }
    return this->content;
}

string editClass::openFile(string fname){
    ifstream infile(fname);
	if (infile.good()) {
		infile.open(fname, ios::in);
		stringstream buf;
		buf << infile.rdbuf();
		this->content = buf.str();
		infile.close();
	} else {
		throw invalid_argument ("File does not exist");
	}
	return this->content;
}

void editClass::saveFile(){
    char fname[100];
    cout << " input file name: " << endl;
    cin.getline(fname, 100);
    ofstream outfile;
    outfile.open(fname);
    outfile<<this->content<<endl;
    outfile.close();
}

void editClass::saveFile(string fname){
    ofstream outfile;
    outfile.open(fname);
    outfile<<this->content<<endl;
    outfile.close();
	ifstream infile(fname);
	if (infile.good()) {
		cout << "Save to file \"" << fname << "\" successfully" << endl;
	} else {	
		throw invalid_argument ("File not saved.");
	}
}

/** others */
void editClass::newFile(){
    cout << " Input file name : " ;
    char fname[100];
    cin.getline(fname, 100);
    string str;
    getline(cin, str);
    ofstream outfile;
    outfile.open(fname);
    outfile<<str<<endl;
    outfile.close();
}

void editClass::displayTXT() {
	cout << this->content;   
}
/*************************** End: Public Member Functions ****************************/

/*************************** Start: Private Member Functions *************************/
void editClass::addStr(unsigned long pos, string str) {
    this->content = this->content.insert(pos,str);
}

void editClass::deleteStr(unsigned long pos, unsigned long length) {
    this->content = this->content.erase(pos, length);
}

void editClass::replace(string needle, string str) {
    while (this->content.find(needle) != -1){
        unsigned long pos = this->content.find(needle);
        unsigned long len = needle.length();
        this->content.replace(pos, len, str);
    }
}

opObj editClass::objGen(string action, vector<string> strParam, vector<unsigned long> numParam) {
    opObj OP(action);
    OP.numParam = numParam;
    OP.strParam = strParam;
    return OP;
}

void editClass::inStack(int whichStack, opObj OP){
    switch (whichStack) {
		case 0: //undo
		        this->undoBuff.push(OP);
		        break;
		case 1: //redo
		        this->redoBuff.push(OP);
		        break;
		default:
		        break;
    }
}

opObj editClass::outStack(int whichStack) {
    opObj op;
    switch (whichStack) {
        case 0: //redo
        	if (redoBuff.size() > 0) {
        		op = this->redoBuff.top();
		        this->redoBuff.pop();
		        break;
        	} else {
        		throw invalid_argument("Error(redoBuff): target buffer is empty.");
        	}                    
        case 1: //undo
        {
			if (undoBuff.size() > 0) {
				op = this->undoBuff.top();
		        this->undoBuff.pop();
		        break;			
			} else {
        		throw invalid_argument("Error(undoBuff): target buffer is empty.");
        	}            
        }            
        default:
            break;
    }
    return op;
}
/*************************** End: Private Member Functions ***************************/


