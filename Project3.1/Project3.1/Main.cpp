#include<iostream>
#include<fstream>
#include "Morse_Code.h"

using namespace std;

int main()
{
	ifstream fin("morse.txt");
	Morse_Code MorseCode;
	string code, line, temp;
	char letter;

	while (fin.good())//while there is data to read
	{
		fin >> line;

		for (int i = 0; i <= line.size(); ++i)
		{
			if (isalnum(line[i]))//determine if is a letter value
				letter = line[i];
			else//get the rest of the info from the line
				code += line[i];
		}
		MorseCode.insertNode(letter, code);//buiilds tree and populates maps
		code = "";//clear code after each iteration
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
	fin.close();
	system("pause");
	return 0;
}