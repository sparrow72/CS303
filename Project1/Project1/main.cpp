// Josh Gregory, Zach Theiss, and Alex Malko
// CS 303 Project 1
// Fall 2016
// Prof. Mohammad Kuhail

#include <iostream>
#include <string>
#include <list>
#include <iomanip>
#include <locale>
#include "Term.cpp"
using namespace std;

void mainMenu();
void fillList(list <Term> &lis);
void printList(const list <Term> &lis);
void addPoly(list<Term>& first, list<Term>& sec, list<Term>& third);
bool compare(const Term& first, const Term& second);

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
			addPoly(lis[0], lis[1], lis[2]);
			printList(lis[2]);//prints the list
			lis[0].clear();
			lis[1].clear();
			lis[2].clear();
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
	Term temp;
	string str, strNum;
	int exp, coeff;
	cout << "please enter the polynomial: ";
	cin >> str;

	while (!str.empty())
	{
		for (int i = 0; i < str.length(); i++)
		{
			// this code block will input the coefficient
			if (str[i] == '-')
			{
				++i;
				///while (isdigit(str[i]))
				while (str[i] == '0' || str[i] == '1' || str[i] == '2' || str[i] == '3' || str[i] == '4' || str[i] == '5' || str[i] == '6' || str[i] == '7' || str[i] == '8' || str[i] == '9')
				{
					strNum.push_back(str[i]);
					++i;
				}
				coeff = stoi(strNum);
				strNum.clear();
				temp.setCoefficient(-coeff);
			}
			else if (str[i] == '+')
			{
				++i;
				///while (isdigit(str[i]))
				while (str[i] == '0' || str[i] == '1' || str[i] == '2' || str[i] == '3' || str[i] == '4' || str[i] == '5' || str[i] == '6' || str[i] == '7' || str[i] == '8' || str[i] == '9')
				{
					strNum.push_back(str[i]);
					++i;
				}
				coeff = stoi(strNum);
				strNum.clear();
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
						///while (isdigit(str[i]))
						while (str[i] == '0' || str[i] == '1' || str[i] == '2' || str[i] == '3' || str[i] == '4' || str[i] == '5' || str[i] == '6' || str[i] == '7' || str[i] == '8' || str[i] == '9')
						{
							strNum.push_back(str[i]);
							++i;
						}
						exp = stoi(strNum);
						strNum.clear();
						temp.setExponent(-exp);
					}
					else if (isdigit(str[i]) || str[i] == '+')
					{
						++i;
						///while (isdigit(str[i]))
						while (str[i] == '0' || str[i] == '1' || str[i] == '2' || str[i] == '3' || str[i] == '4' || str[i] == '5' || str[i] == '6' || str[i] == '7' || str[i] == '8' || str[i] == '9')
						{
							strNum.push_back(str[i]);
							++i;
						}
						exp = stoi(strNum);
						strNum.clear();
						temp.setExponent(exp);
					}
				}
			}

			lis.push_back(temp);
			//destructor for temp
		}

	}

}

bool compare(const Term& first, const Term& second)
{

	if (first < second)
		return true;
	else if (first > second)
		return false;
	else
		return true;
}

void addPoly(list<Term>& first, list<Term>& sec, list<Term>& third)
{

	first.sort(compare);
	Term temp;
	list<Term>::iterator iter = first.begin();
	list<Term>::iterator iter2 = sec.begin();

	while (iter != first.end() || iter2 != sec.end())
	{
		if (*iter == *iter2)
		{
			temp = *iter + *iter2;
			third.push_back(temp);
		}
		else
		{
			third.push_back(*iter);
			third.push_back(*iter2);
		}
		++iter;
		++iter2;
	}
	first.sort(compare);
	sec.sort(compare);
	third.sort(compare);
	printList(third);

}

void printList(list<Term>& poly)
{
	poly.sort(compare);
	list<Term>::iterator iter = poly.begin();
	for (list<Term>::iterator iter = poly.begin(); iter != poly.end(); ++iter)
	{
		cout << *iter;
	}

	cout << '\n';
}


