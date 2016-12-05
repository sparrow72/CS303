// Josh Gregory and Zach Theiss
// CS 303 Project 3B
// Fall 2016
// Prof. Mohammad Kuhail

#ifndef _Morse_Code
#define _Morse_Code

#include<iostream>
#include<fstream>
#include<string>
#include<map>
using namespace std;

struct tree {
	tree() { Left = nullptr; Right = nullptr; }
	string letter;
	string letterCode;
	tree *Left, *Right;
};

class Morse_Code {
public:
	Morse_Code();
	void insertNode(char letter, string letterDotdash); // populates map and creates tree
	string decode(string code);							// returns the letter value of code
	string getLetter(string code);						
	string encode(string letter);						// returns the code value of letters
	

private:
	tree *root;
	map<char, string> letterToCode;						// maps the letter to the code value
};

#endif 