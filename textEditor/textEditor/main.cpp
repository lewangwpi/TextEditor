#include <iostream>
#include <map>
#include "editClass.hpp"
#include "opObj.hpp"

using namespace std;

int main() {
	editClass textEditor;
	string filename = "a.txt";
	string sstr = "ABC";
	string ndlStr = "o";
	string rplStr = "O";
	int pos = 2;	
	int length = 3;
	map <int, string> m;
	m[0] = "append string";
	m[1] = "insert string";
	m[2] = "erase string";
	m[3] = "erase trail";
	m[4] = "replace string";	
		
	string text = textEditor.openFile(filename);
	cout << "Load file \"" << filename << "\" original text --> ";
	textEditor.displayTXT();
	cout << endl;	
	text = textEditor.appendStr(sstr);
	cout << "Append string \"" << sstr << "\" --> ";
	textEditor.displayTXT();
	
	text = textEditor.insertStr(sstr, pos);
	cout << "Insert string \"" << sstr << "\" at position " << pos << " --> ";
	textEditor.displayTXT();	
	
	text = textEditor.eraseStr(pos,length);
	cout << "Erase " << length << " letters at position " << pos << " --> ";
	textEditor.displayTXT();
	
	text = textEditor.eraseTrail(length);
	cout << "Erase " << length << " letters at trail --> ";
	textEditor.displayTXT();
	
	text = textEditor.replaceStr(ndlStr, rplStr);
	cout << "Replace " << ndlStr << " to " << rplStr << " --> "; 
	textEditor.displayTXT();
	cout << endl;
	
	for (int i = 0; i < 5; i++ ) {
		cout << "Undo " << m[4 - i] << " --> ";
		text = textEditor.undoOP();
		textEditor.displayTXT();
	}
	cout << endl;
	for (int j = 0; j < 5; j++) {
		cout << "Redo " << m[j] << " --> ";
		text = textEditor.redoOP();
		textEditor.displayTXT();
	}
	
	cout << endl;
	textEditor.saveFile("b.txt");
	return 0;
}
