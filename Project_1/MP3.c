#include "MP3.h"
#include <stdio.h>
#include <stdlib.h>

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
//	int len = strlen(name);
       // char* lname =(char*) malloc(len+1);
        //strcpy(lname,name);

	mp3_t* tempH = head;
	mp3_t* tempT = tail;
        if (head==NULL)
		return;
	while(head != NULL&&!strcmp(head->artist,name)){//check if empty list
			head = head -> next;
			head->prev = NULL;
			free(tempH);
			printf("%s",head->artist);
		}
		if(head==NULL){
			tail=NULL;
			return;
		}
	while (tail!=NULL&& !strcmp(tail->artist,name)){
			tail = tail -> prev;
			tail->next = NULL;
			free(tempT);
			printf("%s",head->artist);
		}

	if(tail == NULL){//check if list is empty after first two loops are true
	   head=NULL;
	   return;
	}
	if (tail==head ||head->next==tail){
		return;
	}
	tempH=head->next;
	while(tempH != tail){//check if middle elements equal artist
		if(strcmp(tempH->artist,name)){
			tempH->next->prev=tempH->prev;
			tempH->prev->next=tempH->next;
			mp3_t* temp=tempH->next;
			free(tempH);
			tempH=temp;

		}else{
			tempH=tempH->next;
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

