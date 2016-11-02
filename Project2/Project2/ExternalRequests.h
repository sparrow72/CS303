// Josh Gregory, Zach Theiss, and Alex Malko
// CS 303 Project 2C
// Fall 2016
// Prof. Mohammad Kuhail

#ifndef _ExternalRequests
#define _ExternalRequests
#include "Requests.h"
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