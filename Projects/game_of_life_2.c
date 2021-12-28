/* 

 * Author: Shitij Vishwakarma, svishwakarma2015@my.fit.edu 

 * Course: CSE 1002, Section 01/02, Spring 2018 

 * Project: game_of_life_2

 */


/*Libraries to be used*/
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*Boolean conditions to be used to read the 
true/false condition in "Cells check function"*/
#define Y 1
#define N -1


	/*Functions to be used*/
int get_matrix(FILE *input_p);
void fill_matrix(int matrix_size, FILE *input_p, int world_old[matrix_size][matrix_size]);
void rules_check(int matrix_size, int world_old[matrix_size][matrix_size], int world_new[matrix_size][matrix_size]);
int cells_check(int matrix_size, int world_old[matrix_size][matrix_size], int row, int col);
void swap_matrix(int matrix_size, int world_old[matrix_size][matrix_size], int world_new[matrix_size][matrix_size]);
void print_matrix (FILE *output_p, int matrix_size, int world_new[matrix_size][matrix_size], int i);

	/*Main Function: this function is responsible of "interacting" with the user.
	The command line call is being used here and most of the functions are called here*/
int main (int argc, char *argv[]){
	int i, j;
	FILE *input_p, *output_p;								//Declaring the FILE pointers//
	
	//argv[0] = ./game_of_life_1, argv[1] = input_test.csv, argv[2] = number of iterations

	input_p = fopen(argv[1], "r");
	output_p = fopen("output.csv", "w");
	int end_of_counter = atoi(argv[2]);
	
	int matrix_size = get_matrix(input_p);					//Getting the size of the matrix//
	int world_old[matrix_size][matrix_size];				//Old genration array//
	int world_new[matrix_size][matrix_size];				//New generation array//
	
	fill_matrix(matrix_size, input_p, world_old);			//"Mirroring" the array onto Old matrix using the input file//
	
	
	for(int i = 1; i <= end_of_counter; i++){				//Number of iterations//
		rules_check(matrix_size, world_old, world_new);		//Calling the function to check each cell from old matrix
		swap_matrix(matrix_size, world_old, world_new);
		sleep(0.5);											//This command prints the matrix with a pause of 'n' seconds//

		print_matrix(output_p, matrix_size, world_new, i);	//Calling the printing function//
	}

	/*The the loop below prints the output file, while formatting it simultaneously*/
	for(i = 0; i < matrix_size; i++){
		for(j = 0; j < matrix_size; j++){
			if(world_new[i][j] == 1){
				if(j == matrix_size-1){
					fprintf(output_p, "%d", 1);
					fprintf(output_p, "%c", '\n');
				}
				else {
					fprintf(output_p, "%d", 1);
					fprintf(output_p, "%c", ';');
				}
			}
			else if(world_new[i][j] == 0){
				if (j == matrix_size-1){
					fprintf(output_p, "%d", 0);
					fprintf(output_p, "%c", '\n');
					
				}
				else {
					fprintf(output_p, "%d", 0);
					fprintf(output_p, "%c", ';');
				}
			}
		}
	}

	fclose(input_p);										//Closing the input file//
	fclose(output_p);										//Closing the generated output file//
	return 0;
}

	/*The function below reads the length of the rows in the file 
	to return the size of the array -since its a square matrix*/
int get_matrix(FILE *input_p) {
	char token;
	int j = 0;
	while ((token = fgetc(input_p)) != EOF){
		if (token == '\n'){
			j++;
		}
	}
	rewind(input_p);										//Closing and reopening the input file to reset everything//
	return j;												//Returning the size of the matrix into "matrix_size" in the main function//
}


	/*The finction below "mirrors" the input file into the first array (old generation) to have an "all-interger" array -nifty! :D */
void fill_matrix(int matrix_size, FILE *input_p, int world_old[matrix_size][matrix_size]) {
	char token;
	int row = 0;
	int col = 0;
	while ((token = fgetc(input_p)) != EOF){
		if (token == '1'){
			world_old[row][col] = 1;
			col++;
		}
		else if (token == '0') {
			world_old[row][col] = 0;
			col++;
		}
		if (row == matrix_size){
			row++;
		}
	}
}


	/*The function below applies the rules of the game to old generation matrix, 
	and makes changes accordingly BEFORE^ generating a new generation matrix -"world_new".
	Finally it calls the swap_matrix function which makes the new generation matrix the new "old generation matrix",
	thus making room for a new "new generation matrix" -another nifty function! :D
	^It calls the "cells_check" function that read the number of "alive cells" around a cell. */
void rules_check(int matrix_size, int world_old[matrix_size][matrix_size], int world_new[matrix_size][matrix_size]){
	int row;
	int col;
	int check;
	
	for(row = 0; row < matrix_size; row++){
		for(col = 0; col < matrix_size; col++){
			check = cells_check(matrix_size, world_old, row, col);	//Calling the cells_check function//
			if(world_old[row][col] == 1){
				if(check < 2 || check > 3){
					world_new[row][col] = 0;
				}
				else{
					world_new[row][col] = 1;
				}
			}
			if(world_old[row][col] == 0){
				if(check == 3){
					world_new[row][col] = 1;
				}
				else{
					world_new[row][col] = 0;
				}
			}
		}
	}
	swap_matrix(matrix_size, world_old, world_new);			//Calling the swap function to re-run the function with a new old generation matrix//
}


	/*As explained above, the fllowing function checks the number of alive cells. 
	It further makes sure that none of the rules of the matrix are violated 
	-like reading beyond the size of the matrix itself. In the end it returns
	the count of alive cells, which is then used by rules_check to generated a new matrix*/
int cells_check(int matrix_size, int world_old[matrix_size][matrix_size], int row, int col){
	int check = 0, l_up = Y, up = Y, r_up = Y, l_down = Y, down = Y, r_down = Y, left = Y, right = Y; //Setting every cell around the test cell to be "true" (Y)//
	/*testing the corners to prevent violation*/
	if(row == 0){
		l_up = N;
		up = N;
		r_up = N;
	}
	if (col == 0){
		l_up = N;
		left = N;
		l_down = N;
	}
	if(row == (matrix_size-1)){
		l_down = N;
		down = N;
		r_down = N;
	}
	if(col == (matrix_size-1)){
		r_up = N;
		right = N;
		r_down = N;
	}
	/*testing the rest of the array to count the number of alive cells*/
	if (l_up == Y && world_old[row-1][col-1] == 1){
		check++;
	}
	if (up == Y && world_old[row-1][col] == 1){
		check++;
	}
	if (r_up == Y && world_old[row-1][col+1] == 1){
		check++;
	}
	if (l_down == Y && world_old[row+1][col-1] == 1){
		check++;
	}
	if (down == Y && world_old[row+1][col] == 1){
		check++;
	}
	if (r_down == Y && world_old[row+1][col+1] == 1){
		check++;
	}
	if (left == Y && world_old[row][col-1] == 1){
		check++;
	}
	if (right == Y && world_old[row][col+1] == 1){
		check++;
	}

	return check;											//returning the number of alive cells//
}


	/*The following function is called by rules_check function in line 126. It swaps the old generation matrix (world_old)
	with the new generation matrix (world_new), thus making the old "new generation matrix" the new "old generation" matrix.
	This helps reuse the two matrices n-number of times -depending on the number of iterations.*/
void swap_matrix(int matrix_size, int world_old[matrix_size][matrix_size], int world_new[matrix_size][matrix_size]){
	int i, j, temp = 0;
	for (i = 0; i < matrix_size; i++){
		for (j = 0; j < matrix_size; j++){
			world_old[i][j] = world_new[i][j];
		}
	}
}
	/*This final function is responsible for printing the final output. It is called by the main function
	on line 52.*/
void print_matrix(FILE *output_p, int matrix_size, int world_new[matrix_size][matrix_size], int iter) {
	int i, j, s = ' ', final_iter;

	system("clear");			//this command refreshes the print screen//

	i = 0;
	j = 0;

	printf("Iteration %d\n", iter);
	printf("\n");

	/*The loop below prints the game matrix on to the screen, while formatting it simultaneously*/
	for (i = 0; i < matrix_size; i++){
		for (j = 0; j < matrix_size; j++){
			if (world_new[i][j] == 0){
				if(j == matrix_size-1){
					printf("| |");
				}
				else{
					printf("| ");
				}
			}
			else if (world_new[i][j] == 1){
				if(j == matrix_size-1){
					printf("|o|");
				}
				else{
					printf("|o");
				}
			}
		}
		printf("\n");
	}
}


				/*END OF THE PROGRAM*/