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

double User::getFinalTime()
{
    return exitTime;
}

void User::setFinalTime(double FT)
{
    exitTime = FT;
}
