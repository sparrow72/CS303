// Josh Gregory, Zach Theiss, and Alex Malko
// CS 303 Project 2C
// Fall 2016
// Prof. Mohammad Kuhail

#ifndef _InternalRequests
#define _InternalRequests
#include <iostream> //Allows for in and output
#include <string> //Allows for use of strings
#include <list> //Allows for use of lists
#include <locale> //Menu functionality
#include <iterator> // next
#include <map> // maps are awesome
#include <queue>

using namespace std;

class InternalRequests 
{
public:
    InternalRequests();
    void setDir(string D);
    string getDir();
    void addUser(int userNum);
    bool hasExitUser(); //Check if Queue empty, true if need off, false otherwise
    int removeUser(); //Return popped item, and remove user from queue
private:
	string eDir;
	queue<int> line;

};
#endif	