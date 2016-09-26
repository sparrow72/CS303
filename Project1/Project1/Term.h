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
	~Term();
	
    void setCoefficient(int new_coefficient = 1); //Mutators
    void setExponent(int new_exponent = 1);
	void setIsfirst(bool isfirst = false);

    int getCoefficient() const; //Accessors
    int getExponent() const;

    //Overlaoded comparison operators
    friend bool operator >(const Term &lhs, const Term &rhs); 
    friend bool operator <(const Term &lhs, const Term &rhs);

    //Overloaded the equality operator
	friend bool operator == (const Term &lhs, const Term &rhs);

	//Overloaded the equality operator
	Term& Term::operator=(const Term& rhs);

    //Overloaded the plus operator
	friend Term operator+(const Term& lhs, const Term& rhs);

    //Overloaded the output operator
	friend ostream& operator<<(ostream& out, Term& item);
	
private:
    int coefficient, exponent; //Keeping the coeff and exp of the polynomial term
	bool isfirst;
};