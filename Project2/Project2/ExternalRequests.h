// Josh Gregory, Zach Theiss, and Alex Malko
// CS 303 Project 2C
// Fall 2016
// Prof. Mohammad Kuhail

#ifndef _ExternalRequests
#define _ExternalRequests
#include <iostream> //Allows for in and output
#include <string> //Allows for use of strings
#include <list> //Allows for use of lists
#include <locale> //Menu functionality
#include <iterator> // next
#include <map> // maps are awesome
#include <queue>

using namespace std;

class ExternalRequests
{
public:
    ExternalRequests();
    void addDownUser(int userNum);
    void addUpUser(int userNum);
    int getUpUser();
    int getDownUser();
    bool hasUpUsers();
    bool hasDownUsers();

private:
    queue<int> upLine;
    queue<int> downLine;
};
#endif