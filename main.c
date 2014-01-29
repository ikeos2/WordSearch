#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define WORD_LEN 14

void error(int code, int shutdown);

int main(){
 //variables
 int i=0,j=0,counter=0;
 char field[61][61];//word search(game field)
 int dem1, dem2; //x,y(width, height)
 int attempt = 0;
 srand(time(NULL));
 
 //File information
 FILE *input;
 int* FileSize; //how many words are in the file
 char FileName[20]; //string to contain the file name
 char * line = NULL; //buffer for input
 char Words[20][20]; //storage for the given words
 int numWords=0;

 //randomization of word placemnet variables
 int orientation = 0; //0 = horizontal, 1 = verticle
 int direction = 0; //0 = forward, 1 = backward

/***************************************************/
/***************************************************/

 //get file
 printf("Please enter file name: ");
 scanf(" %s", FileName);
 printf("Please enter your puzzle demensions(x,y): ");
 scanf(" %d,%d", &dem1, &dem2);
 //load information from file
 //open file
 input = fopen(FileName, "r");
 if(input == NULL){ error(1,1); }
 
 while(!feof(input)){
       fgets(Words[i],WORD_LEN, input);    
       //printf("%d: %s\n",i,Words[i]); //debug
       i++;      
 }
 numWords = i;
 printf("numWords: %d\n", numWords);
 i = 0; //reset the global counter to 0
 //fill field with blanks
 for(i=0;i<dem1;i++){
        for(j=0;j<dem2;j++){
            field[i][j] = ' ';
        }                    
 }
 
 //strip off return characters
 int lenss; //temp storage, ignore this!
 for(i=0;i<numWords;i++){
 	Words[i][strlen(Words[i])-1] = '\0';
 }
 
 
 //insert words
 int WordLen;//temp storage for how long words are for fittings checks
 //don't confuse WordLen with WORD_LEN - that's the max num chars
 int LocX, LocY, count; //x is used for the random x position, and y for the random y position. count is used to verify the words fit
 
 
 for(i = 0;i<numWords;i++){ //cycle through each word
   restart: //incase we found a position that didn't work, restart the loop with out changing words
   attempt++;
   if(attempt <= 100) i++;
	count = 0; //reset counter
	//Give me some random numbers for my wordsearch!
	LocX = rand()% dem1 + 1;
	Sleep(50); //allow for time to pass since the numbers are based on time
	LocY = rand()% dem2 + 1;
	
   WordLen = strlen(Words[i]); //figure out how long each word is
   printf("%s Len: %d\n", Words[i], WordLen);
 	
   if(orientation == 0){ //horizontal
        if(direction == 0){ //down
    		//check to see if the word fits going this direction
    		if(LocX + WordLen < dem1){ //does the word fit in the array?
                for(j=0;j<WordLen;j++){ if(field[LocX+j][LocY] == ' ' || field[LocX+j][LocY] == Words[i][j]) count++; } //count the number of available spaces
                
                if(count == WordLen){ //does the planned spot for the word work? compare counted spaces to expected
	    			//place the word on the field
	    			for(j=0;j<WordLen;j++){
	    				field[LocX+j][LocY] = Words[i][j];
	    			}
	    			printf("Word placed\n");
	    		}
	    		else{ //if the word wont fit, reset count and move on.
                      count = 0;
                      goto restart; 
                    }
            }
            else{ goto restart; }
        }
        else{ //up
  			//check to see if the word fits going this direction
    		if(LocX - WordLen > 0){ //does the word fit in the array?
                for(j=0;j<WordLen;j++){ if(field[LocX-j][LocY] == ' ' || field[LocX-j][LocY] == Words[i][j]) count++; } //count the number of available spaces
                
                if(count == WordLen){ //does the planned spot for the word work? compare counted spaces to expected
	    			//place the word on the field
	    			for(j=0;j<WordLen;j++){
	    				field[LocX-j][LocY] = Words[i][j];
	    			}
	    			printf("Word placed\n");
	    		}
	    		else{ //if the word wont fit, reset count and move on.
                      count = 0;
                      goto restart; 
                    }
			}
			else{ goto restart; }
		}
	}
   if(orientation == 1){ //horizontal
        if(direction == 0){ //left
    		//check to see if the word fits going this direction
    		if(LocY + WordLen < dem2){ //does the word fit in the array?
                for(j=0;j<WordLen;j++){ if(field[LocX][LocY+j] == ' ' || field[LocX][LocY+j] == Words[i][j]) count++; } //count the number of available spaces
                
                if(count == WordLen){ //does the planned spot for the word work? compare counted spaces to expected
	    			//place the word on the field
	    			for(j=0;j<WordLen;j++){
	    				field[LocX][LocY+j] = Words[i][j];
	    			}
	    			printf("Word placed\n");
	    		}
	    		else{ //if the word wont fit, reset count and move on.
                      count = 0;
                      goto restart; 
                    }
            }
            else { goto restart; }
        }
        else{ //right
  			//check to see if the word fits going this direction
    		if(LocX - WordLen < 0){ //does the word fit in the array?
                for(j=0;j<WordLen;j++){ if(field[LocX][LocY-j] == ' ' || field[LocX][LocY-j] == Words[i][j]) count++; } //count the number of available spaces
                
                if(count == WordLen){ //does the planned spot for the word work? compare counted spaces to expected
	    			//place the word on the field
	    			for(j=0;j<WordLen;j++){
	    				field[LocX][LocY-j] = Words[i][j];
	    			}
	    			printf("Word placed\n");
	    		}
	    		else{ //if the word wont fit, reset count and move on.
                      count = 0;
                      goto restart; 
                    }
			}
			else{ goto restart; }
		}	
   }
   //flip things up
   counter++;
   if(counter%2 == 0) orientation = 1;
   else {orientation = 0; }
   if(counter%4 == 0) direction = 1;
   else {direction = 0;}
   }     
 
 //output key
 printf("\n\nKey:\n");
 for(i=0;i<dem1;i++){
 	for(j=0;j<dem2;j++){
 		printf("%c ",field[i][j]);
 	}
 	printf("\n");
 }
 //output key file
 FILE *file = fopen("key.pzl", "a");
 for(i=0;i<dem1;i++){
      for(j=0;j<dem2;j++){
          fprintf(file, " %c", field[i][j]);
      }
      fprintf(file,"\n");
 }
 fclose(file);
 
 //fill the rest of the field with random letters
 char randomized;
 
 for(i=0;i<dem1;i++){
 	for(j=0;j<dem2;j++){
 		randomized = 'A' + rand() % 26;
 		if(field[i][j] == ' ') field[i][j] = randomized;
 	}
 }
 //output puzzle
 printf("\n\nPuzzle:\n");
 for(i=0;i<dem1;i++){
 	for(j=0;j<dem2;j++){
 		printf("%c ",field[i][j]);
 	}
 	printf("\n");
 }
 //output key file
 file = fopen("puzzle.pzl", "a");
 for(i=0;i<dem1;i++){
      for(j=0;j<dem2;j++){
          fprintf(file, " %c", field[i][j]);
      }
      fprintf(file,"\n");
 }
 fclose(file);
 
 
 printf("End of program\n");
 system("pause");
 //house keeping
 free(line);
 free(input);
 
 return 0;   
}


void error(int code, int shutdown){
     printf("error %d: ",code);
     if(code == 1) printf("File not opened\n");
     else printf("Error unknown");

     system("pause");
     printf("\n");
     if(shutdown) exit(1);
}
