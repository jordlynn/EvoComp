#include <iostream>
#include <cstdlib>
#include <cmath>

double exponential(int j){
	return j*j;
}

double linear(int j){
	return j;
}
 
double RandFunc(int x1, int x2, int x3){
	double toReturn = 0;
	toReturn = ((x1 * 2)*(x2+1) - (pow(x2,2)) + 5*x3 + (pow(x3, 3)) +5);
	//toReturn = pow(x1, 3) + pow(x2, 3) + pow(x3, 3);
	return toReturn;
}