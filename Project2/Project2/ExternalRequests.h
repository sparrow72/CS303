// Josh Gregory, Zach Theiss, and Alex Malko
// CS 303 Project 2C
// Fall 2016
// Prof. Mohammad Kuhail

#ifndef _ExternalRequests
#define _ExternalRequests
#include "Requests.h"
#include <queue>

class ExternalRequests 
{
public:
    ~ExternalRequests();
	ExternalRequests(int userNum = 0)
	{
		line.push(userNum);
	}
	void addUser(int userNum)
	{
		line.push(userNum);

	}

	int getUpUser()
	{

	}
	bool hasUpUsers()
	{

	}
	bool hasDownUsers()
	{

	}

private:
	queue<int> line;

};
#endif	