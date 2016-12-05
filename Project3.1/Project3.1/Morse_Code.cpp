// Josh Gregory and Zach Theiss 
// CS 303 Project 3B
// Fall 2016
// Prof. Mohammad Kuhail

#include "Morse_Code.h"

Morse_Code::Morse_Code()
{
	root = new tree;
	root->letter = "~NULL~";
	root->letterCode = "";
	root->Left = nullptr;
	root->Right = nullptr;
}

void Morse_Code::insertNode(char tempLetter, string code)
{
	letterToCode[tempLetter] = code;
	tree *currNode = root;
	for (int i = 0; i <= code.length(); i++)
	{
		if (code[i] == '.')							// go left
		{
			if (currNode->Left == nullptr)				// DNE
			{
				currNode->Left = new tree;				// empty node
				currNode = (currNode->Left);
			}
			else
				currNode = (currNode->Left);			// node exists
		}
		else if (code[i] == '-' || code[i] == '_')	// go right
		{
			if (currNode->Right == nullptr)				// DNE
			{
				currNode->Right = new tree;				// empty node
				currNode = (currNode->Right);
			}
			else
				currNode = (currNode->Right);			// node exists
		}
	}

	currNode->letterCode = code;						// set dots and letters
	currNode->letter = tempLetter;

}

string Morse_Code::decode(string code)
{
	string decodedMSG = "";
	while (!code.empty())
	{
		string tempStr = code.substr(0, code.find(" "));
		decodedMSG += getLetter(tempStr);
		code.erase(0, code.find_first_of(" ") + 1);
	}
	return decodedMSG;
}

string Morse_Code::getLetter(string code)
{
	tree *currNode = root;
	for (int i = 0; i < code.length(); i++)
	{
		if (currNode == NULL)
			cerr << "Tree is empty";
		if (code[i] == '.')
			currNode = (currNode->Left);
		else
			currNode = (currNode->Right);
	}
	return currNode->letter;
}

string Morse_Code::encode(string  letter)
{
	string encodedMSG;
	for (int i = 0; i < letter.length(); ++i)
	{
		encodedMSG += letterToCode[letter[i]];
	}
	encodedMSG.pop_back();
	return string(encodedMSG);
}
