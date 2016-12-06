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
	float G = 6.67408*pow(10,-11);//gravitational constant in SI units
	float Ms = 1.98855*pow(10,30);//mass of sun in kg
	float Me = 5.9722*pow(10,24);//mass of earth in kg
	float k = -G*(Ms+Me);//total constant for 2 body problem with 1 body of mass Me
	float x = 1.49598*pow(10,11), y = 0; 
	cout << "x0 = " << x << endl;
	//initial distance = 1au in x direction, 0 in y direction. Value given here in mm
	float t = 0; //initial time is 0
	float ax, ay; //a is acceleration
	float vx = 0, vy = 30000;
	//initial velocity set to 0 in x direction, 30 km/s in y direction. 
	//This is the speed of the Earth's orbit 
	float deltaT = 30.44*24*3600;
	// deltaT is measured in seconds; 3600 is the number of seconds in an hour; 
	//24 is the number of hours in two days, so deltaT = 1 days 
	float dx1 = 0, dx2 = 0, dx3 = 0, dx4, dy1 = 0, dy2 = 0, dy3 = 0, dy4, dx, dy;
	float dvx1, dvx2, dvx3, dvx4, dvy1, dvy2, dvy3, dvy4, dvx, dvy;
	float r = sqrt((x*x) + (y*y));// r is the straight line distance between the two bodies
	//Now we go mental with Runge-Kutta stuff
	float ddx1 = x + dx1/2, ddy1 = y + dy1/2;
	float ddx2 = x + dx2/2, ddy2 = y + dy2 /2;
	float ddx3 = x + dx3 / 2, ddy3 = y + dy3/2;
	float dr1 = sqrt((ddx1*ddx1) + (ddy1*ddy1));
	float dr2 = sqrt((ddx2*ddx2) + (ddy2*ddy2));
	float dr3 = sqrt((ddx3*ddx3) + (ddy3*ddy3));
	//loop time
	int j;
	ofstream mehfile;
	mehfile.open("data.txt", ios::trunc);
	ofstream secondfile;
		secondfile.open("data2.txt");//save meh data pls
   cout << "k = "<< k << endl;
	for (j = 0; j < 12000000; j++)//we repeat the simulation 190 times (just over a year)
		
	{
		cout << "ROUND " << j + 1 << endl;
		ax = (k*x) / pow(r, 3);
		//cout << "ax = " << ax << endl;
		ay = (k*y) / pow(r, 3);
		//cout << "ay = " << ay <<endl;

		//dx1 = deltaT*vx;
		//dy1 = deltaT*vy;
		//dvx1 = deltaT*ax;
		//dvy1 = deltaT*ay;

		//dx2 = deltaT*(vx + 0.5*dvx1);
		//dy2 = deltaT*(vy + 0.5*dvy1);
		//dvx2 = deltaT*((k*ddx1) / pow(dr1, 3));
		//dvy2 = deltaT*((k*ddy1) / pow(dr1, 3));
		//in other words dx2 is deltaT*a when x = x + dx1/2

		//dx3 = deltaT*(vx + 0.5*dvx2);
		//dy3 = deltaT*(vy + 0.5*dvy2);
		//dvx3 = deltaT*((k*ddx2) / pow(dr2, 3));
		//dvy3 = deltaT*((k*ddy2) / pow(dr2, 3));

		//final step
		//dx4 = deltaT*(vx + 0.5*dvx3);
		//dy4 = deltaT*(vy + 0.5*dvy3);
		//dvx4 = deltaT*((k*ddx3) / pow(dr3, 3));
		//dvy4 = deltaT*((k*ddy3) / pow(dr3, 3));

		//dx = (dx1 + 2 * dx2 + 2 * dx3 + dx4) / 6;
		//dy = (dy1 + 2 * dy2 + 2 * dy3 + dy4) / 6;
		//dvx = (dvx1 + 2 * dvx2 + 2 * dvx3 + dvx4) / 6;
		//dvy = (dvy1 + 2 * dvy2 + 2 * dvy3 + dvy4) / 6;

		//x = x + dx;
		//y = y + dy;
		//vx = vx + dvx;
		//vy = vy + dvy;
		//ignore the old Euler stuff. Ew. 	
		vx = vx + deltaT*ax;
		//cout << "vx = " << vx << endl;
		vy = vy + deltaT*ay;
		//cout << "vy = " << vy << endl;
	    x = x + deltaT*vx;
		cout << "x = " << x << endl;
		y = y + deltaT*vy;
		//cout << "y = " << y << endl;
		r = sqrt((x*x) + (y*y));
		//cout << "r = " << r << endl;
		
		mehfile << x << " " << endl;
		secondfile << y << endl;
		
	}
	
	mehfile.close();
	secondfile.close();
	int integer;
	cout << "Insert any integer the press enter to exit." << endl;
	cin >> integer;
	return 0;
	
}

