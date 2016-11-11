#include "InternalRequests.h"
// Josh Gregory, Zach Theiss, and Alex Malko
// CS 303 Project 2C
// Fall 2016
// Prof. Mohammad Kuhail

InternalRequests::InternalRequests()
{
	eDir = "";
}

void InternalRequests::setDir(string D)
{
    eDir = D;
}

string InternalRequests::getDir()
{
    return eDir;
}

void InternalRequests::addUser(int userNum)
{
    line.push(userNum);
}

bool InternalRequests::hasExitUser()
{
    if (line.empty())
        return false;
    else
        return true;
}

int InternalRequests::removeUser()
{
    int remdUser;
    remdUser = line.front();
    line.pop();
    return remdUser;
}
