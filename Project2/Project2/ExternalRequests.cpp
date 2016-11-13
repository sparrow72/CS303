// Josh Gregory, Zach Theiss, and Alex Malko
// CS 303 Project 2C
// Fall 2016
// Prof. Mohammad Kuhail

#include "ExternalRequests.h"
#include "User.h"

ExternalRequests::ExternalRequests(){} //Default constructor

void ExternalRequests::addUpUser(int userNum)
{
    upLine.push(userNum); //Add to queue of going up
}

void ExternalRequests::addDownUser(int userNum)
{
    downLine.push(userNum); //Add to queue going down
}

int ExternalRequests::getUpUser()
{
    int tempUser; //Get the first person off, up
    tempUser = upLine.front();
	upLine.pop(); //Remove from the queue
    return tempUser;
}

int ExternalRequests::getDownUser()
{
    int tempUser; //Get first person off, down
    tempUser = downLine.front();
    downLine.pop(); //Remove from the queue
    return tempUser;
}

bool ExternalRequests::hasUpUsers()
{
    if (upLine.empty()) //Check if need to go up
        return false;
    else 
        return true;
}

bool ExternalRequests::hasDownUsers()
{
    if (downLine.empty()) //Check if need to go down
        return false;
    else
        return true;
}