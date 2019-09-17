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
        new_mp3->runtime=runtime;
        new_mp3->next=NULL;
        new_mp3->prev=NULL;
i}

void push(mp3_t** head_ref,mp3_t** tail_ref, mp3_t* data){ //connects the next mp3 struct and updates the new tail refrence
        if (*head_ref == NULL)
                *head_ref = *tail_ref = data;
        else{
        }
        if((*tail_ref) != NUll)
                (*tail_ref) -> next = data;
		data -> prev = (*tail_ref)
        (*tail_ref) = data;
}

void pop(mp3_t** head_ref, mp3_t** tail_ref, char* name){ // Removes all the entries with that artist
	mp3_t** temp = *head_ref
	mp3_t** temp2 = *tail_ref

	if (strcmp(temp -> artist, name))
		*head_ref -> next  -> prev = *head_ref -> prev;

	if (strcomp(temp2 -> artist, name))
		*tail_ref -> prev -> next = *tail_ref -> next;

	remove(temp -> next, temp2 -> prev, name);

	free(head_ref);
	free(tail_ref);
}

void printListBegin(mp3_t** head_ref){
	mp3_t** temp = *head_ref;
	
	while (temp-> next != NULL)
		cout << temp << endl;
		temp -> next = temp;
	
	cout << temp << endl;//to print the last mp3
}

void printListEnd(mp3_t** tail_ref){
	mp3_t** temp = *tail_ref;
	
	while (temp -> prev != NULL)
		cout << temp << endl;
		temp -> prev = temp;

	cout << temp << endl;//to print the first mp3
}

mp3_t* make_Mp3(){
	char* artist;
        char* song;
        int year;
        int runTime;

	printf("Make mp3: %s\n");
	fgets(artist,20,stdin);
	fgets(song,20,stdin);
	year = scanf("%d%", &year);
	runTime = scanf("%d", &runTime):
	
	getNewMp3(artist,song,year,runTime);
	return getNewMp3;
}

void exit(int status);
