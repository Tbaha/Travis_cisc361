#include "MP3.h"

int main(){
	char* name;//name of artist user wants to delete
	char userAnswer[100];//to clear keyboard buffer
	int year;
	int runTime;
	char* artist;
	char* song;
	int number;
	
	printf("1 - Do you want to make a mp3: \n");
	printf("2 - Do you want to delete artist: \n");
	printf("3 - Do you want print list from the beginning: \n");
	printf("4 - Do you want print list from the End: \n");
	printf("5 - Do you want to quit: \n");

	printf("Enter a number from 1-5 \n");
	scanf("%d", &number);
	switch(number){
               case 1: 
                        artist = malloc(100);
                        song = malloc(100);

                        printf("Enter artist name: \n");
			fgets(userAnswer,100,stdin);//to clear keyboard buffer
                        fgets(artist,100,stdin);

                        printf("Enter song name: \n");
                        fgets(song,100,stdin);

                        printf("Enter year release: \n");
                        scanf("%d",&year);

                        printf("Enter length of runtime: \n");
                        scanf("%d",&runTime);

			fgets(userAnswer,100,stdin);//to clear keyboard buffer

                        push(getNewMp3(artist,song,year,runTime));

			main();
			break;

		case 2:
                        printf("Enter artist name: \n");
			fgets(userAnswer,100,stdin);//to clear keyboard buffer
                        fgets(name,100,stdin);

                        pop(name);

			main();
			break;

		case 3:
			printListBegin();

			main();
			break;

		case 4:
			printListEnd();

			main();
 			break;

		case 5:
			exit(0);

		default:
			printf("Wrong choice \n");

			main();
			break;
	}
	return 0;
}
