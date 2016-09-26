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
	Term(const Term &data) { exponent = data.getExponent(); coefficient = data.getCoefficient(); }
    //Default constructor 
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

	//Overloaded the equality operator
	Term& Term::operator=(const Term& rhs);

    //Overloaded the plus operator
	friend Term operator+(const Term& lhs, const Term& rhs);

    //Overloaded the output operator
	friend ostream& operator<<(ostream& out, Term& item);
	
private:
    int coefficient, exponent; //Keeping the coeff and exp of the polynomial term
	bool isfirst; //Bool to save 
};