#include "MP3.h"

mp3_t* getNewMp3(char* artist,char* song,int year, int runTime){//Make mp3 struct
        mp3_t* new_mp3=(mp3_t*)malloc(sizeof(mp3_t));
        int len = strlen(artist);
        new_mp3->artist=(char*) malloc(len+1);
        strcpy(new_mp3->artist,artist);
        len = strlen(song);
        new_mp3->song=(char*) malloc(len+1);
        strcpy(new_mp3->song,song);
        new_mp3->year=year;
        new_mp3->runTime=runTime;
        new_mp3->next=NULL;
        new_mp3->prev=NULL;
}

mp3_t* head = NULL;
mp3_t* tail = NULL;

void push(mp3_t* data){ //connects the next mp3 struct and updates the new tail refrence
        if(head == NULL){
		head = tail = data;

	}else{
		tail -> next = data;
		data-> prev = tail;
        	tail = data;
	}
}


void pop(char* name){ // Removes all the entries with that artist
	int len = strlen(name);
        name =(char*) malloc(len+1);
        strcpy(name,name);

	mp3_t* tempH = head;
	mp3_t* tempT = tail;

	while(head == NULL){//check if empty list
		if(strcmp(head->artist, name)){//remove  head if equals artist
			head = head -> next;
			head->prev = NULL;
			free(tempH);
			printf("%s",head->artist);
		}

		if(strcmp(tail->artist,name)){//remove  tail if equals artist
			tail = tail -> prev;
			tail->next = NULL;
			free(tempT);
			printf("%s",head->artist);
		}

		if(head == NULL){//check if list is empty after first two loops are true
		return;
		}

		tempH=head->next;
		while(tempH != NULL){//check if middle elements equal artist
			mp3_t* store_next = NULL;
			mp3_t* store_prev = NULL;
			if(strcmp(tempH->artist,name)){
				store_next = tempH->next;
				store_prev = tempH->prev;

				tempH=NULL;
				free(tempH);

				store_next -> prev = store_prev;
				store_prev -> next = store_next;
				tempH = store_next;
			}else{
			tempH=tempH->next;
			}
		}
	}
}

void printHelper(mp3_t* ref){//print statment for printlist functions
	printf("Contents of mp3 are:\n  %s, %s, %d, %d \n" , ref -> artist, ref -> song, ref -> year, ref -> runTime);
}

void printListBegin(){//Prints list from Head to tail
	mp3_t* tmp = head;
	while (tmp != NULL){
		printHelper(tmp);
		tmp = tmp -> next;
	}
}

void printListEnd(){//Prints list from tail to head
	mp3_t* tmp = tail;
	while (tmp != NULL){
		printHelper(tmp);
		tmp = tmp -> prev;
	}
}

void exit(int status);

