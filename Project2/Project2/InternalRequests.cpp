// Josh Gregory, Zach Theiss, and Alex Malko
// CS 303 Project 2C
// Fall 2016
// Prof. Mohammad Kuhail

#include "InternalRequests.h"

InternalRequests::InternalRequests()
{
	eDir = ""; //Set blank direction
}

void InternalRequests::setDir(string D)
{
    eDir = D; //Set direction passed in
}

string InternalRequests::getDir()
{
    return eDir; //Get the direction of request
}

void InternalRequests::addUser(int userNum)
{
    line.push(userNum); //Add to the queue of users
}

bool InternalRequests::hasExitUser()
{
    if (line.empty()) //Check if someone needs to get off
        return false;
    else
        return true;
}

int InternalRequests::removeUser()
{
    int remdUser; //User got off at floor
    remdUser = line.front();
    line.pop();
    return remdUser;
}