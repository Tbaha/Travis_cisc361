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

mp3_t* push(mp3_t** head_ref,mp3_t** tail_ref, mp3_t* data){ //connects the next mp3 struct and updates the new tail refrence
        if (*head_ref == NULL)
                *head_ref = *tail_ref = data;
        else{
        }
        if((*tail_ref) != NULL)
                (*tail_ref) -> next = data;
		data -> prev = *tail_ref;
        *tail_ref = data;
	return data;
}

void pop(mp3_t** head_ref, mp3_t** tail_ref, char* name){ // Removes all the entries with that artist
	mp3_t* temp = *head_ref;
	mp3_t* temp2 = *tail_ref;

	if (strcmp(temp -> artist, name))
		(*head_ref) -> next  -> prev = (*head_ref) -> prev;
		*head_ref = (*head_ref) -> next;

	if (strcmp(temp2 -> artist, name))
		(*tail_ref) -> prev -> next = (*tail_ref) -> next;
		*tail_ref = (*tail_ref) -> prev;

	pop(head_ref, tail_ref, name);

	free(temp);
	free(temp2);
}

void printHelper(mp3_t** ref){
	printf("Contents of mp3 are %s, %s, %d, %d\n" , (*ref) -> artist, (*ref) -> song, (*ref) -> year, (*ref) -> runTime);
}

void printListBegin(mp3_t** head_ref){
	mp3_t** temp = head_ref;
	
	while ((*temp) -> next != NULL)
		printHelper(temp);
		*temp = (*head_ref) -> next;
	
	printHelper(temp);//to print the last mp3
}

void printListEnd(mp3_t** tail_ref){
	mp3_t** temp = tail_ref;
	
	while ((*temp) -> prev != NULL)
		printHelper(temp);
		*temp = (*tail_ref) -> prev;

	printHelper(temp);//to print the first mp3
}

mp3_t*  make_mp3(){
	char* artist;
        char* song;
        int year;
        int runTime;
	mp3_t** head_ref = NULL;
	mp3_t** tail_ref = NULL;

	printf("Make mp3: \n");
	fgets(artist,20,stdin);
	fgets(song,20,stdin);
	year = scanf("%d", &year);
	runTime = scanf("%d", &runTime);
	
	return push(head_ref, tail_ref, getNewMp3(artist,song,year,runTime));
}

void exit(int status);

