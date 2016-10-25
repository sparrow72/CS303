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

#ifndef _Requests
#define _Requests


class Req
{
public:
	~Req();

	bool isUp();
private:


protected:
	bool dirUp;
	int currElevFloor;
	int currUserFloor;

};
#endif	