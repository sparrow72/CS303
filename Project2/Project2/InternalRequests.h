// Josh Gregory, Zach Theiss, and Alex Malko
// CS 303 Project 2C
// Fall 2016
// Prof. Mohammad Kuhail

#ifndef _InternalRequests
#define _InternalRequests
#include <iostream> //Allows for in and output
#include <string> //Allows for use of strings
#include <list> //Allows for use of lists
#include <locale> 
#include <iterator> //Parse through
#include <map> //Main way of tracking
#include <queue>

using namespace std;

class InternalRequests 
{
public:
    InternalRequests(); //Default constructor
    void setDir(string D); //Set the direction
    string getDir(); //Get the direction
    void addUser(int userNum); //Add someone to the inside elevator requests
    bool hasExitUser(); //Check if Queue empty, true if need off, false otherwise
    int removeUser(); //Return popped item, and remove user from queue
private:
	string eDir; //Direction of elevator
	queue<int> line; //Track everyone in elevator

};
#endif	