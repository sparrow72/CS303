// Josh Gregory, Zach Theiss, and Alex Malko
// CS 303 Project 2C
// Fall 2016
// Prof. Mohammad Kuhail

#include "Requests.h"
#include "User.h"
#include "ExternalRequests.h"
#include "InternalRequests.h"
#include <fstream>
#include <iostream>
#include <string>
#include <map>

using namespace std;
void extRequests(map<int, User>&, map<int, ExternalRequests>, double&, int&);

int main()
{

	ofstream fout("output.txt");

	Requests req;
	InternalRequests intReq;
	map<int, User> uMap;
	map<int, Requests> eMap;///is elevator, iter will be current floor of elevator, eMap.first->next will be next destination
	map<int, ExternalRequests> extReqMap;///use to keep track of all external users at floor
	map<int, InternalRequests> intReqMap;///not sure if I need this, it may come in handy. :)

	int id = 0;
	double cTime = 000000; //current time hh.mm.ss

	extRequests(uMap, extReqMap, cTime, id);


	//closes the files
	fout.close();
	return 1;
}

void extRequests(map<int, User>& uMap, map<int, ExternalRequests> extReqMap, double& cTime, int& id)
{///dont forget about capacity of elevator
	//opens the files
	ifstream fin("input.txt");

	///make sure it is compatible for // proc
	///consider putting it in a while(fin.good()) function.. 
	double uTime; //user time (time user takes action)
				  ///have user time and current time to denote when each user takes the action, 
				  ///should exept no action being taken and multiple actions at once
	string uDir;
	int uFloor, dFloor; //user floor and destination floor.

	fin >> uTime, uDir, uFloor, dFloor;

	if (uTime >= cTime)
	{
		User usr;
		usr = User(uTime, uFloor, dFloor, uDir);
		uMap.insert(pair<int, User>(id, usr));
		id++;		///next elevator to pass user floor in same direction they hit, will stop
		if (extReqMap.count(uFloor))//if key exists
		{
			extReqMap[uFloor].addUser(id);
		}
		else //key does not exist
		{
			ExternalRequests extReq;
			extReq = ExternalRequests(id);
			extReqMap.insert(pair<int, ExternalRequests>(uFloor, extReq));
		}

	}
	else
	{
		cTime++;///find a better way to increment the time... this is not incrementing with all the classes
	}

	//closes the files
	fin.close();
}