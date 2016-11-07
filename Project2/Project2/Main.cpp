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
		map<int, ExternalRequests>::iterator extIter = extReqMap.end();
		int nextUpUser = -1;
		while (extIter->first > intIter->first) //check all floors above elevator
		{
			if ((*extIter).second.hasUpUsers())
			{
				nextUpUser = (*extIter).first;
			}
			--extIter;

		}
		if (intIter == intReqMap.end() && intIter == intReqMap.begin())// if no more int req
		{///for loop, check all extReq above for any users going up, if none, go to top, if no extReq, setDir ""

			//get next ext floor with up user
				//if none, go to extreqmap.end()... even if its below the elevator, and set the dir to down
				//if no ext req, set dir to ""

			if (extReqMap.empty())//no more req
				(*intIter).second.setDir("");
			else if (nextUpUser > (*intIter).first)//go to next ext up user
			{
				InternalRequests intReq;
				intReqMap.insert(pair<int, InternalRequests>(nextUpUser, intReq));
				++intIter;
			}
			else//go to extReqMap.end()
			{
				map<int, ExternalRequests>::iterator extEnd = extReqMap.end();
				if ((*extEnd).first > (*intIter).first) // going up
				{
					InternalRequests intReq;
					intReqMap.insert(pair<int, InternalRequests>((*extEnd).first, intReq));
					++intIter;
				}
				else//going down
				{
					(*intIter).second.setDir("down");
					InternalRequests intReq;
					intReqMap.insert(pair<int, InternalRequests>((*extEnd).first, intReq));
					--intIter;
					cTime++;
				}
			}

		}
		else if (intIter != intReqMap.end())//if not at top req, go to next floor
		{
			//check all floors inbetween the floors
			int currentFloor = (*intIter).first;
			++intIter;
			int nextFloor = (*intIter).first;

			if (nextUpUser < currentFloor)//next ext up user is bellow current
			{
				//already went to ++intIter
				cTime++;
			}
			else if (nextUpUser < nextFloor)//next ext up user is inbetween int req
			{
				--intIter;
				//go to next ext up user
				InternalRequests intReq;
				intReqMap.insert(pair<int, InternalRequests>(nextUpUser, intReq));
				++intIter;
				cTime++;
			}
			else //next ext up user is above the next int floor
			{
				cTime++;
			}

		}
		else if (intIter == intReqMap.end())//is at top with requests for lower floors
		{
			if (extReqMap.empty())//no ext req
			{
				(*intIter).second.setDir("down");
				//check inbetween floors
				--intIter;
				cTime++;
			}
			else if (nextUpUser > (*intIter).first)//ext up user above current floor
			{
				//go that floor
				InternalRequests intReq;
				intReqMap.insert(pair<int, InternalRequests>(nextUpUser, intReq));
				++intIter;
			}
			else //check if ext floor above current
			{
				map<int, ExternalRequests>::iterator extEnd = extReqMap.end();
				if ((*extEnd).first > (*intIter).first) // going up
				{
					InternalRequests intReq;
					intReqMap.insert(pair<int, InternalRequests>((*extEnd).first, intReq));
					++intIter;
				}
				else//going down
				{
					(*intIter).second.setDir("down");
					InternalRequests intReq;
					intReqMap.insert(pair<int, InternalRequests>((*extEnd).first, intReq));
					--intIter;
					cTime++;
				}
				//go to extReqMap.end()
			}

		}
	}
	else if ((*intIter).second.getDir() == "down")
	{///elevator is going down
		if ((*intIter).second.hasExitUser())
		{
			cTime++;
			while ((*intIter).second.hasExitUser())
			{
				int id;
				id = (*intIter).second.removeUser();
				uMap[id].setFinalTime(cTime);
			}
		}
		if (extReqMap[intIter->first].hasDownUsers())
		{
			cTime++;
			while (extReqMap[intIter->first].hasDownUsers())///will check if there are any users going in same dir
			{
				int id, dFloor;
				id = extReqMap[intIter->first].getDownUser();
				dFloor = uMap[id].getDestFloor();

				if (extReqMap.count(dFloor))//if key exists
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
		map<int, ExternalRequests>::iterator extIter = extReqMap.begin();
		int nextDownUser = -1;
		while (extIter->first < intIter->first) //check all floors below elevator
		{
			if ((*extIter).second.hasDownUsers())
			{
				nextDownUser = (*extIter).first;
			}
			++extIter;

		}
		if (intIter == intReqMap.end() && intIter == intReqMap.begin())// if no more req
		{
			if (extReqMap.empty())//no more req
				(*intIter).second.setDir("");
			else if (nextDownUser < (*intIter).first)//go to next ext down user
			{
				InternalRequests intReq;
				intReqMap.insert(pair<int, InternalRequests>(nextDownUser, intReq));
				--intIter;
			}
			else//go to extReqMap.begin()
			{
				map<int, ExternalRequests>::iterator extEnd = extReqMap.begin();
				if ((*extEnd).first > (*intIter).first) // going up
				{
					(*intIter).second.setDir("up");
					InternalRequests intReq;
					intReqMap.insert(pair<int, InternalRequests>((*extEnd).first, intReq));
					++intIter;
				}
				else//going down
				{
					InternalRequests intReq;
					intReqMap.insert(pair<int, InternalRequests>((*extEnd).first, intReq));
					--intIter;
					cTime++;
				}
			}
		}
		else if (intIter != intReqMap.begin())//go to next floor
		{

			//check all floors inbetween the floors
			int currentFloor = (*intIter).first;
			--intIter;
			int nextFloor = (*intIter).first;

			if (nextDownUser > currentFloor)//next ext down user is above current
			{
				//already went to --intIter
				cTime++;
			}
			else if (nextDownUser > nextFloor)//next ext down user between the floors
			{
				++intIter;
				//go to next ext up user
				InternalRequests intReq;
				intReqMap.insert(pair<int, InternalRequests>(nextDownUser, intReq));
				--intIter;
				cTime++;
			}
			else //next ext down user is below the next int floor
			{
				cTime++;
			}

			
		}
		else if (intIter == intReqMap.begin())//is at bottom with requests for upper floors
		{
			if (extReqMap.empty())//no ext req
			{
				(*intIter).second.setDir("up");
				++intIter;
				cTime++;
			}
			else if (nextDownUser < (*intIter).first)//ext down user below current floor
			{
				//go that floor
				InternalRequests intReq;
				intReqMap.insert(pair<int, InternalRequests>(nextDownUser, intReq));
				--intIter;

			}
			else //check if ext floor below current
			{
				map<int, ExternalRequests>::iterator extEnd = extReqMap.begin();
				if ((*extEnd).first > (*intIter).first) // going up
				{
					(*intIter).second.setDir("up");
					InternalRequests intReq;
					intReqMap.insert(pair<int, InternalRequests>((*extEnd).first, intReq));
					++intIter;
				}
				else//going down
				{
					InternalRequests intReq;
					intReqMap.insert(pair<int, InternalRequests>((*extEnd).first, intReq));
					--intIter;
					cTime++;
				}
				//go to extReqMap.begin()
			}

		}
	}
	else if ((*intIter).second.getDir() == "")
	{///make sure to only send closest elevator to new external requests

	}



}