#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFERSIZE 128

typedef struct mp3{
	char *artist;
	char *song;
	int year;
	int runTime;
	struct mp3 *next;
	struct mp3 *prev;
}mp3_t;

mp3_t* getNewMp3(char* artist,char* song,int year, int runTime);

void push(struct mp3** head_ref,mp3_t** tail_ref, mp3_t* data);

void remove(mp3_t** head_ref, mp3_t** tail_ref, mp3_t* data);

void printListBegin();

void printListEnd();

mp3_t* make_mp3();

void exit(int status);

