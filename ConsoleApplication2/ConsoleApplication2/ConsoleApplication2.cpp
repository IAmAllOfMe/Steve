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
	float G = 6.67*(10 ^ -11);//gravitational constant
	float Ms = 1.99*(10 ^ 30);//mass of sun
	float Me = 5.97*(10 ^ 24);//mass of earth
	float k = -G*Ms*Me;//total constant for 2 body problem with 1 body of mass Me
	float r = 1.50*(10 ^ 8); //initial distance = 1au. Value given here in km
	float t = 0; //initial time is 0
	float a; //a is acceleration
	float v = 1*(10^8);//initial velocity set to 0
	float deltaT = 1000 * 3.15*(10 ^ 7); // 3.15*10^7 is the number of seconds in a year, so here deltaT = 1000yrs
	int j;
	for (j = 0; j < 5; j++)//we repeat the simulation 5 times
	{
		a = k / (r*r);
		cout << "a =" << a << endl;
		v = v + deltaT*a;
		cout << "v = " << v << endl;
		r = r + deltaT*v;
		cout << "r = " << r << endl;
		cout << "r/initial r =" << r / 1.5*(10 ^ 8) << endl;
		cout << "NEXT ROUND" << endl;



	}
	float poo;
	cout << "Insert any integer the press enter to exit." << endl;
	cin >> poo;
	return 0;

}

