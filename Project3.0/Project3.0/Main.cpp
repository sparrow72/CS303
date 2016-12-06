// Josh Gregory, Zach Theiss, Bricen Biehler
// CS 303 Project 3B
// Fall 2016
// Prof. Mohammad Kuhail

#include<iostream>			//cin, cout functionality
#include<fstream>			//stream class to read and write from/to files
#include "Morse_Code.h"		//included header file

using namespace std;

void makeTree(Morse_Code&);
void output(Morse_Code&);

int main()
{
	Morse_Code MorseCode;	//makes new MorseCode of class Morse_Code

	makeTree(MorseCode);	//makes the tree from the morse text document
	output(MorseCode);		//outputs the decoded and encoded msg

	system("pause");	
	return 0;
}

void makeTree(Morse_Code& MorseCode)
{
	ifstream fin("morse.txt");	//reads in text file that contains letter and it's Morse Code equivalent
	string code, line, temp;	//Morse Code dot/dash characters, characters in a single line of text, temp storage used for conversion
	char letter;				//alphabet letter
			
	while (fin.good())			//while there is available data to read from file
	{
		fin >> line;							//reads in the line from text file

		for (int i = 0; i <= line.size(); ++i)	//iterates through characters in text line
		{
			if (isalnum(line[i]))				//determines if this is a letter value
				letter = line[i];				//store character
			else								//get the rest of the characters from the line
				code += line[i];
		}
		MorseCode.insertNode(letter, code);		//builds the tree and populates maps	
		code = "";								//clears the code after each iteration	
	}

	fin.close();								//closes input stream
}

void output(Morse_Code& MorseCode)
{
	//currently test strings, change the string to test for different outcomes
	///NOTE: decode must end in a space to work
	cout << "helloworld\n" << MorseCode.decode(".... . ._.. ._.. ___ .__ ___ ._. ._.. _.. ") << endl;
	cout << ".... . ._.. ._.. ___ .__ ___ ._. ._.. _.. \n" << MorseCode.encode("helloworld") << endl;
}