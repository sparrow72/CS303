// Josh Gregory, Zach Theiss, Bricen Biehler
// CS 303 Project 3B
// Fall 2016
// Prof. Mohammad Kuhail

#include "Morse_Code.h" //include Morse_Code header file

Morse_Code::Morse_Code()
{
	root = new tree; //initializes a new tree
	root->letter = "~NULL~"; //root's letter data field set to '~NULL~'
	root->dotdash = ""; //root's dot/dash data
	root->Left = nullptr; //root's left child is empty
	root->Right = nullptr; //root's right child is empty
}

//Method inserts a node into a binary tree
void Morse_Code::insertNode(char tempLetter, string code) {
	letterToCode[tempLetter] = code;
	tree *currNode = root; //Pointer to a pointer to root node
	for (int i = 0; i <= code.length(); i++) //iterate through characters in code 
	{
		if (code[i] == '.') {//dot then navigate to left child
		
			if (currNode->Left == nullptr){ //left child does not exist
				currNode->Left = new tree; //sets left child to new empty node
				currNode = (currNode->Left); //advance to dummy node
			}
			else {
				currNode = (currNode->Left); //node exists, continue
			}
		}
		else if (code[i] == '-' || code[i] == '_') { //dash then navigate to right child
			if (currNode->Right == nullptr) { //right child does not exist
				currNode->Right = new tree; //sets right child to new empty node
				currNode = (currNode->Right); ////advance to dummy node
			}
			else {
				currNode = (currNode->Right); //node exists, continue
			}
		}
	}

	currNode->dotdash = code; //found the correct location
	currNode->letter = tempLetter; //set dots and letters

}

//Converts message in Morse Code to alphabet letters
string Morse_Code::decode(string code)
{
	string decodedMSG = ""; //initialized to empty string
	while (!code.empty()) //while string code is not empty
	{
		string tempStr = code.substr(0, code.find(" "));
		decodedMSG += getLetter(tempStr);
		code.erase(0, code.find_first_of(" ") + 1);
	}
	return decodedMSG; //returns message in letters
}

//returns alphabetical letter of code
string Morse_Code::getLetter(string code)
{
	tree *currNode = root; //starts traversal at root node
	for (int i = 0; i < code.length(); i++) //iterates throught characters in code
	{
		if (currNode == NULL) //when current node is null
			cerr << "Tree is empty"; //message output
		if (code[i] == '.') //if dot character
			currNode = (currNode->Left); //traverse to current node's left child
		else
			currNode = (currNode->Right); //traverse to current node's right child
	}
	return currNode->letter; //returns the letter data field of the current node
}

//Message in alphabet letters are converted to Morse Code dot/dash
string Morse_Code::encode(string letter)
{
	string encodedMSG; //message we wish to encode
	for (int i = 0; i < letter.length(); ++i) //iter
	{
		encodedMSG += letterToCode[letter[i]]; //conversion
	}
	encodedMSG.pop_back(); //pops character in the string vector
	return string(encodedMSG); //returns the encoded message
}