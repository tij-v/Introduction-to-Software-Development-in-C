/* 

 * Author: Shitij Vishwakarma, svishwakarma2015@my.fit.edu 

 * Course: CSE 1002, Section 01/02, Spring 2018 

 * Project: stock

 */

/*Libraries to be used*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//declaring a struct "STOCK" with the following fields:
typedef struct{
	char date[20];
	float open;
	float high;
	float low;
	float close;
	float vol;
	float adj;
} STOCK;

//main function//
int main(int argc, char *argv[]){

	//opening the file//
	FILE *file_ptr;
	//argv[0] = ./stock, argv[1] = DJIA.csv  //

	//the code below dynamically constructs an array of STOCK with size of 5000000
	STOCK *n = (STOCK*) malloc (sizeof(STOCK)* 5000000);
	//the code below is the call to open the file DJIA.csv from the system
	file_ptr = fopen(argv[1], "r");
	if (file_ptr == NULL){
		perror("Error");
		return -1;
	}

	int count = 0;
	char array[499];

	//the code below gets "rid" of the first line in the file
	fgets(array, 499, file_ptr);
	int i = 0;

	//the loop below executes until the end of the file. 
	while(fgets(array, 499, file_ptr) != NULL){
		//using strtok to tokenize with a ",".
		//the purpose is to read everything until a "," is read, then 
		//copy/allocate the value into the respective fields.
		char *token = strtok(array, ",");

		strcpy(n[i].date, token);

		token = strtok(NULL, ",");
		n[i].open = atof(token);

		token = strtok(NULL, ",");
		n[i].high = atof(token);

		token = strtok(NULL, ",");
		n[i].low = atof(token);	
		
		token = strtok(NULL, ",");
		n[i].close = atof(token);	

		token = strtok(NULL, ",");
		n[i].vol = atof(token);

		token = strtok(NULL, ",");
		n[i].adj = atof(token);

		i++;
		count++;
	}	

	//declaring the a storage variable of STOCK type.
	STOCK storage;

	float temp = 0;
	int j = 0;

	//the loop below reads "encounters" a high value and assigns it to temp.
	//it also assigns values to the other respective fields, for the particular "highest" value.
	//if the comparison fails then the index is incremented.
	while(j < count){
		if(n[j].high > temp){
			temp = n[j].high;
			strcpy(storage.date, n[j].date);
			storage.open = n[j].open;
			storage.high = n[j].high;
			storage.low = n[j].low;
			storage.close = n[j].close;
			storage.vol = n[j].vol;
			storage.adj = n[j].adj;
			j++;
		}
		else{
			j++;
		}
	}
	//when the loop completes, "storage" variable now conrains the highest value
	//with the respective information about other fields; which is printed out below.

	printf("\n");
	printf("Date: %s\n\nOpen: %.2f\n\nHigh: %.2f\n\nLow: %.2f\n\nClose: %.2f\n\nVolume: %.2f\n\nAdj. Close: %.2f\n\n", storage.date, storage.open, storage.high, storage.low, storage.close, storage.vol, storage.adj);
	
	fclose(file_ptr);
	return 0;
}


/*		END OF THE PROGRAM		*/