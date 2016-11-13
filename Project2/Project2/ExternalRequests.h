// Josh Gregory, Zach Theiss, and Alex Malko
// CS 303 Project 2C
// Fall 2016
// Prof. Mohammad Kuhail

#ifndef _ExternalRequests
#define _ExternalRequests
#include <iostream> //Allows for in and output
#include <string> //Allows for use of strings
#include <list> //Allows for use of lists
#include <locale>
#include <iterator> //Parse through
#include <map> //Main way of tracking
#include <queue>

using namespace std;

class ExternalRequests
{
public:
    ExternalRequests(); //Default Constructor
    void addDownUser(int userNum); //Add a User going down
    void addUpUser(int userNum); //Add a User going up
    int getUpUser(); //Get next Up Pick up
    int getDownUser(); //Get next Down Pick up
    bool hasUpUsers(); //Has someone going up
    bool hasDownUsers(); //Has someone going down

private:
    queue<int> upLine; //List of requests Up
    queue<int> downLine; //List of requests Down
};
#endif