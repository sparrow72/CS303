#pragma once
// Josh Gregory, Zach Theiss, and Alex Malko
// CS 303 Project 1
// Fall 2016
// Prof. Mohammad Kuhail
#include <iostream>
#include <list>
#include <string>
using namespace std;

class Term {
public:
	Term(int new_coefficient=1, int new_exponent = 1); //Example can be found in List Header on BBoard
	
    void setCoefficient(int new_coefficient = 1); //Mutators
    void setExponent(int new_exponent = 1);

    int getCoefficient() const; //Accessors
    int getExponent() const;

    friend bool operator >(const Term &lhs, const Term &rhs);
    friend bool operator <(const Term &lhs, const Term &rhs);

	friend bool operator == (const Term &lhs, const Term &rhs);
	friend Term operator+(const Term& lhs, const Term& rhs);



	friend ostream& operator<<(ostream& out, Term& item);
	friend istream& operator>>(istream& in, Term& item);

	
private:

    int coefficient, exponent;
};