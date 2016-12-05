#include "Morse_Code.h"

Morse_Code::Morse_Code()
{
	root = new tree;
	root->letter = "~NULL~";
	root->dotdash = "";
	root->Left = nullptr;// no nodes
	root->Right = nullptr;
}

void Morse_Code::insertNode(char tempLetter, string code) {
	letterToCode[tempLetter] = code;
	tree *currNode = root;// Pointer to a pointer to root
	for (int i = 0; i <= code.length(); i++)
	{
		if (code[i] == '.')
		{// left
			if (currNode->Left == nullptr)
			{// DNE
				currNode->Left = new tree;			// make it as empty node
				currNode = (currNode->Left);		// advance to dummy node
			}
			else {
				currNode = (currNode->Left);		// node exists lets go
			}
		}
		else if (code[i] == '-' || code[i] == '_') { // dash = navigate right
			if (currNode->Right == nullptr) {
				currNode->Right = new tree;
				currNode = (currNode->Right);			// go read the comments above
			}
			else {
				currNode = (currNode->Right);
			}
		}
	}

	currNode->dotdash = code;							// found the correct location
	currNode->letter = tempLetter;					// set dots and letters

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