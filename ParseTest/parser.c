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

              
        //I used a tokenizer to split the entity_body, then in the while loop
        //I look for certain words and then cat them.           
        char *tok = entity_body;
        while((tok = strtok(tok,"")) != NULL)
        {   
                    
                    
                    
                //printf("\n %s \n ",tok);
                //printf("\n================================================\n");
                char *finder;
                finder = strstr(tok,"filename="); 
                if(finder != NULL){
                //printf("\n found a file name \n");
                strcat(fileNames,finder);
                 }
                tok = NULL;
        }
        printf("\n Contents of fileNames: \n %s \n \n", fileNames);
        //const char file_finder[100] = "\r\n\r\n";
        //size_t length = strlen(entity_body);

        //char * filename = strstr(entity_body,file_finder); 
        //printf("the substring is : %s \n",filename);
}


