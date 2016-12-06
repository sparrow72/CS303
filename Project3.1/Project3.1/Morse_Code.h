<<<<<<< HEAD
// Josh Gregory and Zach Theiss
=======
// Josh Gregory, Zach Theiss, Bricen Biehler
>>>>>>> refs/remotes/origin/addComment
// CS 303 Project 3B
// Fall 2016
// Prof. Mohammad Kuhail

#ifndef _Morse_Code
#define _Morse_Code

<<<<<<< HEAD
#include<iostream>
#include<fstream>
#include<string>
#include<map>
=======
#include<iostream> //cin, cout functionality
#include<fstream> //stream class to read and write from/to files
#include<string> //for using type string
#include<map> //for using map container object used for conversion
#include<vector>//for using vector object

>>>>>>> refs/remotes/origin/addComment
using namespace std;

struct tree 
{
	//Constructor with initializer list
	tree() { Left = nullptr; Right = nullptr; }
<<<<<<< HEAD
	string letter;
	string letterCode;
	tree *Left, *Right;
=======
	
	string letter; //alphabetical value
	string dotdash; //Morse code value
	tree *Left; //pointer to node's left child
	tree *Right; //pointer to node's right child
>>>>>>> refs/remotes/origin/addComment
};

class Morse_Code {
public:
	//Constructor
	Morse_Code();
<<<<<<< HEAD
	void insertNode(char letter, string letterDotdash); // populates map and creates tree
	string decode(string code);							// returns the letter value of code
	string getLetter(string code);						
	string encode(string letter);						// returns the code value of letters
	

private:
	tree *root;
	map<char, string> letterToCode;						// maps the letter to the code value
=======

	void insertNode(char letter, string letterDotdash); //also populates maps
	string decode(string code); //converts Morse Code dot/dash to alphabet letter
	string encode(string letter); //converts alphabet letter to Morse Code dash/dot

	//Accessor
	string getLetter(string code); //returns alphabetical letter of code
	

private:
	tree *root; //pointer to the root node of tree
	map<char, string> letterToCode; //uses C++ map object to convert alphabet letter to Morse Code
>>>>>>> refs/remotes/origin/addComment
};

#endif 