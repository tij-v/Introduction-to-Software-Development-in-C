/* 

* Author: Shitij Vishwakarma, svishwakarma2015@my.fit.edu 

* Course: CSE 1002, Section 01/02, Spring 2018 

* Project: tic_tac_toe

*/


// Libraries to be used
#include <stdio.h>
#include <string.h>


//main function
int main(void){
	int i, count_x = 0, count_o = 0, dash = 0;
	char x, o, boolean = 'f';
	char check[9];

	printf("Enter a test case: \n");

	for(i = 0; i < 9; i++){
		scanf("%c", &check[i]);
		if(check[i] == 'x'){
			count_x++;
		}
		else if(check[i] == 'o'){
			count_o++;
		}
		else if(check[i] == '_'){
			dash++;
		}
	}

	if(dash > 0){
		boolean = 't';
	}
	else{
		boolean = 'f';
	}


	//first "success" combination

	if(check[0] && check[1] && check[2] == 'x'
	|| check[3] && check[4] && check[5] == 'x'
	|| check[6] && check[7] && check[8] == 'x'
	|| check[0] && check[1] && check[2] == 'o'
	|| check[3] && check[4] && check[5] == 'o'
	|| check[6] && check[7] && check[8] == 'o') 
	{

			if(boolean == 't'){
			if(count_x > count_o){
				printf("start x\n");
				if(count_x == count_o+1){
					printf("win x\n");
				}
			}
			else if(count_o > count_x){
				printf("start o\n");
				if(count_o == count_x+1){
					printf("win o\n");
				}
			}
			else if (count_x == count_o){
				if((check[0] && check[1] && check[2] == 'x')
				|| (check[3] && check[4] && check[5] == 'x')
				|| (check[6] && check[7] && check[98] == 'x'))
				{
					printf("win x\n");
				}
				else if((check[0] && check[1] && check[2] == 'o')
					 || (check[3] && check[4] && check[5] == 'o')
					 || (check[6] && check[7] && check[8] == 'o'))
				{
					printf("win o\n");
				}
			}
		}
		else if(boolean == 'f'){
			printf("start o|x\n");
			printf("impossible\n");
		}
	}

	//second success combination

	if((check[0] && check[3] && check[6] == 'x')
		 || (check[1] && check[4] && check[7] == 'x')
		 || (check[2] && check[5] && check[8] == 'x')
		 || (check[0] && check[3] && check[6] == 'o')
		 || (check[1] && check[5] && check[7] == 'o')
		 || (check[2] && check[6] && check[8] == 'o'))
	{
		if(boolean == 't'){
			if(count_x > count_o){
				printf("start x\n");
				if(count_x == count_o+1){
					printf("win x\n");
				}
			}
			else if(count_o > count_x){
				printf("start o\n");
				if(count_o > count_x+1){
					printf("win o\n");
				}
			}
			else if (count_x == count_o){
				if((check[0] && check[3] && check[6] == 'x')
		 		|| (check[1] && check[4] && check[7] == 'x')
			 	|| (check[2] && check[5] && check[8] == 'x'))
		 		{
					printf("win x\n");
				}
				else if((check[0] && check[3] && check[6] == 'o')
		 			 || (check[1] && check[4] && check[7] == 'o')
			 		 || (check[2] && check[5] && check[8] == 'o')/*147 or 258 or 369 = o*/)
		 		{
					printf("win o\n");
				}
			}
		}
		else if(boolean == 'f'){
			printf("start o|x\n");
			printf("impossible\n");
		}  
	}



	//third success combination
	else if((check[0] && check[4] && check[8] == 'x')
		 || (check[2] && check[4] && check[6] == 'x')
		 || (check[0] && check[4] && check[8] == 'o')
		 || (check[2] && check[4] && check[6] == 'o')/*159 or 357 = x or o*/)
	{
		//printf("3\n");
		if(boolean == 't'){
			if(count_x > count_o){
				printf("start x\n");
				if(count_x == count_o+1){
					printf("win x\n");
				}
			}
			else if(count_o > count_x){
				printf("start o\n");
				if(count_o > count_x+1){
					printf("win o\n");
				}
			}
			else if (count_o == count_x){
				if((check[0] && check[4] && check[9] == 'x')
		 		|| (check[2] && check[4] && check[6] == 'x')/*159 or 357 = x*/)
				{
					printf("win x\n");
				}
				else if((check[0] && check[4] && check[8] == 'o')
		 			 || (check[2] && check[4] && check[6] == 'o')/*159 or 357 = o*/)
				{
					printf("win o\n");
				}
			}
		}
		else if(boolean == 'f'){
			printf("start o|x\n");
			printf("impossible\n");
		}
	}
	

	else if (boolean == 't' && count_x == count_o){
		//printf("4\n");
		printf("start o|x\n");
		printf("unfinished\n");
	}



	//randomness checking combination

	if(boolean == 'f' && count_x > count_o || boolean == 'f' && count_x < count_o){
		//printf("5\n");
		if(count_x > count_o) {
			printf("Start x\n");
			if(count_x == count_o+1){
				printf("draw\n");
			}
			else{
				printf("impossible\n");
			}
		}
		else if(count_o > count_x){
			printf("start o\n");
			if(count_o == count_x+1){
				printf("draw\n");
			}
			else{
				printf("impossible\n");
			}
		}
	}
}


//end of the function