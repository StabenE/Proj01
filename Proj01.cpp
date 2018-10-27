// Proj1.cpp
//Evan Staben

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::atof;
using std::getline;
using std::istringstream;
using std::noskipws;

int day = 1;
int week = 1;
bool cont = true;  
string input;
int dailyData[14][4]; //Order of storage = Sum, Max, Min, Count
int weeklyData[2][5];  //Order of storage = Sum, Max, Min, Count, DeltaCount

bool CheckForFloat(string);
void weekMath();
void dataProcess(double);
void dayReport();
void weekReport();
void nextDay();

void minPrep();
void inputCheck(string);
int main()
{
	cout << "Welcome to your blood sugar monitor, enter a number to record a reading, nextDay to change to the next day, Day to print out a summary for that day, and Week to print out a summary for that week. Enter end to stop the program." << endl;
	minPrep();
	while(cont)
	{
		cout << "Enter readings for day " << day << " week " << week << ".";
		getline(cin,input);
		inputCheck(input);
	}
}

void minPrep() //set min values to very high number so zero isn't always min.
{
	for (int i = 0; i < 14; i++)
		dailyData[i][2] = 1000;
}
bool CheckForFloat(string input)   //check string for float
{
	istringstream isThingy(input);
	float check;
	isThingy >> noskipws >> check;
	return isThingy.eof() && !isThingy.fail();
}
void weekMath()  //calculations for per week data
{
	int startDay = 0;
	if (week == 2)//change starting index depending on week
	{
		startDay = 6;
	}
	int temp = 0;
	for (int i = 0; i < 7; i++)  // add up all daily sums to get weekly sum
	{
		temp += dailyData[(startDay + i)][0];
	}
	weeklyData[week - 1][0] = temp;
	temp = weeklyData[startDay][1];   //compare all daily maxes to get the greatest
	for (int i = 0; i < 7; i++)
	{
		if (dailyData[(startDay + i)][1] > temp)
		{
			temp = dailyData[(startDay + i)][1];
		}
	}
	weeklyData[week - 1][1] = temp;
	temp = weeklyData[startDay][2];    //compare all daily mins to get the smallest
	for (int i = 0; i < 7; i++)
	{
		if (dailyData[(startDay + i)][2] < temp)
		{
			temp = dailyData[(startDay + i)][2];
		}
	}
	weeklyData[week - 1][2] = temp;
	for (int i = 0; i < 7; i++)
	{
		temp += dailyData[(startDay + i)][3];
	}
	weeklyData[week - 1][3] = temp;
	int maxCount = 0;
	int minCount = 100000;
	for (int i = 0; i < 7; i++)
	{
		if (dailyData[(startDay + i)][3] > maxCount)
		{
			maxCount = dailyData[(startDay + i)][3];
		}
	}
	for (int i = 0; i < 7; i++)
	{
		if (dailyData[(startDay + i)][3] < minCount)
		{
			minCount = dailyData[(startDay + i)][3];
		}
	}
	weeklyData[week - 1][4] = (maxCount - minCount);
}
void dataProcess(double entry) // takes entered double and checks it against existing data
{
	int dayExact = (day - 1);
	if (week == 2)   // factor in 7 days per week
	{
		dayExact += 7;
	}
	dailyData[dayExact][0] += entry;    //agregate readings per day
	if (entry > dailyData[dayExact][1])  //if new data is greater than max for day change it to new max
	{
		dailyData[dayExact][1] = entry;
	}
	if (entry < dailyData[dayExact][2])  //if new data is less than min change it to new min. 
	{
		dailyData[dayExact][2] = entry;
	}
	dailyData[dayExact][3]++;  // increment readings count
}
void dayReport()   //print out report for current day
{
	cout << "On day # " << day << " week # " << week << " the Sum, Max, Min, and Count of your blood sugar readings were respectively: " << dailyData[day - 1][0] << ", " << dailyData[day - 1][1] << ", " << dailyData[day - 1][2] << ", " << dailyData[day - 1][3];
}
void weekReport()  //prints out report for current week
{
	weekMath();
	cout << "On week # " << week << " the Sum, Max, Min, Count, and Max Delta in readings taken are respectively: " << weeklyData[week - 1][0] << ", " << weeklyData[week - 1][1] << ", " << weeklyData[week - 1][2] << ", " << weeklyData[week - 1][3] << ", " << weeklyData[week - 1][4];
}
void nextDay()    //moves to next day
{
	weekMath();
	if (day == 7)
	{
		week++;
		day = 1;
	}
	else if ((day == 7) && (week == 2))
	{
		cont = false;
	}
	else
	{
		day++;
	}
}

void inputCheck(string entry) //takes user input directly and forwards it to relevant function
{
	if (CheckForFloat(entry))//Check entry for number
	{
		double entryDouble = atof((entry).c_str());
		if (entryDouble >= 0)
		{
			dataProcess(entryDouble);
		}
	}
	else if (entry == "end")
	{
		cont = false;
	}
	else if (entry == "nextDay")
	{
		nextDay();
	}
	else if (entry == "Day")
	{
		dayReport();
	}
	else if (entry == "Week")
	{
		weekReport();
	}

}
