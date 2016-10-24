// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <string>

using namespace std;

void Euler(float x, float y) {
	cout << "This will be the definition. Enter a number for x." << endl;
	cin >> x;
	cout << "Enter a number for y. The two numbers will be added together." << endl;
	cin >> y;
	cout <<" x + y = " << x + y << endl;

}

int main()
{
	cout << "If I have done this right then you should be reading these words now." << endl;
	cout << "I plan on starting by creating a C++ maths function for the Euler method of integration" << endl;
	cout << "Enter any integer and press enter." << endl;
	int poo;
	cin >> poo;
	Euler(1,6);
	cout << "Enter any integer and press enter to close the program" << endl;
	int poop;
	cin >> poop;
    return 0;
}

void Euler(float x, float y[])
{
}
