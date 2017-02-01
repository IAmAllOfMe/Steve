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
float ty = 3.145*pow(10, 7);//number of seconds in a year
float au = 1.49598*pow(10, 11); //one Astronomical Unit converted into metres
float pi = 3.1415926536;
float n = 1;
float r20 = 3 * au;//initial outer disc inner edge
float s1 = 27000;// in kg/m^2
//s stands for sigma in the Terquem paper

//Declare acceleration functions
double accelx(double x, double y, double vx, double vy, double t);
double accely(double x, double y, double vx, double vy, double t);

//Define function for accleration in x direction
double accelx(double x, double y, double vx, double vy, double t) {
	double r = sqrt((x*x) + (y*y));
	double H = 0.05*r;
	double s;
	double r2 = r20 + (10 * au - r20)*t / (3.2*pow(10, 6));
	if ( r < r2) {
	 s = 0;
	}
	else {

		 s = 0.1*(s1 / r)*au;
	}
	//using equations 1 and 7 in the Terquem paper. At some point she also multiplies the whole thing by 0.1
	
	double tmig = ty*(2 /3.8)*(Ms / Me)*pow(0.05, 2)*(Ms / (2*pi*s*au*au))*pow(au / r, 0.5);
		//assuming eccentricity = 0

	double tecc = 0.1*ty*(Ms/Me)*pow(0.05,4)*(Ms / (2 * pi*s*au*au))*pow(au / r, 0.5);
	//assuming eccentricity = 0
	double ax;
	
	if(r < r2+(au/4)){
		ax = (-G*(Ms + Me)*x) / pow(r, 3) + vx / tmig + (2 / (pow(r, 2)*tecc))*(vx*x + vy*y)*x;
	}
	else {
		
		ax = (-G*(Ms + Me)*x) / pow(r, 3) - vx / tmig - (2 / (pow(r, 2)*tecc))*(vx*x + vy*y)*x;
	}
	return ax;
}
//Define function for accleration in y direction
double accely(double x, double y, double vx, double vy, double t) {
	double r = sqrt((x*x) + (y*y));
	double H = 0.05*r;
	double s;
	double r2 = r20 + (10 * au - r20)*t / (3.2*pow(10, 6));
	
	if ( r < r2) {
		s = 0;
	}
	else {
		s = 0.1*(s1 / r)*au;
		
	}
	
	//using equations 1 and 7 in the Terquem paper
	
	double tmig = ty*(2 / 3.8)*(Ms / Me)*pow(0.05, 2)*(Ms / (2 * pi*s*au*au))*pow(au / r, 0.5);
	//assuming eccentricity = 0
	//tmig is in years, so we multiply by ty to give it's value in seconds
	
	double tecc = 0.1*ty*(Ms / Me)*pow(0.05, 4)*(Ms / (2 * pi*s*au*au))*pow(au / r, 0.5);
	//assuming eccentricity = 0
	//tecc is in years, so we multiply by ty to give it's value in seconds
	double ay;
	//cout << tmig << endl;
	if(r < r2+(au/4)){
		ay = (-G*(Ms + Me)*y) / pow(r, 3) + vy / tmig + (2 / (pow(r, 2)*tecc))*(vx*x + vy*y)*y;
	}
	else {
		
		ay = (-G*(Ms + Me)*y) / pow(r, 3) -vy / tmig - (2 / (pow(r, 2)*tecc))*(vx*x + vy*y)*y;
	}
	//cout << tecc << endl; 
	return ay;
}

int main()
{   
	//initial distance = 10au in x direction, 0 in y direction. Value given here in m
	double x = 4*au, y = 0;
	double r = sqrt(x*x + y*y);
	
	//initial velocity = circular orbit velocity in y direction, 0 in x direction. Value here given in m/s
	double vx = 0, vy = sqrt((G*Ms)/x);

	//acceleration in x and y directions defined
	double ax, ay;

	//timestep, h, for the Runge-Kutta method will be 12 hours. h is given in seconds.
	double h = 12 * 3600;

	//various useful Runge-Kutta things declared here
	double dx1, dx2, dx3, dx4, dy1, dy2, dy3, dy4;
	double dvx1, dvx2, dvx3, dvx4, dvy1, dvy2, dvy3, dvy4;
	double dx, dy, dvx, dvy;

	//save the recorded x and y values in text files
	ofstream mehfile;
	mehfile.open("xvalues.txt", ios::trunc);
	ofstream secondfile;
	secondfile.open("yvalues.txt");
	double t = 0;//time passed in years
	int j;
	for (j = 0; j < 2* 365400; j++) {
		//cout << "ROUND " << j + 1 << endl;
		//j = 12 hours
		t = (j*12*3600)/ ty;

		ax = accelx(x, y, vx, vy, t);
		ay = accely(x, y, vx, vy, t);
		
		dx1 = h*vx;
		dy1 = h*vy;
		dvx1 = h*ax;
		dvy1 = h*ay;

		dx2 = h*(vx + (dvx1 / 2));
		dy2 = h*(vy + (dvy1 / 2));
		dvx2 = h*accelx(x + dx1 / 2, y + dy1 / 2, vx + dvx1 / 2, y + dvy1 / 2, t);
		dvy2 = h*accely(x + dx1 / 2, y + dy1 / 2, x + dvx1 /  2, vy + dvy1 / 2, t);

		dx3 = h*(vx + (dvx2 / 2));
		dy3 = h*(vy + (dvy2 / 2));
		dvx3 = h*accelx(x + dx2 / 2, y + dy2 / 2, vx + dvx2 / 2, vy + dvy2 / 2, t);
		dvy3 = h*accely(x + dx2 / 2, y + dy2 / 2, vx + dvx2 / 2, vy + dvy2 / 2, t);

		dx4 = h*(vx + dvx3);
		dy4 = h*(vy + dvy3);
		dvx4 = h*accelx(x + dx3, y + dy3, vx + dvx3 / 2, vy + dvy3 / 2, t);
		dvy4 = h*accely(x + dx3, y + dy3, vx + dvx3 / 2, vy + dvy3 / 2, t);

		dx = (dx1 + 2 * dx2 + 2 * dx3 + dx4) / 6;
		dy = (dy1 + 2 * dy2 + 2 * dy3 + dy4) / 6;
		dvx = (dvx1 + 2 * dvx2 + 2 * dvx3 + dvx4) / 6;
		dvy = (dvy1 + 2 * dvy2 + 2 * dvy3 + dvy4) / 6;

		x = x + dx;
		y = y + dy;
		vx = vx + dvx;
		vy = vy + dvy;
		r = sqrt((x*x) + (y*y));
		//cout << "Year" << t << endl;
		cout << "r = " << r / au << " AU" << endl;
		
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

