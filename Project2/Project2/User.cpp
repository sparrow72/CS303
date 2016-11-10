#include "User.h"
// Josh Gregory, Zach Theiss, and Alex Malko
// CS 303 Project 2C
// Fall 2016
// Prof. Mohammad Kuhail

User::User(double uT, int uF, int dF, string dir)
{
    uTime = uT;
    uFloor = uF;
    dFloor = dF;
    uDir = dir;
    atDest = false;
}

int User::getDestFloor()
{
	return dFloor;
}

int User::getStartFloor()
{
	return uFloor;
}


double User::getFinalTime()
{
    return exitTime;
}

double User::getStartTime()
{
	return uTime;
}

void User::setFinalTime(double FT)
{
    exitTime = FT;
}
