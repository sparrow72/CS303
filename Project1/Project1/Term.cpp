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
	result.setExponent(lhs.getExponent);
	result.setCoefficient(lhs.getCoefficient + rhs.getCoefficient);
	return result;
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
	string str, temp;
    int exp, coeff, fin_str;
	in >> str;

    while(str != "") {
        for (int i = 0; i < str.length(); ++i)
        {
            if (str[i] == 'x')
            {
                Term(coeff, exp);
                //end coeff block
            }
            else if (str[i] == '-')
            {
                fin_str = stoi(str);
                //Convert str to int, create term, move to next
            }
            else if (str[i] == '+')
            {
                fin_str = stoi(str);
                //Convert str to int, create term, move to next
            }
            else if (str[i] == '^')
            {
                exp = str[i + 1];
                //Enter Exponent storage block
            }
            else {
                if (!isalpha(str[i + 1])) {
                    temp = str[i] + str[i + 1];
                    coeff = stoi(temp);
                }
                else if (str[i] == 0)
                    continue;
                else
                    coeff = str[i];

                //Add to coeff block
                //String concatination, if str[i+1] is an int, str[i] + str[i+1]
            }
        }
			//ect
			//make sure to include the posiblity of - and + exponents and coefficients
			//and if the numbers are larger than one char
		//Create a node w/all left over
	}
	return in;
}

