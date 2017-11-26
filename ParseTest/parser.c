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

            char fileNames[2000];
            char contents[4096];
             char entity_body[4096];
                    //This code is from the class c example 1
            FILE* fhnd;

            fhnd = fopen("text.txt", "r");

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

	
 	char* finder  = strstr(entity_body,"boundary");
	char* p1 = finder;
	char* p2 = finder+9;              
	//printf("\n %s \n",finder);

	for(;;){
	if(*p1 == '\n'){
	printf("\nFound the end of the line\n");
	*p1 = '\0';
	break;
	}
	p1++;
	}
	char bound[100];

	strcpy(bound,p2); 
	//printf("\n%s\n",bound);
	*p1 = '-';



	//============================================================================
	//bound = seperator line
	/**
	char* token = strtok(entity_body,bound);

	while(token!= NULL){
	printf("%s\n",token);

	token = strtok(NULL,bound);
	}	
	*/


	printf("\n----------------------------------------------------------------------\n");

  	char *delim = bound;
	char* pp1 = entity_body;
  	char *pp2;

  	do {

		 pp1 = strstr(pp1,"filename=");
    		 pp2 = strstr(pp1,delim);
    		 if (pp2){ 
      		*pp2 = '\0';}

    		printf("\n ============================================================= \n %s\n",pp1);

    		pp1 = pp2+strlen(delim);

  	}while(pp2!=NULL);


}
