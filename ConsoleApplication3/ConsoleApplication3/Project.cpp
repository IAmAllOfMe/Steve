// ConsoleApplication3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <string>
#include <stdio.h>

using namespace std;

//Define constants
float G = 6.67*pow(10, -11);//gravitational constant in SI units
float Ms = 1.99*pow(10, 30);//mass of sun in kg
float Me = 5.97*pow(10, 24);//mass of earth in kg
float sigma1 = 2700; // in g/cm^2

//Declare acceleration functions
double accelx(double x, double y, double vx);
double accely(double x, double y, double vx);

//Define function for accleration in x direction
double accelx(double x, double y, double vx, double vy) {
	double r = sqrt((x*x) + (y*y));
	double v = sqrt((vx*vx) + (vy*vy));
	double sigma = sigma1 / r;// *1.49598*pow(10, 11);

	double tmig = 6 * pow(10, 5)*(1000 / sigma);//*1.49598*pow(10, 11)));
	//tmig value is actually the above multiplied by Me/Mp where Mp is the mass of the planet, but in this case Me = Mp, so Me/Mp = 1

	double tecc = 300 * (1000 / (sigma));//*1.49598*pow(10, 11)));
	//As with tmig, we multiply also by Me/Mp = 1
   
	double ax = (-G*(Ms+Me)*x)/pow(r, 3) - vx/tmig - (2/(pow(r,2)*tecc))*(vx*x+vy*y)*x;
	return ax;
}
//define function for accleration in y direction
double accely(double x, double y, double vx, double vy) {
	double r = sqrt((x*x) + (y*y));
	double v = sqrt((vx*vx) + (vy*vy));
	double sigma = sigma1 / r;//*1.49598*pow(10, 11)

	double tmig = 6 * pow(10, 5)*(1000 / (sigma));// *1.49598*pow(10, 11)));
	
	double tecc = 300 * (1000 / (sigma));//*1.49598*pow(10, 11)));

	double ay = (-G*(Ms + Me)*y) / pow(r, 3) - vy / tmig - (2 / (pow(r, 2)*tecc))*(vx*x + vy*y)*y;
	return ay;
}

int main()
{   
	//initial distance = 1au in x direction, 0 in y direction. Value given here in m
	double x = 1.49598*pow(10, 11), y = 0;
	double r = sqrt(x*x + y*y);
	
	//initial velocity = mean Earth velocity in y direction, 0 in x direction. Value here given in m/s
	double vx = 0, vy = 30000;

	//acceleration in x and y directions defined
	double ax, ay;

	//timestep, h, for the Runge-Kutta method will be 12 hours. h is given in seconds.
	double h = 12 * 3600;

	//various useful Runge-Kutta things defined here
	double dx1, dx2, dx3, dx4, dy1, dy2, dy3, dy4;
	double dvx1, dvx2, dvx3, dvx4, dvy1, dvy2, dvy3, dvy4;
	double dx, dy, dvx, dvy;

	//Declare sigma, surface denisty profile of the protoplanetary disc
	double sigma;

	//set initial value for M50, the mass of the disc within 50au of the sun. 
	double M50 = 0.1*Ms;

	//declare tmig and tecc, time for migration and eccentricity damping (see Terquem paper 2.2)
	double tmig, tecc;

	//save the recorded x and y values in text files
	ofstream mehfile;
	mehfile.open("xvalues.txt", ios::trunc);
	ofstream secondfile;
	secondfile.open("yvalues.txt");

	int j;
	for (j = 0; j < 2*365400; j++) {
		cout << "ROUND " << j + 1 << endl;

		ax = accelx(x, y, vx, vy);
		ay = accely(x, y, vx, vy);
		
		dx1 = h*vx;
		dy1 = h*vy;
		dvx1 = h*ax;
		dvy1 = h*ay;

		dx2 = h*(vx + (dvx1 / 2));
		dy2 = h*(vy + (dvy1 / 2));
		dvx2 = h*accelx(x + dx1 / 2, y + dy1 / 2, vx + dvx1 / 2, y + dvy1 / 2);
		dvy2 = h*accely(x + dx1 / 2, y + dy1 / 2, x + dvx1 /  2, vy + dvy1 / 2);

		dx3 = h*(vx + (dvx2 / 2));
		dy3 = h*(vy + (dvy2 / 2));
		dvx3 = h*accelx(x + dx2 / 2, y + dy2 / 2, vx + dvx2 / 2, vy + dvy2 / 2);
		dvy3 = h*accely(x + dx2 / 2, y + dy2 / 2, vx + dvx2 / 2, vy + dvy2 / 2);

		dx4 = h*(vx + dvx3);
		dy4 = h*(vy + dvy3);
		dvx4 = h*accelx(x + dx3, y + dy3, vx + dvx3 / 2, vy + dvy3 / 2);
		dvy4 = h*accely(x + dx3, y + dy3, vx + dvx3 / 2, vy + dvy3 / 2);

		dx = (dx1 + 2 * dx2 + 2 * dx3 + dx4) / 6;
		dy = (dy1 + 2 * dy2 + 2 * dy3 + dy4) / 6;
		dvx = (dvx1 + 2 * dvx2 + 2 * dvx3 + dvx4) / 6;
		dvy = (dvy1 + 2 * dvy2 + 2 * dvy3 + dvy4) / 6;

		x = x + dx;
		y = y + dy;
		vx = vx + dvx;
		vy = vy + dvy;
		cout << "x = " << x << endl;

		//storing generated x and y values
		mehfile << x << endl;
		secondfile << y << endl;
	}
	mehfile.close();
	secondfile.close();
	//this final bit is only so my pop up window doesn't automatically close itself
	int integer;
		cout << "Insert any integer the press enter to exit." << endl;
		cin >> integer;
		return 0;
}

