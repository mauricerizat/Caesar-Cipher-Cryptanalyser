/*
CAESAR CIPHER ANALYSER
*/

#include "header.h"

//Function to round up given number num up to place decimal places
float roundN (float num, int place)
{
	int n = num * pow(10.0, place+1); 
	
	int r = n % 10;
	
	n /= 10;
	
	if (r >= 5)
		n += 1;
		
	num = n / pow(10.0, place);
	
	return num;
}


