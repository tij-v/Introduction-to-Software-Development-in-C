/* 

 * Author: Shitij Vishwakarma, svishwakarma2015@my.fit.edu 

 * Course: CSE 1002, Section 01/02, Spring 2018 

 * Project: percolation

 */


/*Libraries to be used*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


//boolean expressions to be used
#define TRUE 1
#define FALSE 0


/*The functions below will be used*/
void declare_array(int size, int board[size][size]);
void random_generation(time_t t, int size, int board[size][size]);
int grid_check(int size, int board[size][size]);
long double function_scan(int size, int board[size][size]);


//main function: responsible of raking the input from the screen
//and calling the functions n-percolation times
//also responsible for printing the output to the screen
int main (int argc, char *argv[]){
	//argv[0] = ./percolation, argv[1] = size, argv[2] = number of percolations
	int i, num_of_iter, j, count = 0, size, iteration = 0;
	size = atoi(argv[1]);
	num_of_iter = atoi(argv[2]);
	time_t t;
	long double threshold = 0;
	int board[size][size];
	for(iteration = 0; iteration < num_of_iter; iteration++){
		declare_array(size, board);
		random_generation(t, size, board);
		threshold = function_scan(size, board) + threshold;
	}
	printf("\n");
	printf("The threshold is: %0.3Lf\n\n", (threshold/num_of_iter));
	printf("The last final grid is: \n\n");
	for (i = 0; i < size; ++i){
		for(j = 0; j < size; j++){
			if(board[i][j] == -1){
				if(j == size-1){
					printf("|-| ");
				}
				else{
					printf("|-");
				}
			}
			else if(board[i][j] == 1){
				if(j == size-1){
					printf("|+|" );
				}
				else{
					printf("|+");
				}
			}
		}
		printf("\n\n");
	}
	return 0;
}



//The function below resets a new array everytime
//the percolation is repeated.
void declare_array(int size, int board[size][size]){
	int i, j;

	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
			board[i][j] = -1;
		}
	}
}


//the sunction below randomly generates points on the array (with the limitation
//of the size of the array) from 0 to (size*size). 
void random_generation(time_t t, int size, int board[size][size]){
	srand(time(&t));
	int val, i, j, counter = 1;
	int t_size = size*size;
	int exit = 0;
	int iter = 0;
	int condition = FALSE;
	while (condition == FALSE){
		val = (int) rand()%t_size;
		for(i = 0; i < size && exit == 0; i++){
			for(j = 0; j < size; j++){
				if(counter == val){
					board[i][j] = 1;
					exit = 1;
					break;
				}
				else if (counter != val){
					counter++;
				}
			}
		}
		exit = 0;
		iter++;
		counter = 1;
		//The function call below checks if the return condition is TRUE
		// if it is FALSE => the points have not been percolated.
		//with the condition FALSE it repeats and allocates the new points, 
		//while reading the already assigned points and resetting them.
		condition = grid_check(size, board);
	}
}


//As explained above, the function below reads and checks if the grid has been 
//percolated or not. If it is not, then it returns the FALSE value, if it is then
//it returns the TRUE value. 
int grid_check(int size, int board[size][size]){
	int stopper = FALSE;
	int i = 0, j = 0, checker = 0;
	while(i < size){
		checker = 0;
		while(j < size && checker == 0){
			if(board[i][j] == 1 && board[i+1][j] == 1){
				checker = 1;
				stopper = TRUE;
			}
			else if(board[i][j] == 1 && board[i][j] != board[i+1][j]){
				if(board[i][j+1] == 1){
					checker = 1;
					stopper = TRUE;
				}
				else if(board[i][j+1] != 1){
					++j;
				}
			}
			else if(board[i][j] == -1){
				++j;
				stopper = FALSE;
			}
		}
		++i;
	}
	if(stopper == TRUE && i == size){
		return TRUE;
	}
	else if(stopper == FALSE && i == size){
		return FALSE;
	}
	
}


//The function below scans for the open spots, and the closed spots
//then divides them to return the average per percolation
long double function_scan(int size, int board[size][size]){
	int i, j;
	long double sum_o = 0, sum_n = 0;
	long double thresh = 0;
	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
			if(board[i][j] == 1){
				sum_n++;
			}
			else if(board[i][j] == -1){
				sum_o++;
			}
		}
	}
	thresh = (sum_o/sum_n);
	return thresh;
}
/*		END OF PROGRAM		*/
