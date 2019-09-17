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
}

void push(mp3_t** head_ref,mp3_t** tail_ref, mp3_t* data){
        if (*head_ref == NULL)
                *head_ref = *tail_ref = data;
        else{
        }
        if((*head_ref) != NUll)
                (*head_ref) -> prev = data;
		data -> next = (*head_ref)
        (*head_ref) = data;
}

void remove(mp3_t* data){
	if (data -> next == NULL)
		if (data -> prev == NULL)


		if(data -> prev != NULL)
			data -> prev -> next = data -> next;
			data -> prev == NULL;

	if (data -> next != NULL)
		if (data -> prev == NULL)
			data -> next -> prev == NULL

		if(data -> prev != NULL)
			data -> prev -> next == data -> next 
			data -> next -> prev == data -> prev

	free(data);
}

void printListBegin(mp3_t* head_ref){
	mp3_t* temp = head_ref;
	
	while (temp-> next != NULL)
		cout << temp << endl;
		temp -> next = temp;
	
	cout << temp << endl;//to print the last mp3
}

void printListEnd(mp3_t* tail_ref){
	mp3_t* temp = tail_ref;
	
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
