#include "averages.h"

//=====================================================================================
/*
average(): calculates average of a list

list: list that is being averaged
 
length: length of list

*/
//=====================================================================================
double average(int length, double list[length])
{
	double sum = 0.;
	for(int i = 0; i < length; i++)
	{
		sum += list[i];
	}
    return sum/((double)length);
}



//=====================================================================================
/*
average2(): calculates average of a squared list

list: list that is being squared then averaged
 
length: length of list

*/
//=====================================================================================
double average2(int length, double list[length])
{
	double sum = 0.;
	for(int i = 0; i < length; i++)
	{
		sum += (list[i]*list[i]);
	}
    return sum/((double)length);
}

