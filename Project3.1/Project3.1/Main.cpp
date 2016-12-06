// Josh Gregory, Zach Theiss, Bricen Biehler
// CS 303 Project 3B
// Fall 2016
// Prof. Mohammad Kuhail

#include<iostream> //cin, cout functionality
#include<fstream> //stream class to read and write from/to files
#include "Morse_Code.h" //included header file

using namespace std;

int main()
{
	ifstream fin("morse.txt"); //reads in text file that contains letter and it's Morse Code equivalent
	Morse_Code MorseCode;
	string code; //Morse Code dot/dash characters 
	string line; //characters in a single line of text
	string temp; //temp storage used for conversion
	char letter; //alphabet letter

	while (fin.good()) //while there is available data to read from file
	{
		fin >> line; //reads in the line from text file

		for (int i = 0; i <= line.size(); ++i) //iterates through characters in text line
		{
			if (isalnum(line[i])) //determines if this is a letter value
				letter = line[i]; //store character
			else //get the rest of the characters from the line
				code += line[i];
		}
		MorseCode.insertNode(letter, code); //builds the tree and populates maps
		code = ""; //clears the code after each iteration
	}

	//currently test strings
	//change the string to test for different outcomes
	//ofstream fout("output.txt");
	cout <<"helloworld" << endl;
	cout << MorseCode.decode(".... . ._.. ._.. ___ .__ ___ ._. ._.. _.. ") << endl;
	cout << ".... . ._.. ._.. ___ .__ ___ ._. ._.. _.. " << endl;
	cout << MorseCode.encode("helloworld") << endl;
	
	//fout << MorseCode.encode("helloworld") << endl;
	//fout << MorseCode.decode("...._ ._ ._.._ ._.._ ____ .___ ____ ._._ ._.._ _.._ ") << endl;
	//fout.close();
	fin.close(); //closes input stream
	system("pause"); //for testing
	return 0;
}