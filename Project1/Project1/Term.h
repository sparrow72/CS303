#pragma once
// Josh Gregory, Zach Theiss, and Alex Malko
// CS 303 Project 1
// Fall 2016
// Prof. Mohammad Kuhail

#include <iostream> //In and output in the implementation
#include <list> //Used to hold the terms
using namespace std; //Set namespace for the entire implementation

class Term {
public:
	Term(int new_coefficient=1, int new_exponent = 1); //Example can be found in List Header on BBoard
	~Term(); //Destructor
	
    void setCoefficient(int new_coefficient = 1); //Setter the Coeff w/1 default
    void setExponent(int new_exponent = 1); //Set the exponent w/1 default
	void setIsfirst(bool isfirst = false); //Check if the value is first in the list

    int getCoefficient() const; //Get the Coeff value
    int getExponent() const; //Get the Exp value

    //Overlaoded comparison operators
    friend bool operator >(const Term &lhs, const Term &rhs); 
    friend bool operator <(const Term &lhs, const Term &rhs);

    //Overloaded the equality operator
	friend bool operator == (const Term &lhs, const Term &rhs);
	//Overloaded the inequality operator
	friend bool operator != (const Term &lhs, const Term &rhs);

	//Overloaded the equals operator
	Term& Term::operator=(const Term& rhs);

    //Overloaded the plus operator
	friend Term operator+(const Term& lhs, const Term& rhs);

    //Overloaded the output operator
	friend ostream& operator<<(ostream& out, Term& item);
	
private:
    int coefficient, exponent; //Keeping the coeff and exp of the polynomial term
	bool isfirst; //Bool to save 
};