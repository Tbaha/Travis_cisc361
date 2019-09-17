#include "MP3.h"#

int main(){
	char userAnswer[1];
	bool yesno = true;//to determine if user wants to continue to make mp3s

	mp3_t* head_ref = NULL;//keep track of the beginning of the list 
	mp3_t* tail_ref = NULL;//keep track of the end of the list

	whiile(yesno){
		printf("Do you want to make mp3, enter y or n: %s\n");
		fgets(userAnswer,1,stdin);

		if('y'  == userAnswer)
			char name[10];//name of mp3 struct
			printf("Enter mp3 file name: %s\n");

			fgets(name,10,stdin);
			mp3_t* name = make_Mp3();
			
			push(head_ref, tail_ref, name);

		if('n' == userAnswer)
			yesno = false;

			mp3_t* arrMp3 = new mp3_t[count];
			for(int i = 0; i < arrMp3.length; i++

			printf("Thank you %s\n");

		else if(userAnswer != 'y' || userAnswer != 'n')
			printf("Wrong input, please enter input again %s\n);
	}
}
