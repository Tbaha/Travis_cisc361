#include "MP3.h"

mp3_t* getNewMp3(char* artist,char* song,int year, int runTime){
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
		head = data;
		tail = data;

	}else{
		data -> prev = tail;
		tail-> next = data;
        	tail = data;
	}
	printf("%s, %s",head->artist, tail->artist);
}


void pop(char* name){ // Removes all the entries with that artist
	mp3_t* tempH = head;
	mp3_t* tempT = tail;

	if(head == NULL || tail == NULL){//check if empty list
		return;
	}
	while(tempH != NULL){
		if(strcmp(tempH->artist, name)){//remove initial head if equals artist
			tempH = tempH -> next;
			free(head);
			head = tempH;
		}else{
			tempH = NULL;
		}
	}
	while(tempT != NULL){
		if(strcmp(tempT->artist,name)){//remove initial tail if equals artist
			tempT = tempT -> prev;
			free(tail);
			tail = tempT;
		}else{
			tempT = NULL;
		}
	}
	if(head == NULL || tail == NULL){//check if list is empty after first two loops are true
		return;
	}
	tempH = head->next;
	while(tempH->next != tail){//check if middle elements equal artist
		if(strcmp(tempH->artist,name)){
			tempH -> prev -> next = tempH -> next;
			tempH -> next -> prev = tempH -> prev;
			tempH = tempH->next;
		}else{
			tempH = tempH->next;
		}
	}
	free(tempH);
	free(tempT);
}

void printHelper(mp3_t* ref){
	printf("Contents of mp3 are:\n  %s, %s, %d, %d \n" , ref -> artist, ref -> song, ref -> year, ref -> runTime);
}

void printListBegin(){
	mp3_t* tmp = head;
	while (tmp != NULL){
		printHelper(tmp);
		tmp = tmp -> next;
	}
}

void printListEnd(){
	mp3_t* tmp = tail;
	while (tmp != NULL){
		printHelper(tmp);
		tmp = tmp -> prev;
	}
}

void exit(int status);

