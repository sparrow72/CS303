// Josh Gregory, Zach Theiss, and Alex Malko
// CS 303 Project 2C
// Fall 2016
// Prof. Mohammad Kuhail

#include "ExternalRequests.h"

ExternalRequests::ExternalRequests(){}

void ExternalRequests::addUpUser(int userNum)
{
    upLine.push(userNum);
}

void ExternalRequests::addDownUser(int userNum)
{
    downLine.push(userNum);
}

int ExternalRequests::getUpUser()
{
    int tempUser;
    tempUser = upLine.front();
    return tempUser;
}

int ExternalRequests::getDownUser()
{
    int tempUser;
    tempUser = downLine.front();
    return tempUser;
}

bool ExternalRequests::hasUpUsers()
{
    if (upLine.front() != NULL)
        return false;
    else 
        return false;
}

bool ExternalRequests::hasDownUsers()
{
    if (downLine.front() != NULL)
        return false;
    else
        return true;
}
