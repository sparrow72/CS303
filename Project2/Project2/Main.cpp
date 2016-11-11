// Josh Gregory, Zach Theiss, and Alex Malko
// CS 303 Project 2C
// Fall 2016
// Prof. Mohammad Kuhail


#include "User.h"
#include "ExternalRequests.h"
#include "InternalRequests.h"
#include <fstream>
#include <iostream>
#include <string>
#include <map>

using namespace std;
void extRequests(map<int, User>&, map<int, ExternalRequests>&, double&, int&, istream& fin);
void elevator(double&, map<int, InternalRequests>::iterator&, map<int, InternalRequests>&, map<int, User>&, map<int, ExternalRequests>&);
void ticks(double&, map<int, InternalRequests>::iterator&, map<int, InternalRequests>&);
void userOutput(map<int, User>&);

int main()
{


	//opens the file
	ifstream fin("input.txt");

	InternalRequests intReq;
	map<int, User> uMap;
	map<int, ExternalRequests> extReqMap;
	map<int, InternalRequests> intReqMap;
	intReqMap.insert(pair<int, InternalRequests>(1, intReq));
	map<int, InternalRequests>::iterator intIter = intReqMap.begin();

	int id = 0;
	double cTime = 000000; //current time hh.mm.ss

	for (double cTime = 000000;cTime < 200;cTime++)
	{

		extRequests(uMap, extReqMap, cTime, id, fin);
		elevator(cTime, intIter, intReqMap, uMap, extReqMap);
	}
	userOutput(uMap);

	//closes the file
	fin.close();
	return 1;
}

void extRequests(map<int, User>& uMap, map<int, ExternalRequests>& extReqMap, double& cTime, int& id, istream& fin)
{///dont forget about capacity of elevator
 ////opens the file
	//ifstream fin("input.txt");

	double uTime; //user time (when the user takes action)
	string uDir;
	int uFloor, dFloor; //user floor and destination floor.

	if (fin.good())
	{
		fin >> uTime >> uDir >> uFloor >> dFloor;

		///maybe just make this a wrapper function, and call the other one when the time matches
		/*while (uTime < cTime)
		{
			cTime++;
		}*/

		//inputs data from txt file
		if (uTime >= cTime)
		{
			User usr;
			usr = User(uTime, uFloor, dFloor, uDir);
			uMap.insert(pair<int, User>(id, usr));
			id++;

			if (extReqMap.count(uFloor) > 0)//if key exists
			{
				if (uDir == "up")
					extReqMap[uFloor].addUpUser(id);
				else if (uDir == "down")
					extReqMap[uFloor].addDownUser(id);
				cTime++;
			}
			else //key does not exist
			{
				ExternalRequests extReq;
				extReqMap.insert(pair<int, ExternalRequests>(uFloor, extReq));
				if (uDir == "up")
					extReqMap[uFloor].addUpUser(id);
				else if (uDir == "down")
					extReqMap[uFloor].addDownUser(id);
				cTime++;
			}
		}

	}

	////closes the file
	//fin.close();
}

void elevator(double& cTime, map<int, InternalRequests>::iterator& intIter, map<int, InternalRequests>& intReqMap, map<int, User>& uMap, map<int, ExternalRequests>& extReqMap)
{///run this function in parallel
	//elevator is going up
	if ((*intIter).second.getDir() == "up")
	{
		//lets people off
		if ((*intIter).second.hasExitUser())
		{
			while ((*intIter).second.hasExitUser())
			{
				cTime++;
				int id;
				id = (*intIter).second.removeUser();
				uMap[id].setFinalTime(cTime);
			}
		}

		//lets people on
		if (extReqMap.count(intIter->first) > 0)
		{
			while (extReqMap[intIter->first].hasUpUsers())
			{
				cTime++;
				int id, dFloor;
				double uTime = 0;
				/// this code is reading in the wrong user
				/// ///////////////////////////////////////////////
				// ///////////////////////////////////////////////
				/// /////////////////////////////////////////////
				// /////////////////////////////////////////////
				/// ///////////////////////////////////////////
				// ///////////////////////////////////////////
				/// /////////////////////////////////////////
				// /////////////////////////////////////////
				/// ///////////////////////////////////////
				// ///////////////////////////////////////
				/// /////////////////////////////////////
				// /////////////////////////////////////
				/// ///////////////////////////////////
				// ///////////////////////////////////
				/// /////////////////////////////////
				// /////////////////////////////////
				
				id = extReqMap[intIter->first].getUpUser();
				uTime = uMap[id].getStartTime();
				/*if (uTime == 0)
				{
					id = extReqMap[intIter->first].getUpUser();

				}*/

				dFloor = uMap[id].getDestFloor();

				if (intReqMap.count(dFloor) > 0)//if key exists
				{
					intReqMap[dFloor].addUser(id);
				}
				else //key does not exist
				{
					InternalRequests intReq;
					intReq.addUser(id);
					intReqMap.insert(pair<int, InternalRequests>(dFloor, intReq));
				}
			}
			if (!extReqMap[intIter->first].hasDownUsers())
			{
				extReqMap.erase(intIter->first);
			}
		}

		//gets current and next floors
		int nextExtFloor = intIter->first;
		if (!extReqMap.empty())
		{
			map<int, ExternalRequests>::iterator extIter = extReqMap.upper_bound(intIter->first);
			while (extIter != extReqMap.end()) //check all floors above elevator
			{
				if ((*extIter).second.hasUpUsers())
				{
					nextExtFloor = (*extIter).first;
					break;
				}
				++extIter;
			}
		}
		int currentIntFloor = (*intIter).first, nextIntFloor = (*intIter).first;
		++intIter;
		if (intIter != intReqMap.end())
			int nextIntFloor = (*intIter).first;
		--intIter;

		//moves elevator
		if (intIter == intReqMap.begin() && --intIter == intReqMap.end())// if no more int req
		{
			++intIter;

			if (extReqMap.empty())//no more req
				(*intIter).second.setDir("");
			else if (nextExtFloor > currentIntFloor)//go to next ext up user
			{
				InternalRequests intReq;
				intReqMap.insert(pair<int, InternalRequests>(nextExtFloor, intReq));
				ticks(cTime, intIter, intReqMap);
				//++intIter;
			}
			else//go to extReqMap.end()
			{
				map<int, ExternalRequests>::iterator extEnd = extReqMap.end();
				--extEnd;
				if ((*extEnd).first > currentIntFloor) // going up
				{
					InternalRequests intReq;
					intReqMap.insert(pair<int, InternalRequests>((*extEnd).first, intReq));
					ticks(cTime, intIter, intReqMap);
					//++intIter;					
				}
				else if ((*extEnd).first < currentIntFloor)//going down
				{
					(*intIter).second.setDir("down");
					InternalRequests intReq;
					intReqMap.insert(pair<int, InternalRequests>((*extEnd).first, intReq));
					ticks(cTime, intIter, intReqMap);
					//--intIter;
				}
				else //is on same floor
				{
					(*intIter).second.setDir("down");
				}
			}

		}
		else if (--intIter != intReqMap.end())//if not at top req, go to next floor
		{
			++intIter;
			if (currentIntFloor < nextExtFloor && nextExtFloor < nextIntFloor)//next ext up user is inbetween int req
			{
				//go to next ext up user
				InternalRequests intReq;
				intReqMap.insert(pair<int, InternalRequests>(nextExtFloor, intReq));
				ticks(cTime, intIter, intReqMap);
				//++intIter;
			}
			else //next ext up user is above the next int floor
			{
				ticks(cTime, intIter, intReqMap);
				//++intIter;
			}

		}
		else if (currentIntFloor == nextIntFloor)//no more int up req
		{
			if (extReqMap.empty())//no ext req
			{
				(*intIter).second.setDir("down");
				ticks(cTime, intIter, intReqMap);
				//--intIter;				
			}
			else if (nextExtFloor > currentIntFloor)//ext up user above current floor
			{
				//go that floor
				InternalRequests intReq;
				intReqMap.insert(pair<int, InternalRequests>(nextExtFloor, intReq));
				ticks(cTime, intIter, intReqMap);
				//++intIter;
			}
			else //go to extReqMap.end()
			{
				map<int, ExternalRequests>::iterator extEnd = extReqMap.end();
				--extEnd;
				if ((*extEnd).first > (*intIter).first) // going up
				{
					InternalRequests intReq;
					intReqMap.insert(pair<int, InternalRequests>((*extEnd).first, intReq));
					ticks(cTime, intIter, intReqMap);
					//++intIter;
				}
				else if ((*extEnd).first < (*intIter).first)//going down
				{
					(*intIter).second.setDir("down");
					InternalRequests intReq;
					intReqMap.insert(pair<int, InternalRequests>((*extEnd).first, intReq));
					ticks(cTime, intIter, intReqMap);
					//--intIter;
				}
				else //is on same floor
				{
					(*intIter).second.setDir("down");
				}
			}
		}
	}

	//elevator is going down
	else if ((*intIter).second.getDir() == "down")
	{

		//lets people off
		if ((*intIter).second.hasExitUser())
		{
			while ((*intIter).second.hasExitUser())
			{
				cTime++;
				int id;
				id = (*intIter).second.removeUser();
				uMap[id].setFinalTime(cTime);
			}
		}

		//lets people on
		if (extReqMap.count(intIter->first) > 0)
		{
			while (extReqMap[intIter->first].hasDownUsers())
			{
				cTime++;
				int id, dFloor;
				id = extReqMap[intIter->first].getDownUser();
				dFloor = uMap[id].getDestFloor();
				/// this code is reading in the wrong user
				/// ///////////////////////////////////////////////
				// ///////////////////////////////////////////////
				/// /////////////////////////////////////////////
				// /////////////////////////////////////////////
				/// ///////////////////////////////////////////
				// ///////////////////////////////////////////
				/// /////////////////////////////////////////
				// /////////////////////////////////////////
				/// ///////////////////////////////////////
				// ///////////////////////////////////////
				/// /////////////////////////////////////
				// /////////////////////////////////////
				/// ///////////////////////////////////
				// ///////////////////////////////////
				/// /////////////////////////////////
				// /////////////////////////////////

				if (intReqMap.count(dFloor) > 0)//if key exists
				{
					intReqMap[dFloor].addUser(id);
				}
				else //key does not exist
				{
					InternalRequests intReq;
					intReq.addUser(id);
					intReqMap.insert(pair<int, InternalRequests>(dFloor, intReq));
				}
			}
			if (!extReqMap[intIter->first].hasUpUsers())
			{
				extReqMap.erase(intIter->first);
			}
		}

		//gets current and next floors
		int nextExtFloor = intIter->first;
		if (!extReqMap.empty())
		{
			map<int, ExternalRequests>::iterator extIter = extReqMap.lower_bound(intIter->first);
			while (extIter != extReqMap.begin()) //check all floors above elevator
			{
				if ((*extIter).second.hasDownUsers())
				{
					nextExtFloor = (*extIter).first;
					break;
				}
				--extIter;
			}
		}
		int currentIntFloor = (*intIter).first, nextIntFloor = (*intIter).first;
		--intIter;
		if (intIter != intReqMap.end())
			int nextIntFloor = (*intIter).first;
		++intIter;

		//moves elevator
		if (intIter == intReqMap.begin() && --intIter == intReqMap.end())// if no more req
		{
			++intIter;

			if (extReqMap.empty())//no more req
				(*intIter).second.setDir("");
			else if (nextExtFloor < currentIntFloor)//go to next ext down user
			{
				InternalRequests intReq;
				intReqMap.insert(pair<int, InternalRequests>(nextExtFloor, intReq));
				ticks(cTime, intIter, intReqMap);
				//--intIter;
			}
			else//go to extReqMap.begin()
			{
				map<int, ExternalRequests>::iterator extEnd = extReqMap.begin();
				if ((*extEnd).first > currentIntFloor) // going up
				{
					(*intIter).second.setDir("up");
					InternalRequests intReq;
					intReqMap.insert(pair<int, InternalRequests>((*extEnd).first, intReq));
					ticks(cTime, intIter, intReqMap);
					//++intIter;
				}
				else if ((*extEnd).first < currentIntFloor)//going down
				{
					InternalRequests intReq;
					intReqMap.insert(pair<int, InternalRequests>((*extEnd).first, intReq));
					ticks(cTime, intIter, intReqMap);
					//--intIter;
				}
				else //is on same floor
				{
					(*intIter).second.setDir("down");
				}
			}
		}
		else if (intIter != intReqMap.begin())//if not at bottem, go to next floor
		{//check all floors inbetween the floors
			if (currentIntFloor > nextExtFloor && nextExtFloor > nextIntFloor)//next ext down user is above current
			{
				InternalRequests intReq;
				intReqMap.insert(pair<int, InternalRequests>(nextIntFloor, intReq));
				ticks(cTime, intIter, intReqMap);
				//--intIter;
			}
			else if (nextExtFloor > nextIntFloor)//next ext down user between the floors
			{
				ticks(cTime, intIter, intReqMap);
				//--intIter;
			}
		}
		else if (currentIntFloor == nextIntFloor)//is at bottom with requests for upper floors
		{
			if (extReqMap.empty())//no ext req
			{
				(*intIter).second.setDir("up");
				ticks(cTime, intIter, intReqMap);
				//++intIter;
			}
			else if (nextExtFloor < currentIntFloor)//ext down user below current floor
			{
				//go that floor
				InternalRequests intReq;
				intReqMap.insert(pair<int, InternalRequests>(nextExtFloor, intReq));
				ticks(cTime, intIter, intReqMap);
				//--intIter;
			}
			else //go to extReqMap.begin()
			{
				map<int, ExternalRequests>::iterator extEnd = extReqMap.begin();
				if ((*extEnd).first > (*intIter).first) // going up
				{
					(*intIter).second.setDir("up");
					InternalRequests intReq;
					intReqMap.insert(pair<int, InternalRequests>((*extEnd).first, intReq));
					ticks(cTime, intIter, intReqMap);
					//++intIter;
				}
				else if ((*extEnd).first < (*intIter).first)//going down
				{
					InternalRequests intReq;
					intReqMap.insert(pair<int, InternalRequests>((*extEnd).first, intReq));
					ticks(cTime, intIter, intReqMap);
					//--intIter;
				}
				else //is on same floor
				{
					(*intIter).second.setDir("down");
				}
			}
		}
	}

	//elevator is not moving
	else if ((*intIter).second.getDir() == "")
	{///make sure to only send closest elevator to new external requests
		if (!extReqMap.empty())
		{
			map<int, ExternalRequests>::iterator down = extReqMap.lower_bound(intIter->first);
			if (down == extReqMap.end())
				--down;
			map<int, ExternalRequests>::iterator up = extReqMap.upper_bound(intIter->first);
			if (up == extReqMap.end())
				--up;

			if (up->first - intIter->first <= down->first - intIter->first)
			{
				InternalRequests intReq;
				intReqMap.insert(pair<int, InternalRequests>(up->first, intReq));
				(*intIter).second.setDir("up");
				ticks(cTime, intIter, intReqMap);
				//(*intIter).second.setDir("up");
				//++intIter;
			}
			else
			{
				InternalRequests intReq;
				intReqMap.insert(pair<int, InternalRequests>(down->first, intReq));
				(*intIter).second.setDir("down");
				ticks(cTime, intIter, intReqMap);
				//--intIter;
			}
		}
	}
}




void ticks(double& cTime, map<int, InternalRequests>::iterator& intIter, map<int, InternalRequests>& intReqMap)
{

	if ((*intIter).second.getDir() == "up")
	{
		int f1 = intIter->first;
		++intIter;
		if (intIter == intReqMap.end())
			--intIter;
		else
		{
			int f2 = intIter->first;
			cTime += 5 * abs(f1 - f2);
			intReqMap.erase(f1);
			(*intIter).second.setDir("up");
		}
	}
	else if ((*intIter).second.getDir() == "down")
	{
		int f1 = intIter->first;
		--intIter;
		if (intIter == intReqMap.end())
			--intIter;
		else
		{
			int f2 = intIter->first;
			cTime += 3 * abs(f1 - f2);
			intReqMap.erase(f1);
			(*intIter).second.setDir("down");
		}
	}

}

void userOutput(map<int, User>& uMap)
{
	ofstream fout("output.txt");

	fout << "User\tStart Time\tFinal Time\t Start Floor\tDestination Floor\n";
	for (map<int, User>::iterator iter = uMap.begin(); iter != uMap.end(); iter++)
	{
		fout << (*iter).first << "\t\t" << (*iter).second.getStartTime() << "\t\t\t" << (*iter).second.getFinalTime() << "\t\t\t" <<
			(*iter).second.getStartFloor() << "\t\t\t\t" << (*iter).second.getDestFloor() << endl;
	}

	//closes the files
	fout.close();
}