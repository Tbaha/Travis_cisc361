#include "MP3.h"

int main(){
	char* userAnswer[1];
	bool make = true;//to determine if user wants to continue to make mp3s
	bool discard = true;// to determine if user wants to delete an mp3
	bool printFront = true;
	bool printEnd = true;

	mp3_t** head_ref = NULL;//keep track of the beginning of the list 
	mp3_t** tail_ref = NULL;//keep track of the end of the list

	while(make){
		printf("Do you want to make mp3, enter y or n: \n");
		fgets(userAnswer,1,stdin);

		if('y'  == userAnswer)
			push(head_ref, tail_ref);

		if('n' == &userAnswer)
			userAnswer = false;

			printf("Finish making mp3s \n");

		else if(userAnswer != 'y' || userAnswer != 'n')
			printf("Wrong input, please enter input again %s\n);
	}

	while(discard){
		printf("Do you want to delete artist, enter y or n: \n");
                fgets(userAnswer,1,stdin);

                if('y'  == userAnswer)
                        char* name[10];//name of mp3 struct
                        printf("Enter artist name: \n");

                        fgets(name,20,stdin);

                        pop(head_ref, tail_ref, name);

                if('n' == userAnswer)
                        discard = false;

                        printf("Not deleting any artist \n");

                else if(userAnswer != 'y' || userAnswer != 'n')
                        printf("Wrong input, please enter input again \n");
	}

	while(printFront){
		printf("Do you want print list from the beginning: \n");
		fgets(userAnswer,1,stdin);
		
		if('y'  == userAnswer)
			printListBegin(head_ref);
		
		if('n' == userAnswer)
			printFront = false;

		 else if(userAnswer != 'y' || userAnswer != 'n')
                        printf("Wrong input, please enter input again \n");
	}

	 while(printEnd){
                printf("Do you want print list from the End: \n");
                fgets(userAnswer,1,stdin);

                if('y'  == userAnswer)
                        printListEnd(tail_ref);

                if('n' == userAnswer)
                        printEnd = false;

                 else if(userAnswer != 'y' || userAnswer != 'n')
                        printf("Wrong input, please enter input again \n");
        }
}
