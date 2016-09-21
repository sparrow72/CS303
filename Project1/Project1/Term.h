#pragma once
// Alex Malko, Zach Theiss, and Josh Gregory
// CS 303 Project 1
// Fall 2016
// Prof. Mohammad Kuhail
#include <iostream>
#include <list>
#include <string>
using namespace std;

class Term {
public:
	Term(); //Example can be found in List Header on BBoard
	list<string> add_poly(); //Add them together
	bool compare(); //Returns true or false based on correct or not
	void setPoly1(list<string>& polynom); //Setters
	void setPoly2(list<string>& polynom);
	void setResult(list<string>& polynom);
	list<string> getPoly1() { return poly1; } //Getters defined
	list<string> getPoly2() { return poly2; }
	list<string> getResult() { return result; }
	~Term(); //Example can be found in List Header on BBoard

private:
	list<string> poly1, poly2, result; //3 DLinked Lists

};