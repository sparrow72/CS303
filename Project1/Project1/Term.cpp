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
    string str;
    int exp, coeff, fin_str;

    while (str != "") { //Continue until empty string
        for (int i = 0; i < str.length(); i++) //Iterate through string
        {
            string temp, temp1; //Resetting empty temps
            if (str[i] == 'X' || str[i] == 'x') //Item is an X
            {
                Term(coeff, exp); //end coeff block
            }
            else if (str[i] == '-') //Item is a minus - 
            {
                fin_str = stoi(str); //Convert str to int, create term, move to next
            }
            else if (str[i] == '+') // Item is a plus + 
            {
                fin_str = stoi(str); //Convert str to int, create term, move to next
            }
            else if (str[i] == '^') //Item is a carrot ^
            {
                i++; //Look at the exponent
                if (str[i] == '-') { // Negative Exponent
                    item.sign = str[i]; //Save the Negative Exponent
                    i++; //Look at exponent
                }
                temp = str[i]; //Save the exponent
                for (int j = i; j < str.length(); j++) { // Check that the exponent is larger than 1 digit (ie 10)
                    if (isalpha(str[j]) || str[j + 1] == '^' || str[j + 1] == '+' || str[j + 1] == '-') //If not a number, end
                        break;
                    if (!isalpha(str[j + 1])) { //Next item is a digit (0)
                        temp1 = str[j + 1]; //Make the exponenet a longer digit 
                        temp += temp1; // (1 + 0 = 10)
                    }
                }
                exp = stoi(temp); //Enter Exponent storage block
            }
            else {
                temp = str[i]; //Save the Coeff
                for (int j = i; j < str.length(); j++) { //Check that the coeff is larger than 1 digit
                    if (isalpha(str[j]) || str[j + 1] == '^' || str[j + 1] == '+' || str[j + 1] == '-') //If not a num, end
                        break;
                    if (!isalpha(str[j + 1])) { //Next item is a digit (0)
                        temp1 = str[j + 1]; //Make the coeff a longer digit
                        temp += temp1; // (1 + 0 = 10)
                    }
                    else if (temp.length() > 0) //string may be over, save the number
                        coeff = stoi(temp); //Convert from string to int
                    else {
                        coeff = stoi(str); // Convert from string to int
                        break;
                    }
                }
            }
        }
        //ect
        //make sure to include the posiblity of - and + exponents and coefficients
        //and if the numbers are larger than one char
        //Create a node w/all left over
    }
	return in;
}

