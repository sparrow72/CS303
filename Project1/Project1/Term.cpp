#include "Term.h"
// Josh Gregory, Zach Theiss, and Alex Malko
// CS 303 Project 1
// Fall 2016
// Prof. Mohammad Kuhail

Term::Term(int new_coefficient, int new_exponent)
{
    coefficient = new_coefficient; exponent = new_exponent;
}

void Term::setCoefficient(int new_coefficient)
{
    coefficient = new_coefficient;      
}

void Term::setExponent(int new_exponent)
{
    exponent = new_exponent;
}

int Term::getCoefficient() const 
{
    return coefficient;
}

int Term::getExponent() const
{ 
    return exponent;
}

bool operator>(const Term & lhs, const Term & rhs)
{
    if (lhs.getExponent() > rhs.getExponent())
    {
        return true;
    }

    else { return false; }
}

bool operator<(const Term & lhs, const Term & rhs)
{
    if (lhs.getExponent() < rhs.getExponent())
    {
        return true;
    }

    else { return false; }
}

bool operator==(const Term & lhs, const Term & rhs)
{
	if (lhs.getExponent() == rhs.getExponent())
	{
		return true;
	}

	else { return false; }
}

Term operator+(const Term& lhs, const Term& rhs)
{
	Term result;
	result.setExponent(lhs.exponent);
	result.setCoefficient(lhs.coefficient + rhs.coefficient);
	return result;
}

ostream& operator<<(ostream& out, Term& item)
{
	if (item.coefficient >= 0)
		out << "+";
	else if (item.coefficient < 0)
		out << "-";

	out << item.coefficient << "x^" << item.exponent << "\n";
	
	return out;
}


