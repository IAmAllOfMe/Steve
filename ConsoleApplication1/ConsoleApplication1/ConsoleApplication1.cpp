// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <string>
#include <stdio.h>

using namespace std;

void Euler(float x, float y, int stepSize) // Practice attempt for y' - y = 0, y(0) = 1  
{
//initial conditions are set
int j;
for (j = 0; j < 5; j++)
{
	cout << "x = " << x << endl;
	x = x + stepSize;

	float slope = y;
	cout << "y = " << y << endl;
	y = y + slope;

}
}

int main()
{
	cout << "If I have done this right then you should be reading these words now." << endl;
	cout << "I plan on starting by creating a C++ maths function for the Euler method of integration" << endl;
	cout << "Enter any integer and press enter." << endl;
	int poo;
	cin >> poo;
	Euler(0, 1, 1);//First number = initial x, second number = initial y, third number = stepsize
		cout << "Enter any integer and press enter to close the program" << endl;
	int poop;
	cin >> poop;
    return 0;
}

void Euler(float x, float y[])
{
}
