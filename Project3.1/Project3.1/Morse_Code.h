#ifndef _Morse_Code
#define _Morse_Code

#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<vector>


using namespace std;

struct tree {
	tree() { Left = nullptr; Right = nullptr; }
	string letter;
	string dotdash;
	tree *Left, *Right;
};

class Morse_Code {
public:
	Morse_Code();
	void insertNode(char letter, string letterDotdash); // also populates maps
	string getLetter(string code); //returns letter value of code
	string decode(string code); //dot dash to letter
	string encode(string letter); //letter to dash dot
	

private:
	tree *root;
	map<char, string> letterToCode; // For encode function
};

#endif 