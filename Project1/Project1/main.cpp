// Alex Malko, Zach Theiss, and Josh Gregory
// CS 303 Project 1
// Fall 2016
// Prof. Mohammad Kuhail

#include <iostream>
#include <string>
#include <list>
#include <iomanip>
#include <locale>
#include "term.h"
using namespace std;

void fillList(list <Term> &lis);
void printList(const list <Term> &lis);
void mainMenu();

void main()
{
	mainMenu();

	string answer;
	bool loop = true;
	locale loc;

	do {
		cout << "\n\nDo you wish to try again? (Y/N): ";
		cin >> answer;
		string::size_type i = 0;
		switch (tolower(answer[i], loc))//will work even if the user enters something other than a char
		{
		case 'n':
			loop = false;
			break;
		case 'y':
			mainMenu();
			loop = true;
			break;
		default:
			cout << "\nInvalid, please try again";
			break;
		}
	} while (loop);

	system("pause");
}

void mainMenu() {


	bool loop = true;
	locale loc;
	string answer;
	list<Term>lis[2];

	do {
		cout << "\n Main Menu:\n";
		cout << "\tA. Enter first polynomial\n";
		cout << "\tB. Enter second polynomial\n";
		cout << "\tC. Add polynomials\n";
		cout << "\tD. Reset\n";
		cout << " Please select option A, B, C, or D: ";

		cin >> answer;

		string::size_type i = 0;
		switch (tolower(answer[i], loc))//will work even if the user enters something other than a char
		{
		case 'a':
			fillList(lis[0]);
			break;
		case 'b':
			fillList(lis[1]);
			break;
		case 'c':
			//addPolys();			
			printList(lis[2]);//prints the list
			//lis[2].clear();
			loop = false;
			break;
		case 'd':
			loop = false;
			break;
		default:
			cout << "Invalid optoin, please try agian\n\n";
			break;
		}
	} while (loop);
}

void fillList(list <Term> &lis)
{
	string str;
	Term ter[30];

	cout << "enter your polynomial:";
	cin >> str;
	for (int i = 0; i != str.size(); i++)//adds the string as char to the list
	{
		//add to term
        //Need to connect into the class, using poly1/2
	}
}

void printList(const list <Term> &lis)
{
	cout << "the sum of polynomials 1 and 2 is: ... \n";
    //Need to link into class using result list
	//loops through the list and outputs code
	//for (list<Term>::iterator iter = lis.begin(); iter != lis.end(); ++iter)
	//{
	//	//
	//}
}

