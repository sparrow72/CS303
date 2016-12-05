// Josh Gregory and Zach Theiss
// CS 303 Project 3B
// Fall 2016
// Prof. Mohammad Kuhail

#include<iostream>
#include<fstream>
#include "Morse_Code.h"

using namespace std;

void makeTree(Morse_Code&);
void output(Morse_Code&);

int main()
{
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
	{
		fin >> line;

		for (int i = 0; i <= line.size(); ++i)
		{
			if (isalnum(line[i]))
				letter = line[i];
			else
				code += line[i];
		}
		MorseCode.insertNode(letter, code);	//builds tree and populates maps
		code = "";							//clear code after each iteration
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
}
