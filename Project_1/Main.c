#include "MP3.h"

int main(){
	char* name;//name of artist user wants to delete
	char userAnswer[100];
	bool create = true;//to determine if user wants to continue to make mp3s
	bool discard = true;// to determine if user wants to delete an mp3
	bool printFront = true;
	bool printEnd = true;
	int year;
	int runTime;
	char* artist;
	char* song;

	mp3_t** head_ref = NULL; //keep track of the front of the list 
	mp3_t** tail_ref = NULL; //keep track of the end of the list

	 while(create){
                printf("Do you want to make a mp3, enter y or n: \n");

                fgets(userAnswer,100,stdin);
                if(userAnswer[0] == 'y'){
                        artist = malloc(100);
                        song = malloc(100);

                        printf("Enter artist name: \n");
                        fgets(artist,100,stdin);

                        printf("Enter song name: \n");
                        fgets(song,100,stdin);

                        printf("Enter year release: \n");
                        scanf("%d",&year);

                        printf("Enter length of runtime: \n");
                        scanf("%d",&runTime);

                        push(getNewMp3(artist,song,year,runTime));

                        }else if(userAnswer[0] == 'n'){
                                create = false;
                                printf("Finish making mp3s \n");
		}
        }
	
	fflush(stdout);

	while(discard){
		printf("Do you want to delete artist, enter y or n: \n");
                fgets(userAnswer,100,stdin);

                if(userAnswer[0] == 'y'){
			name = malloc(100);
                        printf("Enter artist name: \n");

                        fgets(name,100,stdin);

                        pop(name);

		}else if(userAnswer[0] == 'n'){
                        discard = false;
                        printf("Not deleting any artist \n");
		}
	}
	
	fflush(stdout);

	while(printFront){
		printf("Do you want print list from the beginning: \n");
		fgets(userAnswer,100,stdin);
		
		if(userAnswer[0] == 'y'){
			printListBegin();
		}else if(userAnswer[0] == 'n'){
			printFront = false;
		}
	}

	fflush(stdout);

	while(printEnd){
                printf("Do you want print list from the End: \n");
                fgets(userAnswer,100,stdin);

                if(userAnswer[0] == 'y'){
                        printListEnd();
		}else if(userAnswer[0] == 'n'){
                        printEnd = false;
		}
	}

	return 0;
}
