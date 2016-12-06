<<<<<<< HEAD
// Josh Gregory and Zach Theiss
=======
// Josh Gregory, Zach Theiss, Bricen Biehler
>>>>>>> refs/remotes/origin/addComment
// CS 303 Project 3B
// Fall 2016
// Prof. Mohammad Kuhail

<<<<<<< HEAD
#include<iostream>
#include<fstream>
#include "Morse_Code.h"
=======
#include<iostream> //cin, cout functionality
#include<fstream> //stream class to read and write from/to files
#include "Morse_Code.h" //included header file
>>>>>>> refs/remotes/origin/addComment

using namespace std;

void makeTree(Morse_Code&);
void output(Morse_Code&);

int main()
{
<<<<<<< HEAD
	Morse_Code MorseCode;

	makeTree(MorseCode);
	output(MorseCode);

	system("pause");
	return 0;
}

void makeTree(Morse_Code& MorseCode)
{
	ifstream fin("morse.txt");
	string code, line, temp;
	char letter;

	while (fin.good())						//while input is still good
=======
	ifstream fin("morse.txt"); //reads in text file that contains letter and it's Morse Code equivalent
	Morse_Code MorseCode;
	string code; //Morse Code dot/dash characters 
	string line; //characters in a single line of text
	string temp; //temp storage used for conversion
	char letter; //alphabet letter

	while (fin.good()) //while there is available data to read from file
>>>>>>> refs/remotes/origin/addComment
	{
		fin >> line; //reads in the line from text file

		for (int i = 0; i <= line.size(); ++i) //iterates through characters in text line
		{
<<<<<<< HEAD
			if (isalnum(line[i]))
				letter = line[i];
			else
				code += line[i];
		}
		MorseCode.insertNode(letter, code);	//builds tree and populates maps
		code = "";							//clear code after each iteration
=======
			if (isalnum(line[i])) //determines if this is a letter value
				letter = line[i]; //store character
			else //get the rest of the characters from the line
				code += line[i];
		}
		MorseCode.insertNode(letter, code); //builds the tree and populates maps
		code = ""; //clears the code after each iteration
>>>>>>> refs/remotes/origin/addComment
	}

	fin.close();
}

void output(Morse_Code& MorseCode)
{
	//ofstream fout("output.txt");

	cout << "helloworld\n" << MorseCode.decode(".... . ._.. ._.. ___ .__ ___ ._. ._.. _.. ") << endl;
	cout << ".... . ._.. ._.. ___ .__ ___ ._. ._.. _.. \n" << MorseCode.encode("helloworld") << endl;
	//fout << "helloworld\n" << MorseCode.decode("...._ ._ ._.._ ._.._ ____ .___ ____ ._._ ._.._ _.._ ") << endl;
	//fout << ".... . ._.. ._.. ___ .__ ___ ._. ._.. _.. \n" << MorseCode.encode("helloworld") << endl;

	//fout.close();
<<<<<<< HEAD
}
=======
	fin.close(); //closes input stream
	system("pause"); //for testing
	return 0;
}
>>>>>>> refs/remotes/origin/addComment
