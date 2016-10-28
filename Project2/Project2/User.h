// Josh Gregory, Zach Theiss, and Alex Malko
// CS 303 Project 2C
// Fall 2016
// Prof. Mohammad Kuhail

#include <iostream> //Allows for in and output
#include <string> //Allows for use of strings
#include <list> //Allows for use of lists
#include <locale> //Menu functionality
#include <iterator> // next
#include <map> // maps are awesome

using namespace std;

#ifndef _User
#define _User

class User
{
public:
	~User()
	{

	}

	User(double uT = 0, int uF = 0, int dF = 0, string dir = "")
	{
		uTime = uT;
		uFloor = uF;
		dFloor = dF;
		uDir = dir;
		atDest = false;
	}

private:
	double uTime, exitTime;
	int uFloor, dFloor;
	string uDir;
	bool atDest;
protected:

};
#endif	