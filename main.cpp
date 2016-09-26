// Josh Gregory, Zach Theiss, and Alex Malko
// CS 303 Project 1
// Fall 2016
// Prof. Mohammad Kuhail

#include <iostream>
#include <string>
#include <list>
#include <iomanip>
#include <locale>
#include "Term.h"
using namespace std;

void mainMenu(); //Function definitions
void fillList(list <Term> &lis);
void printList(list <Term> &lis);
void addPoly(list<Term>& first, list<Term>& sec, list<Term>& third);
bool compare(const Term& first, const Term& second);

void main()
{

	mainMenu(); //Allow for input from user

	string answer;
	bool loop = true;
	locale loc;

	do {
		cout << "\n\nDo you wish to try again? (Y/N): ";
		cin >> answer; //Entering if they want to go again
		string::size_type i = 0;
		switch (tolower(answer[i], loc))//will work even if the user enters something other than a char
		{
		case 'n': //Do not go again
			loop = false;
			break;
		case 'y': //Go again
			mainMenu();
			loop = true;
			break;
		default: //Bad input
			cout << "\nInvalid, please try again";
			break;
		}
	} while (loop); //Start again

	system("pause");
}

void mainMenu() {

	bool loop = true;
	locale loc;
	string answer;
	list<Term>lis[2];

	do { //Start the menu options
		cout << "\n Main Menu:\n";
		cout << "\tA. Enter first polynomial\n";
		cout << "\tB. Enter second polynomial\n";
		cout << "\tC. Add polynomials\n";
		cout << "\tD. Reset\n";
		cout << " Please select option A, B, C, or D: ";

		cin >> answer;

		string::size_type i = 0;
		switch (tolower(answer[i], loc))//will work even if the user enters something other than a char
		{ //Puts the character to a lower format
		case 'a': //Entering the first polynomial
			fillList(lis[0]);
			break;
		case 'b': //Entering the second polynomial
			fillList(lis[1]);
			break;
		case 'c': //Adds the polynomials
			addPoly(lis[0], lis[1], lis[2]);
			printList(lis[2]);//prints the list
			lis[0].clear();
			lis[1].clear();
			lis[2].clear();
			loop = false;
			break;
		case 'd': //Reset the values
			loop = false;
			break;
		default: //Bad input
			cout << "Invalid optoin, please try agian\n\n";
			break;
		}
	} while (loop);
}

void fillList(list <Term> &lis)
{
	Term temp;
	string str, strNum;
	int exp, coeff;
	cout << "please enter the polynomial: ";
	cin >> str;
	temp.setCoefficient(0);
	temp.setExponent(0);
	for (int i = 0; i < str.length(); i++)
	{
		strNum = "0";
		exp = 0; coeff = 0;
		// this code block will input the coefficient
		if (str[i] == '-')
		{
			++i;
			while (isdigit(str[i]))
			{
				strNum.push_back(str[i]); //Add the number
				++i; //Increment the spot we are looking at
			}
			coeff = stoi(strNum); //Set the Coeff
			strNum.clear();
			temp.setCoefficient(-coeff); //Set the Negative Coeff
		}
		else if (str[i] == '+')
		{
			++i;
			while (isdigit(str[i]))
			{
				strNum.push_back(str[i]); //Add the number
				++i; //Increment 
			}
			coeff = stoi(strNum); //Set coeff
			strNum.clear();
			temp.setCoefficient(coeff); //Save the coeff to class obj
		}
		else if (isdigit(str[i]))
		{
			while (isdigit(str[i]))
			{
				strNum.push_back(str[i]); //Add the number
				++i; //Increment 
			}
			coeff = stoi(strNum); //Set coeff
			strNum.clear();
			temp.setCoefficient(coeff); //Save the coeff to class obj
		}
		else
		{
			//the user entered x with an assumed coefficient of 1
			coeff = 1;
			temp.setCoefficient(coeff);
		}

		//this code block will input the exponent
		if (tolower(str[i]) == 'x')
		{
			//'skip' do not input
			++i;
			if (str[i] == '^')
			{
				//'skip' do not input
				++i;
				if (str[i] == '-')
				{
					++i;
					while (isdigit(str[i]))
					{ //Check if the integer is larger than one digit
						strNum.push_back(str[i]);
						++i;
					}
					exp = stoi(strNum); //Save the exponent
					strNum.clear();
					temp.setExponent(-exp); //Save as a negative exp
				}
				else if (str[i] == '+')
				{
					++i;
					while (isdigit(str[i]))
					{
						strNum.push_back(str[i]); //Push back the int to the list
						++i;
					}
					exp = stoi(strNum); //Save the Exp
					strNum.clear();
					temp.setExponent(exp); //Save the pos exp to the class obj
				}
				else if (isdigit(str[i]))
				{
					while (isdigit(str[i]))
					{
						strNum.push_back(str[i]); //Push back the int to the list
						++i;
					}
					exp = stoi(strNum); //Save the Exp
					strNum.clear();
					temp.setExponent(exp); //Save the pos exp to the class obj
				}
			}
			else
			{
				//the user entered x with an assumed exponent of 1
				exp = 1;
				temp.setExponent(exp);
			}
		}
		lis.push_back(temp);
	}
	///TEST OUTPUT AND SORT... DEL BEFORE WE SUBMIT
	printList(lis); //Output the final answer
}

bool compare(const Term& first, const Term& second)
{

	if (first < second) //Compare the terms first poly to second
		return true;
	else if (first > second) //Compare second term to first
		return false;
	else //Everything else
		return true;
}

void addPoly(list<Term>& first, list<Term>& sec, list<Term>& third)
{

	first.sort(compare); //Sort the list and compare
	sec.sort(compare);
	Term temp, temp2;
	list<Term>::iterator iter = first.begin(); //Create an itr
	list<Term>::iterator iter2 = sec.begin(); //Create a second itr

	while (iter != first.end() || iter2 != sec.end())
	{ //Go until reaching the end
		if (*iter == *iter2) //Compare if itr values are equal
		{
			temp = *iter + *iter2; //Set a value of the values combined
			third.push_back(temp); //At the temp to the final answer
		}
		else
		{ 
			temp = *iter;
			third.push_back(temp); //Add to the final term
			temp2 = *iter2;
			third.push_back(temp2); //Add to the final term
		}
		++iter; //Increment
		++iter2; //Increment
	}
	printList(third); //Output the final answer

}

void printList(list<Term>& poly)
{
	poly.sort(compare);		
	for (list<Term>::iterator iter = poly.begin(); iter != poly.end(); iter++)
	{
		if (iter==poly.begin())
		(*iter).setIsfirst(true);

		cout << *iter; //Output the value at the interator
	}

	cout << '\n'; //Newline
}