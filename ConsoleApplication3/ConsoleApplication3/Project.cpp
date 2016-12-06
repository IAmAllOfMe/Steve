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

//Declare acceleration functions
double accelx(double x, double y);
double accely(double x, double y);

double accelx(double x, double y) {
	double r = sqrt((x*x) + (y*y));
   double ax = (-G*(Ms+Me)*x)/pow(r, 3);
	return ax;
}

double accely(double x, double y) {
	double r = sqrt((x*x) + (y*y));
	double ay = (-G*(Ms+Me)*y)/pow(r, 3 );
	return ay;
}

int main()
{
	double a, b, ax, ay;
	cin >> a;
	cin >> b;
	ay = accely(a, b);
	cout << ay << endl;
	int integer;
	cout << "Insert any integer the press enter to exit." << endl;
	cin >> integer;
    return 0;
}

