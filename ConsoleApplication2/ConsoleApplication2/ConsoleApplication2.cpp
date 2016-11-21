// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <string>
#include <stdio.h>

using namespace std;

int main()
{
	float G = 6.67*pow(10,-11);//gravitational constant
	float Ms = 1.99*pow(10,30);//mass of sun
	float Me = 5.97*pow(10,24);//mass of earth
	float k = -G*(Ms+Me);//total constant for 2 body problem with 1 body of mass Me
	float x = 1.50*pow(10,11), y = 0; //initial distance = 1au in x direction, 0 in y direction. Value given here in mm
	float t = 0; //initial time is 0
	float ax, ay; //a is acceleration
	float vx = 0, vy = 30000;//initial velocity set to 0 in x direction, 30 km/s in y directio 
	float deltaT = 48*3600; // deltaT is measured in seconds; 3600 is the number of seconds in an hour; 48 is the number of hours in two days, so deltaT = 2 days 
	float r = sqrt((x*x) + (y*y));// r is the straight line distance between the two bodies
	int j;
	cout << "k = "<< k << endl;
	for (j = 0; j < 5; j++)//we repeat the simulation 5 times
		
	{
		cout << "ROUND " << j + 1 << endl;
		ax = (k*x) / pow(r, 3);
		cout << "ax = " << ax << endl;
		ay = (k*y) / pow(r, 3);
		cout << "ay = " << ay <<endl;
		vx = vx + deltaT*ax;
		cout << "vx = " << vx << endl;
		vy = vy + deltaT*ay;
		cout << "vy = " << vy << endl;
		x = x + deltaT*vx;
		cout << "x = " << x << endl;
		y = y + deltaT*vy;
		cout << "y = " << y << endl;
		r = sqrt((x*x) + (y*y));
		cout << "r = " << r << endl;
		


	}
	float poo;
	cout << "Insert any integer the press enter to exit." << endl;
	cin >> poo;
	return 0;

}

