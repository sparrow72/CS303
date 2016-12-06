// Josh Gregory, Zach Theiss, Bricen Biehler
// CS 303 Project 3B
// Fall 2016
// Prof. Mohammad Kuhail


#ifndef _Morse_Code
#define _Morse_Code

#include<iostream>	//cin, cout functionality
#include<fstream>	//stream class to read and write from/to files
#include<string>	//for using type string
#include<map>		//for using map container object used for conversion
using namespace std;

struct tree {
	//Constructor with initializer list
	tree() { Left = nullptr; Right = nullptr; }

	string letter;		//alphabetical value
	string letterCode;	//Morse code value
	tree *Left, *Right;	//pointer to node's left child and right child
};						

class Morse_Code {
public:
	//Constructor
	Morse_Code();

	void insertNode(char tempLetter, string code);	//also populates maps
	string decode(string code);						//converts Morse Code dot/dash to alphabet letter
	string getLetter(string code);					//converts alphabet letter to Morse Code dash/dot
	string encode(string letter);					//returns alphabetical letter of code


private:
	tree *root;						//pointer to the root node of tree
	map<char, string> letterToCode;	//uses C++ map object to convert alphabet letter to Morse Code					
};

#endif 