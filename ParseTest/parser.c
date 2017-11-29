#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <string.h>


main( int argc, char *argv[] ) { 
	    //Reading the file and setting it equal to entity_body
            char fileNames[2000];
            char contents[4096];
             char entity_body[200000];
        
            FILE* fhnd;

            fhnd = fopen("post.txt", "r");

            char line[50];

            if (fhnd != NULL) {

            while (fgets(line, sizeof(line), fhnd) != NULL) {

           strcat(entity_body, line);
          }   
         }

         fclose(fhnd);
         //printf("\nContents of the txt file: \n %s \n \n", entity_body);
         //printf("\n=====================================================\n");


        //Beginning of Parse, Now that the file is read correctly
	
	//=============================================================================
	//Parsing the boundary
	//printf("\nHere is the HTTP Message \n%s\n",entity_body);
	
 	char* finder  = strstr(entity_body,"boundary=");
	char* findEnd = finder;
	//printf("\n %s \n",finder);

	for(;;){
	if(*findEnd == '\n'){
	//printf("\nFound the end of the line\n");
	*findEnd = '\0';
	break;
	}
	findEnd++;
	}
	finder = finder+9;

	/**
	size_t delimLen = strlen(finder);
	char * bound = malloc(delimLen *4);
	*/
	char bound[200];
	strcpy(bound,finder);
	printf("\n Bound= \n%s\n",bound);
	
	//Getting the null Terminator
	char nullBound[30000]; 
	strcpy(nullBound,finder);
	//strcpy(nullBound,bound);
	char dashes[10];
	strcpy(dashes,"-------");
	strcat(nullBound,dashes);
	printf("\nnullBound =\n%s\n",nullBound);

	//Fuck it, I think basic strcat test
	
	char test1[100];
	char test2[100];
	strcpy(test1,"the dog walked");
	strcpy(test2,"across the lake somehow");
	strcat(test1,test2); 
	printf("\n test1 = %s \n",test1);
	*findEnd = '\n';
	//Now here goes nothing in getting the nullTerminator

	//============================================================================
	//Beginning of main parser, It uses two pointers (pp1, and pp2) to print and display
	//what we want to see. It uses strstr to find the file, sets the end of the link equal 
	//a null terminator and then moves the first pointer down a little to get rid of things
	//like "filename=, and stuff like that". Its not very complex, but it also requires a lot
	//of pen and paper to visualize.

	//printf("\n----------------------------------------------------------------------\n");

  	char *delim = bound;
	char* pp1 = entity_body;
  	char *pp2;

  	do {
		//Find filename
		 pp1 = strstr(pp1,"filename=");
		//Set pp2 equal to end of line
		pp2 = pp1;
		for(;;){
			if(*pp2 == '\n'){
			pp2 = pp2 -2;
			*pp2 = '\0';
			break;
			}
		pp2++;
		}
		//Get rid of filename= (9 characters)
		pp1 = pp1 + 10;
	
		//Print the line
		printf("\n ====================================================== \n%s\n",pp1);
		//it Works, now to move the pp1 past content Type
		pp1 = pp2+4;
		//Basically this is a glorified, skip a line procedure 
		for(;;){
			if(*pp1 == '\n'){
			pp1++;
			break;
			}
			pp1++;
		}
		//This is where we get the contents of the file
		//We set pp2 = to the next boundary, and set it as a null terminator
    		 pp2 = strstr(pp1,delim);
    		 if (pp2){ 
		pp2 = pp2 -2;
      		*pp2 = '\0';}
		else{
		break;
		}
		//Then its just a simple matter of printing pp1

    		printf("%s\n",pp1);
		//This was the tricky part,you set pp1 after the '\0' by making it equals to pp1
		// + the length of the boundary
    		pp1 = pp2+strlen(delim);

  	}while(pp2!=NULL);
}
