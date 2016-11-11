// Josh Gregory, Zach Theiss, and Alex Malko
// CS 303 Project 2C
// Fall 2016
// Prof. Mohammad Kuhail

#include "omp.h"
#include "User.h"
#include "ExternalRequests.h"
#include "InternalRequests.h"
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <iomanip>      // std::setw

using namespace std;
void extRequests(map<int, User>&, map<int, ExternalRequests>&, double&, int&, istream& fin, double&);
void elevator(double&, map<int, InternalRequests>::iterator&, map<int, InternalRequests>&, map<int, User>&, map<int, ExternalRequests>&);
void ticks(double&, map<int, InternalRequests>::iterator&, map<int, InternalRequests>&);
void userOutput(map<int, User>&);

int main()
{
	ifstream fin("input.txt"); //Open the file

	InternalRequests intReq;
	map<int, User> uMap; //Create a User Map
	map<int, ExternalRequests> extReqMap; //Create a Map of external (Outside elevator) requests
	map<int, InternalRequests> intReqMap; //Create a Map of internal (Inside elevator) requests
	intReqMap.insert(pair<int, InternalRequests>(1, intReq));
	map<int, InternalRequests>::iterator intIter = intReqMap.begin(); //Create an iterator at the beginning

	int id = 0; //Default ID
	double cTime = 1, uTime = 1; //Current time hh.mm.ss
								 //	omp_set_num_threads(3); //Parallel the for loop
								 //#pragma omp parallel for
	for (double cTime = 000000;cTime < 200; cTime++)
	{ //This for loop is executing all of the requests
		extRequests(uMap, extReqMap, cTime, id, fin, uTime);
		elevator(cTime, intIter, intReqMap, uMap, extReqMap);
	}
	userOutput(uMap); //Output the final Map

	fin.close(); //Close the file
	return 0;
}

void extRequests(map<int, User>& uMap, map<int, ExternalRequests>& extReqMap, double& cTime, int& id, istream& fin, double& uTime)
{///dont forget about capacity of elevator
 ////opens the file
 //ifstream fin("input.txt");


	string uDir; //Elevator Direction
	int uFloor, dFloor; //user floor and destination floor.
	if (uTime == 1) //Start inputting requests
		fin >> uTime; //Input time

					  ///maybe just make this a wrapper function, and call the other one when the time matches
					  /*while (uTime < cTime)
					  {
					  cTime++;
					  }*/

					  //inputs data from txt file
	if (uTime >= cTime && fin.good()) //If atleast 1 request and file is reading
	{
		fin >> uDir >> uFloor >> dFloor; //Input direction and floors
		User usr; //Create user class
		usr = User(uTime, uFloor, dFloor, uDir); //Create User
		uMap.insert(pair<int, User>(id, usr)); //Insert User into Map


		if (extReqMap.count(uFloor) > 0)//if key exists
		{
			if (uDir == "up") //Going Up
				extReqMap[uFloor].addUpUser(id); //Add User going up External
			else if (uDir == "down") //Going Down
				extReqMap[uFloor].addDownUser(id); //Add User going down External
			cTime++; //Increment time
		}
		else //key does not exist
		{
			ExternalRequests extReq; //No Key exists
			extReqMap.insert(pair<int, ExternalRequests>(uFloor, extReq)); //Insert User to Map External
			if (uDir == "up") //Going Up
				extReqMap[uFloor].addUpUser(id); //External User Up
			else if (uDir == "down") //Going Down
				extReqMap[uFloor].addDownUser(id); //External User Down
			cTime++; //Increment Time
		}
		if (fin.good()) //File good
			fin >> uTime; //New Time
		else
			uTime = -1;

		id++; //Increment next ID
	}
	//fin.close(); //Close File
}

void elevator(double& cTime, map<int, InternalRequests>::iterator& intIter, map<int, InternalRequests>& intReqMap, map<int, User>& uMap, map<int, ExternalRequests>& extReqMap)
{///run this function in parallel
	if ((*intIter).second.getDir() == "up") //Elevator is going up
	{
		if ((*intIter).second.hasExitUser()) //Let People Off
		{
			while ((*intIter).second.hasExitUser()) //Has User getting off
			{
				cTime++; //Increment time
				int id = (*intIter).second.removeUser(); //Remove passenger
				uMap[id].setFinalTime(cTime); //Set their arrival time
			}
		}

		if (extReqMap.count(intIter->first) > 0) //Let people on
		{
			while (extReqMap[intIter->first].hasUpUsers()) //External has Users going up
			{
				cTime++; //Increment time
				int id, dFloor; //Create Variables
				double uTime = 0;

				id = extReqMap[intIter->first].getUpUser(); //Get the first user
				uTime = uMap[id].getStartTime(); //Get the request time

				dFloor = uMap[id].getDestFloor(); //Get destination
				if (intReqMap.count(dFloor) > 0)//If key exists
				{
					intReqMap[dFloor].addUser(id); //Add user for Internal
				}
				else //key does not exist
				{
					InternalRequests intReq;
					intReq.addUser(id); //Create the User ID
					intReqMap.insert(pair<int, InternalRequests>(dFloor, intReq)); //Add to Map Internal
				}
			}
			if (!extReqMap[intIter->first].hasDownUsers()) //No down users
			{
				extReqMap.erase(intIter->first); //Delete External Request
			}
		}

		//gets current and next floors
		int nextExtFloor = intIter->first; //Next stop
		if (!extReqMap.empty()) //If people waiting
		{
			map<int, ExternalRequests>::iterator extIter = extReqMap.upper_bound(intIter->first); //Iterator on upper
			while (extIter != extReqMap.end()) //Check all floors above elevator
			{
				if ((*extIter).second.hasUpUsers()) //If external up users
				{
					nextExtFloor = (*extIter).first; //Go to that floor
					break;
				}
				++extIter; //Add a new passenger
			}
		}
		int currentIntFloor = (*intIter).first, nextIntFloor = (*intIter).first; //Start floor, end floor
		++intIter; //Add Internal
		if (intIter != intReqMap.end()) //More internal passengers
			int nextIntFloor = (*intIter).first; //Next floor
		--intIter; //Remove a passenger


		//moves elevator
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		if (intReqMap.size() == 1)//If no more int req
		{


			if (extReqMap.empty())//no more req
				(*intIter).second.setDir("");
			else if (nextExtFloor > currentIntFloor)//go to next ext up user
			{
				InternalRequests intReq;
				intReqMap.insert(pair<int, InternalRequests>(nextExtFloor, intReq)); //Add new request
				ticks(cTime, intIter, intReqMap); //Change time
												  //++intIter;
			}
			else //Go to extReqMap.end()
			{
				map<int, ExternalRequests>::iterator extEnd = extReqMap.end(); //Create iterator
				--extEnd; //Decrease iterator
				if ((*extEnd).first > currentIntFloor) //Going up
				{
					InternalRequests intReq;
					intReqMap.insert(pair<int, InternalRequests>((*extEnd).first, intReq)); //New Internal request
					ticks(cTime, intIter, intReqMap);
					//++intIter;					
				}
				else if ((*extEnd).first < currentIntFloor)//Going down
				{
					(*intIter).second.setDir("down"); //Going down
					InternalRequests intReq;
					intReqMap.insert(pair<int, InternalRequests>((*extEnd).first, intReq)); //New Internal Request
					ticks(cTime, intIter, intReqMap);
					//--intIter;
				}
				else //is on same floor
				{
					(*intIter).second.setDir("down"); //Going down
				}
			}

		}
		else if (currentIntFloor != nextIntFloor) //If not at top req, go to next floor
		{
			if (currentIntFloor < nextExtFloor && nextExtFloor < nextIntFloor) //Next ext up user is inbetween int req
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
		else if (currentIntFloor == nextIntFloor) //No more Internal Up Requests
		{
			if (extReqMap.empty()) //No External Requests
			{
				(*intIter).second.setDir("down"); //Going down
				ticks(cTime, intIter, intReqMap);
				//--intIter;				
			}
			else if (nextExtFloor > currentIntFloor) //External Up user above current floor
			{
				//Go that floor
				InternalRequests intReq;
				intReqMap.insert(pair<int, InternalRequests>(nextExtFloor, intReq));
				ticks(cTime, intIter, intReqMap);
				//++intIter;
			}
			else //go to extReqMap.end()
			{
				map<int, ExternalRequests>::iterator extEnd = extReqMap.end(); //Iterator to end
				--extEnd; //Decrement one spot
				if ((*extEnd).first > (*intIter).first) //Going up
				{
					InternalRequests intReq;
					intReqMap.insert(pair<int, InternalRequests>((*extEnd).first, intReq));
					ticks(cTime, intIter, intReqMap);
					//++intIter;
				}
				else if ((*extEnd).first < (*intIter).first) //Going down
				{
					(*intIter).second.setDir("down"); //Go down
					InternalRequests intReq;
					intReqMap.insert(pair<int, InternalRequests>((*extEnd).first, intReq));
					ticks(cTime, intIter, intReqMap);
					//--intIter;
				}
				else //Is on same floor
				{
					(*intIter).second.setDir("down"); //Go down
				}
			}
		}
	}

	//Elevator is going down
	else if ((*intIter).second.getDir() == "down")
	{
		if ((*intIter).second.hasExitUser()) //Lets people off
		{
			while ((*intIter).second.hasExitUser()) //Has an exitter
			{
				cTime++; //Increment time
				int id = (*intIter).second.removeUser(); //Remove the Passenger
				uMap[id].setFinalTime(cTime); //Set arrival time
			}
		}
		if (extReqMap.count(intIter->first) > 0) //Lets people on
		{
			while (extReqMap[intIter->first].hasDownUsers()) //Need to go down
			{
				cTime++;
				int id = extReqMap[intIter->first].getDownUser(); //Set ID for going down
				int dFloor = uMap[id].getDestFloor(); //Set ending floor
													  /// this code is reading in the wrong user
													  /// /////////////////////////////////////////////// Redacted code from the US Gov
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
													  // 888'Y88     e   e     888 ///////////   
													  ///888, 'Y    d8b d8b    888 //////////
													  // 888C8     e Y8b Y8b   888 /////////
													  ///888 "    d8b Y8b Y8b  888  ,d ////
													  // 888     d888b Y8b Y8b 888, d88 //
													  // ////////////////////////////////
													  /// //////////////////////////////
													  // //////////////////////////////
													  /// ////////////////////////////
													  // ////////////////////////////


				if (intReqMap.count(dFloor) > 0) //If key exists
				{
					intReqMap[dFloor].addUser(id); //Add the user riding
				}
				else //Key does not exist
				{
					InternalRequests intReq;
					intReq.addUser(id); //Create the new User
					intReqMap.insert(pair<int, InternalRequests>(dFloor, intReq)); //Add user to the requests
				}
			}
			if (!extReqMap[intIter->first].hasUpUsers()) //External has no up Users
			{
				extReqMap.erase(intIter->first); //Erase
			}
		}
		//Gets current and next floors
		int nextExtFloor = intIter->first;
		if (!extReqMap.empty())
		{
			map<int, ExternalRequests>::iterator extIter = extReqMap.lower_bound(intIter->first);
			while (extIter != extReqMap.begin()) //check all floors above elevator
			{
				if ((*extIter).second.hasDownUsers()) //Needs to go down
				{
					nextExtFloor = (*extIter).first; //Next floor is External User
					break;
				}
				--extIter; //Decrement
			}
		}
		int currentIntFloor = (*intIter).first, nextIntFloor = (*intIter).first; //Set current, ending floor
		--intIter;
		if (intIter != intReqMap.end()) //Not at the end of internal requests
			int nextIntFloor = (*intIter).first; //Go to next internal request
		++intIter;

		//Moves elevator
		if (intReqMap.size() == 1)// if no more req
		{
			if (extReqMap.empty()) //No more Requests
				(*intIter).second.setDir(""); //No current direction
			else if (nextExtFloor < currentIntFloor) //Go to next External down user
			{
				InternalRequests intReq;
				intReqMap.insert(pair<int, InternalRequests>(nextExtFloor, intReq));
				ticks(cTime, intIter, intReqMap); //Add the new user

			}
			else //Go to extReqMap.begin()
			{
				map<int, ExternalRequests>::iterator extEnd = extReqMap.begin(); //Reset Iterator
				if ((*extEnd).first > currentIntFloor) //Going up
				{
					(*intIter).second.setDir("up"); //Set direction, Up
					InternalRequests intReq;
					intReqMap.insert(pair<int, InternalRequests>((*extEnd).first, intReq));
					ticks(cTime, intIter, intReqMap); //Add a new passenger

				}
				else if ((*extEnd).first < currentIntFloor)//going down
				{
					InternalRequests intReq;
					intReqMap.insert(pair<int, InternalRequests>((*extEnd).first, intReq));
					ticks(cTime, intIter, intReqMap); //Add a new passenger

				}
				else //Is on same floor
				{
					(*intIter).second.setDir("down"); //Begin going down
				}
			}
		}
		else if (intIter != intReqMap.begin()) //If not at bottem, go to next floor
		{ //Check all floors inbetween the floors
			if (currentIntFloor > nextExtFloor && nextExtFloor > nextIntFloor) //Next ext down user is above current
			{
				InternalRequests intReq;
				intReqMap.insert(pair<int, InternalRequests>(nextIntFloor, intReq));
				ticks(cTime, intIter, intReqMap); //Add new Internal User

			}
			else if (nextExtFloor > nextIntFloor) //Next ext down user between the floors
			{
				ticks(cTime, intIter, intReqMap);
			}
		}
		else if (currentIntFloor == nextIntFloor) //Is at bottom with requests for upper floors
		{
			if (extReqMap.empty()) //No External requests
			{
				(*intIter).second.setDir("up"); //Begin going up
				ticks(cTime, intIter, intReqMap);

			}
			else if (nextExtFloor < currentIntFloor) //Ext down user below current floor
			{
				//Go that floor
				InternalRequests intReq;
				intReqMap.insert(pair<int, InternalRequests>(nextExtFloor, intReq));
				ticks(cTime, intIter, intReqMap); //New Internal user

			}
			else //Go to extReqMap.begin()
			{
				map<int, ExternalRequests>::iterator extEnd = extReqMap.begin();
				if ((*extEnd).first > (*intIter).first) //Going up
				{
					(*intIter).second.setDir("up"); //Begin going up
					InternalRequests intReq;
					intReqMap.insert(pair<int, InternalRequests>((*extEnd).first, intReq));
					ticks(cTime, intIter, intReqMap); //New user

				}
				else if ((*extEnd).first < (*intIter).first) //Going down
				{
					InternalRequests intReq;
					intReqMap.insert(pair<int, InternalRequests>((*extEnd).first, intReq));
					ticks(cTime, intIter, intReqMap); //New user

				}
				else //Is on same floor
				{
					(*intIter).second.setDir("down"); //Start going down
				}
			}
		}
	}

	//Elevator is not moving
	else if ((*intIter).second.getDir() == "")
	{///make sure to only send closest elevator to new external requests
		if (!extReqMap.empty())
		{
			map<int, ExternalRequests>::iterator down = extReqMap.lower_bound(intIter->first);
			if (down == extReqMap.end()) //Last request is down
				--down;
			map<int, ExternalRequests>::iterator up = extReqMap.upper_bound(intIter->first);
			if (up == extReqMap.end()) //Last request is up
				--up;

			if (up->first - intIter->first <= down->first - intIter->first)
			{
				InternalRequests intReq;
				intReqMap.insert(pair<int, InternalRequests>(up->first, intReq));
				(*intIter).second.setDir("up"); //Go up
				ticks(cTime, intIter, intReqMap);

			}
			else
			{
				InternalRequests intReq;
				intReqMap.insert(pair<int, InternalRequests>(down->first, intReq));
				(*intIter).second.setDir("down"); //Go down
				ticks(cTime, intIter, intReqMap);

			}
		}
	}
}

void ticks(double& cTime, map<int, InternalRequests>::iterator& intIter, map<int, InternalRequests>& intReqMap)
{
	int floorRate = 1;
	if ((*intIter).second.getDir() == "up") //If going up
	{
		int f1 = intIter->first; //Save user
		++intIter;
		if (intIter == intReqMap.end()) //At end
			--intIter;
		else
		{
			int f2 = intIter->first; //Save user
			cTime += floorRate * abs(f1 - f2);
			intReqMap.erase(f1); //Delete User
			(*intIter).second.setDir("up"); //Go up
		}
	}
	else if ((*intIter).second.getDir() == "down") //If going down
	{
		int f1 = intIter->first; //Save user
		--intIter;
		if (intIter == intReqMap.end()) //At end
			--intIter;
		else
		{
			int f2 = intIter->first; //Save user
			cTime += floorRate * abs(f1 - f2);
			intReqMap.erase(f1); //Delete User
			(*intIter).second.setDir("down"); //Go down
		}
	}

}

void userOutput(map<int, User>& uMap)
{
	ofstream fout("output.txt"); //Output file

	fout << "User\tStart Time\tFinal Time\t Start Floor\tDestination Floor\n"; //Output format
	for (map<int, User>::iterator iter = uMap.begin(); iter != uMap.end(); iter++)
	{ //Output the map
		fout << (*iter).first << "\t\t" << (*iter).second.getStartTime() << "\t\t\t" << (*iter).second.getFinalTime() << setw(13) <<
			(*iter).second.getStartFloor() << "\t\t\t\t" << (*iter).second.getDestFloor() << endl;
	}
	fout.close(); //Close the file
}