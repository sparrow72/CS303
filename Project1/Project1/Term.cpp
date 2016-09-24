#include "Term.h"




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




ostream& operator<<(ostream& out, Term& item)
{
	if (item.sign == '+' || item.sign == '-')
		out << item.sign;

	out << item.coefficient << "x^" << item.exponent << "\n";
	
	return out;
}

istream& operator>>(istream& in, Term& item)
{
	string str;
	in >> str;

	for (int i = 0; i<str.length(); ++i)
	{
		if (str[i] == 'x')
		{
		}
			//ect
			//make sure to include the posiblity of - and + exponents and coefficients
			// and if the numbers are larger than one char
			
	}
	return in;
	

}

