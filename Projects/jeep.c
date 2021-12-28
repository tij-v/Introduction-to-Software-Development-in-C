/* 

 * Author: Shitij Vishwakarma, svishwakarma2015@my.fit.edu 

 * Course: CSE 1002, Section 01/02, Spring 2018 

 * Project: jeep

 */


//The following libraries will be used.
#include <stdio.h>
#include <math.h>

//The following function(s) will be used.
long double final_dist(int n, long double cap, long double rate);


//Main function.

int main(void){
	int i = 1, n;
	long double dist = 0, cap, rate, total;
	dist = 0;
	//Recursive loop to calculate the maximum distance.
	do{
	scanf("%d", &n);
	if(n == 0){
		break;
	}
	scanf("%Lf %Lf", &cap, &rate);
	total = 0;
	//function call.
	total = (((final_dist(n, cap, rate)*cap)/rate)*100);
	printf("%d. Distance is %.2Lf kilometers\n", i, total);

	i++;

	}
	while(n != 0);
	return 0;
}

//Recursive function.
long double final_dist(int n, long double cap, long double rate){
	//Basis case.
	if(n == 1){
		return 1;
	}
	if(n == 2){
		return 2;
	}
	//Recursion.
	return final_dist(n -1, cap, rate) +1 / (2* (double)n - 3);
}

/*END*/