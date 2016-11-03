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
void extRequests(map<int, User>&, map<int, ExternalRequests>&, double&, int&);

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

void extRequests(map<int, User>& uMap, map<int, ExternalRequests>& extReqMap, double& cTime, int& id)
///Read in data, insert to User, th
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
			if (uDir == "up")
				extReqMap[uFloor].addUpUser(id);
			else if (uDir == "down")
				extReqMap[uFloor].addDownUser(id);
		}
		else //key does not exist
		{
			ExternalRequests extReq;
			extReqMap.insert(pair<int, ExternalRequests>(uFloor, extReq));
			if (uDir == "up")
				extReqMap[uFloor].addUpUser(id);
			else if (uDir == "down")
				extReqMap[uFloor].addDownUser(id);
		}

	}
	else
	{
		cTime++;///find a better way to increment the time... this is not incrementing with all the classes
	}

	//closes the files
	fin.close();
}

void elevator(map<int, InternalRequests>::iterator& intIter, int& elevFloor, int& extFloor, double& cTime, map<int, User>& uMap, map<int, InternalRequests>& intReqMap, map<int, ExternalRequests>& extReqMap)
{///run this function in parallel
	if ((*intIter).second.getDir() == "up")
	{///elevator is going up

		if ((*intIter).second.hasExitUser())
		{
			cTime++;
			while ((*intIter).second.hasExitUser())//lets ppl off
			{
				int id;
				id = (*intIter).second.removeUser();
				uMap[id].setFinalTime(cTime);
			}
		}

		if (extReqMap[intIter->first].hasUpUsers())
		{
			cTime++;
			while (extReqMap[intIter->first].hasUpUsers())//lets ppl on
			{///will check if there are any users going in same dir

				int id, dFloor;
				id = extReqMap[intIter->first].getUpUser();
				dFloor = uMap[id].getDestFloor();

				if (intReqMap.count(dFloor))//if key exists
				{
					intReqMap[dFloor].addUser(id);
				}
				else //key does not exist
				{
					InternalRequests intReq;
					intReq = InternalRequests(id);
					intReqMap.insert(pair<int, InternalRequests>(dFloor, intReq));
				}
			}
		}
		///check all external requests for request going up, 
		if (intIter == intReqMap.end() && intIter == intReqMap.begin())// if no more int req
		{///for loop, check all extReq above for any users going up, if none, go to top, if no extReq, setDir ""

			//get next ext floor with up user
				//if none, go to extreqmap.end()... even if its below the elevator, and set the dir to down
				//if no ext req, set dir to ""

			if (extReqMap.empty())
				(*intIter).second.setDir("");
			else
			{
				map<int, ExternalRequests>::iterator extIter = extReqMap.end();
				int nextUpUser = 0;
				while (extIter->first > intIter->first) //check all floors above elevator
				{
					/// //////////////////////////////////////////////////////
					// //////////////////////////////////////////////////////
					/// //////////////////////////////////////////////////////
					// //////////////////////////////////////////////////////
					/// //////////////////////////////////////////////////////
					// //////////////////////////////////////////////////////
					/// //////////////////////////////////////////////////////
					// //////////////////////////////////////////////////////	
					/// //////////////////////////////////////////////////////
					// //////////////////////////////////////////////////////
					/// //////////////////////////////////////////////////////
					// //////////////////////////////////////////////////////
					/// //////////////////////////////////////////////////////
					// //////////////////////////////////////////////////////
					/// //////////////////////////////////////////////////////
					// //////////////////////////////////////////////////////
					/// //////////////////////////////////////////////////////
					// //////////////////////////////////////////////////////
					/// //////////////////////////////////////////////////////
					// //////////////////////////////////////////////////////
					/// //////////////////////////////////////////////////////
					// //////////////////////////////////////////////////////
					/// //////////////////////////////////////////////////////
					// //////////////////////////////////////////////////////
				}
			}

		}
		else if (intIter != intReqMap.end())//if not at top req, go to next floor
		{
			++intIter;
			cTime++;
		}
		else if (intIter == intReqMap.end())//is at top with requests for lower floors
		{
			(*intIter).second.setDir("down");
			--intIter;
			cTime++;
		}
	}
	//else if ((*intIter).second.getDir() == "down")
	//{///elevator is going down
	//	if ((*intIter).second.hasExitUser())
	//	{
	//		cTime++;
	//		while ((*intIter).second.hasExitUser())
	//		{
	//			int id;
	//			id = (*intIter).second.removeUser();
	//			uMap[id].setFinalTime(cTime);
	//		}
	//	}

	//	if (extReqMap[intIter->first].hasDownUsers())
	//	{
	//		cTime++;
	//		while (extReqMap[intIter->first].hasDownUsers())///will check if there are any users going in same dir
	//		{
	//			int id, dFloor;
	//			id = extReqMap[intIter->first].getDownUser();
	//			dFloor = uMap[id].getDestFloor();

	//			if (extReqMap.count(dFloor))//if key exists
	//			{
	//				intReqMap[dFloor].addUser(id);
	//			}
	//			else //key does not exist
	//			{
	//				InternalRequests intReq;
	//				intReq = InternalRequests(id);
	//				intReqMap.insert(pair<int, InternalRequests>(dFloor, intReq));
	//			}
	//		}
	//	}

	//	if (intIter == intReqMap.end() && intIter == intReqMap.begin())// if no more req
	//	{
	//		(*intIter).second.setDir("");
	//	}
	//	else if (intIter != intReqMap.begin())//go to next floor
	//	{
	//		--intIter;
	//		cTime++;
	//	}
	//	else if (intIter == intReqMap.begin())//is at bottom with requests for lower floors
	//	{
	//		(*intIter).second.setDir("up");
	//		++intIter;
	//		cTime++;
	//	}
	//}
	//else if ((*intIter).second.getDir() == "")
	//{///make sure to only send closest elevator to new external requests

	//}



}