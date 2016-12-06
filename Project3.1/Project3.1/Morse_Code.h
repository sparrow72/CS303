// Josh Gregory, Zach Theiss, Bricen Biehler
// CS 303 Project 3B
// Fall 2016
// Prof. Mohammad Kuhail

#ifndef _Morse_Code
#define _Morse_Code

#include<iostream> //cin, cout functionality
#include<fstream> //stream class to read and write from/to files
#include<string> //for using type string
#include<map> //for using map container object used for conversion
#include<vector>//for using vector object

using namespace std;

struct tree 
{
	//Constructor with initializer list
	tree() { Left = nullptr; Right = nullptr; }
	
	string letter; //alphabetical value
	string dotdash; //Morse code value
	tree *Left; //pointer to node's left child
	tree *Right; //pointer to node's right child
};

class Morse_Code {
public:
	//Constructor
	Morse_Code();

	void insertNode(char letter, string letterDotdash); //also populates maps
	string decode(string code); //converts Morse Code dot/dash to alphabet letter
	string encode(string letter); //converts alphabet letter to Morse Code dash/dot

	//Accessor
	string getLetter(string code); //returns alphabetical letter of code
	

private:
	tree *root; //pointer to the root node of tree
	map<char, string> letterToCode; //uses C++ map object to convert alphabet letter to Morse Code
};

#endif 