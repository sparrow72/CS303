// Josh Gregory, Zach Theiss, and Alex Malko
// CS 303 Project 2C
// Fall 2016
// Prof. Mohammad Kuhail

#include "User.h"

User::User(double uT, int uF, int dF, string dir)
{
    uTime = uT; //Constructor for the User class
    uFloor = uF; //Sets passed in values
    dFloor = dF;
    uDir = dir;
    atDest = false;
	exitTime = 0;
}

int User::getDestFloor()
{
	return dFloor; //Get the End Floor
}

int User::getStartFloor()
{
	return uFloor; //Get the start floor
}

double User::getFinalTime()
{
    return exitTime; //Get final time
}

double User::getStartTime()
{
	return uTime; //Get start time
}

string User::getUDir()
{
	return uDir; //Get request direction
}

void User::setFinalTime(double FT)
{
    exitTime = FT; //Set time of arrival
}