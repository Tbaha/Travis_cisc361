#include "MP3.h"

int main(){
	char name[100];//name of artist user wants to delete
	char userAnswer[100];
	bool create = true;//to determine if user wants to continue to make mp3s
	bool discard = true;// to determine if user wants to delete an mp3
	bool printFront = true;
	bool printEnd = true;

	mp3_t** head_ref = NULL;//keep track of the beginning of the list 
	mp3_t** tail_ref = NULL;//keep track of the end of the list

	while(create){
		printf("Do you want to make mp3, enter y or n: \n");
		fgets(userAnswer,2,stdin);

		if(userAnswer[0] == 'y')
			make_mp3();

		if(userAnswer[0] == 'n')
			create = false;

			printf("Finish making mp3s \n");

		if(userAnswer[0] != 'y' || userAnswer[0] != 'n')
			printf("Wrong input, please enter input again \n");
	}

	while(discard){
		printf("Do you want to delete artist, enter y or n: \n");
                fgets(userAnswer,2,stdin);

                if(userAnswer[0] == 'y')
                        printf("Enter artist name: \n");

                        fgets(name,20,stdin);

                        pop(head_ref, tail_ref, name);

                if(userAnswer[0] == 'y')
                        discard = false;

                        printf("Not deleting any artist \n");

                if(userAnswer[0] != 'y' || userAnswer[0] != 'n')
                        printf("Wrong input, please enter input again \n");
	}

	while(printFront){
		printf("Do you want print list from the beginning: \n");
		fgets(userAnswer,1,stdin);
		
		if(userAnswer[0] == 'y')
			printListBegin(head_ref);
		
		if(userAnswer[0] == 'n')
			printFront = false;

		if(userAnswer[0] != 'y' || userAnswer[0] != 'n')
                        printf("Wrong input, please enter input again \n");
	}

	 while(printEnd){
                printf("Do you want print list from the End: \n");
                fgets(userAnswer,1,stdin);

                if(userAnswer[0] == 'y')
                        printListEnd(tail_ref);

                if(userAnswer[0] == 'n')
                        printEnd = false;

                if(userAnswer[0] != 'y' || userAnswer[0] != 'n')
                        printf("Wrong input, please enter input again \n");
        }
}
