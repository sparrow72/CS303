// Josh Gregory, Zach Theiss, and Alex Malko
// CS 303 Project 2C
// Fall 2016
// Prof. Mohammad Kuhail

#ifndef _ExternalRequests
#define _ExternalRequests
#include "Requests.h"

class ExtReq :public Req
{
public:
	~ExtReq();
	void addFloor(); //adds external user floor to queue

private:


};
#endif	