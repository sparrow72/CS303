#include "Term.h" //Include the header
using namespace std;
// Josh Gregory, Zach Theiss, and Alex Malko
// CS 303 Project 1
// Fall 2016
// Prof. Mohammad Kuhail

Term::Term(int new_coefficient, int new_exponent)
{ //Default Constructor, setting to the input given
	coefficient = new_coefficient; exponent = new_exponent; isfirst = false;
}

Term::~Term()
{ //Destructor for the variable defined
	coefficient = 0; //Reset value
	exponent = 0; //Reset value
	isfirst = false; //Reset value
}

void Term::setCoefficient(int new_coefficient)
{ //Setting Coeff w/value passed in
	coefficient = new_coefficient;isfirst = false;
}

void Term::setExponent(int new_exponent)
{ //Setting exp w/value passed in
	exponent = new_exponent;isfirst = false;
}

void Term::setIsfirst(bool first)
{ //Marks the term as the first item in the polynomial
	isfirst = first;
}

int Term::getCoefficient() const
{ //Getting the Coeff
	return coefficient;
}

int Term::getExponent() const
{ //Getting the Exp
	return exponent;
}

bool operator>(const Term & lhs, const Term & rhs)
{ //Overloading Comparison operator
	if (lhs.getExponent() > rhs.getExponent())
	{ //If left is greater than it's true
		return true;
	}
	//Right hand side is larger
	else { return false; }
}

bool operator<(const Term & lhs, const Term & rhs)
{
	if (lhs.getExponent() < rhs.getExponent())
	{ //Right hand side is greater than left
		return true;
	}
	//Left hand side is greater than the right
	else { return false; }
}

bool operator==(const Term & lhs, const Term & rhs)
{
	if (lhs.getExponent() == rhs.getExponent())
	{ //Left side is the same as right side
		return true;
	}
	//The left and right side do not match
	else { return false; }
}

bool operator!=(const Term & lhs, const Term & rhs)
{
	if ((lhs.getExponent() != rhs.getExponent()) && (lhs.getCoefficient() != rhs.getCoefficient()))
	{ //Left side is the same as right side
		return true;
	}
	//The left and right side do not match
	else { return false; }
}

Term operator+(const Term& lhs, const Term& rhs)
{
	Term result; //Create a result variable
	result.setExponent(lhs.exponent); //Get the exponent that matches the sides
	result.setCoefficient(lhs.coefficient + rhs.coefficient); //Add the coeff together
	return result; //Return the result of this
}

Term& Term::operator=(const Term& rhs)
{
	if (this == &rhs)
	{ //If this Term is itself return itself
		return *this;
	}

	coefficient = rhs.coefficient; //Coeff is now the coeff of rhs
	exponent = rhs.exponent; //Exp is now the exp of rhs
	return *this;
} // implements the rhs

ostream& operator<<(ostream& out, Term& item)
{
	if (item.coefficient == 0) //If Coeff is 0
	{
		out << "0"; //Insert a 0
		return out; //Output the 0
	}

	if (!item.isfirst)
	{ //If this is not the first term in the list
		if (item.coefficient > 0) //Coeff is not negative
			out << " + "; //Insert a plus sign

		else if (item.coefficient < 0) //Coeff is negative
		{
			out << " - "; //Insert a minus sign
			if (item.exponent == 0) //If the exponent is 0
				out << abs(item.coefficient); //Output the absolute value of the coeff
			else if (item.exponent == 1) //If the exponent is 1
				out << abs(item.coefficient) << "x"; //Output only an x
			else //If the exponenet is greater than 1
				out << abs(item.coefficient) << "x^" << item.exponent;
			//Output the x and carrot symbol
			return out; //Return the polynomial
		}

	}
    //Term is the first term
	if (item.exponent == 0) //If the exponent is 0
		out << item.coefficient; //Output only the coeff
	else if (item.exponent == 1) //If the exp is 1
		out << item.coefficient << "x"; //Output an x
	else //Exp is greater than 1
		out << item.coefficient << "x^" << item.exponent;
	//Output the x and carrot symbol
	return out; //Return the polynomial
}