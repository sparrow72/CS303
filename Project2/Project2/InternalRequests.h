// Josh Gregory, Zach Theiss, and Alex Malko
// CS 303 Project 2C
// Fall 2016
// Prof. Mohammad Kuhail

#ifndef _InternalRequests
#define _InternalRequests
#include "Requests.h"

class InternalRequests 
{
public:
	~InternalRequests()
	{

	}
	InternalRequests(int userNum = 0)
	{
		line.push(userNum);
	}
	string getDir()
	{
		return eDir;
	}
	void addUser(int userNum)
	{
		line.push(userNum);

	}
	bool hasExitUser()
	{

	}
	int removeUser()
	{
		
	}
private:
	string eDir;
	queue<int> line;

};
#endif	