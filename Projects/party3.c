#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef char CHARACTER[20];

typedef struct int_node{
	CHARACTER name;
	struct int_node *next;
}int_node;

typedef struct{
	int_node *head;
	int_node *tail;
	int size;
}int_q;

void bouncer(int_q *qPtr, CHARACTER newChar);
void police(int_q *qPtr);
void print(int_q *qPtr);

int main(void){
	//Step 1: open the file
	FILE *file_ptr;
	file_ptr = fopen("party.csv", "r");

	//Step 2: Declare myQueue 
	int_q myQueue;

	//Step 3: Initialize the pointers to NULL
	myQueue.head = NULL;
	myQueue.tail = NULL;
	myQueue.size = 0;

	//Step 4: Code the driving program
	int i = 0;
	char *token;
	double timer = 0, globalClock = 0, lapseWatch = 0; 
	char guestList[50];
	int counter = 0;
	for(i = 0; i < 50; i++){
		fgets(guestList, 50, file_ptr);
		token = strtok(guestList, ",");
		bouncer(&myQueue, token);
	}
	//int k = 0;

	while(myQueue.tail != NULL){
		//printf("k: %d\n", k);
		if(fmod(timer, 1.5) == 0 && fgets(guestList, 50, file_ptr) != 0){
			token = strtok(guestList, ",");
			if(strcmp(token, "Mark") == 0){
				printf("Mark Zuckerberg arrived at: %.lf\n", globalClock);
			}
			bouncer(&myQueue, token);
		}
		if(lapseWatch == 15){
			for(counter = 0; counter < 5; counter++){
				police(&myQueue);
			}
			if(myQueue.tail == NULL){
				printf("End time: %.2f\n", globalClock);
				return 0;
			}
		}
		else if(lapseWatch == 30){
			for(counter = 0; counter < 6; counter++){
				police(&myQueue);
			}
			if(myQueue.tail == NULL){
				printf("End time: %.2f\n", globalClock);
				return 0;
			}
		}
		else if(lapseWatch == 60){
			for(counter = 0; counter < 4; counter++){
				police(&myQueue);
			}
			if(myQueue.tail == NULL){
				printf("End time: %.2f\n", globalClock);
				return 0;
			}
		}
		else if(lapseWatch == 120){
			for (counter = 0; counter < 20; counter++){
				police(&myQueue);
			}
			if(myQueue.tail == NULL){
				printf("End time: %.2f\n", globalClock);
				break;
			}
			lapseWatch = 0;
		}
		timer = 0.5+timer;
		lapseWatch = 0.5+lapseWatch;
		globalClock = 0.5+globalClock;
	}

	//print(&myQueue);


	fclose(file_ptr);
}

void bouncer(int_q *qPtr, CHARACTER newChar){
	int_node *newNode = (int_node*)malloc(sizeof(int_node));
	strcpy(newNode->name, newChar);
	newNode->next = NULL;

	if(qPtr->size == 0){
		qPtr->tail = newNode;
		qPtr->head = newNode;
	}
	else{
		qPtr->tail->next = newNode;
		qPtr->tail = newNode;
	}
	(qPtr->size)++;
	return;
}

void police(int_q *qPtr){
	int_node *tempPtr;
	char tempChar[20];

	tempPtr = qPtr->head;
	strcpy(tempChar, tempPtr->name);
	qPtr->head = tempPtr->next;
	(qPtr->size)--;

	if(qPtr->size == 0){
		qPtr->tail = NULL;
	} 
	free(tempPtr);
	return;
}

void print(int_q *qPtr){
	int_node *tempNode;
	tempNode = qPtr->head;
	int i = 0;
	while(tempNode != NULL){
		i++;
		printf("%d. %s\n", i, tempNode);
		tempNode = tempNode->next;
	}
}

/*END OF PROGRAM*/