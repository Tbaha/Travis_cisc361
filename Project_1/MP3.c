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
mp3_t* head=NULL;
mp3_t* tail=NULL;


void push(mp3_t* data){ //connects the next mp3 struct and updates the new tail refrence
        if(head == NULL){
		head = data;
		tail = data;

	}else{
		tail->next = data;
		data->prev = tail;
        	tail = data;
	}
}

void pop(char* name){ // Removes all the entries with that artist
	mp3_t* tmp1 = head;
	mp3_t* tmp2 = tail;
	if(head == NULL || tail == NULL){
	return;
	}
	while(tmp1->next != NULL){
		if(strcmp(tmp1->artist, name)){
			tmp1 = tmp1 -> next;
			head = tmp1;
		}else{
			tmp1 = tmp1-> next;
		}
	}
	while(tmp2->prev != NULL){
		if(strcmp(tmp2->artist,name)){
			tmp2 = tmp2 -> prev;
			tail = tmp2;
		}else{
			tmp2 =tmp2 -> prev;
		}
	}

	free(tmp1);
	free(tmp2);
}

void printHelper(mp3_t* ref){
	printf("Contents of mp3 are:\n %s, %s, %d, %d\n" , (ref) -> artist, (ref) -> song, (ref) -> year, (ref) -> runTime);
}

void printListBegin(){
	mp3_t* tmp = head;
	while (tmp -> next != NULL){
		printHelper(tmp);
		tmp = tmp -> next;
	}
	printHelper(tmp);
}

void printListEnd(){
	mp3_t* tmp = tail;
	while (tmp -> prev != NULL){
		printHelper(tmp);
		tmp = tmp -> prev;
	}
	printHelper(tmp);

}

void exit(int status);

