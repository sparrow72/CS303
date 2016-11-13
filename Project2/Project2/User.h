// Josh Gregory, Zach Theiss, and Alex Malko
// CS 303 Project 2C
// Fall 2016
// Prof. Mohammad Kuhail

#include <iostream> //Allows for in and output
#include <string> //Allows for use of strings
#include <list> //Allows for use of lists
#include <locale>
#include <iterator> //Parse through
#include <map> //Main way of tracking

using namespace std;

#ifndef _User
#define _User

class User
{
public:
    User(double uT = 0, int uF = 0, int dF = 0, string dir = ""); //Constructor pass in
	int getDestFloor(); //Get End floor
	int getStartFloor(); //Get Start floor
    double getFinalTime(); //Get arrival time
	double getStartTime(); //Get starting time
	string getUDir(); //Get End floor
    void setFinalTime(double FT); //Set the arrival time, when get off

private:
	double uTime, exitTime; //Timers
	int uFloor, dFloor; //Floors to note
	string uDir; //Direction of elevator
    bool atDest; //At requested floor
};
#endif	