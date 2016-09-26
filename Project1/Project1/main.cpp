// Josh Gregory, Zach Theiss, and Alex Malko
// CS 303 Project 1
// Fall 2016
// Prof. Mohammad Kuhail

#include <iostream> //Allows for in and output
#include <string> //Allows for use of strings
#include <list> //Allows for use of lists
#include <locale> //Menu functionality
#include "Term.h" //Include the Term Class
using namespace std; //Use the C++ standard namespace

void mainMenu(); //Function Declerations
void fillList(list <Term> &lis); //Function Declerations
void printList(list <Term> &lis); //Function Declerations
void addPoly(list<Term> &first, list<Term> &sec, list<Term> &third); //Function Declerations
bool compare(const Term &first, const Term &second); //Function Declerations

void main()
{
    mainMenu(); //Allow for input from user

    string answer; //User input variable
    bool loop = true; //Set loop to start
    locale loc; //Using locale file

    do { //Ask to restart the menu
        cout << "\n\nDo you wish to try again? (Y/N): "; //
        cin >> answer; //Entering if they want to go again
        string::size_type i = 0; //Takes the first char of the string
        switch (tolower(answer[i], loc))//will work even if the user enters something other than a char
        {
        case 'n': //Do not go again
            loop = false; //End the loop
            break; //End the case
        case 'y': //Go again
            mainMenu(); //Rerun the menu
            loop = true; //Start the loop again
            break; //End the case
        default: //Bad input
            cout << "\nInvalid, please try again"; //Bad input
            break; //End the case
        }
    } while (loop); //Start again

}

void mainMenu() 
{
    bool loop = true; //Set loop to true to start 
    locale loc; //Using locale file
    string answer; //User Input
    list<Term>lis[3]; //Create 3 lists

    do { //Start the menu options
        cout << "\n Main Menu:\n";
        cout << "\tA. Enter first polynomial\n";
        cout << "\tB. Enter second polynomial\n";
        cout << "\tC. Add polynomials\n";
        cout << "\tD. Reset\n";
        cout << " Please select option A, B, C, or D: ";

        cin >> answer; //Accept input from the user

        string::size_type i = 0; //Takes the first char of the string
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
        temp.setCoefficient(0);
        temp.setExponent(0);
        
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

        if (tolower(str[i]) == 'x') 
        {
            ++i;
            if (str[i] == '^')
            {
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
					--i;
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
					--i;
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
                    --i;
                }
            }

            else
            {
                //the user entered x with an assumed exponent of 1
                exp = 1;
                temp.setExponent(exp);
				--i;
            }
        }
        lis.push_back(temp);
    }
    ///TEST OUTPUT AND SORT... DEL BEFORE WE SUBMIT
    printList(lis); //Output the final answer
}

bool compare(const Term &first, const Term &second)
{
    if (first < second) //Compare the terms first poly to second
        return true;
    else if (first > second) //Compare second term to first
        return false;
    else //Everything else
        return true;
}

void addPoly(list<Term> &first, list<Term> &sec, list<Term> &third)
{
    first.sort(); //Sort the list
    first.reverse(); //Put the highest term in front
    sec.sort(); //Sort the list
    sec.reverse(); //Put the highest term in front
    Term temp, temp2; //Create to temporary terms objects
    list<Term>::iterator iter = first.begin(); //Create an itr
    list<Term>::iterator iter2 = sec.begin(); //Create a second itr

    while (iter != first.end())
    { //Go until reaching the end
        if (*iter == *iter2) //Compare if itr values are equal
        {
            temp = *iter + *iter2; //Set a value of the values combined
            third.push_back(temp); //At the temp to the final answer
        }
        else
        {
            third.push_back(*iter); //Add to the final term
            third.push_back(*iter2); //Add to the final term
        }
        ++iter; //Increment
        ++iter2; //Increment
    }
    while (iter2 != sec.end())
    { //Go until reaching the end
        third.push_back(*iter2); //Add to the final term
        ++iter2; //Increment
    }
	for (list<Term>::iterator iter3 = third.begin(); iter3 != third.end(); ++iter3)
	{
		for (list<Term>::iterator iter4 = third.begin(); iter4 != third.end(); ++iter4)
		{
			if (*iter3 == *iter4) //Compare if itr values are equal
			{
				temp = *iter3 + *iter4; //Set a value of the values combined
				third.push_back(temp); //At the temp to the final answer
				if (*iter3 != *iter4)
				{
					third.remove(*iter3);
					third.remove(*iter4);
				}
				else
					third.remove(*iter3);
			}
		}
	}
    printList(third); //Output the final answer
}

void printList(list<Term>& poly)
{
    poly.sort(); //Sort the list
    poly.reverse(); //Put the largest term in front
    for (list<Term>::iterator iter = poly.begin(); iter != poly.end(); iter++)
    { //Set the iterator to front and begin parsing through
        if (iter == poly.begin()) //If the iterator is at the start
            (*iter).setIsfirst(true); //Set the first term to true
        else if (iter != poly.begin()) //If the iter is not at the start
        {
            (*iter).setIsfirst(false); //
        }

        cout << *iter; //Output the value at the interator
    }
    cout << '\n'; //Newline
}